// thread pool.cpp : Defines the entry point for the console application.
//



#include "stdafx.h"
#include "../include/ThreadPool.h"
#include <iostream>
#include <random>
using namespace std;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);

void simple_hard_computation() {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// Simple function that adds multiplieds two numbers and points the resutl
void multiply(const int a, const int b) {
	simple_hard_computation();
	const int res = a * b;
	std::cout << a << " * " << b << " = " << res << std::endl;
}

// Same as before but now we have an output parameter
void multiply_output(int &out, const int a, const int b) {
	simple_hard_computation();
	out = a * b;
	std::cout << a << " * " << b << " = " << out << std::endl;
}

// Same as before but now we have an output parameter
int multiply_return(const int a, const int b) {
	simple_hard_computation();
	const int res = a * b;
	std::cout << a << " * " << b << " = " << res << std::endl;
	return res;
}






int main()
{
	ThreadPool pool(3);
	pool.init();
	
	for (int i = 1; i < 3; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			pool.submit(multiply, i, j);
		}
	}


	// Submit function with output parameter passed by ref
	//int output_ref;
	//auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

	//// Wait for multiplication output to finish
	//future1.get();
	//std::cout << "Last operation result is equals to " << output_ref << std::endl;

	while (true)
	{

	}

	pool.shutdown();

    return 0;
}

