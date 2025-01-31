/* Original data packet:
 - 14-byte header
 - 64-byte payload
 =================
 78 bytes

 Tagged data packet:
 - 14-byte header
 - 4-byte FEC header
 - 64-byte payload

 Tagged parity packet:
 - 14-byte header
 - 4-byte FEC header
 - 2-byte payload length
 - 78-byte payload
 - 14-byte header
 - 64-byte payload
 */

#include "Decoder.h"
#include "Decoder_core.h"

static const unsigned TRAFFIC_CLASS_COUNT = 1 << FEC_TRAFFIC_CLASS_WIDTH;
static const unsigned PING_PONG_BUFFER_SIZE = DIVIDE_AND_ROUND_UP(
    FEC_MAX_PACKET_SIZE + FEC_PACKET_LENGTH_WIDTH / 8, BYTES_PER_WORD);

enum command
{
  COMMAND_IDLE, COMMAND_OUTPUT_DATA, COMMAND_DECODE, COMMAND_BYPASS
};

typedef ap_uint<FEC_PACKET_LENGTH_WIDTH> packet_length;

struct packet_info
{
    bool Data_packet;
    packet_index Packet_index;
    packet_length Bytes_per_packet;
    packet_type Original_type;
};

struct parameters
{
    input_tuples Input_tuples;
    command Command;
    unsigned Packet_count;
};

static block_index Current_blocks[TRAFFIC_CLASS_COUNT];
static packet_index Packet_counts[TRAFFIC_CLASS_COUNT];
static k_type Data_packet_counts[TRAFFIC_CLASS_COUNT];

static command Select_command(bool Wait_for_data, bool Data_packet,
bool New_block, unsigned Traffic_class, unsigned k, bool Bypass)
{
  command Command;

  if (Bypass)
    Command = COMMAND_BYPASS;
  else if (Wait_for_data)
  {
    if (!New_block)
    {
      if (Data_packet_counts[Traffic_class] == k && Data_packet)
        Command = COMMAND_OUTPUT_DATA;
      else
        Command = COMMAND_IDLE;
    }
    else
    {
      if (Packet_counts[Traffic_class] < k)
        Command = COMMAND_OUTPUT_DATA;
      else if (Data_packet_counts[Traffic_class] < k)
        Command = COMMAND_DECODE;
      else
        Command = COMMAND_IDLE;
    }
  }
  else
  {
    if (!New_block)
    {
      if (Packet_counts[Traffic_class] != k)
        Command = COMMAND_IDLE;
      else if (Data_packet_counts[Traffic_class] == k)
        Command = COMMAND_OUTPUT_DATA;
      else
        Command = COMMAND_DECODE;
    }
    else
    {
      if (Packet_counts[Traffic_class] < k)
        Command = COMMAND_OUTPUT_DATA;
      else
        Command = COMMAND_IDLE;
    }
  }

  return Command;
}

static bool Decide_to_drop(bool Wait_for_data, unsigned Traffic_class,
bool New_block, unsigned k)
{
  if (New_block)
    return false;
  else if (Wait_for_data)
    return Data_packet_counts[Traffic_class] >= k;
  else
    return Packet_counts[Traffic_class] >= k;
}

