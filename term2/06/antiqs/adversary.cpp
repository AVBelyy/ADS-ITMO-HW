#include <stdlib.h>
#include <stdio.h>

int *val;
int ncmp;
int nsolid;
int candidate;
int gas;

#define freeze(x) val[x] = nsolid++

void not_so_q_sort(int *a, int left, int right, int(*compare)(const void*, const void*)) {
    int i, j, key, buf;
    key = a[(left + right) / 2];
    i = left;
    j = right;
    while (i <= j) {
        while (compare(&a[i], &key) < 0) i++;
        while (compare(&key, &a[j]) < 0) j--;
        if (i <= j) {
            buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
        if (left < j) not_so_q_sort(a, left, j, compare);
        if (i < right) not_so_q_sort(a, i, right, compare);
    }
}

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int cmp(const void *px, const void *py) {
    const int x = *(const int*)px;
    const int y = *(const int*)py;
    ncmp++;
    if(val[x]==gas && val[y]==gas) {
        if(x == candidate) {
            freeze(x);
        } else {
                freeze(y);
        }
    }
    if(val[x] == gas)
        candidate = x;
    else if(val[y] == gas)
        candidate = y;
    return val[x] - val[y];
}

int antiqsort(int n, int *a) {
    int i;
    int *ptr = (int*)malloc(n*sizeof(*ptr));
    val = a;
    gas = n - 1;
    nsolid = ncmp = candidate = 0;
    for (i = 0; i < n; i++) {
        ptr[i] = i;
        val[i] = gas;
    }
    not_so_q_sort(ptr, 0, n - 1, cmp);
    free(ptr);
    return ncmp;
}

int main() {
    int n = 10000;
    int* arr = (int*)malloc(n * sizeof(int));
    printf("ncmp = %d\n", antiqsort(n, arr));
    printf("Killer:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
    printf("Sorted:\n");
    not_so_q_sort(arr, 0, n - 1, compare);
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
    free(arr);
}
