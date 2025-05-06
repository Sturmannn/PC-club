#include <gtest/gtest.h>
#include <sstream>

#include "Handler.hpp"

TEST(ComputerClubTest, BasicFunctionality) {
  std::ofstream test_file("../GTest_file.txt");
  test_file << "2\n";
  test_file << "09:00 19:00\n";
  test_file << "10\n";
  test_file << "09:30 1 client1\n";
  test_file << "09:45 2 client1 1\n";
  test_file << "10:00 1 client2\n";
  test_file << "10:15 2 client2 2\n";
  test_file << "12:00 4 client1\n";
  test_file << "18:30 4 client2\n";
  test_file.close();

  std::string expected_output = 
  "09:00\n"
  "09:30 1 client1\n"
  "09:45 2 client1 1\n"
  "10:00 1 client2\n"
  "10:15 2 client2 2\n"
  "12:00 4 client1\n"
  "18:30 4 client2\n"
  "19:00\n"
  "1 30 02:15\n"
  "2 90 08:15\n";

  try {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    pc_club::Handler handler("../GTest_file.txt");
    handler.handle_file();
    std::cout.rdbuf(old); // Restore original cout buffer
    std::string output = buffer.str();
    ASSERT_EQ(output, expected_output);
  } catch (const std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    FAIL() << "Exception thrown: " << e.what();
  }
}