static void Collect_packets(hls::stream<input_tuples> & Tuple_input,
    hls::stream<packet_interface> & Packet_input, hls::stream<parameters> & Parameter_FIFO,
    hls::stream<data_word> Data_FIFOs[TRAFFIC_CLASS_COUNT],
    hls::stream<packet_info> Info_FIFOs[TRAFFIC_CLASS_COUNT],
    hls::stream<packet_interface> & Bypass_FIFO, bool Wait_for_data)
{
  input_tuples Input_tuples = Tuple_input.read();
  tuple_Decoder_input Decoder_input = Input_tuples.Decoder_input;
  bool Bypass = !Decoder_input.Stateful_valid;
  unsigned K = Decoder_input.K;
  unsigned H = Decoder_input.H;

  unsigned Packet_length = Input_tuples.Hdr.Fec.range(FEC_PACKET_LENGTH_END, FEC_PACKET_LENGTH_START);
  unsigned Original_type = Input_tuples.Hdr.Fec.range(FEC_ORIGINAL_TYPE_END, FEC_ORIGINAL_TYPE_START);
  unsigned Packet_index = Input_tuples.Hdr.Fec.range(FEC_PACKET_INDEX_END, FEC_PACKET_INDEX_START);
  unsigned Block_index = Input_tuples.Hdr.Fec.range(FEC_BLOCK_INDEX_END, FEC_BLOCK_INDEX_START);
  unsigned Traffic_class = Input_tuples.Hdr.Fec.range(FEC_TRAFFIC_CLASS_END, FEC_TRAFFIC_CLASS_START);

  parameters Parameters;
  Parameters.Input_tuples = Input_tuples;

  bool New_block = Block_index != Current_blocks[Traffic_class];
  bool Data_packet = Packet_index < K;
  bool Drop = Decide_to_drop(Wait_for_data, Traffic_class, New_block, K);

  bool End = false;
  packet_interface Input;
  unsigned Offset = 0;
  do
  {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline

    Input = Packet_input.read();

    End = Input.End_of_frame;

    if (Bypass)
      Bypass_FIFO.write(Input);
    else if (!Drop && Offset < Packet_length)
      Data_FIFOs[Traffic_class].write(Input.Data);

    Offset += BYTES_PER_WORD;
  }
  while (!End);

  if (!Bypass)
  {
    if (!Drop)
    {
      packet_info Info;
      Info.Data_packet = Data_packet;
      Info.Packet_index = Packet_index;
      Info.Bytes_per_packet = Packet_length;
      Info.Original_type = Original_type;
      Info_FIFOs[Traffic_class].write(Info);
    }

    if (!New_block)
    {
      if (Data_packet)
        Data_packet_counts[Traffic_class]++;
      Packet_counts[Traffic_class]++;
    }

    Parameters.Packet_count = Packet_counts[Traffic_class];
  }

  Parameters.Command = Select_command(Wait_for_data, Data_packet, New_block, Traffic_class, K,
      Bypass);

  if (!Bypass && New_block)
  {
    Packet_counts[Traffic_class] = 1;
    Data_packet_counts[Traffic_class] = 0;
    if (Data_packet)
      Data_packet_counts[Traffic_class]++;
    Current_blocks[Traffic_class] = Block_index;
  }

  Parameter_FIFO.write(Parameters);
}

static void Select_packets(hls::stream<parameters> & Input_parameter_FIFO,
    hls::stream<data_word> Input_FIFOs[TRAFFIC_CLASS_COUNT],
    hls::stream<packet_info> Input_info_FIFOs[TRAFFIC_CLASS_COUNT],
    hls::stream<parameters> & Output_parameter_FIFO, hls::stream<data_word> & Output_raw_data_FIFO,
    hls::stream<data_word> & Output_encoded_data_FIFO,
    hls::stream<packet_info> & Output_raw_info_FIFO,
    hls::stream<packet_info> & Output_encoded_info_FIFO, unsigned & Packet_count)
{
  parameters Parameters = Input_parameter_FIFO.read();
  Output_parameter_FIFO.write(Parameters);
  command Command = Parameters.Command;
  Packet_count = Parameters.Packet_count;

  unsigned Start = FEC_PACKET_LENGTH_WIDTH + FEC_ETHER_TYPE_WIDTH + FEC_PACKET_INDEX_WIDTH + FEC_BLOCK_INDEX_WIDTH;
  unsigned Traffic_class = Parameters.Input_tuples.Hdr.Fec.range(FEC_TRAFFIC_CLASS_END, FEC_TRAFFIC_CLASS_START);
  unsigned K = Parameters.Input_tuples.Decoder_input.K;

  if (Command == COMMAND_DECODE || Command == COMMAND_OUTPUT_DATA)
  {
    unsigned Count = Command == COMMAND_DECODE ? K : Packet_count;
    Packet_count = 0;
    for (unsigned Packet = 0; Packet < Count; Packet++)
    {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
      packet_info Info = Input_info_FIFOs[Traffic_class].read();
      if (Command == COMMAND_DECODE)
        Output_encoded_info_FIFO.write(Info);
      else if (Info.Data_packet)
        Output_raw_info_FIFO.write(Info);

      unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(Info.Bytes_per_packet, BYTES_PER_WORD);
      for (unsigned Offset = 0; Offset < Words_per_packet; Offset++)
      {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
        data_word Input = Input_FIFOs[Traffic_class].read();
        if (Command == COMMAND_DECODE)
          Output_encoded_data_FIFO.write(Input);
        else if (Info.Data_packet)
          Output_raw_data_FIFO.write(Input);
      }

      Packet_count += Command == COMMAND_DECODE || Info.Data_packet ? 1 : 0;
    }
  }
}

