#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT "jizerska50.txt"
#define OUTPUT "vysledkova_listina.txt"
#define SIZE 200
#define DELI ",;:("

typedef struct {
    int hod;
    int min;
    int sec;
} CAS;

typedef struct {
    int sCislo;
    char prijmeni[50];
    char jmeno[50];
    int rocnik;
    char narodnost[4];
    CAS cas;
} DATA;

int timeConv(DATA *data, int i) {
    return data[i].cas.hod*3600+data[i].cas.min*60+data[i].cas.sec;
}

int getYear() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf ("%d", t->tm_year+1900);
    return t->tm_year+1900;
}

DATA parseLine(char *buffer) {
    DATA data;
    char *parse;
    int i = 0;
    parse = strtok(buffer, DELI);
    while (parse != NULL) {
        switch (i) {
            case 0:
                data.sCislo = atoi(parse);
            break;
            case 1:
                strcpy(data.prijmeni, parse);
            break;
            case 2:
                strcpy(data.jmeno, parse);
            break;
            case 3:
                data.rocnik = atoi(parse);
            break;
            case 4:
                strcpy(data.narodnost, parse);
            break;
            case 5:
                data.cas.hod = atoi(parse);
            break;
            case 6:
                data.cas.min = atoi(parse);
            break;
            case 7:
                data.cas.sec = atoi(parse);
            break;
        }
        i++;
        parse = strtok(NULL, DELI);
    }
    return data;
}

DATA *saveDataToFile(FILE *file, int *count) {
    DATA *data = NULL;
    char buffer[SIZE];
    int j = 0;
    fgets(buffer, SIZE, file);
    while (fgets(buffer, SIZE, file) != NULL) {
        j++;
        DATA *newData = (DATA *) realloc(data, j*sizeof(DATA));
        if (newData!= NULL) {
            data = newData;
            data[j-1] = parseLine(buffer);
        }
    }
    *count = j;
    return data;
}

DATA *openFile (int *count)  {
    FILE * f;
    f = fopen (INPUT,"r");
    if (f==NULL) {printf("error opening file"); return 0;}

    DATA *data = saveDataToFile(f, count);

    if (fclose(f) == EOF) {
        printf("error closing file");
    }
    return data;
}

void bubbleSort(DATA *data, int count) {
    for (int i = 0; i<count; i++) {
        for (int j = 0; j<(count-1); j++) {
            if (timeConv(data, j) > timeConv(data, j+1)) {
                DATA temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

void printData(DATA *data, int count) {
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%5d%20s%20s%8d%10s %02d:%02d:%02d\n",
            data[i].sCislo,
            data[i].prijmeni,
            data[i].jmeno,
            data[i].rocnik,
            data[i].narodnost,
            data[i].cas.hod,
            data[i].cas.min,
            data[i].cas.sec
        );
    }
}

int main(void) {
    int count;
    DATA *data = openFile(&count);
    printData(data, count);
    bubbleSort(data, count);
    printData(data, count);
    free(data);
    return 0;
}
