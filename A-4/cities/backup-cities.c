#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CityID 0
#define PopulID 4
#define CntryID 5
#define COLUMNS 8

typedef struct {
    char *city;
    double popul;
    char *country;
} City;



void createCity(char* city, double popul, char* country, int i, City* cities){
    //City *newcity = (City*) malloc(sizeof(City));
    //newcity->city = city;
    //newcity->country = country;
    //newcity->popul = popul;

    int len1 = strlen(city) + 1;
    int len2 = strlen(country) + 1;

    cities[i].city = (char*) malloc(len1 * sizeof(char));
    cities[i].country = (char*) malloc(len2 * sizeof(char));
    //cities[i].popul = (char*) malloc(len2 * sizeof(char));

    strcpy(cities[i].city, city);
    strcpy(cities[i].country, country);
    cities[i].popul = popul;
    //return cities[i];
}


void printCity(FILE* newfile, int total, City* cities){
    //City* newcity = createCity(city, popul, country);

    int i;

    for (i = 0; i < total; i++){
        fprintf(newfile, "%s,%g,%s\n", cities[i].city, cities[i].popul, cities[i].country );
        printf("%s,%g,%s\n", cities[i].city, cities[i].popul, cities[i].country );
    }

    //free(newcity->city);
    //free(newcity->country);
    //free(newcity);
}


int cmpfunc(const void * a, const void * b) {
    City *cmpa = (City *) a;
    City *cmpb = (City *) b;


    return cmpb->popul - cmpa->popul;
}

int totalRows(FILE *fcities){
    int rows = 0;
    char buf[500];

    while( fgets(buf, 500, fcities) )
        rows++;
    rewind(fcities); /* resets back to the first line of file */
    return rows - 1; /*sub 1 to account for heading row */
}


void readcsv(FILE *fcities, City* cities){


    int rows = 0;
    int col = 0;
    char buf[500];
    //char* cty = (char *) malloc(n * sizeof(char));
    double popl;

    char* cty = (char*) malloc(sizeof(char));
    char* cntry = (char*) malloc(sizeof(char));
    char* tok = (char*) malloc(sizeof(char));


    while( fgets(buf, 500, fcities) )
    {
        if (rows == 0) rows++;
        else
        {
            /* Reading each column */
            for(col = 0; col <= 8; col++){
                for(tok = strtok(buf, ","); tok && *tok; tok = strtok(NULL, ",\n")  ){
                    if (col == CityID)
                        strcpy(cty, tok);
                    else if (col == PopulID)
                        popl = atof(tok);
                    else if (col == CntryID)
                        strcpy(cntry, tok);
                    col++;
                }
            }
            createCity(cty, popl, cntry, rows-1, cities);
            rows++;
        }
    }

}

void freeCities(City* cities, int n){

    free( cities );
}

int main(){


    FILE *fcities = fopen("cities.csv", "r");
    if (!fcities){
        printf("Can't open specified file");
        exit(0);

    }
    printf("opening...\n");
    int rows = totalRows(fcities);
    City cities[rows];

    readcsv(fcities, cities);

    FILE *funsorted = fopen("unsorted.csv", "a");
    FILE *fsorted = fopen("sorted.csv", "a");
    printCity(funsorted, rows, cities);

    printf("after sorting...\n");

    qsort(cities, rows, sizeof(City), cmpfunc);
    printCity(fsorted, rows, cities);

    fclose(fcities);
    fclose(fcities);
    freeCities(cities, rows);
    return 0;
}


