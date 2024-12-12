#include <stdio.h>
#define SIZE 10
#define WIN 3

void printTable (char table[SIZE][SIZE]) {
    printf("Piskvorky\n\n");
    printf("   ");
    for (int k = 0; k < SIZE; k++) {            // vypise cislo sloupce
        printf("|%4.2d ", k + 1);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {           // vypise hraci pole
        printf("|%.2d", i + 1);          // vypise cislo radku
        for (int j = 0; j < SIZE; j++) {                // vypise obsah v policku
            printf("| [%c] ", table[i][j]);
        }
        printf("\n");
    }
}

void turn (char table[SIZE][SIZE], char player) {
    int x, y;
    int countChar = 0;
    printf("Players %c turn, choose your tile (row space column): ", player);       //prvni hrac si vzbere pole a ulozi se docasne jeho tah
    scanf("%d %d", &x, &y);
    while (getchar() != '\n') {
        countChar++;
    };
    x--;
    y--;
    if (countChar != 0 || x<0 || x>SIZE-1 || y<0|| y>SIZE-1 || table[x][y] != ' ') {              //kontroluje zda je vyber pole validni
        printf("Invalid input, try again.\n");
        turn(table, player);
    } else {
        table[x][y] = player;               //yapise tah do pole
    }
}

int column (char table[SIZE][SIZE]) {
    int countX, countO;
    for (int i = 0; i < SIZE; i++) {        //meni sloupce
        countX = 0;
        countO = 0;
        for (int j = 0; j < SIZE; j++) {   //meni radky
            if (table[j][i] == 'x') {       //pokud je x zvysi pocet x a vznuluje pocet o
                countO = 0;
                countX++;
            } else if (table[j][i] == 'o') { //pokud je o zvysi pocet o a vznuluje pocet x
                countX = 0;
                countO++;
            } else {                               // pokud je prazdne vynuluje oba
                countO = 0;
                countX = 0;
            }
            if (countX == WIN || countO == WIN) {       //pokud je pocet x nebo y roven nastavenemu poctu pro vyhru ukonci hru vypise pole a viteze
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
    for (int i = 0; i < SIZE; i++) {            //meni radky
        countX = 0;
        countO = 0;
        for (int j = 0; j < SIZE; j++) {        //meni sloupce
            if (table[i][j] == 'x') {           //to same jako predtim jen pro radky
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
    for (int i = 0; i < SIZE; i++) {            //meni radky
        countX = 0;
        countO = 0;
        for (int j = 0; j < SIZE; j++) {        //meni sloupce
            if (table [j][i] != ' ') {            //prochazi pouze polecka kde neco je
                if (table[j][i] == 'x') {        //pokud najde x tak si ho zapise a vznuluje y
                    countO = 0;
                    countX++;
                    for (int k = 1; k < WIN; k++) {            //opakuje dokud nenajde dost x pro vzhru
                        if (table[j + k][i + k] == 'x') {            // posunuje se diagonalne ve smeru do prava nahoru pokud najde x picte k poctu 
                            countX++;
                            if (countX == WIN) {                //pokud nasel dost x pro vzhru vzpise posledni tah a ukonci hru
                                printTable(table);
                                printf("x wins");
                                return 1;
                            }
                        } else if (table[j + k][i - k] == 'x') {            //posunuje do leva dolu
                            countX++;
                            if (countX == WIN) {
                                printTable(table);
                                printf("x wins");
                                return 1;
                            }
                        } else {
                            countX = 0;            // pokud jina moznost vznuluje x
                        }
                    }
                } else if (table[j][i] == 'o') {        //to same co u x ale u y
                    countX = 0;
                    countO++;
                    for (int k = 1; k < WIN; k++) {
                        if (table[j + k][i + k] == 'o') {
                            countO++;
                            if (countO == WIN) {
                                printTable(table);
                                printf("o wins");
                                return 1;
                            }
                        } else if (table[j + k][i - k] == 'x') {           
                            countX++;
                            if (countX == WIN) {
                                printTable(table);
                                printf("x wins");
                                return 1;
                            }
                        } else {
                            countO = 0;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int winChecker (char table[SIZE][SIZE]) {
    if (row(table) == 1 || column(table) == 1 || diagonal(table) == 1) {                //pokud jaka koliv moznost zaznamenala win vrati jedincku
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
        char table[SIZE][SIZE];            // vytvori pole
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {     //naplni pole
                table[i][j] = ' ';
            }
    }

    char player = 'x';                        //nastavi default hrace na x
    while (winChecker(table) != 1) {            //opakuje proces dokud  nevrati winchecker 1
        printTable(table);
        turn(table, player);
        player = (player == 'x') ? 'o' : 'x';        //meni hrace
    }

    return 0;            
}
