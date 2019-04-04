#ifndef PRE_PROC_H
#define PRE_PROC_H

#include <string>
#include <stdexcept>

class ProtoCompiler
{
public:
    explicit ProtoCompiler();

private:
    static inline std::string cpp_wrap(const std::string& block, const std::string& prefix, const std::string& postfix);
    static inline std::string cpp_switch(const std::string& block, const std::string& var);
    static inline std::string cpp_case(const std::string& block, const std::string& val, const std::string& comment);
    static inline std::string cfn_redeem(const std::string& type, const std::string& comment);
    static inline std::string cfn_insert(const std::string& type, const std::string& index, const std::string& comment);

    inline std::string util_indent(std::string block, const std::string& indent = "\t");

    std::string _indent_str = "  ";
};

#endif // PRE_PROC_H
