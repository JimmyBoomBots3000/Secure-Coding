// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// JR: Generic custom exception
// Modified from: https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
struct CustomException : std::exception 
{
	const char* what() const throw () {
		return "Custom exception.";
	}
};


bool do_even_more_custom_application_logic()
{
	// DONE: Throw any standard exception

	std::cout << "Running Even More Custom Application Logic." << std::endl;
	throw std::invalid_argument("Exception thrown from do_even_more_custom_application_logic().");

	return true;
}
void do_custom_application_logic()
{
	// DONE: Wrap the call to do_even_more_custom_application_logic()
	//  with an exception handler that catches std::exception, displays
	//  a message and the exception.what(), then continues processing
	std::cout << "Running Custom Application Logic." << std::endl;

	try
	{
		if (do_even_more_custom_application_logic())
		{
			std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
		}
	}

	// JR: Exception thrown up the call chain by do_even_more...() caught here.
	catch (std::exception& e)
	{
		std::cout << "EXCEPTION: " << e.what() << std::endl 
			<< "\t" << "Exception caught by do_custom_application_logic()." << std::endl;
	}


	// DONE: Throw a custom exception derived from std::exception
	//  and catch it explictly in main
	throw CustomException();
	std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
	// DONE: Throw an exception to deal with divide by zero errors using
	//  a standard C++ defined exception
	if (den == 0) 
	{
		throw std::runtime_error("Can't divide by zero!");
	}
	return (num / den);
}

void do_division() noexcept
{
	//  DONE: create an exception handler to capture ONLY the exception thrown
	//  by divide.

	float numerator = 10.0f;
	float denominator = 0;

	try
	{
		auto result = divide(numerator, denominator);
		std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cout << "EXCEPTION: " << e.what() << std::endl;
	}

}

int main()
{
	std::cout << "Exceptions Tests!" << std::endl;

	// DONE: Create exception handlers that catch (in this order):
	//  your custom exception
	//  std::exception
	//  uncaught exception 
	//  that wraps the whole main function, and displays a message to the console.
	try
	{
		do_division();
		do_custom_application_logic();
	}

	// JR: Catches exception thrown from do_custom_application_logic()
	catch (CustomException& e)
	{
		std::cout << "EXCEPTION: " << e.what() << std::endl;

	}

	catch (std::exception& e)
	{
		std::cout << "EXCEPTION: " << e.what() << std::endl;

	}

	catch (...)
	{
		std::cout << "EXCEPTION: " << "Uncaught exception." << std::endl;

	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
