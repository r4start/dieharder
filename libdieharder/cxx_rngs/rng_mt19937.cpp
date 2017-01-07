#include <limits>
#include <random>

#include <cstdint>

#include "rng_mt19937.h"

namespace {

class mt19937_generator {
public:
  mt19937_generator() : generator_{0xdeadbeef} {}

  std::mt19937::result_type operator()();

private:
  std::mt19937 generator_;
  std::uniform_int_distribution<> dist_;
};

std::mt19937::result_type mt19937_generator::operator()() {
  return dist_(generator_);
}


class bad_mt19937_generator {
public:
  bad_mt19937_generator() : generator_{0xdeadbeef} {}

  std::mt19937::result_type operator()();

private:
  std::mt19937 generator_;
};

std::mt19937::result_type bad_mt19937_generator::operator()() {
  std::uniform_int_distribution<> dist;
  generator_.discard(3000);
  return dist(generator_);
}

} // namespace

extern "C" {

unsigned long int mt19937_get(void *vstate) {
  if (vstate == nullptr) {
    return 0;
  }

  mt19937_state_t *rng_state = static_cast<mt19937_state_t *>(vstate);
  try {
    mt19937_generator *generator =
        static_cast<mt19937_generator *>(rng_state->rng_class);
    if (generator == nullptr) {
      return 0;
    }

    return (*generator)();
  } catch (const std::exception &) {
  }

  return 0;
}

double mt19937_get_double(void *vstate) {
  return static_cast<double>(mt19937_get(vstate)) /
         static_cast<double>(std::numeric_limits<unsigned long int>::max() >>
                             0);
}

void mt19937_set(void *vstate, unsigned long int s) {
  if (vstate == nullptr) {
    return;
  }

  mt19937_state_t *rng_state = static_cast<mt19937_state_t *>(vstate);
  try {
    mt19937_generator *generator =
        static_cast<mt19937_generator *>(rng_state->rng_class);
    if (rng_state->rng_class != nullptr) {
      delete generator;
    }

    generator = new mt19937_generator;

    rng_state->rng_class = generator;
  } catch (const std::exception &) {
  }
}

unsigned long int bad_mt19937_get(void *vstate) {
  if (vstate == nullptr) {
    return 0;
  }

  mt19937_state_t *rng_state = static_cast<mt19937_state_t *>(vstate);
  try {
    bad_mt19937_generator *generator =
        static_cast<bad_mt19937_generator *>(rng_state->rng_class);
    if (generator == nullptr) {
      return 0;
    }

    return (*generator)();
  } catch (const std::exception &) {
  }

  return 0;
}

double bad_mt19937_get_double(void *vstate) {
  return static_cast<double>(bad_mt19937_get(vstate)) /
         static_cast<double>(std::numeric_limits<unsigned long int>::max() >>
                             0);
}

void bad_mt19937_set(void *vstate, unsigned long int s) {
  if (vstate == nullptr) {
    return;
  }

  mt19937_state_t *rng_state = static_cast<mt19937_state_t *>(vstate);
  try {
    bad_mt19937_generator *generator =
        static_cast<bad_mt19937_generator *>(rng_state->rng_class);
    if (rng_state->rng_class != nullptr) {
      delete generator;
    }

    generator = new bad_mt19937_generator;

    rng_state->rng_class = generator;
  } catch (const std::exception &) {
  }
}

} // extern "C"
