
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ALIGN8(x) ((((x) - 1) >> 3) << 3) + 8
#define Arena_Hdr 64
#define Bin_Hdr 40


int main(int ac, char **av) {

    // if (ac != 2) {
    //     printf("Usage: ./zone_size <coef>\n");
    //     return 1;
    // }

    // int coef = atoi(av[1]);
    int page_size =  4096;

    for (int k = 0; k <= 32; k++) {
        int best_compromise = -1;
        int best_result = 400;

        for (int i = 1; i < 1000; i++) {
          int mmap_size = page_size * k;
          int align = ALIGN8(i);
          int bin_size = mmap_size / align;
          int res = (bin_size + Bin_Hdr) * 100;
          int remain = mmap_size - (res + Arena_Hdr);

          if (remain >= 0 && remain < best_result) {
            best_compromise = align;
            best_result = remain;
          }
        }
        if (best_compromise < 0) {
          continue;
        }
        printf("coef = %d\n", k);
        printf("Best compromise: %d\n", best_compromise);
        printf("zone_size = %d\n", (page_size * k) / best_compromise);
        printf("remain = %d\n", best_result);
        printf("---------\n");
    }

    return 0;
}

// mmap_size - ( (mmap_size/(128)+40 ) * 100 + 64)

/*

./zone_size 4 
Best compromise: 136
zone_size = 120
remain = 320

./zone_size 6
Best compromise: 120
zone_size = 204
remain = 112

./zone_size 10
Best compromise: 112
zone_size = 365
remain = 396

 ./zone_size 26
Best compromise: 104
zone_size = 1024
remain = 32

./zone_size 27
Best compromise: 104
zone_size = 1063
remain = 228
*/