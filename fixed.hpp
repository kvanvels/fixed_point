#ifndef FIXED_HPP

#include <tuple>
#include <cstdint>
#include <bitset>
#include <cassert>


unsigned char
intLow(char a){
  unsigned char ret = 0;
  constexpr auto digs = std::numeric_limits<char>::digits;
  constexpr unsigned char mask = (1 << ((digs+1)/2))-1;
  //std::cout << "a = " << static_cast<std::bitset<8>>(a) << std::endl;
  //std::cout << "mask = " << static_cast<std::bitset<8>>(mask) << std::endl;
  ret = mask & a;
  //std::cout << "ret = " << static_cast<std::bitset<8>>(ret) << std::endl;

  return ret;
}

unsigned char
unsignedLow(unsigned char a){
  //std::cout << "Here\n";
  //std::cout << "a = " << static_cast<std::bitset<8> >(a) << std::endl;
  unsigned char ret;
  constexpr auto digs = std::numeric_limits<char>::digits +1;
  //std::cout << "digs = " << digs << std::endl;
  const unsigned char  mask = (1 << (digs/2)) -1;
  //std::cout << "mask = " << static_cast<unsigned>(mask) << std::endl;
  ret = mask & a;
  return ret;
}

char
intHigh(char a){
  constexpr auto digs = std::numeric_limits<char>::digits + 1;
  char ret = (a >> (digs/2));

  return ret;
};

unsigned char
unsignedHigh(unsigned char a){
  constexpr auto digs = std::numeric_limits<char>::digits + 1;
  return (a >> (digs/2));
};


std::pair<unsigned char,char>
myMult(char x, char y){
  //std::cout << "Here\n";
  //  std::cout << "x = " << static_cast<int>(x) << std::endl;
  const unsigned char xlow = intLow(x);
  const char xhigh = intHigh(x);
  //std::cout << "xlow = " << static_cast<unsigned>(xlow) << std::endl;
  //  std::cout << "xhigh = " << static_cast<int>(xhigh) << std::endl;
  //std::cout << "xhigh << 4 = " << static_cast<int>(xhigh << 4) << std::endl;

  assert(x == xlow + (xhigh <<4));
  
  const unsigned char ylow = intLow(y);
  //  std::cout << "ylow = " << static_cast<unsigned>(ylow) << std::endl;

  const char yhigh = intHigh(y);
  //std::cout << "yhigh = " << static_cast<int>(yhigh) << std::endl;
  assert(y == ylow + (yhigh <<4));
  
  const unsigned char xlyl = xlow * ylow;
  //std::cout << "xlyl = " << static_cast<int>(xlyl) << std::endl;
  const unsigned char xlyl_L = unsignedLow(xlyl);
  //std::cout << "xlyl_L = " << static_cast<unsigned int>(xlyl_L) << std::endl;

  const char xlyl_H = unsignedHigh(xlyl);
  //std::cout << "xlyl_H = " << static_cast<int>(xlyl_H) << std::endl;
  assert(xlyl == xlyl_L +(xlyl_H <<4));
  


  const char xlyh = ((char) xlow ) * yhigh;
  const unsigned char xlhy_L = intLow(xlyh);
  const char xlyh_H = intHigh(xlyh);
  assert(xlyh == xlhy_L + (xlyh_H << 4));
  

  const char xhyl = xhigh * ((char) ylow);
  const unsigned char xhyl_L = intLow(xhyl);
  const char xhyl_H = intHigh(xhyl);
  assert(xhyl == xhyl_L + (xhyl_H << 4) );

  const char xhyh = xhigh * yhigh;
  const unsigned char xhyh_L = intLow(xhyh);
  const char xhyh_H = intHigh(xhyh);
  assert(xhyh == xhyh_L + (xhyh_H << 4));

  //first compute the upper half of the  least significant part, since
  //there is room for the carry.

  unsigned char LS = xlyl_H + xlhy_L + xhyl_L;
  const unsigned char LS_carry = unsignedHigh(LS);
  constexpr auto digs = std::numeric_limits<char>::digits + 1;
  LS <<= (digs/2);
  LS += xlyl_L;

  char MS = xhyh_H;
  MS <<= (digs/2);
  MS += xlyh_H;
  MS += xhyl_H;
  MS += xhyh_L;
  MS += LS_carry;

  return std::make_pair(LS,MS);

}

