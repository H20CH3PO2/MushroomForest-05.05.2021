

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

#include "MushroomForest.h"

BOOST_AUTO_TEST_CASE(Test_1)
{
	unsigned long long queries_count, number_one, number_two;
	mushroom_forest("Test_1.txt", "Test_1_after_analysis.txt");
	ifstream test_1_after_analysis("Test_1_after_analysis.txt", ios_base::in);
	ifstream answer_1("Answer_1.txt", ios_base::in);
	ifstream test_1("Test_1.txt", ios_base::in);
	test_1.ignore();
	test_1.ignore();
	test_1 >> queries_count;
	for (unsigned long long i = 0; i < queries_count; i++)
	{
		test_1_after_analysis >> number_one;
		answer_1 >> number_two;
		BOOST_CHECK(number_one == number_two);
	}
	test_1_after_analysis.close();
	answer_1.close();
	test_1.close();
}
