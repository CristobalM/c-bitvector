
#include <stdlib.h>
#include <string.h>

#include "bitvector.h"

#define BVCTYPE_BITS sizeof(uint32_t) * 8

#define CONVERT_BITS_TO_CONTAINER_NUM(bits_num, container_type)                \
  ((bits_num) / sizeof(container_type)) +                                      \
      (((bits_num) % sizeof(container_type)) > 0 ? 1 : 0)

#define CHECK_BOUNDARIES(input_bitvector, position)                            \
  do {                                                                         \
    if ((position) >= (input_bitvector->size_in_bits)) {                       \
      return ERR_OUT_OF_BOUNDARIES;                                            \
    }                                                                          \
  } while (0)

#define BLOCK_INDEX(block_size_in_bits, bit_position)                          \
  ((bit_position) / (block_size_in_bits))

#define POSITION_IN_BLOCK(block_size_in_bits, bit_position)                    \
  ((bit_position) % (block_size_in_bits))

#define BITMASK_FROM_POS_IN_BLOCK(pos_in_block) (1 << (31 - (pos_in_block)))

uint32_t _extract_right_side(uint32_t input_block, uint32_t extract_index);

int init_bitvector(struct bitvector *input_bitvector, uint32_t size_in_bits_) {
  if (!input_bitvector)
    return ERR_NULL_BITVECTOR;

  input_bitvector->container_size =
      CONVERT_BITS_TO_CONTAINER_NUM(size_in_bits_, uint32_t);
  input_bitvector->container =
      (uint32_t *)malloc(input_bitvector->container_size * sizeof(uint32_t));
  input_bitvector->size_in_bits = size_in_bits_;

  memset(input_bitvector->container, 0, input_bitvector->container_size);

  return SUCCESS_ECODE;
}

int clean_bitvector(struct bitvector *input_bitvector) {
  if (!input_bitvector)
    return ERR_NULL_BITVECTOR;
  if (!input_bitvector->container)
    return ERR_NULL_BITVECTOR_CONTAINER;

  free(input_bitvector->container);
  input_bitvector->container = NULL;

  return SUCCESS_ECODE;
}

int bit_read(struct bitvector *input_bitvector, uint32_t position) {
  CHECK_BOUNDARIES(input_bitvector, position);

  BVCTYPE *container = input_bitvector->container;

  uint32_t block_index = BLOCK_INDEX(BVCTYPE_BITS, position);
  uint32_t position_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, position);
  uint32_t pos_bitmask = BITMASK_FROM_POS_IN_BLOCK(position_in_block);
  return (int)((pos_bitmask & container[block_index]) > 0 ? 1 : 0);
}

int bit_set(struct bitvector *input_bitvector, uint32_t position) {
  CHECK_BOUNDARIES(input_bitvector, position);
  if (bit_read(input_bitvector, position))
    return SUCCESS_ECODE;

  BVCTYPE *container = input_bitvector->container;

  uint32_t block_index = BLOCK_INDEX(BVCTYPE_BITS, position);
  uint32_t position_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, position);
  uint32_t pos_bitmask = BITMASK_FROM_POS_IN_BLOCK(position_in_block);

  container[block_index] |= pos_bitmask;

  return SUCCESS_ECODE;
}

int bit_clear(struct bitvector *input_bitvector, uint32_t position) {
  CHECK_BOUNDARIES(input_bitvector, position);
  if (!bit_read(input_bitvector, position))
    return SUCCESS_ECODE;

  BVCTYPE *container = input_bitvector->container;

  uint32_t block_index = BLOCK_INDEX(BVCTYPE_BITS, position);
  uint32_t position_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, position);
  uint32_t pos_bitmask = BITMASK_FROM_POS_IN_BLOCK(position_in_block);

  container[block_index] ^= pos_bitmask;

  return SUCCESS_ECODE;
}

uint32_t _extract_right_side(uint32_t input_block, uint32_t extract_index) {
  return input_block & ((1 << extract_index) - 1);
}

