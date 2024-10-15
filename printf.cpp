// stratton jelley
// printf practice
// 2024-10-15

#include<iostream>
using namespace std;

int main()
{
    char name[100];
    int age;
    char initial;
    float grade;

    cout << "Enter your name: " << endl;
    scanf("%s", &name);

    cout << "Enter your age: " << endl;
    scanf("%d", &age);

    cout << "Enter your last initial: " << endl;
    scanf(" %c", &initial);

    cout << "Enter your grade average: " << endl;
    scanf("%f", &grade);

    printf("Your name is %s.%c. You are %d years old, and you have a grade average of %.2f.", name, initial, age, gradeAvg);

    return 0;
}
