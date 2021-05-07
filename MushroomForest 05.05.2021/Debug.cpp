#include <iostream>
#include <ctime>
using namespace std;

#include"MushroomForest.h"
#include "TestGenerator.h"
#include "MushroomForest_alien.h"

int main()
{
     // TODO: Построить решето, где чётных ячеек просто нет.
     
     // Ещё можно учесть, что задача 
     // симметрична относительно диагонали, и достаточно 
     // вместо квадрата посчитать треугольник без диагонали, помножить на 2, добавить диагональ.

     // А ещё ты можешь создать два массива размером [max_x_y] и сразу первый заполнить наименьшими 
     // делителями координат, а второй наибольшими. Это вместо решета. В ячейку массива писать делитель, 
     // а не флаг "число составное" — для первого массива в случае, когда делителя там ещё нет, для второго в любом случае.

     // TODO: Сам придумал, что быстрее обратится к массиву и записать 
     // туда значение или идти в цикле и делать проверку и брать текущее значение инкремента цикла
    cout << "Start test_generator..." << endl;
    test_generator("Test_4.txt", 50, 100000, 200000);

    cout << "Start mushroom_forest..." << endl;
    mushroom_forest_alien("Test_4.txt", "Test_4_after_analysis.txt");
    mushroom_forest("Test_4.txt", "Test_4_after_analysis.txt");
    system("pause>0");
}
