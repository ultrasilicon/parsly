#include "proto_compiler.h"

ProtoCompiler::ProtoCompiler() {

}

std::string ProtoCompiler::cppWrap(const std::string &block, const std::string &prefix, const std::string &postfix)
{
    return prefix + block + postfix;
}

std::string ProtoCompiler::cppSwitch(const std::string &block, const std::string &type)
{
    return "switch (" + type + ") {\n" + utilIndent(block) + "}\n";
}

std::string ProtoCompiler::cppCase(const std::string &block, const std::string &val, const std::string &comment)
{

}

std::string ProtoCompiler::fnRedeem(const std::string &type, const std::string &comment)
{

}

std::string ProtoCompiler::fnInsert(const std::string &type, const std::string &index, const std::string &comment)
{

}

std::string ProtoCompiler::utilIndent(std::string block, const std::string &indent)
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
