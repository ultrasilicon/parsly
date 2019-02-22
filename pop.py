import sys
import os
import json

str_to_type = {
	"int8"   : "int8_t",
	"int16"  : "int16_t",
	"int32"  : "int32_t",
	"int64"  : "int64_t",
	"uint8"  : "uint8_t",
	"uint16" : "uint16_t",
	"uint32" : "uint32_t",
	"uint64" : "uint64_t",
	"string" : "std::string"
}

header_size_to_type = {
	1  : "char",
	8  : "uint8_t", 
	16 : "uint16_t",
	32 : "uint32_t",
	64 : "uint64_t",
}

global arg_json_file 
global arg_output_dir 

global pop_json
global pop_main_header_type
global pop_flag_enum_map
global pop_flag_field_map

global out_encoder_code
global out_encoder_label
out_encoder_label = "_POP_ENCODER_INJECT_POINT"
global out_decoder_code
global out_decoder_label
out_decoder_label = "_POP_DECODER_INJECT_POINT"


def check_args():
	if len(sys.argv) != 3:
		print("fatal: argument count error, 2 needed.\nusage: %s <protocol json file> <output directory>" % sys.argv[0])
		exit(1)
	global arg_json_file 
	global arg_output_dir 
	arg_json_file = sys.argv[1]
	arg_output_dir = sys.argv[2]


def read_json(dir):
	global pop_json
	pop_json = json.loads(open(dir).read())


def parse_json():
	global pop_json
	global pop_main_header_type
	global pop_flag_enum_map
	pop_flag_enum_map = {}
	global pop_flag_field_map
	pop_flag_field_map = {}

	# "header" : 4
	pop_main_header_type = pop_json["protocol"]["header"]	

	enum_counter = 0
	for flag in pop_json["protocol"]["flags"]:
		if flag in pop_json["fields"]:
			pop_flag_enum_map[flag] = enum_counter
			pop_flag_field_map[flag] = pop_json["fields"][flag]
			enum_counter += 1
		else:
			print("error: message field of flag %s is not defined in \"fields\" object.\n" % flag)
			exit(1)


def pop_redeem(type_str, comment):
	if type_str == "string":
		return "\t\t\tredeemStr<pe_str_len_t>(pos, end), // " + comment + "\n"
	else:
		if type_str not in str_to_type:
			print("error: unknown type %s.\n" % type_str)
			exit(1)
		return "\t\t\tredeemVal<" + str_to_type[type_str] + ">(pos, end), // " + comment + "\n"


def pop_insert(type_str, comment, idx):
	''' e.g. insertStr(stream, pos, packet->data[2].get<std::string>()); '''

	if type_str == "string":
		return "\t\t\tinsertStr(stream, pos, packet->data[{}].get<std::string>()); // ".format(idx) + comment + "\n"
	else:
		if type_str not in str_to_type:
			print("error: unknown type %s.\n" % type_str)
			exit(1)
		return "\t\t\tinsertVal(stream, pos, packet->data[{}].get<".format(idx) + str_to_type[type_str] + ">()); // " + comment + "\n"


def pop_wrap(code, prefix, postfix):
	return prefix + code + postfix


def pop_case(code, case_num, comment):
	return "\tcase " + str(case_num) + ": { // " + comment + "\n" + code + "\t\tbreak;\n\t}\n"


def pop_switch(code, enum_name):
	return "\tswitch (" + enum_name + ") {\n" + code + "\t}\n"


def generate_decoder():
	global out_decoder_code
	switch_block = ""
	case_counter = 0
	for key in pop_flag_field_map:
		redeem_block = ""
		for field in pop_flag_field_map[key]:
			redeem_block += pop_redeem(field[0], field[1])
		# redeem_block += "\n"
		case_block = pop_wrap(redeem_block, "\t\treturn new Packet{{\n", "\t\t}, flag};\n")
		switch_block += pop_case(case_block, case_counter, key)
		case_counter += 1

	out_decoder_code = pop_switch(switch_block, "flag")
	return out_decoder_code


def generate_encoder():
	global out_encoder_code
	switch_block = ""
	case_counter = 0
	for key in pop_flag_field_map:
		insert_block = ""
		for idx, field in enumerate(pop_flag_field_map[key]):
			insert_block += pop_insert(field[0], field[1], idx)
		# insert_block += "\n"
		switch_block += pop_case(insert_block, case_counter, key)
		case_counter += 1

	out_encoder_code = pop_switch(switch_block, "flag")
	return out_encoder_code


def inject_to_file(dir, label, data):
	if not os.path.isfile(dir):
		print("fatal: file %s not found.\n" % dir)
		exit(1)

	lines = []
	with open(dir, "r") as dec_cpp:
		lines = dec_cpp.readlines()

	with open(dir, "w") as dec_cpp:
		for i, line in enumerate(lines):
			if line.find(label) > -1:
				until = i
				for j in range(i + 1, len(lines)):
					if lines[j].find(label) == -1:
						until = j
					else:
						break
				n = until - i
				while n > 0:
					lines.pop(i + 1)
					n -= 1

				lines.insert(i + 1, data) # inject
				dec_cpp.writelines(lines)
				break


if __name__=="__main__":
	check_args()
	read_json(arg_json_file)
	print("pop: Parsing %s ...\n" % arg_json_file)
	parse_json()
	print("pop: Generating decoder in C++ ...\n")
	print (generate_decoder())
	print("pop: Generating encoder in C++ ...\n")
	print(generate_encoder())
	inject_to_file(arg_output_dir + "/parse_engine_decode_pop.cpp", out_decoder_label, out_decoder_code)
	inject_to_file(arg_output_dir + "/parse_engine_encode_pop.cpp", out_encoder_label, out_encoder_code)

