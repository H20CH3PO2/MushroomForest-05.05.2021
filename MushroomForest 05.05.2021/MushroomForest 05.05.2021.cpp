#include <iostream>
//#include <ctime>
using namespace std;

unsigned char* Raw_sew = NULL;
unsigned long long Max_x_y = 0;
unsigned long long* Min_prime_divisor = NULL;
unsigned long long* Max_prime_divisor = NULL;
unsigned long long* Max_prime_divisor_sum_till_index = NULL;

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
void build_sieve_primes(unsigned long long max_x_y)
{
    if (Min_prime_divisor != NULL || Max_prime_divisor != NULL) return;
    Min_prime_divisor = new unsigned long long[max_x_y];
    Max_prime_divisor = new unsigned long long[max_x_y];
    Max_prime_divisor_sum_till_index = new unsigned long long[max_x_y];
    for (unsigned long long i = 0; i < max_x_y; i++)
        Min_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        Max_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        Max_prime_divisor_sum_till_index[i] = 0;
    Min_prime_divisor[1] = 1;
    Max_prime_divisor[1] = 1;
    Max_prime_divisor_sum_till_index[1] = 1;
    for (unsigned long long i = 2; i < max_x_y; i++)
    {
        for (unsigned long long j = 2; j <= i; j++)
        {
            if (Raw_sew[j] == 1 && i % j == 0)
                if (Min_prime_divisor[i] == 0)
                {
                    Min_prime_divisor[i] = j;
                    Max_prime_divisor[i] = j;
                }
                else
                    Max_prime_divisor[i] = j;
        }
        Max_prime_divisor_sum_till_index[i] = Max_prime_divisor_sum_till_index[i - 1] + Max_prime_divisor[i];
    }
}

int main()
{
    unsigned long long x_field_range, y_field_range, queries_count, max_x = 0, max_y = 0, max_x_y;
    cin >> x_field_range >> y_field_range;

    // Мерим время для отладки!
    /*unsigned int start_time = clock();*/

    cin >> queries_count;
    unsigned long long* queries_x = new unsigned long long[queries_count];
    unsigned long long* queries_y = new unsigned long long[queries_count];
    /*unsigned long long* queries_answer = new unsigned long long[queries_count];*/
    /*for (unsigned long long i = 0; i < queries_count; i++)
        queries_answer[i] = 0;*/
    for (unsigned long long i = 0; i < queries_count; i++)
    {
        cin >> queries_x[i] >> queries_y[i];
        if (queries_x[i] > max_x) max_x = queries_x[i];
        if (queries_y[i] > max_y) max_y = queries_y[i];
    }
    max_x_y = ((max_x > max_y) ? max_x : max_y);
    build_sieve_raw(max_x_y + 1);
    build_sieve_primes(max_x_y + 1);
    unsigned long long summa_division_min_prime_devision;
    unsigned long long max_prime_divisor_sum_till_index_current;
    /*unsigned long longcurrent_x, current_y, index_before;*/
     // Мерим время для отладки!
    /*cout << "Building time: " << clock() - start_time << endl;*/

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
    for (unsigned long long i = 0; i < queries_count; i++)
    {
        /*current_x = queries_x[i];
        current_y = queries_y[i];
        index_before = i;*/
        // Попробуем найти был ли такой уже запрос. Запросы не отсортированы. Идём по всем.
        /*for (unsigned long long p = 0; p < queries_count; p++)
        {
            if (queries_x[p] == current_x && queries_y[i] == current_y)
                index_before = p;
        }*/
        if (queries_answer[index_before] == 0)
        {
            summa_division_min_prime_devision = 0;
            max_prime_divisor_sum_till_index_current = Max_prime_divisor_sum_till_index[current_y];
            for (unsigned long long j = 1; j <= current_x; j++)
                summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * Min_prime_divisor[j];
            if (i != queries_count - 1)
                cout << summa_division_min_prime_devision << endl;
            else
                cout << summa_division_min_prime_devision;
        }
        else
        {
            if (i != queries_count - 1)
                cout << queries_answer[index_before] << endl;
            else
                cout << queries_answer[index_before];
        }
    }
    if (queries_x != NULL) delete[] queries_x;
    if (queries_y != NULL) delete[] queries_y;
    // if (queries_answer != NULL) delete[] queries_answer;
    if (Raw_sew != NULL) delete[] Raw_sew;
    if (Min_prime_divisor != NULL) delete[] Min_prime_divisor;
    if (Max_prime_divisor != NULL) delete[] Max_prime_divisor;
    if (Max_prime_divisor_sum_till_index != NULL) delete[] Max_prime_divisor_sum_till_index;

     // Мерим время для отладки!
    /*unsigned int end_time = clock();
    cout << endl;
    cout <<"Processing time: " << end_time - start_time;
    system("pause>0");*/
}
