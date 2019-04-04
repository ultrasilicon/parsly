#include "proto_compiler.h"

ProtoCompiler::ProtoCompiler() {

}

std::string ProtoCompiler::cpp_wrap(const std::string &block, const std::string &prefix, const std::string &postfix)
{
    return prefix + block + postfix;
}

std::string ProtoCompiler::cpp_switch(const std::string &block, const std::string &var)
{
    return "\tswitch (" + enum_name + ") {\n" + code + "\t}\n"
}

std::string ProtoCompiler::cpp_case(const std::string &block, const std::string &val, const std::string &comment)
{

}

std::string ProtoCompiler::cfn_redeem(const std::string &type, const std::string &comment)
{

}

std::string ProtoCompiler::cfn_insert(const std::string &type, const std::string &index, const std::string &comment)
{

}

std::string ProtoCompiler::util_indent(std::string block, const std::string &indent)
{
    if(indent.find('\n'))
        throw std::invalid_argument("Invalid character '\n' found in argument \"indent\"");
    block = indent + block;
    for(auto it = block.begin() ; it < block.end(); ++ it)
    {
        if(*it == '\n')
            block.insert(it, indent.begin(), indent.end());
    }
    return block;
}
