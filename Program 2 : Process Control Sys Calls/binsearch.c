#include <stdio.h>

int main() {
    int a[50], n, ele;
    int beg, end, mid;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter sorted elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &ele);

    beg = 0;
    end = n - 1;

    while (beg <= end) {
        mid = (beg + end) / 2;

        if (a[mid] == ele) {
            printf("Element found at position %d\n", mid + 1);
            return 0;
        } else if (ele < a[mid]) {
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }

    printf("Element not found\n");
    return 0;
}
