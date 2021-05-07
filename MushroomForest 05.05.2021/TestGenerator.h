#pragma once
#include <iostream>
#include <random>
#include <fstream>
using namespace std;

typedef unsigned long long ULL;

void test_generator(const char* name_test, unsigned long long side_x, unsigned long long side_y, unsigned long long querries_count)
{
    random_device my_random;
    ofstream file_random_mashroom_forest;
    file_random_mashroom_forest.open(name_test, ios_base::trunc);
    ULL max_side = (side_x > side_y) ? side_x : side_y;
    unsigned char* tmp_x = new unsigned char[max_side + 1];
    unsigned char* tmp_y = new unsigned char[max_side + 1];
    ULL generate_x = 0, generate_y = 0;
    for (ULL i = 0; i < max_side + 1; i++) {
        tmp_x[i] = 0; tmp_y[i] = 0;
    }
    file_random_mashroom_forest << side_x << " " << side_y << '\n' << querries_count << '\n';
    for (int i = 0; i < querries_count; i++)
    {
        do {
            tmp_x[generate_x] = 1; tmp_x [generate_y]= 1;
            generate_x = my_random.operator()() % side_x + 1;
            generate_y = my_random.operator()() % side_y + 1;
        } while ((tmp_x[generate_x] !=0 || tmp_x[generate_y] != 0) && generate_x < 2 && generate_y < 2);
        file_random_mashroom_forest << generate_x << " " << generate_y << '\n';
    }
    file_random_mashroom_forest.close();
    if (tmp_x != NULL) delete[] tmp_x;
    if (tmp_y != NULL) delete[] tmp_y;
}