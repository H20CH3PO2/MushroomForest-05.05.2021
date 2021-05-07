#include <iostream>
using namespace std;

 // Массив, который заполнится флагами - число простое или нет. Например, Raw_sew[2] = 1, Raw_sew[4] = 0.
unsigned char* Raw_sew = NULL;
 // Массив, который заполнится минимальными простыми делителями соответствующих индексов. Например, Min_prime_divisor[18] = 2.
unsigned long long* Min_prime_divisor = NULL;
 // Массив, который заполняется максимальными простыми делителями соответствующих индексов. Например, Max_prime_divisor[18] = 3.
unsigned long long* Max_prime_divisor = NULL;
 // Массив в котором будет хранится сумма значений либо F1(x) до индекса,
 // либо сумма F2(y) до индекса. Если max_x > max_y, то первый случий и наоборот. 
 // Это связанно с тем, что мы считаем сумму произведений в каждой ячейке.
 // Проилюстрирую в чём суть для слючая max_x > max_y истина:
 /*
 F1(1)*F2(1) F1(2)*F2(1)  F1(3)*F2(1)  F1(4)*F2(1)  F1(6)*F2(1)  F1(8)*F2(1)  F1(9)*F2(1)  F1(10)*F2(1)  F1(11)*F2(1)
 F1(1)*F2(2) F1(2)*F2(2)  F1(3)*F2(2)  F1(4)*F2(2)  F1(6)*F2(2)  F1(8)*F2(2)  F1(9)*F2(2)  F1(10)*F2(2)  F1(11)*F2(2)
 F1(1)*F2(3) F1(2)*F2(3)  F1(3)*F2(3)  F1(4)*F2(3)  F1(6)*F2(3)  F1(8)*F2(3)  F1(9)*F2(3)  F1(10)*F2(3)  F1(11)*F2(3)
 F1(1)*F2(4) F1(2)*F2(4)  F1(3)*F2(4)  F1(4)*F2(4)  F1(6)*F2(4)  F1(8)*F2(4)  F1(9)*F2(4)  F1(10)*F2(4)  F1(11)*F2(4)
 F1(1)*F2(5) F1(2)*F2(5)  F1(3)*F2(5)  F1(4)*F2(5)  F1(6)*F2(5)  F1(8)*F2(5)  F1(9)*F2(5)  F1(10)*F2(5)  F1(11)*F2(5)
 F1(1)*F2(6) F1(2)*F2(6)  F1(3)*F2(6)  F1(4)*F2(6)  F1(6)*F2(6)  F1(8)*F2(6)  F1(9)*F2(6)  F1(10)*F2(6)  F1(11)*F2(6)
 F1(1)*F2(7) F1(2)*F2(7)  F1(3)*F2(7)  F1(4)*F2(7)  F1(6)*F2(7)  F1(8)*F2(7)  F1(9)*F2(7)  F1(10)*F2(7)  F1(11)*F2(7)
 Теперь выносим F1 в каждом столбце за собки как общий множитель.
 F2(1) F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)
 F2(2) F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)
 F2(3) F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)
 F2(4) F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)
 F2(5) F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)
 F2(6) F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)
 F2(7) F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)
 *      *       *      *     *      *       *      *     *
 F(1)   F(2)    F(3)   F(4)  F(5)   F(6)    F(7)  F(8)   F(9)

 А значения в скобках складывать в цикле.

 F2(1) F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)  F2(1)
   +    +       +      +      +      +      +      +      +
 F2(2) F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)  F2(2)
    +    +       +      +      +      +      +      +      +
 F2(3) F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)  F2(3)
    +    +       +      +      +      +      +      +      +
 F2(4) F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)  F2(4)
    +    +       +      +      +      +      +      +      +
 F2(5) F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)  F2(5)
    +    +       +      +      +      +      +      +      +
 F2(6) F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)  F2(6)
    +    +       +      +      +      +      +      +      +
 F2(7) F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)  F2(7)
 *      *       *      *     *      *       *      *     *
 F(1)   F(2)    F(3)   F(4)  F(5)   F(6)    F(7)  F(8)   F(9)
 */
 // В массив Sum_till_index складываем на место i сумму чисел от F(1) до F(i)
 // В F1, если max_x > max_y истина, в обратном случае F2
 // Пример - max_x > max_y истина, тогда Sum_till_index[3] = F1(3) + F1(2) + F1(1)
unsigned long long* Sum_till_index = NULL;

 // Функция строит Raw_sew методом решета.
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

 // Функция строит массивы Min_prime_divisor, Max_prime_divisor, Sum_till_index
