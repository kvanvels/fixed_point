#ifndef INT_MULT
#define INT_MULT

#include "mask.hpp"
#include <bitset>
#include <limits>
#include <cassert>






template<typename Int_t>
Int_t
upper(Int_t a){
  using uSigned_t = std::make_unsigned_t<Int_t>;
  constexpr int N = std::numeric_limits<uSigned_t>::digits;
  constexpr int Nby2 = N/2;
  return a >> Nby2;
}

template<typename Int_t>
std::make_unsigned_t<Int_t>
lower(const Int_t& a){
  using uSigned_t = std::make_unsigned_t<Int_t>;
  constexpr int N = std::numeric_limits<uSigned_t>::digits;
  constexpr int Nby2 = N/2;
  constexpr Int_t mask
    = static_cast<Int_t>(std::numeric_limits<uSigned_t>::max() >> Nby2);
  return static_cast<uSigned_t> (a & mask);
}

template<typename Int_t, int shift>
Int_t from_pair(const Int_t& a_h, const std::make_unsigned_t<Int_t>& a_l){
  static_assert(std::is_signed_v<Int_t> );
  //std::cout << "shift = " << shift << std::endl;

  using uSigned_t = std::make_unsigned_t<Int_t>;
  constexpr unsigned N = std::numeric_limits<uSigned_t>::digits;
  constexpr uSigned_t mask1 = mask<uSigned_t>(N-shift-1,N);
  constexpr uSigned_t notMask1 = static_cast<uSigned_t>(~mask1);
  //  std::cout << "mask1 = " << static_cast<std::bitset<8> >(mask1) << std::endl;
  //  std::cout << "mask1 = " << static_cast<uSigned >(mask1) << std::endl;
  if constexpr (shift >= int(0)){
    // std::cout << "HERE Line: "
    // 	      <<  __LINE__  << std::endl;
    // std::cout << "a_h = " << static_cast<int >(a_h) << std::endl;
    if(a_h < Int_t(-1)){
      //std::cout << "Not Here __LINE__" << std::endl;
      return std::numeric_limits<Int_t>::min();
    } else if (a_h == Int_t(-1) ){
      //std::cout << "Here" << std::endl;
      if(a_l < mask1){
	//std::cout << "And Here" << std::endl;
 	return std::numeric_limits<Int_t>::min(); }
      else {return static_cast<Int_t>(a_l << shift);}      
    } else if (a_h == Int_t(0) ){
      // std::cout << "a_l = " << static_cast<int>(a_l) << std::endl;
							
      // std::cout << "~mask = "
      // 		<< static_cast<std::bitset<8> >(~mask1) << std::endl;
      if(a_l > notMask1){
	//std::cout << "a_l = " << static_cast<unsigned>(a_l) << std::endl;
	//std::cout << "notMask1 = "
	//<< static_cast<unsigned >(notMask1) << std::endl;

	//std::cout << "Here" << std::endl;
	return std::numeric_limits<Int_t>::max();
      } else {
	return static_cast<Int_t>(a_l << shift);
      }
    } else {
      assert(a_h > Int_t(0) );
      return std::numeric_limits<Int_t>::max();
    }
  } else {
        assert(false);//Not implemented
  }



  return Int_t(0);
}

  // if constexpr (shift >= 0){ 
  //   if (a_h < Int_t(-1)){
  //     return std::numeric_limits<Int_t>::min();
  //   } else if (a_h == Int_t(-1) ){
  //     if(a_l < mask1){ 	return std::numeric_limits<Int_t>::min(); }
  //     else {return static_cast<Int_t>(a_l << shift);}
  //   } else if (a_h == Int_t(0) ){
  //     if(a_l > ~mask1){	return std::numeric_limits<Int_t>::max();}
  //     else {return static_cast<Int_t>(a_h >> shift); }
  //   else {
  //   assert(a_h > Int_t(0));
  //   return std::numeric_limits<Int_t>::max();	
  //   }
  // } else {
  //   assert(false, "Not implemented");
  // }




      
      
	  




template<typename Int_t, unsigned shift>
Int_t intMul(const Int_t& a, const Int_t& b){
  static_assert(std::is_signed_v<Int_t> );
  
  using uSigned_t = std::make_unsigned_t<Int_t>;

  const Int_t a_high = upper(a);
  const Int_t b_high = upper(b);
  const uSigned_t a_low = lower(a);
  const uSigned_t b_low = lower(b);

  const Int_t ahbh = a_high * b_high;
  const Int_t ahbh_h = upper(ahbh);
  const uSigned_t ahbh_l = lower(ahbh);

  const Int_t ahbl = a_high * static_cast<Int_t>(b_low);
  const Int_t ahbl_h = upper(ahbl);
  const uSigned_t ahbl_l = lower(ahbl);

  const Int_t albh = static_cast<Int_t>(a_low) * b_high;
  const Int_t albh_h = upper(albh);
  const uSigned_t albh_l = lower(albh);
  
  const uSigned_t albl = a_low * b_low;
  const uSigned_t albl_h = upper(albl);
  const uSigned_t albl_l = lower(albl);
  //first we want to compute the "carry" from the LSB's
  constexpr int N = std::numeric_limits<uSigned_t>::digits;
  constexpr int Nby2 = N/2;
  uSigned_t prod_lower = albl_h + albh_l + ahbl_l;
  const uSigned_t carry = upper(prod_lower);
  prod_lower <<= N/2;
  prod_lower += albl_l;
  Int_t prod_upper = ahbh;
  prod_upper += static_cast<Int_t>(carry);  
  prod_upper += albh_h;
  prod_upper += ahbl_h;
  
  constexpr uSigned_t myMask = mask<uSigned_t>(N-shift,N);
  constexpr uSigned_t round_mask = mask<uSigned_t>(N-shift-1,N-shift);
  const uSigned_t round_Q = prod_lower & myMask;
  const uSigned_t shift_in = prod_lower & myMask;
  const uSigned_t aligned = shift_in >> (N - shift);
  prod_upper <<= shift;
  prod_upper += static_cast<Int_t>(aligned);
  if(round_Q != 0){
    ++prod_upper;
  }
  return prod_upper;  
}



#endif
