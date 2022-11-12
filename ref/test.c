#include <stdint.h>
#include <stdio.h>
#include "params.h"
#include "ntt-test.h"

int main()
{

  NTTWrapper* myNTT = newNTT(1048, 7);
  uint64_t modulus = GetModulus(myNTT);

  printf("Rocha: %ld\n", modulus);

  return 0;
}
