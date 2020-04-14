#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CityID 0
#define PopulID 4
#define CntryID 5
#define N 50
#define BUFSIZE 500

typedef struct {
    char *city;
    char* popul;
    char *country;
} City;

void createCity(char* city, char* popul, char* country, int i, City* cities);
void printCity(FILE* newfile, int total, City* cities);
int cmpfunc(const void * a, const void * b);
int totalRows(FILE *fcities);
void readcsv(FILE *fcities, City* cities);
void freeCities(City* cities, int n);


void createCity(char* city, char* popul, char* country, int i, City* cities){

    int lencty = strlen(city) + 1;
    int lencny = strlen(country) + 1;
    int lenpop = strlen(popul) + 1;

    cities[i].city = (char*) malloc(lencty * sizeof(char));
    cities[i].country = (char*) malloc(lencny * sizeof(char));
    cities[i].popul = (char*) malloc(lenpop * sizeof(char));

    strcpy(cities[i].city, city);
    strcpy(cities[i].country, country);
    strcpy(cities[i].popul, popul);
}


void printCity(FILE* newfile, int total, City* cities){

    int i;
    /* outputting to new file */
    for (i = 0; i < total; i++){
        fprintf(newfile, "%s,%s,%s\n", cities[i].city, cities[i].popul, cities[i].country );
        printf("%s,%s,%s\n", cities[i].city, cities[i].popul, cities[i].country );
    }
}


int cmpfunc(const void * a, const void * b) {
    City *cmpa = (City *) a;
    City *cmpb = (City *) b;

    double apop = atof(cmpa->popul);
    double bpop = atof(cmpb->popul);

    return bpop - apop;
}

int totalRows(FILE *fcities){
    int rows = 0;
    char buf[BUFSIZE];

    while( fgets(buf, BUFSIZE, fcities) )
        rows++;
    rewind(fcities); /* resets back to the first line of file */
    return rows - 1; /*sub 1 to account for heading row */
}


void readcsv(FILE *fcities, City* cities){


    int rows = 0;
    int col;
    char buf[BUFSIZE];

    char* cty = (char*) malloc(N*sizeof(char));
    char* cntry = (char*) malloc(N*sizeof(char));
    char* popl = (char*) malloc(N*sizeof(char));
    char* tok = (char*) malloc(N*sizeof(char));


    while( fgets(buf, BUFSIZE, fcities) ) /* Reading each row */
    {
        if (rows == 0) rows++;
        else
        {
            /* Reading each column */
            for(col = 0; col <= CntryID; col++){
                for(tok = strtok(buf, ","); tok && *tok; tok = strtok(NULL, ",\n")  ){
                    if (col == CityID)
                        strcpy(cty, tok);
                    else if (col == PopulID)
                        strcpy(popl, tok);
                    else if (col == CntryID)
                        strcpy(cntry, tok);
                    col++;
                }
            }
            createCity(cty, popl, cntry, rows-1, cities);
            rows++;
        }
    }
    free(cty);
    free(cntry);
    free(popl);
    free(tok);
}


void freeCities(City* cities, int n){
    int i;
    for(i=0; i<=n; i++){
        free(cities[i].city);
        free(cities[i].country);
        free(cities[i].popul);
    }
}

int main(){
    char* filename = "cities.csv";
    char* filesort = "sorted.csv";
    FILE *fcities = fopen(filename, "r");
    if (!fcities){
        printf("Cannot open %s\n", filename);
        exit(0);
    }

    int rows = totalRows(fcities);
    printf("Opened %s\n", filename);
    City cities[rows];

    readcsv(fcities, cities);

    FILE *fsorted = fopen(filesort, "w");
    if (!fsorted){
        printf("Cannot open %s\n", filesort);
        exit(0);
    }
    qsort(cities, rows, sizeof(City), cmpfunc);
    printf("Sorted %s\n", filesort);
    /* printCity(fsorted, rows, cities); */

    fclose(fcities);
    fclose(fsorted);
    freeCities(cities, rows); 
    return 0;
}


