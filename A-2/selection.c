#include <stdio.h>

#define N 10

void selection_sort(int a[], int n);

int main(void)
{
  int a[N], i;

    printf("Enter %d numbers to be sorted: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &a[i]);

  selection_sort(a, N);

  printf("In sorted order:");
  for (i = 0; i < N; i++)
    printf(" %d", a[i]);
  printf("\n");

  return 0;
}

void selection_sort(int a[], int n){
    int i, int large, temp;
    large = n-1;
    for(i = 0; i < n, i++ ){
        if(a[i] < a[large])
            large = i;
        }
    a[n] = temp;
    a[large] = a[n];
    a[n] = a[large];
    selection_sort(a, n-1);

    }
}