#include <stdio.h>
#include <stdlib.h>


int main() {
    char name[20];
    int age;
    int classYear;
    char hairColor[20];
    int heightInInches;
    char eyeColor[20];
    printf("Enter your name: ");
    fgets(name, 20, stdin);
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("Enter your class year: ");
    scanf("%d", &classYear);
    printf("Enter your hair color: ");
    fgets(hairColor, 20, stdin);
    printf("Enter your height in inches: ");
    scanf("%d", &heightInInches);
    printf("Enter your eye color: ");
    fgets(eyeColor, 20, stdin);
    printf("\nName: %sAge: %d \nClass year: %d \nHair color: %s \nHeight in inches: %d \nEye color: %s \n", 
            name, age, classYear, hairColor, heightInInches, eyeColor);
    return 0;
}