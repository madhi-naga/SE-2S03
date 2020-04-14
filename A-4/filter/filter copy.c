#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct pixel{
    int r, g, b;
} Pixel;

typedef struct image{
    int width, height, max;
    Pixel **data;
} Image;

typedef struct kernal{
    int n;
    int scale;
    int **matrix;
} Kernal;


void printPPM(Image *image){
    for (int i = 0; i < image-> height; i++){
        for (int j = 0; j < image->width; j++){
            printf("#%02x%02x%02x ", image->data[i][j].r, image->data[i][j].g, image->data[i][j].b);
        }
        printf("\n");
    }
}

Image *readPPM(char *newfile){
    FILE *file = fopen(newfile, "r");
    if (!file){
        printf( "Unable to open %s", newfile);
        return NULL;
    }

    char format[3];
    fscanf(file, "%s\n", format);
    if (strcmp(format, "P3")) //in .ppm, P3 is type of image format
        return NULL;


    Image *image = malloc(sizeof(Image));

    if (fscanf(file, "%u %u %u", &image->width, &image->height, &image->max ) != 3)
        return NULL;

    image->data = malloc(sizeof(Pixel *) * image->height);

    unsigned int i, j;
    for ( i = 0; i < image->height; i++)
        image->data[i] = malloc(sizeof(Pixel) * image->width);

    for ( i = 0; i < (image->height); i++){
        for ( j = 0; j < (image->width); j++){

            int pixels_read = fscanf(file, "%u %u %u", &(image->data[i][j].r),
            &(image->data[i][j].g), &(image->data[i][j].b) );

            if (pixels_read != 3)
                return NULL;

        }
    }
    fclose(file);
    return image;

}

Kernal* readKer(char* newker){
    FILE *fkern = fopen(newker, "r");
    if (!fkern){
        printf("Unable to open %s", newker);
        return NULL;
    }
    Kernal *kernal = (Kernal*) malloc(sizeof(Kernal));

    fscanf(fkern, "%d", &(kernal->n));
    fscanf(fkern, "%d", &(kernal->scale));
    int nsize = kernal->n;


    int i, j;
    kernal->matrix = malloc( nsize * sizeof(int *) );

    for(i = 0; i < nsize; i++){
        kernal->matrix[i] = malloc( nsize * sizeof(int *) );
        for(j = 0; j < nsize; j++) {
            fscanf(fkern, "%d", &(kernal->matrix[i][j]) );
            //printf("%d", kernal->matrix[i][j]);
        }
    }
    fclose(fkern);
    return kernal;
}

Image* imgFilter(Image *image, Kernal *kernal ){

    int i, j, x, y;
    //Pixel* sumpix = (Pixel*) malloc(sizeof(Pixel));

    Image *newimage = malloc(sizeof(Image));
    newimage->width = image->width;
    newimage->height = image->height;
    newimage->max = image->max;
    newimage->data = malloc(sizeof(Pixel *) * image->height);
    for ( i = 0; i < image->height; i++)
        newimage->data[i] = malloc(sizeof(Pixel) * image->width);

    double sumr = 0;
    double sumg = 0;
    double sumb = 0;
    int zero = 0;
    int pad = (kernal->n - 1) / 2;

    for ( i = 0; i < image->height  ; i++){

        for ( j = 0; j < image->width; j++){
            if (  (i < pad || j < pad) || (image->height-i-1 < pad || image->width-j-1 < pad) ){
                newimage->data[i][j].r = zero;
                newimage->data[i][j].g = zero;
                newimage->data[i][j].b = zero;
            }
            else{
                for ( x = (-1*pad); x <= pad; x++){
                    for ( y = (-1*pad); y <= pad; y++){
                        sumr += image->data[i+x][j+y].r * kernal->matrix[x+pad][y+pad];
                        sumg += image->data[i+x][j+y].g * kernal->matrix[x+pad][y+pad];
                        sumb += image->data[i+x][j+y].b * kernal->matrix[x+pad][y+pad];
                    }
                }
                sumr = (sumr / kernal->scale);
                sumg = (sumg / kernal->scale);
                sumb = (sumb / kernal->scale);
                newimage->data[i][j].r = sumr;
                newimage->data[i][j].g = sumb;
                newimage->data[i][j].b = sumg;

                sumr = 0;
                sumg = 0;
                sumb = 0;
            }
        }
    }
    return newimage;
}

int writePPM(char *newfile, Image *image){
    FILE *file = fopen(newfile, "w");
    if (!file){
        printf("Unable to open %s", newfile);
        return -1;
    }

    fprintf(file, "P3\n");
    fprintf(file, "%u %u\n", image->width, image->height);
    fprintf(file, "%u\n", image->max );

    int i, j;
    for ( i = 0; i < image->height; i++){

        for ( j = 0; j < image->width; j++){
            fprintf(file, "%u %u %u ", image->data[i][j].r, image->data[i][j].g, image->data[i][j].b );
        }
        fprintf(file, "\n");

    }
    fclose(file);
    return 0;

}

int main(){
    printf("opened\n");
    Image* img = readPPM("image.ppm");
    Kernal* kern = readKer("kernal");

    if (!img){
        printf("rip");
        return -1;
    }
    //printPPM(img);
    printf("wrote1");
    writePPM("output.ppm", img);


    Image* imgmod = imgFilter(img, kern);
    printf("wrote2");
    writePPM("output2.ppm", imgmod);


    return 0;
}
