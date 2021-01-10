#include<iostream>
#include<gtest/gtest.h>

int main(int argc, char** argv) {
  std::cout << "\n RUNNING PAPILLON UNIT TESTS\n\n"; 

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
