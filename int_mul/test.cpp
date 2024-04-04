#include <iostream>
#include <bitset>
#include "int_mul.hpp"

int main(){
  std::cout << "mask = " << (std::bitset<16>) mask_base<4,std::uint16_t>::value
	    << std::endl;


  std::cout << "mask2 = " << (std::bitset<16>) mask<4,0,std::uint16_t>::value
	    << std::endl;

  std::cout << "mask2 = " << (std::bitset<16>) mask<16,12,std::uint16_t>::value
	    << std::endl;
  return 0;
}
