//
//  main.c
//  C++(HomeTasks)
//
//  Created by Egor Safronov on 00.09.16.
//  Copyright © 2016 Egor Safronov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    int n, x1, x2, y1, y2;
    scanf("%d", &n);
    
    int *a = (int *) malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[n * i + j] = (i + 1) * (j + 1);
        }
    }
    
    while (1) {
        scanf("%d", &x1);
        if (x1 == 0) {
            free(a);
            return 0;
        } else {
            scanf("%d %d %d", &y1, &x2, &y2);
            x1--;
            y1--;
            if ((x1 < 0) || (y1 <= 0) || (x2 <= 0) || (y2 <= 0)) {
                printf("%s", "Invalid location");
            } else {
                if ((x1 > n) || (y1 > n) || (x2 > n) || (y2 > n)) {
                    printf("%s", "Invalid location");
                } else {
                    for (int i = x1; i < x2; i++) {
                        for (int j = y1; j < y2; j++) {
                            printf("%d ", a[i * n + j]);
                        }
                        printf("\n");
                    }
                }
            }
        }
    }
    
    return 0;
}
