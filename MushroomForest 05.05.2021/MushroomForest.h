#pragma once

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

unsigned char* Raw_sew = NULL;
unsigned long long Max_x_y = 0;
unsigned long long* Min_prime_divisor = NULL;
unsigned long long* Max_prime_divisor = NULL;
unsigned long long* Sum_till_index = NULL;

void build_sieve_raw(unsigned long long max_x_y)
{
    if (Raw_sew != NULL) return;
    Raw_sew = new unsigned char[max_x_y];
    for (unsigned long long i = 0; i < max_x_y; i++)
        Raw_sew[i] = 1;
    Raw_sew[0] = 0;
    Raw_sew[1] = 0;
    for (unsigned long long k = 0; k * k < max_x_y; k++)
        if (Raw_sew[k] == 1)
            for (unsigned long long p = 2 * k; p < max_x_y; p += k)
                Raw_sew[p] = 0;
}

// TODO: Подумать, как избавится от вложенных циклов.
void build_sieve_primes(unsigned long long max_x_y, unsigned long long max_x, unsigned long long max_y)
{
    if (Min_prime_divisor != NULL || Max_prime_divisor != NULL) return;
    Min_prime_divisor = new unsigned long long[max_x_y];
    Max_prime_divisor = new unsigned long long[max_x_y];
    Sum_till_index = new unsigned long long[max_x_y];
    for (unsigned long long i = 0; i < max_x_y; i++)
        Min_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x; i++)
        Max_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_y; i++)
        Sum_till_index[i] = 0;
    Min_prime_divisor[1] = 1;
    Max_prime_divisor[1] = 1;
    Sum_till_index[1] = 1;
    for (unsigned long long i = 2; i < max_x_y; i++)
    {
        if (Raw_sew[i] == 0)
        {
            for (unsigned long long j = 2; j <= i; j++)
            {
                if (Raw_sew[j] == 1 && i % j == 0)
                    if (Min_prime_divisor[i] == 0)
                    {
                        if (i < max_x) Min_prime_divisor[i] = j;
                        if (i < max_y) Max_prime_divisor[i] = j;
                    }
                    else
                        if (i < max_y) Max_prime_divisor[i] = j;
            }
        }
        else
        {
            // Если ещё не вышли за границу леса по x, то записываем минимальный простой делитель числа i.
            if (i < max_x) Min_prime_divisor[i] = i;
            // Если ещё не вышли за границу леса по y, то записываем максимальны простой делитель числа i.
            if (i < max_y) Max_prime_divisor[i] = i;
        }
        if(max_y > max_x)
            Sum_till_index[i] = Sum_till_index[i - 1] + Max_prime_divisor[i];
        else
            Sum_till_index[i] = Sum_till_index[i - 1] + Min_prime_divisor[i];
    }
}

void mushroom_forest(const char* file_name_for_analysis, const char* file_name_for_answer)
{
    unsigned long long x_field_range, y_field_range, queries_count, max_x = 0, max_y = 0, max_x_y;
    ifstream file_for_analysis(file_name_for_analysis, ios_base::in);
    ofstream file_for_answer(file_name_for_answer, ios_base::trunc);
    file_for_analysis >> x_field_range >> y_field_range;

    // Мерим время для отладки!
    unsigned int start_time = clock();

    file_for_analysis >> queries_count;
    unsigned long long* queries_x = new unsigned long long[queries_count];
    unsigned long long* queries_y = new unsigned long long[queries_count];
    /*unsigned long long* queries_answer = new unsigned long long[queries_count];*/
    /*for (unsigned long long i = 0; i < queries_count; i++)
        queries_answer[i] = 0;*/
    for (unsigned long long i = 0; i < queries_count; i++)
    {
        file_for_analysis >> queries_x[i] >> queries_y[i];
        if (queries_x[i] > max_x) max_x = queries_x[i];
        if (queries_y[i] > max_y) max_y = queries_y[i];
    }
    max_x_y = ((max_x > max_y) ? max_x : max_y);
    build_sieve_raw(max_x_y + 1);
    build_sieve_primes(max_x_y + 1, max_x + 1, max_y + 1);
    unsigned long long summa_division_min_prime_devision;
    unsigned long long max_prime_divisor_sum_till_index_current;

    // Мерим время для отладки!
    system("cls");
    cout << "Building time: " << clock() - start_time << endl;

    // Для отладки
    /*for (int i = 0; i <= max_x_y; i++)
        cout << "Raw_sew[" << i << "] = " << Raw_sew[i] << endl;
    for (int i = 0; i <= max_x_y; i++)
        cout << "Min_prime_divisor[" << i << "] = " << Min_prime_divisor[i] << endl;
    for (int i = 0; i <= max_x_y; i++)
        cout << "Max_prime_divisor[" << i << "] = " << Max_prime_divisor[i] << endl;
    for (int i = 0; i <= max_x_y; i++)
        cout << "Max_prime_divisor_sum_till_index[" << i << "] = " << Max_prime_divisor_sum_till_index[i] << endl;*/

        // TODO: Сделать проверку на одинаковые запросы. Пока идея плохая.
    start_time = clock();

    for (unsigned long long i = 0; i < queries_count; i++)
    {
        summa_division_min_prime_devision = 0;
        if (max_y > max_x)
        {
            max_prime_divisor_sum_till_index_current = Sum_till_index[queries_y[i]];
            for (unsigned long long j = 1; j <= queries_x[i]; j++)
                summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * Min_prime_divisor[j];
        }
        else
        {
            max_prime_divisor_sum_till_index_current = Sum_till_index[queries_x[i]];
            for (unsigned long long j = 1; j <= queries_y[i]; j++)
                summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * Max_prime_divisor[j];
        }
        if (i != queries_count - 1)
            file_for_answer << summa_division_min_prime_devision << endl;
        else
            file_for_answer << summa_division_min_prime_devision;

    }
    if (queries_x != NULL) delete[] queries_x;
    if (queries_y != NULL) delete[] queries_y;
    if (Raw_sew != NULL) delete[] Raw_sew;
    if (Min_prime_divisor != NULL) delete[] Min_prime_divisor;
    if (Max_prime_divisor != NULL) delete[] Max_prime_divisor;
    if (Sum_till_index != NULL) delete[] Sum_till_index;
    file_for_analysis.close();
    file_for_answer.close();
    // Мерим время для отладки!
    
    cout << endl;
    cout << "Processing time: " << clock() - start_time<<endl;
    cout << endl;
    cout << "Precessing end.";
    // system("pause>0");
}
