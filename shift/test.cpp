#include <iostream>
#include <bitset>
#include <tuple>
#include <random>
#include "shift.hpp"


int
main(){
  std::default_random_engine e1(0);
  std::uniform_int_distribution<std::int8_t> int_dist(-128,127);
  std::uniform_int_distribution<std::uint8_t> uInt_dist(0,255);
  for(int i = 0; i < 100; ++i){    
    std::uint8_t a_l = uInt_dist(e1);
    std::int8_t a_h = int_dist(e1);
    auto myTuple = split(a_h,a_l,7);
    std::cout << static_cast<std::bitset<8> >(a_h) << static_cast<std::bitset<8> > (a_l) << std::endl;
    std::cout << static_cast<std::bitset<8> >(std::get<0>(myTuple) ) << std::endl;
    std::cout << "       " << static_cast<std::bitset<8> >(std::get<1>(myTuple)) << std::endl;
    std::cout << "        " << static_cast<std::bitset<8> >(std::get<2>(myTuple) ) << std::endl;
  }
  return 0;
}
