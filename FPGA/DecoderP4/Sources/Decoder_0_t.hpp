#ifndef SDNET_ENGINE_Decoder_0_t
#define SDNET_ENGINE_Decoder_0_t

#include "sdnet_lib.hpp"

#include "Decoder.h"

namespace SDNET {

//######################################################
class Decoder_0_t { // UserEngine
public:

	// tuple types
	struct Update_fl_t {
		static const size_t _SIZE = 24;
		_LV<8> k_1;
		_LV<8> h_1;
		_LV<8> packet_count_1;
		Update_fl_t& operator=(_LV<24> _x) {
			k_1 = _x.slice(23,16);
			h_1 = _x.slice(15,8);
			packet_count_1 = _x.slice(7,0);
			return *this;
		}
		_LV<24> get_LV() { return (k_1,h_1,packet_count_1); }
		operator _LV<24>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tk_1 = " + k_1.to_string() + "\n" + "\t\th_1 = " + h_1.to_string() + "\n" + "\t\tpacket_count_1 = " + packet_count_1.to_string() + "\n" + "\t)";
		}
		Update_fl_t() {} 
		Update_fl_t( _LV<8> _k_1, _LV<8> _h_1, _LV<8> _packet_count_1) {
			k_1 = _k_1;
			h_1 = _h_1;
			packet_count_1 = _packet_count_1;
		}
	};
	struct hdr_t_0 {
		static const size_t _SIZE = 162;
		struct _struct_eth {
			static const size_t _SIZE = 113;
			_LV<1> isValid;
			_LV<48> dst;
			_LV<48> src;
			_LV<16> type;
			_struct_eth& operator=(_LV<113> _x) {
				isValid = _x.slice(112,112);
				dst = _x.slice(111,64);
				src = _x.slice(63,16);
				type = _x.slice(15,0);
				return *this;
			}
			_LV<113> get_LV() { return (isValid,dst,src,type); }
			operator _LV<113>() { return get_LV(); } 
			std::string to_string() const {
				return std::string("(\n")  + "\t\tisValid = " + isValid.to_string() + "\n" + "\t\tdst = " + dst.to_string() + "\n" + "\t\tsrc = " + src.to_string() + "\n" + "\t\ttype = " + type.to_string() + "\n" + "\t)";
			}
			_struct_eth() {} 
			_struct_eth( _LV<1> _isValid, _LV<48> _dst, _LV<48> _src, _LV<16> _type) {
				isValid = _isValid;
				dst = _dst;
				src = _src;
				type = _type;
			}
		};
		_struct_eth eth;
		struct _struct_fec {
			static const size_t _SIZE = 49;
			_LV<1> isValid;
			_LV<3> traffic_class;
			_LV<5> block_index;
			_LV<8> packet_index;
			_LV<16> original_type;
			_LV<16> packet_length;
			_struct_fec& operator=(_LV<49> _x) {
				isValid = _x.slice(48,48);
				traffic_class = _x.slice(47,45);
				block_index = _x.slice(44,40);
				packet_index = _x.slice(39,32);
				original_type = _x.slice(31,16);
				packet_length = _x.slice(15,0);
				return *this;
			}
			_LV<49> get_LV() { return (isValid,traffic_class,block_index,packet_index,original_type,packet_length); }
			operator _LV<49>() { return get_LV(); } 
			std::string to_string() const {
				return std::string("(\n")  + "\t\tisValid = " + isValid.to_string() + "\n" + "\t\ttraffic_class = " + traffic_class.to_string() + "\n" + "\t\tblock_index = " + block_index.to_string() + "\n" + "\t\tpacket_index = " + packet_index.to_string() + "\n" + "\t\toriginal_type = " + original_type.to_string() + "\n" + "\t\tpacket_length = " + packet_length.to_string() + "\n" + "\t)";
			}
			_struct_fec() {} 
			_struct_fec( _LV<1> _isValid, _LV<3> _traffic_class, _LV<5> _block_index, _LV<8> _packet_index, _LV<16> _original_type, _LV<16> _packet_length) {
				isValid = _isValid;
				traffic_class = _traffic_class;
				block_index = _block_index;
				packet_index = _packet_index;
				original_type = _original_type;
				packet_length = _packet_length;
			}
		};
		_struct_fec fec;
		hdr_t_0& operator=(_LV<162> _x) {
			eth = _x.slice(161,49);
			fec = _x.slice(48,0);
			return *this;
		}
		_LV<162> get_LV() { return (eth.isValid,eth.dst,eth.src,eth.type,fec.isValid,fec.traffic_class,fec.block_index,fec.packet_index,fec.original_type,fec.packet_length); }
		operator _LV<162>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\teth = " + eth.to_string() + "\n" + "\t\tfec = " + fec.to_string() + "\n" + "\t)";
		}
		hdr_t_0() {} 
		hdr_t_0( _LV<113> _eth, _LV<49> _fec) {
			eth = _eth;
			fec = _fec;
		}
	};
	struct ioports_t {
		static const size_t _SIZE = 8;
		_LV<4> ingress_port;
		_LV<4> egress_port;
		ioports_t& operator=(_LV<8> _x) {
			ingress_port = _x.slice(7,4);
			egress_port = _x.slice(3,0);
			return *this;
		}
		_LV<8> get_LV() { return (ingress_port,egress_port); }
		operator _LV<8>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tingress_port = " + ingress_port.to_string() + "\n" + "\t\tegress_port = " + egress_port.to_string() + "\n" + "\t)";
		}
		ioports_t() {} 
		ioports_t( _LV<4> _ingress_port, _LV<4> _egress_port) {
			ingress_port = _ingress_port;
			egress_port = _egress_port;
		}
	};
	struct local_state_t {
		static const size_t _SIZE = 16;
		_LV<16> id;
		local_state_t& operator=(_LV<16> _x) {
			id = _x.slice(15,0);
			return *this;
		}
		_LV<16> get_LV() { return (id); }
		operator _LV<16>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tid = " + id.to_string() + "\n" + "\t)";
		}
		local_state_t() {} 
		local_state_t( _LV<16> _id) {
			id = _id;
		}
	};
	struct Parser_extracts_t {
		static const size_t _SIZE = 32;
		_LV<32> size;
		Parser_extracts_t& operator=(_LV<32> _x) {
			size = _x.slice(31,0);
			return *this;
		}
		_LV<32> get_LV() { return (size); }
		operator _LV<32>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tsize = " + size.to_string() + "\n" + "\t)";
		}
		Parser_extracts_t() {} 
		Parser_extracts_t( _LV<32> _size) {
			size = _size;
		}
	};
	struct Decoder_input_t {
		static const size_t _SIZE = 17;
		_LV<1> stateful_valid;
		_LV<8> k;
		_LV<8> h;
		Decoder_input_t& operator=(_LV<17> _x) {
			stateful_valid = _x.slice(16,16);
			k = _x.slice(15,8);
			h = _x.slice(7,0);
			return *this;
		}
		_LV<17> get_LV() { return (stateful_valid,k,h); }
		operator _LV<17>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tstateful_valid = " + stateful_valid.to_string() + "\n" + "\t\tk = " + k.to_string() + "\n" + "\t\th = " + h.to_string() + "\n" + "\t)";
		}
		Decoder_input_t() {} 
		Decoder_input_t( _LV<1> _stateful_valid, _LV<8> _k, _LV<8> _h) {
			stateful_valid = _stateful_valid;
			k = _k;
			h = _h;
		}
	};
	struct Decoder_output_t {
		static const size_t _SIZE = 8;
		_LV<8> packet_count;
		Decoder_output_t& operator=(_LV<8> _x) {
			packet_count = _x.slice(7,0);
			return *this;
		}
		_LV<8> get_LV() { return (packet_count); }
		operator _LV<8>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\tpacket_count = " + packet_count.to_string() + "\n" + "\t)";
		}
		Decoder_output_t() {} 
		Decoder_output_t( _LV<8> _packet_count) {
			packet_count = _packet_count;
		}
	};
	struct CONTROL_STRUCT {
		static const size_t _SIZE = 37;
		_LV<14> offset;
		_LV<14> virtual_offset;
		_LV<4> section;
		_LV<1> activeBank;
		_LV<1> done;
		_LV<3> error;
		CONTROL_STRUCT& operator=(_LV<37> _x) {
			offset = _x.slice(36,23);
			virtual_offset = _x.slice(22,9);
			section = _x.slice(8,5);
			activeBank = _x.slice(4,4);
			done = _x.slice(3,3);
			error = _x.slice(2,0);
			return *this;
		}
		_LV<37> get_LV() { return (offset,virtual_offset,section,activeBank,done,error); }
		operator _LV<37>() { return get_LV(); } 
		std::string to_string() const {
			return std::string("(\n")  + "\t\toffset = " + offset.to_string() + "\n" + "\t\tvirtual_offset = " + virtual_offset.to_string() + "\n" + "\t\tsection = " + section.to_string() + "\n" + "\t\tactiveBank = " + activeBank.to_string() + "\n" + "\t\tdone = " + done.to_string() + "\n" + "\t\terror = " + error.to_string() + "\n" + "\t)";
		}
		CONTROL_STRUCT() {} 
		CONTROL_STRUCT( _LV<14> _offset, _LV<14> _virtual_offset, _LV<4> _section, _LV<1> _activeBank, _LV<1> _done, _LV<3> _error) {
			offset = _offset;
			virtual_offset = _virtual_offset;
			section = _section;
			activeBank = _activeBank;
			done = _done;
			error = _error;
		}
	};

	// engine members
	std::string _name;
	Packet packet_in;
	Packet packet_out;
	CONTROL_STRUCT control;
	Update_fl_t Update_fl;
	hdr_t_0 hdr;
	ioports_t ioports;
	local_state_t local_state;
	Parser_extracts_t Parser_extracts;
	Decoder_input_t Decoder_input;
	Decoder_output_t Decoder_output;

	Packet Packets[FEC_MAX_K];
	output_tuples Tuples[FEC_MAX_K];
	int Packet_count;

	// engine ctor
	Decoder_0_t(std::string _n, std::string _filename = "") : _name(_n), Packet_count(0) {
	}

	template<unsigned long Input_width, int Output_width> void Convert(ap_uint<Output_width> & Output, const _LV<Input_width> & Input) {
		assert(Input_width == Output_width);
		for (unsigned long i = 0; i < Input_width; i++)
			Output[i] = Input[i];
	}

	template<class input_class, int Width> void Convert_struct(ap_uint<Width> & Output, input_class & Input) {
		assert(Input._SIZE == Width);
		for (unsigned long i = 0; i < Width; i++)
			Output[i] = Input.get_LV()[i];
	}

	template<int Input_width, unsigned long Output_width> void Convert(_LV<Output_width> & Output, const ap_uint<Input_width> & Input) {
		assert(Input_width == Output_width);
		for (unsigned long i = 0; i < Output_width; i++)
			Output[i] = Input[i];
	}

	template<int Width, class output_class> void Convert_struct(output_class & Output, const ap_uint<Width> & Input) {
		assert(Width == Output._SIZE);
		_LV<Output._SIZE> Temp;
		for (unsigned long i = 0; i < Width; i++)
			Temp[i] = Input[i];
		Output = Temp;
	}

	// engine function
	void operator()() {
		std::cout << "===================================================================" << std::endl;
		std::cout << "Entering engine " << _name << std::endl;
		// input packet
		std::cout << "input packet (" << packet_in.size() << " bytes)" << std::endl;
		std::cout << packet_in;
		// input and inout tuples:
		std::cout << "initial input and inout tuples:" << std::endl;
		std::cout << "	control = " << control.to_string() << std::endl;
		std::cout << "	Update_fl = " << Update_fl.to_string() << std::endl;
		std::cout << "	hdr = " << hdr.to_string() << std::endl;
		std::cout << "	ioports = " << ioports.to_string() << std::endl;
		std::cout << "	local_state = " << local_state.to_string() << std::endl;
		std::cout << "	Parser_extracts = " << Parser_extracts.to_string() << std::endl;
		std::cout << "	Decoder_input = " << Decoder_input.to_string() << std::endl;
		// clear internal and output-only tuples:
		std::cout << "clear internal and output-only tuples" << std::endl;
		Decoder_output = 0;
		std::cout << "	Decoder_output = " << Decoder_output.to_string() << std::endl;

		if (Packet_count == 0) {
			hls::stream<input_tuples> Tuple_input;

			input_tuples Tuple;
			Convert(Tuple.Decoder_input.Stateful_valid, Decoder_input.stateful_valid);
			Convert(Tuple.Decoder_input.K, Decoder_input.k);
			Convert(Tuple.Decoder_input.H, Decoder_input.h);
			Convert_struct(Tuple.Hdr.Eth, hdr.eth);
			Convert_struct(Tuple.Hdr.Fec, hdr.fec);
			Convert(Tuple.Update_fl.Packet_count_1, Update_fl.packet_count_1);
			Convert(Tuple.Update_fl.K_1, Update_fl.k_1);
			Convert(Tuple.Update_fl.H_1, Update_fl.h_1);
			Convert(Tuple.Ioports.Egress_port, ioports.egress_port);
			Convert(Tuple.Ioports.Ingress_port, ioports.ingress_port);
			Convert(Tuple.Local_state.Id, local_state.id);
			Convert(Tuple.Parser_extracts.Size, Parser_extracts.size);
			Tuple_input.write(Tuple);

			hls::stream<packet_interface> Packet_input;
			unsigned Words_per_packet = DIVIDE_AND_ROUND_UP(packet_in.size(), BYTES_PER_WORD);
			for (int i = 0; i < Words_per_packet; i++) {
				ap_uint<FEC_AXI_BUS_WIDTH> Word = 0;
				for (int j = 0; j < BYTES_PER_WORD; j++)
				{
					Word <<= 8;
					unsigned Offset = BYTES_PER_WORD * i + j;
					if (Offset < packet_in.size())
						Word |= packet_in[Offset];
				}
				bool End = i == Words_per_packet - 1;
				packet_interface Input;
				Input.Data = Word;
				Input.Start_of_frame = i == 0;
				Input.End_of_frame = End;
				Input.Count = packet_in.size() % BYTES_PER_WORD;
				if (Input.Count == 0 || !End)
					Input.Count = 8;
				Input.Error = 0;
				Packet_input.write(Input);
			}

			hls::stream<output_tuples> Tuple_output;
			hls::stream<packet_interface> Packet_output;

			Decoder(Tuple_input, Tuple_output, Packet_input, Packet_output);

			Packet_count = 0;
			while (!Tuple_output.empty())
				Tuples[Packet_count++] = Tuple_output.read();

			for (int i = 0; i < Packet_count; i++) {
				Packets[i].clear();
				bool End = false;
				while (!End) {
					packet_interface Output = Packet_output.read();
					for (int j = 0; j < Output.Count; j++) {
						char Byte = (Output.Data >> (8 * (BYTES_PER_WORD - j - 1))) & 0xFF;
						Packets[i].push_back(Byte);
					}
					End = Output.End_of_frame == 1;
				}
			}
		}

		Decoder_output.packet_count = Packet_count;
		if (Packet_count == 0)
			packet_out = Packet();
		else {
			packet_out = Packets[0];
			
			Convert_struct(hdr.eth, Tuples[0].Hdr.Eth);
			Convert_struct(hdr.fec, Tuples[0].Hdr.Fec);
			Convert(Update_fl.packet_count_1, Tuples[0].Update_fl.Packet_count_1);
			Convert(Update_fl.k_1, Tuples[0].Update_fl.K_1);
			Convert(Update_fl.h_1, Tuples[0].Update_fl.H_1);
			Convert(ioports.egress_port, Tuples[0].Ioports.Egress_port);
			Convert(ioports.ingress_port, Tuples[0].Ioports.Ingress_port);
			Convert(local_state.id, Tuples[0].Local_state.Id);
			Convert(Parser_extracts.size, Tuples[0].Parser_extracts.Size);
			
			for (int i = 1; i < Packet_count; i++)
			{
				Packets[i - 1] = Packets[i];
				Tuples[i - 1] = Tuples[i];
			}
			Packet_count--;
		}

		// inout and output tuples:
		std::cout << "final inout and output tuples:" << std::endl;
		std::cout << "	control = " << control.to_string() << std::endl;
		std::cout << "	Update_fl = " << Update_fl.to_string() << std::endl;
		std::cout << "	hdr = " << hdr.to_string() << std::endl;
		std::cout << "	ioports = " << ioports.to_string() << std::endl;
		std::cout << "	local_state = " << local_state.to_string() << std::endl;
		std::cout << "	Parser_extracts = " << Parser_extracts.to_string() << std::endl;
		std::cout << "	Decoder_output = " << Decoder_output.to_string() << std::endl;
		// output packet
		std::cout << "output packet (" << packet_out.size() << " bytes)" << std::endl;
		std::cout << packet_out;
		std::cout << "Exiting engine " << _name << std::endl;
		std::cout << "===================================================================" << std::endl;
	}
};
//######################################################
// top-level DPI function
extern "C" void Decoder_0_t_DPI(const char*, int, const char*, int, int, int);


} // namespace SDNET

#endif // SDNET_ENGINE_Decoder_0_t
