#pragma once
#include <iostream>
#include <random>
#include <fstream>
using namespace std;

void test_generator(const char* name_test, unsigned long long side, unsigned long long querries_count)
{
    random_device my_random;
    ofstream file_random_mashroom_forest;
    file_random_mashroom_forest.open(name_test, ios_base::trunc);
    file_random_mashroom_forest << side << " " << side << endl << querries_count << endl;
    for (int i = 0; i < querries_count; i++)
        file_random_mashroom_forest << my_random.operator()() % side << " " << my_random.operator()() % side << endl;
    file_random_mashroom_forest.close();
}