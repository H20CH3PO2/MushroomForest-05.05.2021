#include <iostream>
using namespace std;

unsigned char* raw_sew = NULL;
unsigned long long Max_x_y = 0;
unsigned long long* min_prime_divisor = NULL;
unsigned long long* max_prime_divisor = NULL;
unsigned long long* max_prime_divisor_sum_till_index = NULL;

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

void build_sieve_primes(unsigned long long max_x_y)
{
    if (min_prime_divisor != NULL || max_prime_divisor != NULL) return;
    min_prime_divisor = new unsigned long long[max_x_y];
    max_prime_divisor = new unsigned long long[max_x_y];
    max_prime_divisor_sum_till_index = new unsigned long long[max_x_y];
    for (unsigned long long i = 0; i < max_x_y; i++)
        min_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        max_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        max_prime_divisor_sum_till_index[i] = 0;
    min_prime_divisor[1] = 1;
    max_prime_divisor[1] = 1;
    max_prime_divisor_sum_till_index[1] = 1;
    for (unsigned long long i = 2; i < max_x_y; i++)
    {
        for (unsigned long long j = 2; j <= i; j++)
        {
            if (raw_sew[j] == 1 && i % j == 0)
                if (min_prime_divisor[i] == 0)
                {
                    min_prime_divisor[i] = j;
                    max_prime_divisor[i] = j;
                }
                else
                    max_prime_divisor[i] = j;
        }
        max_prime_divisor_sum_till_index[i] = max_prime_divisor_sum_till_index[i - 1] + max_prime_divisor[i];
    }
}

int main()
{
    unsigned long long x_field_range, y_field_range, queries_count, max_x = 0, max_y = 0, max_x_y;
    cin >> x_field_range >> y_field_range;
    cin >> queries_count;
    unsigned long long* queries_x = new unsigned long long[queries_count];
    unsigned long long* queries_y = new unsigned long long[queries_count];

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

    for (unsigned long long i = 0; i < queries_count; i++)
    {
        summa_division_min_prime_devision = 0;
        max_prime_divisor_sum_till_index_current = max_prime_divisor_sum_till_index[queries_y[i]];
        for (unsigned long long j = 1; j <= queries_x[i]; j++)
            summa_division_min_prime_devision += max_prime_divisor_sum_till_index_current * min_prime_divisor[j];
        if (i != queries_count - 1)
            cout << summa_division_min_prime_devision << endl;
        else
            cout << summa_division_min_prime_devision;

    }

    if (queries_x != NULL) delete[] queries_x;
    if (queries_y != NULL) delete[] queries_y;
    if (raw_sew != NULL) delete[] raw_sew;
    if (min_prime_divisor != NULL) delete[] min_prime_divisor;
    if (max_prime_divisor != NULL) delete[] max_prime_divisor;
    if (max_prime_divisor_sum_till_index != NULL) delete[] max_prime_divisor_sum_till_index;
}
