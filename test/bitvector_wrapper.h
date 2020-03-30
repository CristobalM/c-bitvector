#include <stdexcept>
extern "C"{
#include "bitvector.h"
}

using namespace std;

class BitvectorWrapper{
  struct bitvector bitvector_;

  void destroy_bitvector(){
    int err = clean_bitvector(&bitvector_);
    if(err)
      throw runtime_error("There was an error during destruction " + err);
  }


  public:

  BitvectorWrapper(uint32_t bitvector_size){
    int err = init_bitvector(&bitvector_, bitvector_size);
    if(err)
      throw runtime_error("There was an error during initialization " + err);
  }

  ~BitvectorWrapper(){
    destroy_bitvector();
  }


  uint32_t size(){
    return bitvector_.size_in_bits;
  }
  uint32_t container_size(){
    return bitvector_.container_size;
  }


  void bitset(uint32_t position){
    int err = bit_set(&bitvector_, position);
    if(err)
      throw runtime_error("There was an error during bitset " + err);
  }

  bool bitread(uint32_t position){
    int err = bit_read(&bitvector_, position);
    if(err < 0)
      throw runtime_error("there was an error during bitread " + err);

    return !!err;
  }

  void bitswrite(uint32_t from, uint32_t to, uint32_t to_write){
    int err = bits_write(&bitvector_, from, to, to_write);
    if(err)
      throw runtime_error("there was an error during bitswrite " + err);
  }

  uint32_t bitsread(uint32_t from, uint32_t to){
    uint32_t result;
    int err = bits_read(&bitvector_, from, to, &result);
    if(err)
      throw runtime_error("there was an error during bitsread " + err);

    return result;
  }
};
