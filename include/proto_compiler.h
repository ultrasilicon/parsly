#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <string>
#include <map>
#include <stdexcept>

class ProtoCompiler
{
public:
    explicit ProtoCompiler();

private:
    inline std::string cppWrap(const std::string& block, const std::string& prefix, const std::string& postfix);
    inline std::string cppSwitch(const std::string& block, const std::string& type);
    inline std::string cppCase(const std::string& block, const std::string& val, const std::string& comment);
    inline std::string fnRedeem(const std::string& type, const std::string& comment);
    inline std::string fnInsert(const std::string& type, const std::string& index, const std::string& comment);

    inline std::string utilIndent(std::string block, const std::string& indent = "\t");

    std::string indent_str_ = "  ";
    std::map<std::string, std::string> str_to_type_;
};

#endif // PRE_PROC_H
