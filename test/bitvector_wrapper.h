#include <stdexcept>
#include <string>
extern "C" {
#include "bitvector.h"
}

using namespace std;

class BitvectorWrapper {
  struct bitvector bitvector_;

  void destroy_bitvector() {
    int err = clean_bitvector(&bitvector_);
    if (err)
      throw runtime_error("There was an error during destruction " +
                          to_string(err));
  }

public:
  BitvectorWrapper(uint32_t bitvector_size) {
    int err = init_bitvector(&bitvector_, bitvector_size);
    if (err)
      throw runtime_error("There was an error during initialization " +
                          to_string(err));
  }

  ~BitvectorWrapper() { destroy_bitvector(); }

  uint32_t size() { return bitvector_.size_in_bits; }
  uint32_t container_size() { return bitvector_.container_size; }

  void bitset(uint32_t position) {
    int err = bit_set(&bitvector_, position);
    if (err)
      throw runtime_error("There was an error during bitset " + to_string(err));
  }

  bool bitread(uint32_t position) {
    int result;
    int err = bit_read(&bitvector_, position, &result);
    if (err)
      throw runtime_error("there was an error during bitread " +
                          to_string(err));

    return result;
  }

  void bitswrite(uint32_t from, uint32_t to, uint32_t to_write) {
    int err = bits_write(&bitvector_, from, to, to_write);
    if (err)
      throw runtime_error("there was an error during bitswrite " +
                          to_string(err));
  }

  uint32_t bitsread(uint32_t from, uint32_t to) {
    uint32_t result;
    int err = bits_read(&bitvector_, from, to, &result);
    if (err)
      throw runtime_error("there was an error during bitsread " +
                          to_string(err));

    return result;
  }
};
