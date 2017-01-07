#include <dieharder/libdieharder.h>

#include "cxx_rngs/rng_mt19937.h"

static const gsl_rng_type mt19937_type = {"cpp_mt19937", /* name */
                                          UINT_MAX,      /* RAND_MAX */
                                          0,             /* RAND_MIN */
                                          sizeof(mt19937_state_t),
                                          &mt19937_set,
                                          &mt19937_get,
                                          &mt19937_get_double};

const gsl_rng_type *gsl_rng_cpp_mt19937 = &mt19937_type;
