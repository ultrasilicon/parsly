import sys
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
	"string" : "std::string",
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
out_encoder_label = "POP_ENCODER_INJECT_POINT"
global out_decoder_code
global out_decoder_label
out_decoder_label = "POP_DECODER_INJECT_POINT"


def check_args():
	if(len(sys.argv) != 3):
		print("fatal: argument count error, 2 needed.\nusage: %s <protocol json file> <output directory>"
		 % sys.argv[0])
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
	global pop_flag_field_map
	pop_flag_field_map = {}


	# "header" : 4
	pop_main_header_type = pop_json["protocol"]["header"]	

	enum_counter = 0
	for flag in pop_json["protocol"]["flags"]:
		if flag in pop_json["fields"]:
			pop_flag_enum_map[flag] = enum_counter
			pop_flag_field_map[flag] = pop_json["fields"][flag]
			enum_counter ++
		else:
			print("error: message field of flag %s is not defined in \"fields\" object.\n" % flag)
			exit(1)

def generate_decoder():
	global out_encoder_code


def write_to_file(dir, data):
	if not os.path.isdir("dir"):
		print("fatal: file %s not found.\n" % dir)
		exit(1)
	open("demofile.txt", "a").write(data)

def pop_wrap(code, prefix, postfix):
	return prefix + code + postfix

def pop_case(code, case_num, comment):
	return "case " + str(case_num) + ": { \\\\ " + comment + "\n" + code + "}\n"

def pop_switch(code, enum_name):
	return "switch (" + enum_name + ") {\n" + code + "}\n"

if __name__=="__main__":
	check_args()
	read_json(arg_json_file)
	print("pop: Parsing %s ...\n" % arg_json_file)
	parse_json()
	print("pop: Generating decoder in C++ ...\n")

	# compileEncode


