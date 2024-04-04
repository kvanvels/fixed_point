#ifndef TEMP_HPP
#define TEMP_HPP

std::pair<std::int8_t, std::uint8_t>
split(std::int16_t in){
  constexpr std::uint16_t unsigned_mask_LSB
    = std::numeric_limits<std::uint16_t>::max() >> std::uint8_t(8);

  //std::cout << "unsigned_mask_LSB = " << unsigned_mask_LSB << std::endl;
  constexpr std::uint16_t unsigned_mask_MSB
    = ((std::numeric_limits<std::uint16_t>::max() >> std::uint8_t(8))
       << std::uint8_t(8) );
  //std::cout << "unsigned_mask_LSB = " << unsigned_mask_MSB << std::endl;
  
  constexpr std::int16_t signed_mask_LSB =
    static_cast<std::int16_t>(unsigned_mask_LSB);
  constexpr std::int16_t signed_mask_MSB
    = static_cast<std::int16_t>(unsigned_mask_MSB);
  
  std::uint8_t lsb = static_cast<std::uint8_t>(in & signed_mask_LSB);
  auto msb = static_cast<std::uint8_t>((in & signed_mask_MSB) >> 8);
  return std::make_pair(msb,lsb);
}
  
std::int16_t
together(std::int8_t a_h, std::uint8_t a_l){
  std::int16_t result = a_h;
  result <<= 8;
  result |= a_l;
  return result;
}




std::int8_t
dumb_shift(std::int8_t a_h, std::uint8_t a_l, int shift){
  std::int16_t A = together(a_h,a_l);
  assert(shift > -15);
  assert(shift < 15);
  constexpr std::int8_t int_MAX = std::numeric_limits<std::int8_t>::max();
  constexpr std::int8_t int_MIN = std::numeric_limits<std::int8_t>::min();
  if(shift <= 0){
    shift = -shift;
    A >>= shift;
    const auto myPair = split(A);
    if(myPair.first > 0){      
      return int_MAX;
    } else if(myPair.first == 0){

      if (myPair.second > static_cast<std::uint8_t>(int_MAX)) {
	return int_MAX;
      } else {
	return static_cast<std::int8_t>(myPair.second);
      }
    } else if (myPair.first == std::int8_t{-1}) {
      if(myPair.second < static_cast<std::uint8_t>(int_MIN)){
	return int_MIN;
      } else {
	return static_cast<std::int8_t>(myPair.second);
      }
    } else if (myPair.first < std::int8_t{-1} ){
      return int_MIN;
    }
  } else {
    return 0;
  }
  return 0;
}

std::int8_t
clamp(std::int16_t A, int shift){
  if(shift < 0){
    shift = -shift;
  }
  (A >>= shift);
  if(A >= static_cast<std::int16_t>(std::numeric_limits<std::int8_t>::max() ) ){
    return std::numeric_limits<std::int8_t>::max();
  } else if (A <= static_cast<std::int16_t>(std::numeric_limits<std::int8_t>::min() ) ){
    return std::numeric_limits<std::int8_t>::min();
  } else {
    return static_cast<std::int8_t>(A);
  }
  
}

    


#endif