static void Preprocess_headers(hls::stream<parameters> & Input_parameter_FIFO,
    hls::stream<data_word> & Input_FIFO, hls::stream<packet_info> & Input_info_FIFO,
    hls::stream<parameters> & Output_parameter_FIFO, hls::stream<data_word> & Output_FIFO,
    hls::stream<packet_info> & Output_info_FIFO)
{
  parameters Parameters = Input_parameter_FIFO.read();
  Output_parameter_FIFO.write(Parameters);
  command Command = Parameters.Command;
  unsigned K = Parameters.Input_tuples.Decoder_input.K;

  if (Command == COMMAND_DECODE)
  {
    for (unsigned Packet = 0; Packet < K; Packet++)
    {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
      packet_info Info = Input_info_FIFO.read();
      unsigned Bytes_per_packet = Info.Bytes_per_packet;
      unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(Bytes_per_packet, BYTES_PER_WORD);

      ap_uint<2 * FEC_AXI_BUS_WIDTH> Data = Bytes_per_packet - FEC_HEADER_SIZE / 8;

      unsigned Count = Info.Data_packet ? FEC_PACKET_LENGTH_WIDTH / 8 : 0;
      unsigned Offset = 0;
      unsigned Packet_type = Info.Original_type;
      for (unsigned Word_offset = 0; Word_offset < Words_per_packet; Word_offset++)
      {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
        data_word Input = Input_FIFO.read();

        for (unsigned Byte_offset = 0; Byte_offset < BYTES_PER_WORD; Byte_offset++)
        {
          bool Output = (Info.Data_packet && Offset < ETH_HEADER_SIZE / 8)
              || (Offset >= (ETH_HEADER_SIZE + FEC_HEADER_SIZE) / 8 && Offset < Bytes_per_packet);
          unsigned Byte = (Input >> (8 * (BYTES_PER_WORD - Byte_offset - 1))) & 0xFF;
          if (Offset >= 12 && Offset < ETH_HEADER_SIZE / 8)
          {
            Byte = (Packet_type >> (FEC_ETHER_TYPE_WIDTH - 8)) & 0xFF;
            Packet_type <<= 8;
          }
          if (Output)
            Data = (Data << 8) | Byte;
          Count += Output ? 1 : 0;
          Offset++;
        }

        if (Count >= BYTES_PER_WORD)
        {
          Output_FIFO.write(Data >> (8 * (Count - BYTES_PER_WORD)));
          Count -= BYTES_PER_WORD;
        }
      }
      if (Count > 0)
        Output_FIFO.write(Data << (8 * (BYTES_PER_WORD - Count)));

      Info.Bytes_per_packet -= FEC_HEADER_SIZE / 8;
      if (!Info.Data_packet)
        Info.Bytes_per_packet -= ETH_HEADER_SIZE / 8;
      else
        Info.Bytes_per_packet += FEC_PACKET_LENGTH_WIDTH / 8;
      Output_info_FIFO.write(Info);
    }
  }
}

