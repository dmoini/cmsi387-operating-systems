#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int mutex = 1;
int full = 0;
int empty = 7;          // maximum of seven messages in buffer
int x = 0;

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main(){
    int n;
    void producer();
    void consumer();
    int wait_( int );
    int signal_( int );
    while( 1 ) {
        if( (mutex == 1) && (empty != 0) ) {
            delay(500);
            producer();
        } else {
            printf( "\nBuffer is full!!" );
        }
        if( (mutex == 1) && (full != 0) ) {
            delay(500);
            consumer();
        } else {
            printf("\nBuffer is empty!!");
        }
    }
    return 0;
}

int wait_( int s ) {
    return( --s );
}

int signal_( int s ) {
    return( ++s );
}

void producer() {
    mutex = wait_( mutex );
    full  = signal_( full );
    empty = wait_( empty );
    x++;
    printf( "\n  Producer produces the item %d", x );
    mutex = signal_( mutex );
}

void consumer() {
    mutex = wait_( mutex );
    full  = wait_( full );
    empty = signal_( empty );
    printf( "\n  Consumer consumes item %d", x );
    x--;
    mutex = signal_( mutex );
}