#pragma once
#include <iostream>
#include <random>
#include <fstream>
using namespace std;

void test_generator(const char* name_test, unsigned long long side, unsigned long long querries_count)
{
    unsigned long long generate_x, generate_y;
    random_device my_random;
    ofstream file_random_mashroom_forest;
    file_random_mashroom_forest.open(name_test, ios_base::trunc);
    do {
        generate_x = (my_random.operator()()) % (side * side) + 1;
        generate_y = (my_random.operator()()) % (side * side) + 1;
    } while (generate_x * generate_y > side * side || generate_x < 100 || generate_y < 100);
    file_random_mashroom_forest << generate_x << " " << generate_y << endl << querries_count << endl;
    for (int i = 0; i < querries_count; i++)
        file_random_mashroom_forest << (my_random.operator()()) % generate_x + 1 << " " << (my_random.operator()()) % generate_y + 1 << endl;
    file_random_mashroom_forest.close();
}