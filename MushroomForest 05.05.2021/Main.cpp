#include <iostream>
using namespace std;

unsigned char* raw_sew = NULL;
unsigned long long Max_x_y = 0;
unsigned long long* min_prime_divisor = NULL;
unsigned long long* Max_prime_divisor = NULL;
unsigned long long* Sum_till_index = NULL;

void build_sieve_raw(unsigned long long max_x_y)
{
    if (raw_sew != NULL) return;
    raw_sew = new unsigned char[max_x_y];
    for (unsigned long long i = 0; i < max_x_y; i++)
        raw_sew[i] = 1;
    raw_sew[0] = 0;
    raw_sew[1] = 0;
    for (unsigned long long k = 0; k * k < max_x_y; k++)
        if (raw_sew[k] == 1)
            for (unsigned long long p = 2 * k; p < max_x_y; p += k)
                raw_sew[p] = 0;
}

void build_sieve_primes(unsigned long long max_x_y, unsigned long long max_x, unsigned long long max_y)
{
    if (min_prime_divisor != NULL || Max_prime_divisor != NULL) return;
    min_prime_divisor = new unsigned long long[max_x];
    Max_prime_divisor = new unsigned long long[max_y];
    Sum_till_index = new unsigned long long[max_x_y];
    for (unsigned long long i = 0; i < max_x; i++)
        min_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_y; i++)
        Max_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        Sum_till_index[i] = 0;
    min_prime_divisor[1] = 1;
    Max_prime_divisor[1] = 1;
    Sum_till_index[1] = 1;
    for (unsigned long long i = 2; i < max_x_y; i++)
    {
        for (unsigned long long j = 2; j <= i; j++)
        {
            if (raw_sew[j] == 1 && i % j == 0)
                if (min_prime_divisor[i] == 0)
                {
                    if (i < max_x) min_prime_divisor[i] = j;
                    if (i < max_y) Max_prime_divisor[i] = j;
                }
                else
                    if (i < max_y) Max_prime_divisor[i] = j;
        }
        if (max_y > max_x)
            Sum_till_index[i] = Sum_till_index[i - 1] + Max_prime_divisor[i];
        else
            Sum_till_index[i] = Sum_till_index[i - 1] + min_prime_divisor[i];
    }
}

int main()
{
    unsigned long long x_field_range, y_field_range, queries_count, max_x_y, current_x, current_y;
    cin >> x_field_range >> y_field_range;
    cin >> queries_count;

    max_x_y = ((x_field_range > y_field_range) ? x_field_range : y_field_range);

    build_sieve_raw(max_x_y + 1);
    build_sieve_primes(max_x_y + 1, x_field_range + 1, y_field_range + 1);

    unsigned long long summa_division_min_prime_devision;
    unsigned long long max_prime_divisor_sum_till_index_current;

    for (unsigned long long i = 0; i < queries_count; i++)
    {
        cin >> current_x >> current_y;
        summa_division_min_prime_devision = 0;
        if (y_field_range > x_field_range)
        {
            max_prime_divisor_sum_till_index_current = Sum_till_index[current_y];
            for (unsigned long long j = 1; j <= current_x; j++)
                summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * min_prime_divisor[j];
        }
        else
        {
            max_prime_divisor_sum_till_index_current = Sum_till_index[current_x];
            for (unsigned long long j = 1; j <= current_y; j++)
                summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * Max_prime_divisor[j];
        }
        if (i != queries_count - 1)
            cout << summa_division_min_prime_devision << endl;
        else
            cout << summa_division_min_prime_devision;
    }

    if (raw_sew != NULL) delete[] raw_sew;
    if (min_prime_divisor != NULL) delete[] min_prime_divisor;
    if (Max_prime_divisor != NULL) delete[] Max_prime_divisor;
    if (Sum_till_index != NULL) delete[] Sum_till_index;
}