static void Reorder_packets(hls::stream<parameters> & Input_parameter_FIFO,
    hls::stream<data_word> & Input_FIFO, hls::stream<packet_info> & Input_info_FIFO,
    hls::stream<parameters> & Output_parameter_FIFO,
    data_word Output_buffer[FEC_MAX_K][PING_PONG_BUFFER_SIZE],
    hls::stream<packet_info> & Output_info_FIFO, packet_index Packet_indices[FEC_MAX_K],
	packet_length Packet_lengths[FEC_MAX_K])
{
  parameters Parameters = Input_parameter_FIFO.read();
  Output_parameter_FIFO.write(Parameters);
  command Command = Parameters.Command;
  unsigned K = Parameters.Input_tuples.Decoder_input.K;

  if (Command == COMMAND_DECODE)
  {
    for (unsigned Packet = 0; Packet < K; Packet++)
    {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
      packet_info Info = Input_info_FIFO.read();
      Output_info_FIFO.write(Info);
      Packet_indices[Packet] = Info.Packet_index;
      Packet_lengths[Packet] = Info.Bytes_per_packet;

      unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(Info.Bytes_per_packet, BYTES_PER_WORD);
      for (unsigned Offset = 0; Offset < Words_per_packet; Offset++)
      {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
        Output_buffer[Packet][Offset] = Input_FIFO.read();
      }
    }
  }
}

static unsigned Find_missing_packet(packet_index Packet_indices[FEC_MAX_K], unsigned k)
{
  unsigned Missing_packet = 0;
  for (unsigned Packet = 0; Packet < FEC_MAX_K; Packet++)
    if (Packet < k && Packet_indices[Packet] == Packet)
      Missing_packet = Packet + 1;
  return Missing_packet;
}

static void Decode_packets(hls::stream<parameters> & Input_parameter_FIFO,
    data_word Input_buffer[FEC_MAX_K][PING_PONG_BUFFER_SIZE],
    hls::stream<packet_info> & Input_info_FIFO, packet_index Packet_indices[FEC_MAX_K],
	packet_length Packet_lengths[FEC_MAX_K],
    hls::stream<parameters> & Output_parameter_FIFO, hls::stream<data_word> & Output_data,
    hls::stream<packet_info> & Output_info_FIFO)
{
#pragma HLS array_partition variable=Packet_indices complete
#pragma HLS array_partition variable=Packet_lengths complete
#pragma HLS ARRAY_PARTITION variable=Input_buffer complete dim=1

  parameters Parameters = Input_parameter_FIFO.read();
  Output_parameter_FIFO.write(Parameters);
  command Command = Parameters.Command;
  unsigned K = Parameters.Input_tuples.Decoder_input.K;
  unsigned H = Parameters.Input_tuples.Decoder_input.H;

  if (Command == COMMAND_DECODE)
  {
    unsigned Missing_packet;
    if (H == 1)
      Missing_packet = Find_missing_packet(Packet_indices, K);

    for (unsigned Packet = 0; Packet < K; Packet++)
    {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
      fec_sym Coefficients[FEC_MAX_K];
#pragma HLS array_partition variable=Coefficients complete
      Lookup_coefficients(Coefficients, K, H, Packet, Missing_packet);

      packet_info Info = Input_info_FIFO.read();
      unsigned Offset = 0;
      unsigned Length = 1024;
      unsigned Words_per_packet = 1024;
      bool End = false;
      while (!End)
      {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline

        data_word Input[FEC_MAX_K];
#pragma HLS array_partition variable=Input complete
        for (unsigned Packet_2 = 0; Packet_2 < FEC_MAX_K; Packet_2++)
        {
          unsigned Byte_offset = BYTES_PER_WORD * Offset;
          data_word Word = Input_buffer[Packet_2][Offset];
          unsigned Length = Packet_lengths[Packet_2];
          for (unsigned Byte = 0; Byte < BYTES_PER_WORD; Byte++)
          {
        	data_word Mask = ~((data_word) 0xFF << (8 * (BYTES_PER_WORD - 1 - Byte)));
        	Word = Byte_offset < Length ? Word : Word & Mask;
        	Byte_offset++;
          }
          Input[Packet_2] = Word;
        }

        data_word Output = Matrix_multiply_word(Input, Coefficients, K);

        End = Offset == Words_per_packet - 1;
        Words_per_packet = DIVIDE_AND_ROUND_UP(Length, BYTES_PER_WORD);
        Length = Info.Bytes_per_packet + FEC_PACKET_LENGTH_WIDTH / 8;

        if (Offset == 0)
          Info.Bytes_per_packet = Output >> (FEC_AXI_BUS_WIDTH - FEC_PACKET_LENGTH_WIDTH);

        Output_data.write(Output);
        
        Offset++;
      }

      Output_info_FIFO.write(Info);
    }
  }
}

