
#include <unistd.h>
#include <stdio.h>

#define ALIGN8(x) (((( (x) - 1) >> 3) << 3) + 8 )
#define ROUND_TO_MULTIPLE_OF_8(x) (((x) + 7) & ~7)

size_t get_page_size()
{
    return sysconf(_SC_PAGESIZE);
}

int main()
{
    printf("ALIGN8(1) = %zu\n", ALIGN8(1));
    printf("ALIGN8(2) = %zu\n", ALIGN8(2));

    printf("ALIGN8(7) = %zu\n", ALIGN8(7));
    printf("ALIGN8(8) = %zu\n", ALIGN8(8));
    printf("ALIGN8(9) = %zu\n", ALIGN8(9));
    printf("ALIGN8(10) = %zu\n", ALIGN8(10));

    printf("ALIGN8(14) = %zu\n", ALIGN8(14));
 
    printf("ALIGN8(23) = %zu\n", ALIGN8(23));
    printf("ALIGN8(24) = %zu\n", ALIGN8(24));
    printf("ALIGN8(25) = %zu\n", ALIGN8(25));
    printf("ALIGN8(26) = %zu\n", ALIGN8(26));

    printf("ALIGN8(32) = %zu\n", ALIGN8(32));
    printf("ALIGN8(33) = %zu\n", ALIGN8(33));
    printf("ALIGN8(34) = %zu\n", ALIGN8(34));

    printf("ALIGN8(83) = %zu\n", ALIGN8(83));
    printf("ALIGN8(84) = %zu\n", ALIGN8(84));
    printf("ALIGN8(85) = %zu\n", ALIGN8(85));

    printf("ALIGN8(87) = %zu\n", ALIGN8(87));
    printf("ALIGN8(88) = %zu\n", ALIGN8(88));
    printf("ALIGN8(89) = %zu\n", ALIGN8(89));

    printf("ALIGN8(90) = %zu\n", ALIGN8(90));
    printf("ALIGN8(100) = %zu\n", ALIGN8(100));
    printf("ALIGN8(120) = %zu\n", ALIGN8(120));
    printf("ALIGN8(121) = %zu\n", ALIGN8(121));
    printf("ALIGN8(122) = %zu\n", ALIGN8(122));
 
    printf("ALIGN8(1024) = %zu\n", ALIGN8(1024));

    printf("ALIGN8(1200) = %zu\n", ALIGN8(1200));
    printf("ROUND_TO_MULTIPLE_OF_8(750) = %zu\n", ROUND_TO_MULTIPLE_OF_8(750));
    printf("ALIGN8(3000000000001) = %zu\n", ALIGN8(3000000000001));
    printf("ROUND_TO_MULTIPLE_OF_8(3000000000001) = %zu\n", ROUND_TO_MULTIPLE_OF_8(3000000000001));

    return 0;
}