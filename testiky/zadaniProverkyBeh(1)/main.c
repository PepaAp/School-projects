#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100
#define DELI ";:"
#define DELICAS "."
#define INPUT "beh.txt"
#define OUTPUT "output.txt"

typedef struct {
    int r;
    int m;
    int d;
}NAROZENI;

typedef struct {
    int h;
    int m;
    int s;
}CAS;

typedef struct {
    int sC;
    char prijmeni[35];
    char jmeno[35];
    char stat[4];
    char oddil[70];
    NAROZENI narozeni;
    CAS cas;
}DATA;

int convTime(DATA *data,int i) {
    return data[i].cas.h*3600+data[i].cas.m*60+data[i].cas.s;
}

void findCzechs(DATA *data, int count) {
    int c = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].stat, "CZE")==0) {
            c++;
        }
    }
    printf("%d cechu\n", c);
}

void bubbleSort(DATA *data, int count) {
    for (int i =0; i<count;i++) {
        for (int j=0;j<count-1;j++) {
            if (convTime(data, j) > convTime(data, j+1)) {
                DATA tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
}

DATA parseBirth(char *buffer) {
    int j = 0;
    char *pparse;
    DATA data;
    pparse = strtok(buffer, DELICAS);
    while (pparse != NULL) {
        switch (j) {
            case 0:
                data.narozeni.d = atoi(pparse);
            break;
            case 1:
                data.narozeni.m = atoi(pparse);
            break;
            case 2:
                data.narozeni.r = atoi(pparse);
            break;
        }
        j++;
        pparse = strtok(NULL, DELICAS);
    }
}

DATA parseLine(char *buffer) {
    DATA data;
    char *parse;
    int i = 0;
    parse = strtok(buffer, DELI);
    while (parse != NULL) {
        switch (i) {
            case 0:
                data.sC = atoi(parse);
            break;
            case 1:
                strcpy(data.prijmeni, parse);
            break;
            case 2:
                strcpy(data.jmeno, parse);
            break;
            case 3:
                parseBirth(parse);
                break;
            case 4:
                strcpy(data.stat, parse);
            break;
            case 5:
                strcpy(data.oddil, parse);
            break;
            case 6:
                data.cas.h = atoi(parse);
            break;
            case 7:
                data.cas.m = atoi(parse);
            break;
            case 8:
                data.cas.s = atoi(parse);
            break;
        }
        i++;
    }
    return data;
}

DATA *parseFile(FILE *file, int *count) {
    DATA *data = NULL;
    char buffer[SIZE];
    int i = 0;
    fgets(buffer, SIZE, file);
    while (fgets(buffer, SIZE, file)!=NULL) {
        i++;
        DATA *newData = (DATA*) realloc(data, i*sizeof(DATA));
        if (newData != NULL) {
            data = newData;
            data[i-1] = parseLine(buffer);
        } else {
            printf("err allocating memorry\n");
            exit(1);
        }
    }
    *count = i;
    return data;
}

DATA *openFile(int *count) {
    FILE *f = fopen(INPUT, "r");
    if (f == NULL) {
        printf("err");
        exit(1);
    }
    DATA *data = parseFile(f, count);
    if (fclose(f) == EOF) {
        printf("err");
        exit(1);
    }
    return data;
}

void printData (DATA *data, int count) {
    for (int i =0;i<count;i++) {
        printf("%25s %25s %02d:%02d:%02d\n", data[i].jmeno, data[i].prijmeni, data[i].cas.h, data[i].cas.m, data[i].cas.s);
    }
}

int getYear() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_year+1900;
}

void findOldest(DATA *data, int count) {
    int a =0;
    for (int i =0;i<count;i++) {
        if (data[a].narozeni.r > data[i].narozeni.r) {
            a=i;
        }
    }
    printf("%s %s je nejstarsi s vekem %d let.\n", data[a].jmeno, data[a].prijmeni, getYear()-data[a].narozeni.r);
}


int main(void) {
    int count ;
    DATA *data = openFile(&count);
    printData(data, count);
    findOldest(data, count);
    printf("----------------------------------------\n");
    bubbleSort(data, count);
    printData(data, count);
    findCzechs(data, count);
    free(data);
    return 0;
}
