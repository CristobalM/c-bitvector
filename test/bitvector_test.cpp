#include <gtest/gtest.h>

#include "bitvector_wrapper.h"


#include <iostream>

using namespace std;

TEST(some_bitvector_test_s, test1){
  BitvectorWrapper some_bitvector(8);

  some_bitvector.bitset(0);
  some_bitvector.bitset(1);
  some_bitvector.bitset(2);

  bool bitread_0 =  some_bitvector.bitread(0);
  uint32_t bits_read_ = some_bitvector.bitsread(0, 7);

  cout << "bitvector bits " << some_bitvector.size() << endl;
  cout << "bitvector size " << some_bitvector.container_size() << endl;
  cout << "bitvector read " << bits_read_<< endl;
  

  ASSERT_TRUE(bitread_0) << "0 failed";
  ASSERT_TRUE(some_bitvector.bitread(1)) << "1 failed";
  ASSERT_TRUE(some_bitvector.bitread(2)) << "2 failed";
  ASSERT_FALSE(some_bitvector.bitread(3)) << "3 failed";
  ASSERT_FALSE(some_bitvector.bitread(4)) << "4 failed";
  ASSERT_FALSE(some_bitvector.bitread(5)) << "5 failed";
  ASSERT_FALSE(some_bitvector.bitread(6)) << "6 failed";
  ASSERT_FALSE(some_bitvector.bitread(7)) << "7 failed";
}


TEST(fills1000, test1){
    BitvectorWrapper some_bitvector(1000);

    for(int i = 0; i < 10; i++){
      some_bitvector.bitset(i);
    }

    for(int i = 0; i < 10; i++){
      ASSERT_TRUE(some_bitvector.bitread(i));
    }

    for(int i = 10; i < 1000; i++){
      ASSERT_FALSE(some_bitvector.bitread(i));
    }

}


TEST(prints100, test1){
    BitvectorWrapper some_bitvector(100);

    for(int i = 0; i < 10; i++){
      some_bitvector.bitset(i);
    }

    for(int i = 0; i < 100; i++){
      cout << some_bitvector.bitread(i) ? 1 : 0;
    }
    cout << endl;

    }
