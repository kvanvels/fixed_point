#ifndef MASK_HPP
#define MASK_HPP


template<typename Int_t>
constexpr Int_t
mask_base(unsigned m){
  if(m == 0) return 0;
  else return 2*mask_base<Int_t>(m-1) + 1;
}

template<typename Int_t>
constexpr Int_t
mask(unsigned start, unsigned stop){
  if(start == 0) return mask_base<Int_t>(stop);
  return 2 * mask<Int_t>(start-1,stop-1);
}

#endif
