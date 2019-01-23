#include <stdio.h>

int main() {
    char name[20];
    int age;
    int classYear;
    char hairColor[20];
    int heightInInches;
    char eyeColor[20];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("Enter your class year: ");
    scanf("%d", &classYear);
    printf("Enter your hair color: ");
    scanf("%s", hairColor);
    printf("Enter your height in inches: ");
    scanf("%d", &heightInInches);
    printf("Enter your eye color: ");
    scanf("%s", eyeColor);
    printf("\nName: %s \nAge: %d \nClass year: %d \nHair color: %s \nHeight in inches: %d \nEye color: %s \n", 
            name, age, classYear, hairColor, heightInInches, eyeColor);
    return 0;
}