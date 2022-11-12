#include "hexl/hexl.hpp"
#include "include/ntt-wrapper.h"

extern "C" {
  NTTWrapper* newNTT(uint64_t degree, uint64_t q){
    return reinterpret_cast<NTTWrapper*>(new intel::hexl::NTT(degree, q));
  }

  void deleteNTT(NTTWrapper* v) {
     delete reinterpret_cast<intel::hexl::NTT*>(v);
  }

  uint64_t GetModulus(NTTWrapper* v) {
    intel::hexl::NTT* myNTT = reinterpret_cast<intel::hexl::NTT*>(v);
    return myNTT->GetModulus();
  }
}