static void Postprocess_headers(hls::stream<parameters> & Input_parameter_FIFO,
    hls::stream<data_word> & Input_FIFO, hls::stream<packet_info> & Input_info_FIFO,
    hls::stream<parameters> & Output_parameter_FIFO, hls::stream<data_word> & Output_FIFO,
    hls::stream<packet_info> & Output_info_FIFO)
{
  parameters Parameters = Input_parameter_FIFO.read();
  Output_parameter_FIFO.write(Parameters);
  command Command = Parameters.Command;
  unsigned K = Parameters.Input_tuples.Decoder_input.K;

  if (Command == COMMAND_DECODE)
  {
    for (unsigned Packet = 0; Packet < K; Packet++)
    {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
      packet_info Info = Input_info_FIFO.read();
      unsigned Bytes_per_packet = Info.Bytes_per_packet;
      unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(
          Bytes_per_packet + FEC_PACKET_LENGTH_WIDTH / 8, BYTES_PER_WORD);

      ap_uint<2 * FEC_AXI_BUS_WIDTH> Data = 0;
      unsigned Count = 0;
      unsigned Offset = 0;
      for (unsigned Word_offset = 0; Word_offset < Words_per_packet; Word_offset++)
      {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
        data_word Input = Input_FIFO.read();

        for (unsigned Byte_offset = 0; Byte_offset < BYTES_PER_WORD; Byte_offset++)
        {
          bool Output = Offset >= FEC_PACKET_LENGTH_WIDTH / 8 && Offset < Bytes_per_packet + FEC_PACKET_LENGTH_WIDTH / 8;
          unsigned Byte = (Input >> (8 * (BYTES_PER_WORD - Byte_offset - 1))) & 0xFF;
          if (Output)
            Data = (Data << 8) | Byte;
          Count += Output ? 1 : 0;
          Offset++;
        }

        if (Count >= BYTES_PER_WORD)
        {
          Output_FIFO.write(Data >> (8 * (Count - BYTES_PER_WORD)));
          Count -= BYTES_PER_WORD;
        }
      }
      if (Count > 0)
        Output_FIFO.write(Data << (8 * (BYTES_PER_WORD - Count)));

      Output_info_FIFO.write(Info);
    }
  }
}

static void Forward_packet(input_tuples Input_tuples, hls::stream<output_tuples> & Tuple_output,
    hls::stream<packet_interface> & Packet_input, hls::stream<packet_interface> & Packet_output)
{
  packet_interface Input;
  do
  {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
    Input = Packet_input.read();
    Packet_output.write(Input);
  }
  while (!Input.End_of_frame);

  output_tuples Tuples;
  Tuples.Decoder_output.Packet_count = 1;
  Tuples.Hdr = Input_tuples.Hdr;
  Tuples.Ioports = Input_tuples.Ioports;
  Tuples.Local_state = Input_tuples.Local_state;
  Tuples.Parser_extracts = Input_tuples.Parser_extracts;
  Tuples.Update_fl = Input_tuples.Update_fl;
  Tuples.Control = Input_tuples.Control;
  Tuple_output.write(Tuples);
}