int bits_write(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
               uint32_t to_write) {
  CHECK_BOUNDARIES(input_bitvector, from);
  CHECK_BOUNDARIES(input_bitvector, to);
  if (from > to) {
    return ERR_BITS_WRITE_FROM_GT_TO;
  }

  BVCTYPE *container = input_bitvector->container;

  uint32_t right_pos_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, to);

  uint32_t left_block_idx = BLOCK_INDEX(BVCTYPE_BITS, from);
  uint32_t right_block_idx = BLOCK_INDEX(BVCTYPE_BITS, to);

  uint32_t bits_to_write = to - from + 1;

  uint32_t left_block = container[left_block_idx];
  uint32_t right_bits_to_right = BVCTYPE_BITS - right_pos_in_block - 1;

  if (left_block_idx == right_block_idx) {
    uint32_t parts_to_remove_rshift = left_block >> right_bits_to_right;

    uint32_t part_to_remove =
        _extract_right_side(parts_to_remove_rshift, bits_to_write)
        << right_bits_to_right;
    uint32_t part_to_add = to_write << right_bits_to_right;

    container[left_block_idx] += part_to_add - part_to_remove;
  } else {
    uint32_t right_block = container[right_block_idx];
    uint32_t right_block_keep_part =
        _extract_right_side(right_block, right_bits_to_right);
    uint32_t right_extract_to_add =
        _extract_right_side(to_write, right_pos_in_block + 1);
    uint32_t right_part_to_add = right_extract_to_add << right_bits_to_right;
    container[right_block_idx] = right_block_keep_part + right_part_to_add;

    uint32_t to_left_pos_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, from) - 1;
    uint32_t left_bits_to_right = BVCTYPE_BITS - to_left_pos_in_block - 1;
    uint32_t left_block_part_to_remove =
        _extract_right_side(left_block, left_bits_to_right);
    uint32_t left_block_part_to_add = to_write >> (right_pos_in_block + 1);
    container[left_block_idx] =
        left_block - left_block_part_to_remove + left_block_part_to_add;
  }

  return SUCCESS_ECODE;
}

int bits_read(struct bitvector *input_bitvector, uint32_t from, uint32_t to,
              uint32_t *result) {
  CHECK_BOUNDARIES(input_bitvector, from);
  CHECK_BOUNDARIES(input_bitvector, to);
  if (from > to) {
    return ERR_BITS_WRITE_FROM_GT_TO;
  }

  BVCTYPE *container = input_bitvector->container;

  uint32_t right_pos_in_block = POSITION_IN_BLOCK(BVCTYPE_BITS, to);

  uint32_t left_block_idx = BLOCK_INDEX(BVCTYPE_BITS, from);
  uint32_t right_block_idx = BLOCK_INDEX(BVCTYPE_BITS, to);

  if (left_block_idx == right_block_idx) {
    uint32_t block = container[left_block_idx];
    uint32_t block_shifted = block >> (BVCTYPE_BITS - right_pos_in_block - 1);
    uint32_t bits_to_read = to - from + 1;

    *result = _extract_right_side(block_shifted, bits_to_read);
    return SUCCESS_ECODE;
  }

  uint32_t from_pos_in_left_block = POSITION_IN_BLOCK(BVCTYPE_BITS, from) - 1;
  uint32_t right_block = container[right_block_idx];
  uint32_t left_block = container[left_block_idx];

  uint32_t to_shift_right = BVCTYPE_BITS - (right_pos_in_block - 1);
  uint32_t right_block_shifted = right_block >> to_shift_right;

  uint32_t left_shift = right_pos_in_block + 1;
  uint32_t left_block_shifted =
      _extract_right_side(left_block, BVCTYPE_BITS - from_pos_in_left_block - 1)
      << left_shift;

  *result = right_block_shifted + left_block_shifted;
  return SUCCESS_ECODE;
}