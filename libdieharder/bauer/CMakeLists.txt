set(BAUER_SOURCES
  rijndael-alg-fst.c
  rng_aes.c
  rng_threefish.c
  skein_block64.c
  skein_block_ref.c)

add_library(bauer STATIC ${BAUER_SOURCES})