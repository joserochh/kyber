CC ?= /usr/bin/cc
CXX = g++
CFLAGS += -Wall -Wextra -Wpedantic -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
RM = /bin/rm

SOURCES = kex.c kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c
SOURCESKECCAK = $(SOURCES) fips202.c symmetric-shake.c
SOURCESNINETIES = $(SOURCES) sha256.c sha512.c aes256ctr.c symmetric-aes.c
HEADERS = params.h kex.h kem.h indcpa.h polyvec.h poly.h ntt.h cbd.h reduce.c verify.h symmetric.h
HEADERSKECCAK = $(HEADERS) fips202.h
HEADERSNINETIES = $(HEADERS) aes256ctr.h sha2.h

HEXL_INC=-I/home/joserochh/mylibs/include

.PHONY: all speed shared clean

all: \
  test_kyber512 \
  test_kyber768 \
  test_kyber1024 \
  test_kex512 \
  test_kex768 \
  test_kex1024 \
  test_vectors512 \
  test_vectors768 \
  test_vectors1024 \
  test_kyber512-90s \
  test_kyber768-90s \
  test_kyber1024-90s \
  test_kex512-90s \
  test_kex768-90s \
  test_kex1024-90s \
  test_vectors512-90s \
  test_vectors768-90s \
  test_vectors1024-90s



speed: \
	test_speed512 \
  test_speed768 \
  test_speed1024 \
  test_speed512-90s \
  test_speed768-90s \
  test_speed1024-90s

shared: \
  libpqcrystals_kyber512_ref.so \
  libpqcrystals_kyber768_ref.so \
  libpqcrystals_kyber1024_ref.so \
  libpqcrystals_kyber512-90s_ref.so \
  libpqcrystals_kyber768-90s_ref.so \
  libpqcrystals_kyber1024-90s_ref.so \
  libpqcrystals_fips202_ref.so \
  libpqcrystals_aes256ctr_ref.so \
  libpqcrystals_sha2_ref.so

srcs = kex.c kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c fips202.c symmetric-shake.c test_speed.c randombytes.c cpucycles.c speed_print.c
objs = kex.o kem.o indcpa.o polyvec.o poly.o ntt.o cbd.o reduce.o verify.o fips202.o symmetric-shake.o test_speed.o randombytes.o cpucycles.o speed_print.o

integration: hexl-wrapper.o reduce.o ntt-test.o test.o test

#$(objs) : $(srcs)
#	$(CC) $(CFLAGS) -DKYBER_K=2 $< -o $@ -c

hexl-wrapper.o: IntelHEXL/ntt/include/ntt-wrapper.h
	g++  -c IntelHEXL/ntt/ntt-wrapper.cc -o ntt-wrapper.o 

reduce.o: 
	$(CC) $(CFLAGS) -DKYBER_K=2 reduce.c -o reduce.o -c

ntt-test.o: 
	$(CC) $(CFLAGS) -DKYBER_K=2 ntt-test.c -o ntt-test.o -c

test.o: 
	$(CC) $(CFLAGS) test.c -o test.o -c

test : 
	$(CXX) $(HEXL_INC) ntt-wrapper.o reduce.o ntt-test.o test.o -o test -L/home/joserochh/mylibs/lib -lhexl -static




libpqcrystals_fips202_ref.so: fips202.c fips202.h
	$(CC) -shared -fPIC $(CFLAGS) fips202.c -o libpqcrystals_fips202_ref.so

libpqcrystals_aes256ctr_ref.so: aes256ctr.c aes256ctr.h
	$(CC) -shared -fPIC $(CFLAGS) aes256ctr.c -o libpqcrystals_aes256ctr_ref.so

libpqcrystals_sha2_ref.so: sha256.c sha512.c sha2.h
	$(CC) -shared -fPIC $(CFLAGS) sha256.c sha512.c -o libpqcrystals_sha2_ref.so

libpqcrystals_kyber512_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=2 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber512_ref.so

libpqcrystals_kyber768_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=3 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber768_ref.so

libpqcrystals_kyber1024_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=4 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber1024_ref.so

test_kyber512: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=2 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber512 -L/home/joserochh/mylibs/lib -lhexl -static

test_kyber768: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=3 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber768 -L/home/joserochh/mylibs/lib -lhexl -static

test_kyber1024: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=4 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber1024 -L/home/joserochh/mylibs/lib -lhexl -static

test_kex512: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=2 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex512 -L/home/joserochh/mylibs/lib -lhexl -static

test_kex768: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=3 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex768 -L/home/joserochh/mylibs/lib -lhexl -static

