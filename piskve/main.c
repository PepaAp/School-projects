#include <stdio.h>
#include <stdlib.h>
#define SIZE 3
#define WIN 2

void printTable (char table[SIZE][SIZE]) {
    printf("Piskvorky\n\n");
    printf("   ");
    for (int k = 0; k < SIZE; k++) {
        printf("|%4.2d ", k + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("|%.2d", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf("| [%c] ", table[i][j]);
        }
        printf("\n");
    }
}

void turn (char table[SIZE][SIZE], char player) {
    int x, y;
    printf("Players %c turn, choose your tile (row and column): ", player);
    scanf("%d %d", &x, &y);
    x--;
    y--;

    if (table[x][y] == ' ') {
        table[x][y] = player;
    } else {
        printf("Invalid move, try again.\n");
        turn(table, player);
    }
}

int column (char table[SIZE][SIZE]) {
    int countX, countO;
    for (int i = 0; i < SIZE; i++) {
        countX = 0;
        countO = 0;
        for (int j = 0; j < SIZE; j++) {
            if (table[j][i] == 'x') {
                countO = 0;
                countX++;
            } else if (table[j][i] == 'o') {
                countX = 0;
                countO++;
            } else {
                countO = 0;
                countX = 0;
            }
            if (countX == WIN || countO == WIN) {
                printTable(table);
                printf("%c wins", (countX == WIN) ? 'x' : 'o');
                return 1;
            }
        }
    }
    return 0;
}

int row (char table[SIZE][SIZE]) {
    int countX, countO;
    for (int i = 0; i < SIZE; i++) {
        countX = 0;
        countO = 0;
        for (int j = 0; j < SIZE; j++) {
            if (table[i][j] == 'x') {
                countO = 0;
                countX++;
            } else if (table[i][j] == 'o') {
                countX = 0;
                countO++;
            } else {
                countX = 0;
                countO = 0;
            }
            if (countX == WIN || countO == WIN) {
                printTable(table);
                printf("%c wins", (countX == WIN) ? 'x' : 'o');
                return 1;
            }
        }
    }
    return 0;
}

int diagonal (char table[SIZE][SIZE]) {
    int countX, countO;
    
    return 0;
}

int winChecker (char table[SIZE][SIZE]) {
    if (row(table) == 1 || column(table) == 1 || diagonal(table) == 1) {
        return 1;
    } else {
        return 0;
    }
}
int main(void) {
        char table[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            table[i][j] = ' ';
        }
    }

    char player = 'x';
    while (winChecker(table) != 1) {
        printTable(table);
        turn(table, player);
        player = (player == 'x') ? 'o' : 'x';
    }

    return 0;
}
