#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DELI ";:"
#define DELIBIRTH "."
#define INPUT "beh.txt"
#define OUTPUT "output.txt"
#define SIZE 100

typedef struct {
    int y;
    int m;
    int d;
} NAROZENI;

typedef struct {
    int h;
    int m;
    int s;
}CAS;

typedef struct {
    int id;
    char jmeno[30];
    char prijmeni[30];
    char stat[4];
    char klub[50];
    CAS cas;
    NAROZENI narozeni;
}DATA;

DATA parseLine(char *buffer) {
    char *parse;
    int k = 0;
    int j = 1;
    DATA data;

    parse = strtok(buffer, DELI);

    while (parse != NULL) {
        switch (j) {
            case 1:
                data.id = atoi(parse);
            break;

            case 2:
                strcpy(data.prijmeni, parse);
            break;

            case 3:
                strcpy(data.jmeno, parse);
            break;

            case 4: {
                char *cparse = strtok(parse, DELIBIRTH);
                while (cparse != NULL) {
                    switch (k) {
                        case 0:
                            data.narozeni.d = atoi(cparse);
                        break;
                        case 1:
                            data.narozeni.m = atoi(cparse);
                        break;
                        case 2:
                            data.narozeni.y = atoi(cparse);
                        break;
                    }
                    cparse = strtok(NULL, DELIBIRTH);
                    k++;
                }
                break;
            }

            case 5:
                strcpy(data.klub, parse);
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

        parse = strtok(NULL, DELI);
        j++;
    }

    return data;
}


DATA *parseFile(FILE *file, int *count) {
    char buffer[SIZE];
    int i = 0;
    DATA *data =NULL;
    fgets(buffer, SIZE, file);
    while (fgets(buffer, SIZE, file)!=NULL) {
        i++;
        DATA *newData = realloc(data,i*sizeof(DATA));
        if (newData == NULL) {printf("err allocating memory\n");exit(1);}
        data = newData;
        data[i-1] = parseLine(buffer);
    }
    *count = i;
    return data;
}

DATA *openFile(int *count) {
    FILE *file = fopen(INPUT, "r");
    if (file == NULL) {printf("err opening file\n"); exit(1);}
    DATA *data = parseFile(file, count);
    if (fclose(file)==EOF){printf("err\n");exit(1);}
    return data;
}

int getYear() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    return t->tm_year+1900;
}

void oldest(DATA *data, int count) {
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (data[index].narozeni.y > data[i+1].narozeni.y) index = i;
    }
    printf("Nejstarsi zavodnik je %s %s s vekem %d let.\n", data[index].jmeno, data[index].prijmeni,getYear()-data[index].narozeni.y);
}

int convTime(DATA *data, int index) {
    return data[index].cas.h*3600+data[index].cas.m*60+data[index].cas.s;
}

void bubbleSort(DATA *data, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (convTime(data, j) > convTime(data, j+1)) {
                DATA tmp = data[j+1];
                data[j+1] = data[j];
                data[j] = tmp;
            }
        }
    }
}

void printData(DATA *data, int count) {
    for (int i = 0;i<count;i++) {
        printf("%02d:%02d:%02d\n", data[i].cas.h, data[i].cas.m, data[i].cas.s);
    }
}

int main(void) {
    int count;
    DATA *data = openFile(&count);
    oldest(data, count);
    printData(data, count);
    bubbleSort(data, count);
    printf("-----------------------------------------------\n");
    printData(data, count);
    free(data);
    return 0;
}
