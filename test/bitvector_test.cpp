#include <gtest/gtest.h>

#include "bitvector_wrapper.h"


#include <iostream>
#include <string>

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


TEST(borders_test, test1){

    string input_ = "11111111111111111111111111111111111111111111110011111111110011111111";
    BitvectorWrapper some_bitvector(input_.size());
    for(int i = 0; i < some_bitvector.size(); i++){
      if(input_[i] == '1')
        some_bitvector.bitset(i);
    }


    uint32_t portion = some_bitvector.bitsread(56, 67);
    ASSERT_EQ(3327, portion);
}
