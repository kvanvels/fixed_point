#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <cassert>
#include <limits>

template<typename uInt_t>
uInt_t
mask(unsigned start, unsigned stop){

  const auto diff = stop - start;
  constexpr auto N = std::numeric_limits<uInt_t>::digits;
  assert(stop <= N);
  assert(start <= stop);
  const uInt_t all = std::numeric_limits<uInt_t>::max();
  const auto mask1 = (all >> (N-diff)) << start;
  return mask1;
  
}

template<typename Int_t>
std::pair<Int_t, std::make_unsigned_t<Int_t> >
shift2(Int_t a_h, std::make_unsigned_t<Int_t> a_l, unsigned shift){
  using uInt_t = std::make_unsigned_t<Int_t>;
  static constexpr auto N = std::numeric_limits<uInt_t>::digits;
  a_l >>= shift;
  const uInt_t mask0 = mask<uInt_t>(0,shift);
  Int_t a_h_LSB = a_h & static_cast<Int_t>(mask0);
  a_h_LSB <<= (N-shift);
  a_h >>= shift;
  a_l |= static_cast<uInt_t>(a_h_LSB);

  return std::make_pair(a_h,a_l);
}


template<typename Int_t>
std::tuple<Int_t, std::make_unsigned_t<Int_t>, std::make_unsigned_t<Int_t> >
split(Int_t a_h, std::make_unsigned_t<Int_t> a_l, unsigned shift){
  using uInt_t = std::make_unsigned_t<Int_t>;
  constexpr unsigned N = std::numeric_limits<uInt_t>::digits;
  //assert(shift
  const uInt_t mask0 = mask<uInt_t>(N-shift,N);
  const uInt_t mask1 = ~mask0;
  Int_t upper = static_cast<Int_t>(mask0) & a_h;
  Int_t middle_upper = static_cast<Int_t>(mask1) & a_h;
  middle_upper <<= shift;
  uInt_t middle_lower = a_l & mask0;
  middle_lower >>= N-shift;
  uInt_t middle = middle_lower | middle_upper;  
  uInt_t lower = mask1 & a_l;
  return std::make_tuple(upper, middle, lower);
  
}


// template<typename Int_t>
// Int_t
// shift_pair(Int_t a_h, std::make_unsigned_t<Int_t> a_l, int shift){
//   using uInt_t = std::make_unsigned_t<Int_t>;
//   constexpr unsigned N = std::numeric_limits<uInt_t>::digits;
//   assert(std::abs(shift) <= N);

//   if(shift >= 0){
//     if(a_h < Int_t(-1)){
//       return std::numeric_limits<Int_t>::min();
//     } else if (a_h == Int_t(-1) ){
//       const uInt_t mask0 = mask<uInt_t>(N-shift-1,N);
//       std::cout << "mask0 = "
// 		<< static_cast<std::bitset<8> >(mask0) << std::endl;
//       if(a_l < mask0){
// 	return std::numeric_limits<Int_t>::min();
//       } else {
// 	a_l <<= shift;
// 	return static_cast<Int_t>(a_l);
//       }
//     } else if (a_h == Int_t(0)) {
//       const uInt_t mask1 = mask<uInt_t>(0,N-shift-1);
//       std::cout << "mask1 = "
// 		<< static_cast<std::bitset<8> >(mask1) << std::endl;
//       if(a_h > mask1){
// 	return std::numeric_limits<Int_t>::max();
//       } else {
// 	a_l <<= shift;
// 	return static_cast<Int_t>(a_l);
//       }
//     }  else {
//       assert(a_h > 0);
//       return std::numeric_limits<Int_t>::max();
//     }
    
    
//   }else {    
//     assert(shift < 0);
//     if(a_h > Int_t(0) ){
//       if(a_h > mask<Int_t>(0,-shift)
//     } else  {
//       assert(false);
//       return 0;
//     }
    
//   }
// }

#endif
