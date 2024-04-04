#include <iostream>
#include "scaled_int.hpp"
#include "temp.hpp"



int main()
{
  for(std::int8_t a_h= -128; ;){
    for(std::uint8_t a_l = 0; ;){
      std::int16_t A = together(a_h,a_l);
      //std::cout << "A = " << A << std::endl;
      std::pair<std::int8_t, std::uint8_t> ahal = split(A);
      assert(ahal.first == a_h);
      assert(ahal.second == a_l);
      if(a_l == std::numeric_limits<std::uint8_t>::max() ) break;
      ++a_l;
    }
    if(a_h == std::numeric_limits<std::int8_t>::max() ) break;
    ++a_h;
  }
  for(std::int16_t A = std::numeric_limits<std::int16_t>::min(); ;){
    //std::cout << "A = " << A << '\n';
    const auto myPair = split(A);
    {
      const auto AA = together(myPair.first, myPair.second);
      assert(A == AA);
    }
    int shift = -6;
    const std::int8_t A_shifted = dumb_shift(myPair.first,myPair.second,shift);
    const std::int8_t A_clamp = clamp(A,shift);

    std::cout << "A_shifted = " << static_cast<int>(A_shifted) << std::endl;

    //std::cout << "A_clamp = " << A_clamp << std::endl;
    assert(A_shifted == A_clamp);

    if(A == std::numeric_limits<std::int16_t>::max() ){ break; }
    ++A;
  }
  
  // //scaled_int<int,-15> a(100);
  // //scaled_int<int,-15> b(100);
  // int8_t ah = int8_t(-1);
  // std::cout << "ah  = " << static_cast<std::bitset<8> >(ah) << std::endl;
  // for(int8_t ah = -1; ah < 1; ++ah){
  //   std::cout << "ah = " << static_cast<int>(ah) << std::endl;
  //   for(uint8_t al = 0; ;){
  //     auto res = from_pair<int8_t,0>(ah,al);
  //     //std::cout << "al  = " << static_cast<std::bitset<8> >(al) << std::endl;
  //     std::cout << "res = " << static_cast<int>(res) << std::endl;
  //     //if(al == 10) break;
  //     if(al == 255) break;
  //     ++al;
  //   }
  // }


  // scaled_int<int,3> b(2.0f);
  // std::cout << "b = " << b << std::endl;

  return 0;
}
