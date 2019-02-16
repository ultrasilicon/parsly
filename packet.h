#ifndef PACKET_H
#define PACKET_H

#include <unordered_map>
#include <variant>

class Packet;

template<size_t _MAX, typename _T, typename... _Ts>
struct max_type_size : max_type_size<(_MAX <= sizeof(_T) ? sizeof(_T) : _MAX), _Ts...>
{
};

template<size_t _MAX, typename _T>
struct max_type_size<_MAX, _T>
{
    static constexpr size_t value = _MAX <= sizeof(_T) ? sizeof(_T) : _MAX;
};


template<typename _T>
struct tagger { int value; tagger(size_t s) : value(s) {} };

template<typename _T, typename... _Ts>
struct tag_of_type: tagger<_T>, tag_of_type<_Ts...>
{
    tag_of_type() : tagger<_T>(sizeof...(_Ts)) {}
};
template<typename _T>
struct tag_of_type<_T> : tagger<_T>
{
    tag_of_type() : tagger<_T>(0) {}
};

template<typename... _Ts>
struct variant
{
    char* m_p;
    tag_of_type<_Ts...> m_tagger;
    int m_curr_tag;

    variant() : m_p(new char[max_type_size<0, _Ts...>::value]) { }
    ~variant() { if(m_p) delete[] m_p; m_p = nullptr; }

    template<typename _T>
    variant& operator=(const _T& v)
    {
        *(_T*)m_p = v;
        m_curr_tag = static_cast<tagger<_T>&>(m_tagger).value;
        return *this;
    }

    template<typename _T>
    _T& get()
    {
        if(m_curr_tag != static_cast<tagger<_T>&>(m_tagger).value)
            throw std::bad_cast{};
        return *(_T*)m_p;
    }
};

using variant_t = variant<
    int8_t
    , int16_t
    , int32_t
    , int64_t
    , uint8_t
    , uint16_t
    , uint32_t
    , uint64_t
    , std::string
>;

class Packet
{
public:
    Packet();
    std::unordered_map<std::string, variant_t> data;
};



#endif // PACKET_H
