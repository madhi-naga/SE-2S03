#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50
/* Note: some code referenced to ppm.c file done in tutorial */

typedef struct pixel{
    int r, g, b;
} Pixel;

typedef struct image{
    int width, height, max;
    Pixel **data;
} Image;

typedef struct kernel{
    int n;
    int scale;
    int **matrix;
} Kernel;

int numFormat(float n);
Image *readPPM(char *newfile);
Kernel* readKer(char* newker);
Image* imageFilter(Image *image, Kernel *kernel);
int writePPM(char *newfile, Image *image);
void freeImage(Image* image);
void freeKernel(Kernel* kernel);


Image *readPPM(char *newfile){
    FILE *file = fopen(newfile, "r");
    if (!file){
        printf( "Unable to open %s", newfile);
        return NULL;
    }

    char format[3];
    fscanf(file, "%s\n", format);
    if (strcmp(format, "P3")) 
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

Kernel* readKer(char* newker){
    FILE *fkern = fopen(newker, "r");
    if (!fkern){
        printf("Unable to open %s\n", newker);
        return NULL;
    }
    Kernel *kernel = (Kernel*) malloc(sizeof(Kernel));

    fscanf(fkern, "%d", &(kernel->n));
    fscanf(fkern, "%d", &(kernel->scale));
    int nsize = kernel->n;


    int i, j;
    kernel->matrix = malloc( nsize * sizeof(int *) );

    for(i = 0; i < nsize; i++){
        kernel->matrix[i] = malloc( nsize * sizeof(int *) );
        for(j = 0; j < nsize; j++) {
            fscanf(fkern, "%d", &(kernel->matrix[i][j]) );
            
        }
    }
    fclose(fkern);
    return kernel;
}

Image* imageFilter(Image *image, Kernel *kernel){

    int i, j, x, y;
    

    Image *newimage = malloc(sizeof(Image));
    if(!newimage)
        return NULL;

    newimage->width = image->width;
    newimage->height = image->height;
    newimage->max = image->max;

    newimage->data = malloc(sizeof(Pixel *) * image->height);
    for ( i = 0; i < image->height; i++)
        newimage->data[i] = malloc(sizeof(Pixel) * image->width);

    float sumr = 0;
    float sumg = 0;
    float sumb = 0;
    int zero = 0;
    int pad = (kernel->n - 1) / 2; 

    for (i = 0; i < image->height; i++){
        for (j = 0; j < image->width; j++){
            /* zero padding output image */
            if (  (i < pad || j < pad) || (image->height-i-1 < pad || image->width-j-1 < pad) ){
                newimage->data[i][j].r = zero;
                newimage->data[i][j].g = zero;
                newimage->data[i][j].b = zero;
            }
            else{
                /* multiplying each kernel entry with a corresponding image pixel */
                for ( x = (-1*pad); x <= pad; x++){
                    for ( y = (-1*pad); y <= pad; y++){
                        sumr += image->data[i+x][j+y].r * kernel->matrix[x+pad][y+pad];
                        sumg += image->data[i+x][j+y].g * kernel->matrix[x+pad][y+pad];
                        sumb += image->data[i+x][j+y].b * kernel->matrix[x+pad][y+pad];
                    }
                }
                sumr = (sumr / kernel->scale);
                sumg = (sumg / kernel->scale);
                sumb = (sumb / kernel->scale);
                newimage->data[i][j].r = numFormat(sumr);
                newimage->data[i][j].g = numFormat(sumg);
                newimage->data[i][j].b = numFormat(sumb);

                sumr = 0;
                sumg = 0;
                sumb = 0;
            }
        }
    }
    freeImage(image);
    return newimage;
}

int numFormat(float n){
    int intnum = (int) n;
    if(n > 255)
        intnum = 255;
    else if(n < 0)
        intnum = 0;

    return intnum;
}

int writePPM(char *newfile, Image *image){
    FILE *fimage = fopen(newfile, "w");
    if (!fimage){
        printf("Unable to open %s", newfile);
        return -1;
    }

    fprintf(fimage, "P3\n");
    fprintf(fimage, "%u %u\n", image->width, image->height);
    fprintf(fimage, "%u\n", image->max );

    int i, j;
    for (i = 0; i < image->height; i++){

        for (j = 0; j < image->width; j++){
            fprintf(fimage, "%u %u %u ", image->data[i][j].r, image->data[i][j].g, image->data[i][j].b );
        }
        fprintf(fimage, "\n");

    }
    fclose(fimage);
    return 0;
}

void freeImage(Image* image){
    int i;
    for (i = 0; i < image->height; i++)
        free(image->data[i]);
    free(image->data);
    free(image);
}

void freeKernel(Kernel* kernel){
    int i;
    for (i = 0; i < kernel->n; i++)
        free(kernel->matrix[i]);
    free(kernel->matrix);
    free(kernel);
}

int main(int argc, char** argv){

    char* finput = (char*) malloc(N * sizeof(char));
    char* fkernel = (char*) malloc(N * sizeof(char));
    char* foutput = (char*) malloc(N * sizeof(char));

    if (argc != 4){
        printf("Incorrect number of arguments\n");
        printf("Format: ./filter input.ppm kernel output.ppm \n");
        return -2;
    }
    strcpy(finput, argv[1]);
    strcpy(fkernel, argv[2]);
    strcpy(foutput, argv[3]);

    Image* img = readPPM(finput);
    printf("opened %s\n", finput);
    Kernel* kern = readKer(fkernel);
    printf("opened %s\n", fkernel);

    if (!img)
        return -1;
    if (!kern)
        return -1;

    Image* imgmod = imageFilter(img, kern);
    if (!imgmod)
        return -1;

    writePPM(foutput, imgmod);
    printf("wrote to %s\n", foutput);
    free(finput);
    free(fkernel);
    free(foutput);
    freeImage(imgmod);
    freeKernel(kern);

    return 0;
}
