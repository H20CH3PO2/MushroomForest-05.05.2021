#include <iostream>
#include <ctime>
using namespace std;

#include"MushroomForest.h"
#include "TestGenerator.h"

int main()
{
    cout << "Start test_generator..." << endl;
    test_generator("Test_4.txt", 2300, 200000);
    system("cls");
    cout << "Start mushroom_forest..." << endl;
    mushroom_forest("Test_4.txt", "Test_4_after_analysis.txt");
    system("pause>0");
}
