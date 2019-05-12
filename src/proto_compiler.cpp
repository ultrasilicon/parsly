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
    return "case " + val + ": {\n" + utilIndent(block) + " break;\n}\n";
}

std::string ProtoCompiler::fnRedeem(const std::string &type, const std::string &comment)
{
    if(type == "string")
    {
        return utilIndent("redeemStr<pe_str_len_t>(pos, end), // " + comment + "\n");
    }
    else
    {
        if(str_to_type_.find(type) != str_to_type_.end())
        {
            fprintf(stderr, "error: unknown type %s.\n", type.c_str());
            exit(1);
        }
        return utilIndent("redeemVal<" + str_to_type_[type] + ">(pos, end), // " + comment + "\n");
    }
}

std::string ProtoCompiler::fnInsert(const std::string &type, const std::string &index, const std::string &comment)
{
    if(type == "string")
    {
        return utilIndent("insertStr(stream, pos, packet->data[" + index + "].get<std::string>()); // " + comment + "\n");
    }
    else
    {
        if(str_to_type_.find(type) != str_to_type_.end())
        {
            fprintf(stderr, "error: unknown type %s.\n", type.c_str());
            exit(1);
        }
        return utilIndent("insertVal(stream, pos, packet->data[" + index + "].get<" + str_to_type_[type] + ">()); // " + comment + "\n");
    }
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
