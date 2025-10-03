#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELI " :,"
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define SIZE 100

typedef struct {
    int min;
    int sec;
    int mil;
}SJEZD;

typedef struct {
    int sec;
    int mil;
}SLALOM;

typedef struct {
    int id;
    char jmeno[20];
    char prijmeni[20];
    char stat[4];
    SJEZD sjezd;
    SLALOM slalom;
}DATA;

DATA parseLine (char *buffer) {
    DATA data;
    char *parse;
    int i = 0;
    parse = strtok(buffer, DELI);
    while (parse!=NULL) {
        switch (i) {
            case 0:
                data.id = atoi(parse);
            break;
            case 1:
                strcpy(data.jmeno, parse);
            break;
            case 2:
                strcpy(data.prijmeni, parse);
            break;
            case 3:
                strcpy(data.stat, parse);
            break;
            case 4:
                data.sjezd.min = atoi(parse);
            break;
            case 5:
                data.sjezd.sec = atoi(parse);
            break;
            case 6:
                data.sjezd.mil = atoi(parse);
            break;
            case 7:
                data.slalom.sec = atoi(parse);
            break;
            case 8:
                data.slalom.mil = atoi(parse);
                break;
        }
        parse = strtok(NULL, DELI);
        i++;
    }
    return data;
}

DATA *parseFile(int *count, FILE *file) {
    char buffer[SIZE];
    int i = 0;
    DATA *data = NULL;
    while (fgets(buffer, SIZE, file) != NULL) {
        i++;
        DATA *newData = realloc(data, i*sizeof(DATA));
        if (newData != NULL) {
            data = newData;
            data[i-1] = parseLine(buffer);
        } else {
            printf("err allocating mem\n");
            exit(1);
        }
    }
    *count = i;
    return data;
}

DATA *loadFile(int *count) {
    FILE *file = fopen(INPUT, "r");
    if (file == NULL) {
        printf("err opening file\n");
        exit(1);
    }
    DATA *data = parseFile(count, file);

    if (fclose(file) == EOF) {
        printf("err closing file");
        exit(1);
    }
    return data;
}

void pp(DATA *data) {
    printf("%s", data[5].jmeno);
}

void printFile() {
    FILE *file = fopen(OUTPUT, "w");
    fprintf(file, "asd");
}

int main(void) {
    int count;
    DATA *data = loadFile(&count);
    pp(data);
    printf("%d", count);
    printFile();
    free(data);
    return 0;
}