char
shift(std::pair<unsigned char, char> LM, unsigned char n){
  //std::cout << "inside shift2\n";
  constexpr auto MAX = std::numeric_limits<unsigned char>::max();
  const unsigned char LS = LM.first;
  char MS = LM.second;

  //std::cout << "LS = " << static_cast<unsigned>(LS) << std::endl;
  //std::cout << "MS = " << static_cast<int>(MS) << std::endl;
  const unsigned char Mask = MAX - (MAX >> n);


  
  //std::cout << "Mask = " << static_cast<unsigned>(Mask) << std::endl;
  
  const unsigned char carryIn = LS & Mask;
  //std::cout << "carryIn = " << static_cast<unsigned>(carryIn) << std::endl;
  constexpr auto digs = std::numeric_limits<unsigned char>::digits;
  //std::cout << "dig = " << digs << std::endl;
  const unsigned char shift = digs - n;
  //const unsigned char roundMask = (1 <<  (shift - 1));
  // std::cout << "roundMask = " << static_cast<std::bitset<8>>(roundMask) << std::endl;
  
  //const unsigned char roundQ = roundMask & LS;
  const unsigned char carryInShifted = carryIn >> shift;
  //std::cout << "carryInShifted = " << static_cast<unsigned>(carryInShifted) << std::endl;
  
  
  //  std::cout << "shift = " << static_cast<unsigned>(shift) << std::endl;
  //std::cout << "n = " << static_cast<unsigned>(n) << std::endl;
  //std::cout << "before shift: MS = " << static_cast<int>(MS) << std::endl;
  //std::cout << "MS = " << static_cast<std::bitset<8>>(MS) << std::endl;
  MS <<= n;
  //std::cout << "after shift: MS = " << static_cast<int>(MS) << std::endl;
  //std::cout << "MS = " << static_cast<std::bitset<8>>(MS) << std::endl;
  MS += static_cast<char>(carryInShifted);
  //std::cout << "after adding: MS = " << static_cast<int>(MS) << std::endl;
  //std::cout << "MS = " << static_cast<std::bitset<8>>(MS) << std::endl;
  //LS <<= n;
  
  // if(roundQ){
  //   ++MS;
  // }


  return MS;  
}



// std::pair<unsigned char, char>
// shift2(std::pair<unsigned char, char> LM, unsigned n){
//   //std::cout << "inside shift2\n";
//   constexpr auto MAX = std::numeric_limits<unsigned char>::max();
//   const auto LS = LM.first;
//   char MS = LM.second;

//   //std::cout << "LS = " << static_cast<unsigned>(LS) << std::endl;
//   //std::cout << "MS = " << static_cast<int>(MS) << std::endl;
//   const unsigned char Mask = MAX - (MAX >> n);
//   //std::cout << "Mask = " << static_cast<unsigned>(Mask) << std::endl;
  
//   const unsigned char carryIn = LS & Mask;
//   //std::cout << "carryIn = " << static_cast<unsigned>(carryIn) << std::endl;
//   constexpr auto digs = std::numeric_limits<unsigned char>::digits;
//   //std::cout << "dig = " << digs << std::endl;
//   const unsigned char shift = digs - n;
//   const unsigned char carryInShifted = carryIn >> shift;
//   //std::cout << "carryInShifed = " << static_cast<unsigned>(carryInShifted) << std::endl;
  
  
  
//   //std::cout << "before shift: MS = " << static_cast<int>(MS) << std::endl;
//   MS <<= n;
//   //std::cout << "after shift: MS = " << static_cast<int>(MS) << std::endl;
//   MS += static_cast<char>(carryInShifted);
//   //std::cout << "after adding: MS = " << static_cast<int>(MS) << std::endl;
//   //LS <<= n;
  
//   return std::make_pair(LS<< n,MS);

  
// }
  



#define FIXED_HPP
#endif
