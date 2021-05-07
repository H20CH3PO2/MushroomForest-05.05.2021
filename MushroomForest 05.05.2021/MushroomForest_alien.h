#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

typedef unsigned long long ULL;

unsigned char* is_prime = NULL;
ULL* sum_for_F1 = NULL;
ULL* sum_for_F2 = NULL;

void build_sieve_raw_alien(ULL max_x_y)
{
    if (is_prime != NULL) return;
    is_prime = new unsigned char[max_x_y];
    sum_for_F1 = new ULL[max_x_y];
    sum_for_F2 = new ULL[max_x_y];
    for (ULL i = 0; i < max_x_y; i++) {
        is_prime[i] = 1;
        sum_for_F1[i] = 0;
        sum_for_F2[i] = 0;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;
    sum_for_F1[1] = 1; // hack for F1(1) = 1
    sum_for_F2[1] = 1; // hack for F2(1) = 1
    for (ULL k = 0; k < max_x_y; k++) {
        if (is_prime[k] == 0) continue;
        for (ULL p = k; p < max_x_y; p += k) {
            sum_for_F2[p] = k;
            if (is_prime[p] == 1) {
                sum_for_F1[p] = k;
                is_prime[p] = 0;
            }
        }
    }
    for (ULL k = 1; k < max_x_y; k++) {
        sum_for_F1[k] += sum_for_F1[k - 1];
        sum_for_F2[k] += sum_for_F2[k - 1];
    }
}

void mushroom_forest_alien(const char* file_name_for_analysis, const char* file_name_for_answer) {
    ULL x_field_range, y_field_range, queries_count, max_x_y, x, y;
    ifstream file_for_analysis(file_name_for_analysis, ios_base::in);
    ofstream file_for_answer(file_name_for_answer, ios_base::trunc);
    file_for_analysis >> x_field_range >> y_field_range;
    file_for_analysis >> queries_count;
    // Мерим время для отладки!
    unsigned int start_time = clock();

    max_x_y = ((x_field_range > y_field_range) ? x_field_range : y_field_range);

    build_sieve_raw_alien(max_x_y + 1);

    for (ULL i = 0; i < queries_count; i++)
    {
        file_for_analysis >> x >> y;
        file_for_answer << sum_for_F1[x] * sum_for_F2[y] << std::endl;
    }

    if (is_prime != NULL) delete[] is_prime;
    if (sum_for_F1 != NULL) delete[] sum_for_F1;
    if (sum_for_F2 != NULL) delete[] sum_for_F2;
    cout << "Full time mushroom_forest_alien: " << clock() - start_time << '\n';
    file_for_analysis.close();
    file_for_answer.close();
}
