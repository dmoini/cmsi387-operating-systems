#include <stdio.h>

int main( int argc, char *argv[] ) {
    int elements[25];
    int index = 0;
    int input_num;  
    while (1) {
        printf("Please enter a number or -9999 to stop [%d/25] \n", index + 1);
        scanf("%d", &input_num);
        if (input_num == -9999) {
            break;
        }
        elements[index] = input_num;
        index += 1;
        if (index == 25) {
            break;
        }
    }
    int sum = 0;
    for (int i = 0; i < index; i++) {
        sum += elements[i];
    }
    printf("Sum: %d \n", sum);

    float average = (float) sum / index;
    printf("Average: %f \n", average);
    
    // char* num_string;
    // for(int i = 0; i < index; i++) {
    //     num_string = *strcat(num_string, (char*) elements[i]);
    // }
    // // printf("sum: %d", sum);
    // int n;
    // n = sprintf();

    int seven_count = 0;
    for (int i = 0; i < index; i++) {
        if (elements[i] == 7) {
            seven_count += 1;
        }
    }
    printf("Number of sevens: %d \n", seven_count);
}