#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INPUT "beh.txt"
#define OUPUT "vystupni-soubor.txt"
#define DELIMETERS ";.:"
#define SIZE 100

typedef struct {
    int hour;
    int min;
    int sec;
} TIME;

typedef struct {
    int day;
    int year;
    int month;
}BIRTH;

typedef struct {
    int rank;
    char firstName [20];
    char lastName [20];
    BIRTH birth;
    char country [5];
    char club [50];
    TIME time;
}DATA;

DATA parseLines (char *buffer) {
    DATA data;
    int i = 0;
    char *parse;
    parse = strtok(buffer, DELIMETERS);
    while(parse != NULL) {
        i++;
        switch (i) {
            case 1:
                data.rank = atoi(parse);
            break;
            case 2:
                strcpy(data.lastName, parse);
            break;
            case 3:
                strcpy(data.firstName, parse);
            break;
            case 4:
                data.birth.day = atoi(parse);
            break;
            case 5:
                data.birth.month = atoi(parse);
            break;
            case 6:
                data.birth.year = atoi(parse);
            break;
            case 7:
                strcpy(data.country, parse);
            break;
            case 8:
                strcpy(data.club, parse);
            break;
            case 9:
                data.time.hour = atoi(parse);
            break;
            case 10:
                data.time.min = atoi(parse);
            break;
            case 11:
                data.time.sec = atoi(parse);
        }
        parse = strtok(NULL, DELIMETERS);
    }
    return data;
}

DATA *saveDataToStruct (FILE *file, int *count) {
    DATA *data = NULL;
    char buffer[SIZE];
    int j = 0;
    fgets(buffer, SIZE, file);
    while(fgets(buffer, SIZE, file) != NULL) {
        j++;
        DATA *newData = (DATA *) realloc(data, j*sizeof(DATA));
        
        if (newData != NULL) {
            data = newData;
            data[j-1] = parseLines(buffer);
        }
    }
    *count = j;
    return data;
}

DATA *openFile (int *count) {
    FILE *file = fopen(INPUT, "r");
    if (file == NULL) {
        printf("error opening file\n");
    } else {
        DATA *data = saveDataToStruct(file, count);
        if (fclose(file) == EOF) {
            printf("error closing file\n");
        }
        return data;
    }
}

int main(void)
{
    int count;
    DATA *data = openFile(&count);
    printf("%d", data[5].birth.month);
    free(data);
    return 0;
}
