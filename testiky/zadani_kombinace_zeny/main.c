#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT "input.txt"
#define OUTPUT "vysledkova_listina_kombinace_zeny.txt"
#define SIZE 100
#define DELI " :,"

typedef struct {
    int sec;
    int mil;
}SLALOM;

typedef struct {
    int min;
    int sec;
    int mil;
}SJEZD;

typedef struct {
    int min;
    int sec;
    int mil;
}TOTAL;

typedef struct {
    int pC;
    char jmeno[30];
    char prijmeni[35];
    char stat[4];
    SJEZD sjezd;
    SLALOM slalom;
    TOTAL celkove;
}DATA;

int getYear() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_year+1900;
}

DATA parseLines(char *buffer) {
    DATA data;
    char *parse;
    int i = 0;
    parse = strtok(buffer, DELI);
    while (parse != NULL) {
        switch (i) {
        }
        i++;
        parse = strtok(buffer, DELI);
    }
    return data;
}

DATA *saveDataToFile(FILE *f, int *count) {
    DATA *data = NULL;
    char buffer[SIZE];
    int j = 0;
    fgets(buffer, SIZE, f);
    while (fgets(buffer, SIZE, f) != NULL) {
        j++;
        DATA *newData = (DATA *) realloc(data, j*sizeof(data));
        if (newData != NULL) {
            data = newData;
            data[j-1] = parseLines(buffer);
        }
    }
    *count = j;
    return data;
}

DATA *openFile(int *count) {
    FILE * f;
    f = fopen(INPUT, "r");
    if (f==NULL) {
        printf("error opening file.\n");
    }

    DATA *data = saveDataToFile(f, count);

    if ((fclose(f)) == EOF) {
        printf("error closing file\n");
    }
}

int main(void) {
    int count;
    DATA *data = openFile(&count);
    free(data);
    return 0;
}

DATA parseLine (char *buffer) {
    DATA data;
    int i = 0;
    char *parse;
    parse = strtok(buffer, DELI);
    while (parse != NULL) {
        switch (i) {

        }
        i++;
        parse = strtok(buffer, DELI);
    }
    return data;
}

DATA *parseFile(FILE *file,int *count) {
    DATA *data = NULL;
    char buffer[SIZE];
    int i = 0;
    fgets(buffer, SIZE, file);
    while (fgets(buffer, SIZE, file) != NULL) {
        i++;
        DATA *newData = realloc(data,i*sizeof(data));
        if (newData != NULL) {
            data = newData;
            data[i-1] = parseLine(buffer);
        }
    }
    *count = i;
    return data;
}


void bubbleSort (DATA *data, int count) {
    for (int i =0;i<count;i++) {
        for (int j =0;j<count;j++) {
            if (timeConv(data, j) > timeConv(data, j-1)) {
                DATA temp = data[j-1];
                data[j-1] = data[j];
                data[j] = temp;
            }
        }
    }
}

DATA *openfile(int *count) {
    FILE *f = fopen(INPUT, "r");
    if (f == NULL) {printf("error opening file\n");exit(1);}
    DATA *data = parseFile(f, count);
    if (fclose(f) == EOF) {printf("error closing file\n");exit(1);}
    return data;
}














DATA pparseLine(char *buffer) {
    char *parse;
    DATA data;
    int i = 0;
    parse = strtok(buffer, DELI);
    while (parse!=NULL) {
        switch (i) {

        }
        i++;
        parse = strtok(buffer, DELI);
    }
    return data;
}

DATA *pparseFile(FILE *file, int *count) {
    char buffer[SIZE];
    DATA *data = NULL;
    int i = 0;
    fgets(buffer, SIZE, file);
    while (fgets(buffer, SIZE, file) != NULL) {
        i++;
        DATA *newData = realloc(data, i*sizeof(data));
        if (newData == NULL) {
            data = newData;
            data[i-1] = parseLine(buffer);
        }
    }
    *count = i;
    return data;
}


DATA *popenFile (int *count) {
    FILE *f = fopen(INPUT, "r");
    if (f == NULL) {
        printf("error");
        exit(1);
    }

    DATA *data = pparseFile(f, count);

    if (fclose(f) != EOF) {
        printf("err");
        exit(1);
    }
    return data;
}

void bubble(DATA *data, int count) {
    for (int i =0;i<count;i++) {
        for (int j = 0; j<count;j++) {
            if (timeConv(data, j) > timeConv(data, j+1)) {
                DATA temp = data[j+1];
                data[j+1] = data[j];
                data[j] = temp;
            }
        }
    }
}

int gggetYear () {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("&d", t->tm_year+1900);
}







int ggetYear() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("%d", t->tm_year+1900);
}
