#include <stdio.h>
#define SIZE 3
#define WIN 3

void printTable () {
    printf("\tPiskvorky\n\n");
    for (int k = 0; k < SIZE; k++) {
          
        printf("|%.2d", k +1);
    }
    printf("\n");
    for (int i = 0; i<SIZE; i++) {
        for (int j = 0; j<SIZE; j++) {
            printf("|[]");
        }
        printf("\n");
    }
}



int main(void) {
    printTable();
    return 0;
}
