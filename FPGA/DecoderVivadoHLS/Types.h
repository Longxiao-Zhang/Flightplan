// Code generated by the Fuselage Factory

// WE DISCOURAGE MODIFYING THIS FILE DIRECTLY!!!
// Changes to P4 code that do not affect the external function signature in P4
// may still result in different variable widths.

#ifndef FUSELAGE_HEADER_INCLUDED
#define FUSELAGE_HEADER_INCLUDED

#include <cstddef>
#include <ap_int.h>
#include <hls_stream.h>

struct tuple_control
{
  ap_uint<23> Control;
};

struct tuple_Update_fl
{
  ap_uint<8> Packet_count_1;
  ap_uint<8> H_1;
  ap_uint<8> K_1;
};

struct tuple_hdr
{
  ap_uint<49> Fec;
  ap_uint<113> Eth;
};

struct tuple_ioports
{
  ap_uint<4> Egress_port;
  ap_uint<4> Ingress_port;
};

struct tuple_local_state
{
  ap_uint<16> Id;
};

struct tuple_Parser_extracts
{
  ap_uint<32> Size;
};

struct tuple_Decoder_input
{
  ap_uint<8> H;
  ap_uint<8> K;
  ap_uint<1> Stateful_valid;
};

struct tuple_Decoder_output
{
  ap_uint<8> Packet_count;
};

struct input_tuples
{
  tuple_control Control;
  tuple_Update_fl Update_fl;
  tuple_hdr Hdr;
  tuple_ioports Ioports;
  tuple_local_state Local_state;
  tuple_Parser_extracts Parser_extracts;
  tuple_Decoder_input Decoder_input;
};

struct output_tuples
{
  tuple_control Control;
  tuple_Update_fl Update_fl;
  tuple_hdr Hdr;
  tuple_ioports Ioports;
  tuple_local_state Local_state;
  tuple_Parser_extracts Parser_extracts;
  tuple_Decoder_output Decoder_output;
};

struct packet_interface
{
  ap_uint<1> Error;
  ap_uint<4> Count;
  ap_uint<64> Data;
  ap_uint<1> End_of_frame;
  ap_uint<1> Start_of_frame;
};

void Decoder(hls::stream<input_tuples> & Tuple_input, hls::stream<output_tuples> & Tuple_output,
    hls::stream<packet_interface> & Packet_input, hls::stream<packet_interface> & Packet_output);

#endif
