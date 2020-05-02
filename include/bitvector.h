#ifndef _BITVECTOR_H_
#define _BITVECTOR_H_

#include <stdint.h>
#include <stdio.h>

#define SUCCESS_ECODE 0
#define ERR_NULL_BITVECTOR -1
#define ERR_NULL_BITVECTOR_CONTAINER -2
#define ERR_OUT_OF_BOUNDARIES -3
#define ERR_BITS_WRITE_FROM_GT_TO -4

typedef uint32_t BVCTYPE;

struct bitvector {
  BVCTYPE *container;
  uint32_t size_in_bits;
  uint32_t container_size;

  uint32_t alloc_tag;
};

int init_bitvector(struct bitvector *input_bitvector, uint32_t size_in_bits_);
int clean_bitvector(struct bitvector *input_bitvector);

int bit_read(struct bitvector *input_bitvector, uint32_t position, int *result);
int bit_set(struct bitvector *input_bitvector, uint32_t position);
int bit_clear(struct bitvector *input_bitvector, uint32_t position);
int bits_write(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
               uint32_t to_write);
int bits_read(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
              uint32_t *result);

#endif /* _BITVECTOR_H_ */