static void Output_packets(input_tuples Input_tuples, hls::stream<output_tuples> & Tuple_output,
    hls::stream<data_word> & Input_data_FIFO, hls::stream<packet_info> & Input_info_FIFO,
    unsigned Packet_count, hls::stream<packet_interface> & Packet_output, command Command)
{
// The following pragma is to avoid a bug in Vivado HLS code generation (See post of 5/18 on Xilinx
// community forums).
#pragma HLS inline
  for (unsigned Packet = 0; Packet < Packet_count; Packet++)
  {
#pragma HLS LOOP_TRIPCOUNT min=5 max=50
    packet_info Info = Input_info_FIFO.read();
    unsigned Bytes_per_packet = Info.Bytes_per_packet;
    unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(Info.Bytes_per_packet, BYTES_PER_WORD);
    for (unsigned Offset = 0; Offset < Words_per_packet; Offset++)
    {
#pragma HLS LOOP_TRIPCOUNT min=8 max=190
#pragma HLS pipeline
      data_word Word = Input_data_FIFO.read();

      bool End = Offset == Words_per_packet - 1;

      packet_interface Output;
      Output.Data = Word;
      Output.Start_of_frame = Offset == 0;
      Output.End_of_frame = End;
      Output.Count = Bytes_per_packet % 8;
      if (!End || Output.Count == 0)
        Output.Count = 8;
      Output.Error = 0;
      Packet_output.write(Output);
    }

    output_tuples Tuples;
    Tuples.Decoder_output.Packet_count = Packet_count;
    Tuples.Hdr = Input_tuples.Hdr;
    Tuples.Hdr.Eth.range(ETH_TYPE_END, ETH_TYPE_START) = Info.Original_type;
    Tuples.Ioports = Input_tuples.Ioports;
    Tuples.Local_state = Input_tuples.Local_state;
    Tuples.Update_fl = Input_tuples.Update_fl;
    Tuples.Control = Input_tuples.Control;
    if (Command != COMMAND_DECODE)
    {
      Tuples.Hdr.Eth[ETH_IS_VALID_START] = 1;
      Tuples.Parser_extracts = Input_tuples.Parser_extracts;
    }
    else
    {
      Tuples.Hdr.Eth[ETH_IS_VALID_START] = 1;
      Tuples.Parser_extracts.Size = 0;
    }
    Tuple_output.write(Tuples);
  }
}

static void Output_packets(hls::stream<parameters> & Parameter_FIFO,
    hls::stream<output_tuples> & Tuple_output, hls::stream<data_word> & Decoded_data_FIFO,
    hls::stream<data_word> & Raw_data_FIFO, hls::stream<packet_info> & Decoded_info_FIFO,
    hls::stream<packet_info> & Raw_info_FIFO, hls::stream<packet_interface> & Bypass_FIFO,
    unsigned Packet_count, hls::stream<packet_interface> & Packet_output)
{
  parameters Parameters = Parameter_FIFO.read();
  command Command = Parameters.Command;
  unsigned K = Parameters.Input_tuples.Decoder_input.K;
  input_tuples Input_tuples = Parameters.Input_tuples;

  if (Command == COMMAND_BYPASS)
    Forward_packet(Input_tuples, Tuple_output, Bypass_FIFO, Packet_output);
  else if (Command == COMMAND_DECODE)
    Output_packets(Input_tuples, Tuple_output, Decoded_data_FIFO, Decoded_info_FIFO, K,
        Packet_output, Command);
  else if (Command == COMMAND_OUTPUT_DATA)
    Output_packets(Input_tuples, Tuple_output, Raw_data_FIFO, Raw_info_FIFO, Packet_count,
        Packet_output, Command);
}

