#include <stdio.h>

#include <bitvector.h>

// Dont want to pollute the header file with this, so it is duplicated
#define SAFE_OP(op)                                                            \
  do {                                                                         \
    if ((op) != SUCCESS_ECODE) {                                               \
      printf("There was an error while running %s. Error code: %d\n", (#op),   \
             (op));                                                            \
      return (op);                                                             \
    }                                                                          \
  } while (0)

int print_bitvector(struct bitvector *input_bitvector) {
  for (int i = 0; i < (int)input_bitvector->size_in_bits; i++) {
    int result;
    SAFE_OP(bit_read(input_bitvector, i, &result));
    if (result < 0) {
      printf("There was an error reading the bit at position %d\n", i);
      return result;
    }
    int printable_bitread = result > 0 ? 1 : 0;
    printf("%i", printable_bitread);
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv) {
  struct bitvector some_bitvector;
  uint32_t bv_size = 8;

  SAFE_OP(init_bitvector(&some_bitvector, bv_size));

  printf("The bitvector was initialized with size of %u\n", bv_size);

  printf("BEFORE FILLING WITH ONES\n");
  SAFE_OP(print_bitvector(&some_bitvector));

  for (int i = 0; i < some_bitvector.size_in_bits; i++) {
    SAFE_OP(bit_set(&some_bitvector, (uint32_t)i));
  }
  printf("AFTER FILLING WITH ONES\n");
  SAFE_OP(print_bitvector(&some_bitvector));

  SAFE_OP(bit_clear(&some_bitvector, 2));

  printf("AFTER CLEARING the third\n");
  SAFE_OP(print_bitvector(&some_bitvector));

  printf("%u\n", some_bitvector.container[0]);

  SAFE_OP(bits_write(&some_bitvector, 0, 7, 0));
  printf("AFTER bitswrite from 0 to 7\n");
  SAFE_OP(print_bitvector(&some_bitvector));

  SAFE_OP(bits_write(&some_bitvector, 1, 3, 7));
  printf("AFTER bitswrite of 7 from 1 to 3\n");
  SAFE_OP(print_bitvector(&some_bitvector));

  uint32_t bits_read_result = -1;
  SAFE_OP(bits_read(&some_bitvector, 1, 3, &bits_read_result));
  printf("The results of bitsread is %u\n", bits_read_result);

  // WRITE NOTHING AFTER THIS
  SAFE_OP(clean_bitvector(&some_bitvector));
  printf("The bitvector was cleaned\n");

  return 0;
}