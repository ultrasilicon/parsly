#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <type_traits>

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
    tag_of_type<_Ts...> m_tagger;

    const size_t m_size = max_type_size<0, _Ts...>::value;
    int m_curr_tag = -1;

    char* m_p;

    template<typename _T>
    variant(const _T& v)
        : m_p(new char[m_size]{})
    {
        new(m_p) _T(v);
        m_curr_tag = static_cast<tagger<_T>&>(m_tagger).value;
    }

    variant() : variant(0) {}

    variant(const variant& that)
        : m_p(new char[m_size]{})
    {
        for(int i = 0; i < m_size; i++)
            m_p[i] = that.m_p[i];
        m_curr_tag = that.m_curr_tag;
    }

    ~variant() { if(m_p) delete[] m_p; m_p = nullptr; }

    template<typename _T>
    variant& operator=(const _T& v)
    {
//        if(!std::is_same<_T, std::string>::value
//                && std::is_base_of<tagger<std::string>, variant>::value
//                && m_curr_tag == static_cast<tagger<std::string>&>(m_tagger).value) // previous and now both strings?
//            ((std::string*)m_p)->~std::basic_string<char>();
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

struct Packet
{
    std::vector<variant_t> data;
    uint8_t msgType;
};



