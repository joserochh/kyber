#ifndef __NTT_WRAPPER_H   /* Include guard */
#define __NTT_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NTTWrapper NTTWrapper;

NTTWrapper* newNTT(uint64_t degree, uint64_t q);

void deleteNTT(NTTWrapper* v);

uint64_t GetModulus(NTTWrapper* v);

#ifdef __cplusplus
}
#endif

#endif // NTT_WRAPPER_H_