void Decoder(hls::stream<input_tuples> & Tuple_input, hls::stream<output_tuples> & Tuple_output,
    hls::stream<packet_interface> & Packet_input, hls::stream<packet_interface> & Packet_output)
{
#pragma HLS DATA_PACK variable=Tuple_input
#pragma HLS DATA_PACK variable=Tuple_output
#pragma HLS DATA_PACK variable=Packet_input
#pragma HLS DATA_PACK variable=Packet_output
#pragma HLS INTERFACE ap_fifo port=Tuple_input
#pragma HLS INTERFACE ap_hs port=Tuple_output
#pragma HLS INTERFACE ap_fifo port=Packet_input
#pragma HLS INTERFACE ap_hs port=Packet_output

#pragma HLS dataflow

  bool Wait_for_data = true;

  const int Packets_needed = FEC_MAX_K + (Wait_for_data ? FEC_MAX_H : 0);
  const int Data_streams_size = Packets_needed * WORDS_PER_PACKET;
  const int Info_stream_size = Packets_needed;
  const int Data_stream_size = WORDS_PER_PACKET;
  const int Raw_data_stream_size = FEC_MAX_K * WORDS_PER_PACKET;

  data_word Ping_pong_buffer[FEC_MAX_K][PING_PONG_BUFFER_SIZE];
  packet_index Packet_indices[FEC_MAX_K];
  packet_length Packet_lengths[FEC_MAX_K];
  static hls::stream<data_word> Data_streams[TRAFFIC_CLASS_COUNT];
#pragma HLS STREAM variable=Data_streams depth=Data_streams_size
  static hls::stream<packet_info> Info_streams[TRAFFIC_CLASS_COUNT];
#pragma HLS STREAM variable=Info_streams depth=Info_stream_size
  hls::stream<data_word> Encoded_data_stream;
#pragma HLS STREAM variable=Encoded_data_stream depth=Data_stream_size
  hls::stream<data_word> Preprocessed_data_stream;
#pragma HLS STREAM variable=Preprocessed_data_stream depth=Data_stream_size
  hls::stream<data_word> Decoded_data_stream;
#pragma HLS STREAM variable=Decoded_data_stream depth=Data_stream_size
  hls::stream<data_word> Postprocessed_data_stream;
#pragma HLS STREAM variable=Postprocessed_data_stream depth=Data_stream_size
  hls::stream<data_word> Raw_data_stream;
#pragma HLS STREAM variable=Raw_data_stream depth=Raw_data_stream_size
  hls::stream<packet_info> Encoded_info_stream;
#pragma HLS STREAM variable=Encoded_info_stream depth=Info_stream_size
  hls::stream<packet_info> Preprocessed_info_stream;
#pragma HLS STREAM variable=Preprocessed_info_stream depth=Info_stream_size
  hls::stream<packet_info> Reordered_info_stream;
#pragma HLS STREAM variable=Reordered_info_stream depth=Info_stream_size
  hls::stream<packet_info> Decoded_info_stream;
#pragma HLS STREAM variable=Decoded_info_stream depth=Info_stream_size
  hls::stream<packet_info> Postprocessed_info_stream;
#pragma HLS STREAM variable=Postprocessed_info_stream depth=Info_stream_size
  hls::stream<packet_info> Raw_info_stream;
#pragma HLS STREAM variable=Raw_info_stream depth=Info_stream_size
  hls::stream<packet_interface> Bypass_stream;
#pragma HLS STREAM variable=Bypass_stream depth=Data_stream_size
  hls::stream<parameters> Parameter_stream_1;
#pragma HLS STREAM variable=Parameter_stream_1 depth=Packets_needed
  hls::stream<parameters> Parameter_stream_2;
  hls::stream<parameters> Parameter_stream_3;
  hls::stream<parameters> Parameter_stream_4;
  hls::stream<parameters> Parameter_stream_5;
  hls::stream<parameters> Parameter_stream_6;

  unsigned Packet_count;

  Collect_packets(Tuple_input, Packet_input, Parameter_stream_1, Data_streams, Info_streams,
      Bypass_stream, Wait_for_data);
  Select_packets(Parameter_stream_1, Data_streams, Info_streams, Parameter_stream_2,
      Raw_data_stream, Encoded_data_stream, Raw_info_stream, Encoded_info_stream, Packet_count);
  Preprocess_headers(Parameter_stream_2, Encoded_data_stream, Encoded_info_stream,
      Parameter_stream_3, Preprocessed_data_stream, Preprocessed_info_stream);
  Reorder_packets(Parameter_stream_3, Preprocessed_data_stream, Preprocessed_info_stream,
      Parameter_stream_4, Ping_pong_buffer, Reordered_info_stream, Packet_indices, Packet_lengths);
  Decode_packets(Parameter_stream_4, Ping_pong_buffer, Reordered_info_stream, Packet_indices, Packet_lengths,
      Parameter_stream_5, Decoded_data_stream, Decoded_info_stream);
  Postprocess_headers(Parameter_stream_5, Decoded_data_stream, Decoded_info_stream,
      Parameter_stream_6, Postprocessed_data_stream, Postprocessed_info_stream);
  Output_packets(Parameter_stream_6, Tuple_output, Postprocessed_data_stream, Raw_data_stream,
      Postprocessed_info_stream, Raw_info_stream, Bypass_stream, Packet_count, Packet_output);
}
