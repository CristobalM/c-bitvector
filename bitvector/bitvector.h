#ifndef _BITVECTOR_H_
#define _BITVECTOR_H_

#include <stdint.h>

#define CONVERT_BITS_TO_CONTAINER_NUM(bits_num, container_type)                \
  ((bits_num) / sizeof(container_type)) +                                      \
      (((bits_num) % sizeof(container_type)) > 0 ? 1 : 0)

#define SUCCESS_ECODE 0
#define ERR_NULL_BITVECTOR -1
#define ERR_NULL_BITVECTOR_CONTAINER -2
#define ERR_OUT_OF_BOUNDARIES -3
#define ERR_BITS_WRITE_FROM_GT_TO -4

#define BVCTYPE uint32_t
#define BVCTYPE_BITS sizeof(uint32_t) * 8

#define CHECK_BOUNDARIES(input_bitvector, position)                            \
  do {                                                                         \
    if ((position) >= (input_bitvector->size_in_bits)) {                       \
      return ERR_OUT_OF_BOUNDARIES;                                            \
    }                                                                          \
  } while (0)

#define SAFE_OP(op)                                                            \
  do {                                                                         \
    if ((op) != SUCCESS_ECODE) {                                               \
      printf("There was an error while running %s. Error code: %d\n", (#op),   \
             (op));                                                              \
      return (op);                                                             \
    }                                                                          \
  } while (0)

#define BLOCK_INDEX(block_size_in_bits, bit_position)                          \
  ((bit_position) / (block_size_in_bits))

#define POSITION_IN_BLOCK(block_size_in_bits, bit_position)                    \
  ((bit_position) % (block_size_in_bits))

#define BITMASK_FROM_POS_IN_BLOCK(pos_in_block) (1 << (31 - (pos_in_block)))

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