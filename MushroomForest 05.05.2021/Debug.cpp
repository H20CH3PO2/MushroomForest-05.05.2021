#include <iostream>
#include <ctime>
using namespace std;

#include"MushroomForest.h"
#include "TestGenerator.h"
#include "MushroomForest_alien.h"

int main()
{
     // TODO: ��������� ������, ��� ������ ����� ������ ���.
     
     // ��� ����� ������, ��� ������ 
     // ����������� ������������ ���������, � ���������� 
     // ������ �������� ��������� ����������� ��� ���������, ��������� �� 2, �������� ���������.

     // � ��� �� ������ ������� ��� ������� �������� [max_x_y] � ����� ������ ��������� ����������� 
     // ���������� ���������, � ������ �����������. ��� ������ ������. � ������ ������� ������ ��������, 
     // � �� ���� "����� ���������" � ��� ������� ������� � ������, ����� �������� ��� ��� ���, ��� ������� � ����� ������.

     // TODO: ��� ��������, ��� ������� ��������� � ������� � �������� 
     // ���� �������� ��� ���� � ����� � ������ �������� � ����� ������� �������� ���������� �����
    cout << "Start test_generator..." << endl;
    test_generator("Test_4.txt", 50, 100000, 200000);

    cout << "Start mushroom_forest..." << endl;
    mushroom_forest_alien("Test_4.txt", "Test_4_after_analysis.txt");
    mushroom_forest("Test_4.txt", "Test_4_after_analysis.txt");
    system("pause>0");
}
