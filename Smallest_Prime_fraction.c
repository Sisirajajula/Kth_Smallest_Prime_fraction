/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int numerator;
    int denominator;
}Fraction;
int compareFractions(const void* a, const void* b) {
  Fraction* f1 = (Fraction*)a;
  Fraction* f2 = (Fraction*)b;
  return f1->numerator * f2->denominator - f1->denominator * f2->numerator;
}
int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize) 
{
    if (arrSize < 2 || arr == NULL || k < 1 || k > arrSize * (arrSize-1) / 2)
    {
        *returnSize = 0;
        return NULL;
    }
    int pq_capacity = arrSize * (arrSize - 1) / 2;
    int pq_size = 0;
    Fraction * pq = malloc(sizeof(Fraction) * pq_capacity);
    if (!pq)
    {
        perror("Error allocating memory");
        abort();
    }
    for (int i = 0 ; i < arrSize - 1; i++)
    {
        for (int j = i + 1; j < arrSize; j++)
        {
            int num = arr[i];
            int denom = arr[j];
            Fraction fraction = {num, denom};
            pq[pq_size++] = fraction;
            /*int idx = pq_size - 1;
            while (idx > 0 && (pq[idx].numerator * pq[idx - 1].denominator < pq[idx].denominator * pq[idx-1].numerator))
            {
                Fraction temp = pq[idx];
                pq[idx] = pq[idx - 1];
                pq[idx - 1] = temp;
                idx--;
            }*/            
        }
    } 
    qsort(pq, pq_size, sizeof(Fraction), compareFractions);

    Fraction kth_element= pq[k -1];
    free(pq);
    int *result = malloc(sizeof(int) * 2);
    *returnSize = 2;
    result[0] = kth_element.numerator;
    result[1] = kth_element.denominator;
    return result;
}
int main() {
    int arr[] = {1, 2, 3, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int returnSize;
    int* result = kthSmallestPrimeFraction(arr, arrSize, 3, &returnSize);
    if (result) {
        printf("Result: %d/%d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No result found.\n");
    }
    return 0;
}