test_kex1024: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=4 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex1024 -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors512: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=2 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors512 -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors768: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=3 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors768 -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors1024: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=4 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors1024 -L/home/joserochh/mylibs/lib -lhexl -static

test_speed512: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=2 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed512 -L/home/joserochh/mylibs/lib -lhexl -static

test_speed768: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=3 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed768 -L/home/joserochh/mylibs/lib -lhexl -static

test_speed1024: $(SOURCESKECCAK) $(HEADERSKECCAK) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -DKYBER_K=4 $(SOURCESKECCAK) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed1024 -L/home/joserochh/mylibs/lib -lhexl -static

libpqcrystals_kyber512-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=2 -DKYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber512-90s_ref.so

libpqcrystals_kyber768-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=3 -DKYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber768-90s_ref.so

libpqcrystals_kyber1024-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=4 -DKYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber1024-90s_ref.so

test_kyber512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=2 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber512-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_kyber768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=3 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber768-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_kyber1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kyber.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=4 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kyber.c -o test_kyber1024-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_kex512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=2 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex512-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_kex768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=3 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex768-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_kex1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_kex.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=4 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c test_kex.c -o test_kex1024-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=2 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors512-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=3 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors768-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_vectors1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h test_vectors.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=4 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc test_vectors.c -o test_vectors1024-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_speed512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=2 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed512-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_speed768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=3 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed768-90s -L/home/joserochh/mylibs/lib -lhexl -static

test_speed1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) IntelHEXL/ntt/include/ntt-wrapper.h cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c
	$(CXX) $(CFLAGS) $(HEXL_INC) -D KYBER_90S -DKYBER_K=4 $(SOURCESNINETIES) IntelHEXL/ntt/ntt-wrapper.cc randombytes.c cpucycles.c speed_print.c test_speed.c -o test_speed1024-90s -L/home/joserochh/mylibs/lib -lhexl -static

PQCgenKAT_kem512: $(SOURCESKECCAK) $(HEADERSKECCAK) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=2 -o $@ $(SOURCESKECCAK) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

PQCgenKAT_kem768: $(SOURCESKECCAK) $(HEADERSKECCAK) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=3 -o $@ $(SOURCESKECCAK) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

PQCgenKAT_kem1024: $(SOURCESKECCAK) $(HEADERSKECCAK) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=4 -o $@ $(SOURCESKECCAK) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

PQCgenKAT_kem512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=2 -DKYBER_90S -o $@ $(SOURCESNINETIES) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

PQCgenKAT_kem768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=3 -DKYBER_90S -o $@ $(SOURCESNINETIES) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

PQCgenKAT_kem1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) PQCgenKAT_kem.c rng.c rng.h
	$(CC) $(NISTFLAGS) -DKYBER_K=4 -DKYBER_90S -o $@ $(SOURCESNINETIES) rng.c PQCgenKAT_kem.c $(LDFLAGS) -lcrypto

clean:
	-$(RM) -rf *.gcno *.gcda *.lcov *.o *.so
	-$(RM) -rf ntt-test
	-$(RM) -rf test
	-$(RM) -rf test_kyber512
	-$(RM) -rf test_kyber768
	-$(RM) -rf test_kyber1024
	-$(RM) -rf test_kex512
	-$(RM) -rf test_kex768
	-$(RM) -rf test_kex1024
	-$(RM) -rf test_vectors512
	-$(RM) -rf test_vectors768
	-$(RM) -rf test_vectors1024
	-$(RM) -rf test_speed512
	-$(RM) -rf test_speed768
	-$(RM) -rf test_speed1024
	-$(RM) -rf test_kyber512-90s
	-$(RM) -rf test_kyber768-90s
	-$(RM) -rf test_kyber1024-90s
	-$(RM) -rf test_kex512-90s
	-$(RM) -rf test_kex768-90s
	-$(RM) -rf test_kex1024-90s
	-$(RM) -rf test_vectors512-90s
	-$(RM) -rf test_vectors768-90s
	-$(RM) -rf test_vectors1024-90s
	-$(RM) -rf test_speed512-90s
	-$(RM) -rf test_speed768-90s
	-$(RM) -rf test_speed1024-90s
	-$(RM) -rf PQCgenKAT_kem512
	-$(RM) -rf PQCgenKAT_kem768
	-$(RM) -rf PQCgenKAT_kem1024
	-$(RM) -rf PQCgenKAT_kem512-90s
	-$(RM) -rf PQCgenKAT_kem768-90s
	-$(RM) -rf PQCgenKAT_kem1024-90s
