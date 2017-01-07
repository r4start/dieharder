set(CXX_RNGS_SOURCES
      rng_mt19937.cpp)

add_library(cxx_rngs STATIC ${CXX_RNGS_SOURCES})
set_target_properties(cxx_rngs PROPERTIES POSITION_INDEPENDENT_CODE ON)
