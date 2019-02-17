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
global pop_field_map


def checkArgs():
	if(len(sys.argv) != 3):
		print("fatal: argument count error, 2 needed.\nusage: %s <protocol json file> <output directory>"
		 % sys.argv[0])
		exit(1)
	global arg_json_file 
	global arg_output_dir 
	arg_json_file = sys.argv[1]
	arg_output_dir = sys.argv[2]

def readJson(dir):
	global pop_json
	pop_json = json.loads(open(dir).read())

def parseJson():
	global pop_json
	global pop_main_header_type
	global pop_field_map

	pop_main_header_type = pop_json["protocol"]["header"]

	flags = pop_json["protocol"]["flags"]
	for flag in flags:
		if flag in pop_json["fields"]:
			pop_field_map = {}
			pop_field_map[flag] = pop_json["fields"][flag]
		else:
			print("error: message field of flag %s is not defined in \"fields\" object.\n" % flag)
			exit(1)

if __name__=="__main__":
	checkArgs()
	readJson(arg_json_file)
	print("pop: Parsing %s ...\n" % arg_json_file)
	parseJson()
	print("pop: Compiling to %s ...\n" % arg_output_dir)


