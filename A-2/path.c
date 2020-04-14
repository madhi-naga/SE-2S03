#include <stdio.h>

int n, m, i, j, k, l;
int A[20];
int path[20][2];

int find_path (int n, int m, int A[], int i, int j, int k, int l, int path [][2]){

    int A2[n][m];
    int z = 0;
    int x, y;
    /* Saving to new 2D matrix*/
    for( x = 0; x < n; x++)
    {
        for( y = 0; y < m; y++)
        {
        A2[x][y] = A[z++];
        }
    }

    int count = 1;
    x = i;
    y = j;

    /*Checking for a valid path*/
    while((x<n) && (y<m))
    {
        if((x == k) && (y == l) && (A2[x][y] == 0))
        {
            return count;
        }
        else
        {         
            if(A2[x][y+1] == 0){ /*checking right*/
                count++; 
                y++;
            }
            else if(A2[x-1][y] == 0){ /*checking up*/
                count++;
                x--;
            }
            else if(A2[x+1][y] == 0){ /*checking down*/
                count++;
                x++;
            }
            else if(A2[x][y-1] == 0){ /*checking left*/
                count++;
                y--;
            } 
        }
    }
    return count;
}

/* Insert main here*/
int main(){
    
    int A[] = { 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 };
    
    printf( "\n%d\n", find_path ( 3, 4, A, 1, 1, 0, 3, path));
    return 1;
}
