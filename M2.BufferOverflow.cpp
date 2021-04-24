// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_order
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  const std::string account_number = "CharlieBrown42";
  // JR: re-implement user_input variable using C++ basic_string class
  //char user_input[20];
  std::string user_input;
  std::cout << "Enter a value: ";
  std::cin >> user_input;

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
