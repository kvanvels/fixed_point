#ifndef SCALE_INT
#define SCALE_INT

#include <algorithm>
#include <sstream>
#include <type_traits>
#include <cmath>
#include "int_mult.hpp"

template<typename Int_t, int scale>
struct scaled_int
{
public:
  scaled_int(Int_t input)
    : m_value(input)
  {}

  
  scaled_int(float a){
    if constexpr(scale <= 0){
      const float alpha = std::exp2(static_cast<float>(-scale));
      const float a_alpha = a * alpha;
      m_value = std::lround(a_alpha);
    } else {
      const float alpha = std::exp2(static_cast<float>(scale));
      const float a_div_alpha = a/alpha;
      m_value = std::lround(a_div_alpha);      
    }
  }

  

  scaled_int<Int_t, scale>&
  operator+=(const scaled_int<Int_t, scale>& a){
    m_value += a.m_value;
    return *this;
  }
  
  scaled_int<Int_t, scale>&
  operator-=(const scaled_int<Int_t, scale>& a){
    m_value -= a.m_value;
    return *this;
  }

  template<int scale_2>
  scaled_int<Int_t, scale>&
  operator*=(const scaled_int<Int_t, scale_2>& a){
    static_assert(scale_2 <= scale);
    using uSigned_t = std::make_unsigned_t<Int_t>;
    //uconstexpr int N = std::numeric_limits<uSigned_t>::digits();
    
    m_value = intMul<Int_t,1>(m_value,a.m_value);
    return *this;
  }


  Int_t m_value;
  
};

template<typename Int_t, int scale, typename char_t, class traits>
std::basic_ostream<char_t, traits>&
operator<<(std::basic_ostream<char_t, traits>& os, const scaled_int<Int_t,scale>& x){
  std::basic_ostringstream<char_t, traits> s;
  s.flags(os.flags());
  s.imbue(os.getloc() );
  s << x.m_value << "* 2^" << scale;
  return os << s.str();
}

// template<typename Int_t, int scale_1, int scale_2>
// scaled_int<Int_t, std::min(scale_1,scale_2)>
// scaled_int<Int_t,scale_1>::operator*(const scaled_int<Int_t, scale_2>& t){
//   scaled_int<Int_t, std::min(scale_1, scale_2)> ret;
//   ret.m_value = 0;
//   return ret;
// }


  

#endif
