#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

unsigned long int mt19937_get(void *vstate);

double mt19937_get_double(void *vstate);

void mt19937_set(void *vstate, unsigned long int s);


unsigned long int bad_mt19937_get(void *vstate);

double bad_mt19937_get_double(void *vstate);

void bad_mt19937_set(void *vstate, unsigned long int s);


typedef struct { void *rng_class; } mt19937_state_t;

#ifdef __cplusplus
}
#endif // __cplusplus