void build_sieve_primes(unsigned long long max_x_y, unsigned long long max_x, unsigned long long max_y)
{
    if (Min_prime_divisor != NULL || Max_prime_divisor != NULL) return;
    Min_prime_divisor = new unsigned long long[max_x];
    Max_prime_divisor = new unsigned long long[max_y];
    Sum_till_index = new unsigned long long[max_x_y];
    for (unsigned long long i = 0; i < max_x; i++)
        Min_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_y; i++)
        Max_prime_divisor[i] = 0;
    for (unsigned long long i = 0; i < max_x_y; i++)
        Sum_till_index[i] = 0;
    Min_prime_divisor[1] = 1;
    Max_prime_divisor[1] = 1;
    Sum_till_index[1] = 1;
     // В цикле идём до максимума из длинн двух сторон леса.
     // Находим минимальный и максимальный простые делители 
     // для каждого числа из этого диапозона
    for (unsigned long long i = 2; i < max_x_y; i++)
    {
        // Если чсло составное, то ищем его минимальный и максимальный простые делители. 
        // Если простое, то оно и есть свой собственный минимальный и максимальный простой делитель.
        if (Raw_sew[i] == 0)
        {
            // Идём по всему массиву с флагами о том, является ли число простым, 
            // но не превышая числа, для которого ищем минимальный и максимальный простые делители
            for (unsigned long long j = 2; j <= i; j++)
            {
                // Если число простое и делитель, то ...
                if (Raw_sew[j] == 1 && i % j == 0)
                {
                    // Если ещё не найден минимальный простой делитель числа, то...
                    if (Min_prime_divisor[i] == 0)
                    {
                        // Если ещё не вышли за границу леса по x, то записываем минимальный простой делитель числа i.
                        if (i < max_x) Min_prime_divisor[i] = j;
                        // Если ещё не вышли за границу леса по y, то записываем максимальны простой делитель числа i.
                        // Это делается, так как минимальный и максимальный могут совпасть.
                        if (i < max_y) Max_prime_divisor[i] = j;
                    }
                    else
                    {
                        // Если найден минимальный простой делитель, то нам нужно искать уже только максимальный. 
                        // Этот else срабатывает, если найден минимальный простой делитель i.
                        // Min_prime_divisor[i] != 0
                        // Если ещё не вышли за границу леса по y, то записываем максимальны простой делитель числа i.
                        if (i < max_y) Max_prime_divisor[i] = j;
                    }
                }
            }
        }
        else
        {
            // Если ещё не вышли за границу леса по x, то записываем минимальный простой делитель числа i.
            if (i < max_x) Min_prime_divisor[i] = i;
            // Если ещё не вышли за границу леса по y, то записываем максимальны простой делитель числа i.
            if (i < max_y) Max_prime_divisor[i] = i;
        }
        // Это было описано выше строка 10. 
        // Заполняем массив суммой минимальных простых делителей до индекса, 
        // если max_y > max_x.
        // И наоборот суммой максимальных простых делителей до индекса
        // в опратном случае.
        if (max_y > max_x)
            Sum_till_index[i] = Sum_till_index[i - 1] + Max_prime_divisor[i];
        else
            Sum_till_index[i] = Sum_till_index[i - 1] + Min_prime_divisor[i];
    }
}

int main()
{
     // x_field_range - длинна стороны леса по x
     // y_field_range - длинна стороны леса по y
     // queries_count - число запросов на сумму грибов в квадрате леса от начала координат.
     // max_x_y - максимальное число из x_field_range, y_field_range.
    unsigned long long x_field_range, y_field_range, queries_count, max_x_y, current_x, current_y;
     // Считываем длинну сторон леса и число запросов.
    cin >> x_field_range >> y_field_range;
    cin >> queries_count;

     // Находим максимум из двух сторон леса.
    max_x_y = ((x_field_range > y_field_range) ? x_field_range : y_field_range);

     // Строим массив флагов для простых чисел - Raw_sew, объявлен в строке 4.
    build_sieve_raw(max_x_y + 1);

     // Строим массивы Min_prime_divisor, Max_prime_divisor, Sum_till_index
     // Подробнее о них в комментариях в начале программы.
    build_sieve_primes(max_x_y + 1, x_field_range + 1, y_field_range + 1);

     // Сумма грибов с поля с заданными сторонами. 
    unsigned long long summa_division_min_prime_devision;

     // Текущий элемент из массива Sum_till_index подробнее о массиве в начале программы.
    unsigned long long divisor_sum_till_index_current;

     // В цикле идём по всем запросам
    for (unsigned long long i = 0; i < queries_count; i++)
    {
         // Считываем x и y для запроса. 
         // Соответствено считаем сумму грибов на квадрате 
         // со сторонами по x от 1 до x, 
         // по y от 1 до y
        cin >> current_x >> current_y;
         // Обнуляем сумму грибов для текущего запроса.
        summa_division_min_prime_devision = 0;
         // Если по стороне вдоль оси сторона леса длиннее,
         // то соответственно, как было описана до этого
         // в массиве Sum_till_index будут суммы F2() от 1 до i.
         // Соответственно нам надо умножить элемент из
         // Sum_till_index на F1(1), F1(2) и так далее, сложить их вместе.
         // В обратном случае наоборот. В Sum_till_index будут суммы F1() и
         // Умножать их надо будет на F2()
        if (y_field_range > x_field_range)
        {
            divisor_sum_till_index_current = Sum_till_index[current_y];
            for (unsigned long long j = 1; j <= current_x; j++)
                summa_division_min_prime_devision += divisor_sum_till_index_current * Min_prime_divisor[j];
        }
        else
        {
            divisor_sum_till_index_current = Sum_till_index[current_x];
            for (unsigned long long j = 1; j <= current_y; j++)
                summa_division_min_prime_devision += divisor_sum_till_index_current * Max_prime_divisor[j];
        }
         // Выводим сумму грибов для текущего запроса
        if (i != queries_count - 1)
            cout << summa_division_min_prime_devision << '\n';
        else
            cout << summa_division_min_prime_devision;
    }

     // Чистим память.
    if (Raw_sew != NULL) delete[] Raw_sew;
    if (Min_prime_divisor != NULL) delete[] Min_prime_divisor;
    if (Max_prime_divisor != NULL) delete[] Max_prime_divisor;
    if (Sum_till_index != NULL) delete[] Sum_till_index;
}
