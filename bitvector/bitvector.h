#ifndef _BITVECTOR_H_
#define _BITVECTOR_H_

#include <stdint.h>

#define SUCCESS_ECODE 0
#define ERR_NULL_BITVECTOR -1
#define ERR_NULL_BITVECTOR_CONTAINER -2
#define ERR_OUT_OF_BOUNDARIES -3
#define ERR_BITS_WRITE_FROM_GT_TO -4

#define SAFE_OP(op)                                                            \
  do {                                                                         \
    if ((op) != SUCCESS_ECODE) {                                               \
      printf("There was an error while running %s. Error code: %d\n", (#op),   \
             (op));                                                            \
      return (op);                                                             \
    }                                                                          \
  } while (0)

typedef uint32_t BVCTYPE;

struct bitvector {
  BVCTYPE *container;
  uint32_t size_in_bits;
  uint32_t container_size;
};

int init_bitvector(struct bitvector *input_bitvector, uint32_t size_in_bits_);
int clean_bitvector(struct bitvector *input_bitvector);

int bit_read(struct bitvector *input_bitvector, uint32_t position);
int bit_set(struct bitvector *input_bitvector, uint32_t position);
int bit_clear(struct bitvector *input_bitvector, uint32_t position);
int bits_write(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
               uint32_t to_write);
int bits_read(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
              uint32_t *result);

uint32_t _extract_right_side(uint32_t input_block, uint32_t extract_index);

#endif /* _BITVECTOR_H_ */