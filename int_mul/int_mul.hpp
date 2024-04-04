#ifndef INT_MULL_HPP
#define INT_MULL_HPP

#include <cstdint>



template<unsigned N>
std::int16_t
together(std::int16_t ms, std::uint16_t ls){
  const auto mymask = mask<16,16-N,std::uint16_t>::value;
  ms <<= N;
  std::uint16_t ls_masked = ls & mymask;
  ls_masked >>= (16-N);
  ms += ls_masked;
  return ms;
}


  

#endif
