#include <iostream>
#include <cstdint>
#include <random>

#include "fixed.hpp"



int main(){
  //char a = 25;
  //char b = 75;  

  //unsigned char blow = intLow(b);
  //char bHigh = intHigh(b);
  // std::cout << "b = " << static_cast<int>(b) << std::endl;
  // std::cout << "blow = " << static_cast<unsigned>(blow) << std::endl;
  // std::cout << "bHigh = " << static_cast<int>(bHigh) << std::endl;
  //assert(b == blow + (bHigh << 4));
  // for(char aa = -128; aa < 125; ++aa){
  //   std::cout << std::endl << std::endl;
  //   std::cout << "aa = " << static_cast<int>(aa) << std::endl;
  //    unsigned char alow = intLow(aa);
  //    std::cout << "alow = " << static_cast<unsigned>(alow) << std::endl;
  //    char aHigh = intHigh(aa);
  //    std::cout << "aHigh = " << static_cast<int>(aHigh) << std::endl;
  //    std::cout << "aHigh_shifted = "
  // 	       << static_cast<int>(aHigh << 4) << std::endl;
  //    assert(aa == alow + (aHigh << 4));
  // }

  //std::cout << "a = " << static_cast<int>(a) << std::endl;
  //std::cout << "b = " << static_cast<int>(b) << std::endl;
  for(int B = -128; B < 128; ++B){
    //std::cout << "   B = " << B << std::endl;
    for(int A = -128; A < 128; ++A){
      //std::cout << "A = " << A << std::endl;
    //A = 73;
    const char a = static_cast<char>(A);



      //B = -56;
      const char b = static_cast<char>(B);
      
      
      
      auto myPair = myMult(a,b);
      
      //std::cout << "myPair.first = "
      //<< static_cast<int>(myPair.first) << std::endl;
      const auto LS = static_cast<unsigned>(myPair.first);
      const auto MS = static_cast<int>(myPair.second);

      //std::cout << "myPair.second = "
      //<< static_cast<int>(myPair.second) << std::endl;

  
      const int AB = A * B;
      // std::cout << "AB = " << AB << std::endl;

      // std::cout << "LS = " << LS << std::endl;
      // std::cout << "MS = " << MS << std::endl;
      // std::cout << "LS + 256 * MS = "
      // 		<< static_cast<int>(LS) + static_cast<int>((256 * MS))
      // 		<< std::endl;
      assert(LS + 256*MS == AB);
      // const auto ABShifted = shift(myPair,2);
      // std::cout << "ABShifted = "
      // 		<< static_cast<int>(ABShifted) << std::endl;
      
    }
    
  }

  // for(int A = -32; A < 32; ++A){
  //   std::cout << "A = " << A << std::endl;
  //   for(unsigned B = 0; B < 256; ++B){

  //     //std::cout << std::endl;
  //     // A = -32;
  //     // B = 101;
  //     const char a = static_cast<char>(A);
  //     const unsigned char b = static_cast<unsigned char>(B);
  //     //std::cout << "a = " << static_cast<int>(a) << std::endl;
  //     //std::cout << "b = " << static_cast<unsigned>(b) << std::endl;
      
  //     const int AB = B + 256 * A;
  //     //std::cout << "B: AB = " << B << std::endl;

      
  //     //std::cout << "AB = " << AB << std::endl;
  //     const int ABShift2 = AB << 2;
      
  //     const std::pair<unsigned char, char> myPair(b,a);
  //     const auto ABShifted = shift2(myPair,2);
  //     const unsigned LS = ABShifted.first;
  //     const int MS = ABShifted.second;
  //     //std::cout << "LS = " << LS << std::endl;
  //     //std::cout << "MS = " << MS << std::endl;
  //     //std::cout << "LS + 256*MS = " << static_cast<int>(LS + 256 * MS) << std::endl;
  //     //std::cout << "ABShift2 = " << ABShift2 << std::endl;
  //     assert(ABShift2 == LS + 256*MS);

  //   }
  // }

  std::default_random_engine e1(0);
  std::uniform_int_distribution<char> int_dist(-127,127);
  //std::uniform_int_distribution<char> int_dist2(-12,120);
    
  //std::uniform_int_distribution<char> int_dist76(-64,64);
  
  //std::uniform_int_distribution<unsigned char> unsigned_dist(0,15);
  
  for(int n = 0; n < 1000000; ++n){

    char a = int_dist(e1);
    a = -128;
    unsigned char alow = intLow(a);
    char aHigh = intHigh(a);
    const char b = int_dist(e1);
    unsigned char blow = intLow(b);
    char bHigh = intHigh(b);
    

    
    //bhigh = 6;
    //bhigh = -5;
    //std::cout << "alow = " << static_cast<unsigned>(alow) << '\n';
    //std::cout << "ahigh = " << static_cast<int>(ahigh) << '\n';
    //    const char a = ((char) alow) + (16 * ahigh);
    std::cout << "a = " << static_cast<int>(a) << std::endl;
    
    //std::cout << "blow = " << static_cast<unsigned>(blow) << '\n';
    //std::cout << "bhigh = " << static_cast<int>(bhigh) << '\n';
    //const char b = ((char) blow) + (16 * bhigh);
    std::cout << "b = " << static_cast<int>(b) << std::endl;
    int ab = ((int) a) * ((int) b);
    //std::cout << "ab = " << ab << std::endl;
    const auto pair = myMult(a,b);
    const auto LS = pair.first;
    const auto MS = pair.second;
    //std::cout << "LS = " << static_cast<unsigned>(LS) << std::endl;
    //std::cout << "MS = " << static_cast<int>(MS) << std::endl;
    const int Z = ((int) LS) + (256 * ((int) MS));
    //std::cout << "LS + 256 * MS = " << Z << std::endl;

    assert(Z == ab);
    const char ZZ = shift(pair,1);
    int ab_shifted = ab >> 7;
    const unsigned mask = (1 << 5);
    //std::cout << "mask = " << static_cast<std::bitset<16>>(mask) << std::endl;
    // if(mask & ab){
    //   std::cout << "HERE\n";
    //   ++ab_shifted;
    // }
    //std::cout << "ZZ = " << static_cast<int>(ZZ) << std::endl;
    //std::cout << "ab_shifted = " << ab_shifted << std::endl;
    assert(((int) ZZ ) == ab_shifted );
    //assert(false);
  }
  

  return 0;

}
