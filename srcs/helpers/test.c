
#include <unistd.h>
#include <stdio.h>

#define ALIGN8(x) (((( (x) - 1) >> 3) << 3) + 8 )

size_t get_page_size()
{
    return sysconf(_SC_PAGESIZE);
}

int main()
{
    printf("ALIGN8(1) = %zu\n", ALIGN8(1));
    printf("ALIGN8(2) = %zu\n", ALIGN8(2));
    printf("ALIGN8(3) = %zu\n", ALIGN8(3));
    printf("ALIGN8(4) = %zu\n", ALIGN8(4));
    printf("ALIGN8(5) = %zu\n", ALIGN8(5));
    printf("ALIGN8(6) = %zu\n", ALIGN8(6));
    printf("ALIGN8(7) = %zu\n", ALIGN8(7));
    printf("ALIGN8(8) = %zu\n", ALIGN8(8));
    printf("ALIGN8(9) = %zu\n", ALIGN8(9));
    printf("ALIGN8(10) = %zu\n", ALIGN8(10));
    printf("ALIGN8(11) = %zu\n", ALIGN8(11));
    printf("ALIGN8(12) = %zu\n", ALIGN8(12));
    printf("ALIGN8(13) = %zu\n", ALIGN8(13));
    printf("ALIGN8(14) = %zu\n", ALIGN8(14));
    printf("ALIGN8(15) = %zu\n", ALIGN8(15));
    printf("ALIGN8(16) = %zu\n", ALIGN8(16));
    printf("ALIGN8(17) = %zu\n", ALIGN8(17));
    printf("ALIGN8(18) = %zu\n", ALIGN8(18));
    printf("ALIGN8(19) = %zu\n", ALIGN8(19));
    printf("ALIGN8(20) = %zu\n", ALIGN8(20));
    printf("ALIGN8(21) = %zu\n", ALIGN8(21));
    printf("ALIGN8(22) = %zu\n", ALIGN8(22));
    printf("ALIGN8(23) = %zu\n", ALIGN8(23));
    printf("ALIGN8(24) = %zu\n", ALIGN8(24));
    printf("ALIGN8(25) = %zu\n", ALIGN8(25));
    printf("ALIGN8(26) = %zu\n", ALIGN8(26));
    printf("ALIGN8(27) = %zu\n", ALIGN8(27));
    printf("ALIGN8(28) = %zu\n", ALIGN8(28));
    printf("ALIGN8(29) = %zu\n", ALIGN8(29));
    printf("ALIGN8(30) = %zu\n", ALIGN8(30));
    printf("ALIGN8(31) = %zu\n", ALIGN8(31));
    printf("ALIGN8(32) = %zu\n", ALIGN8(32));
    printf("ALIGN8(33) = %zu\n", ALIGN8(33));
    printf("ALIGN8(34) = %zu\n", ALIGN8(34));
    printf("ALIGN8(35) = %zu\n", ALIGN8(35));
    printf("ALIGN8(36) = %zu\n", ALIGN8(36));
    printf("ALIGN8(37) = %zu\n", ALIGN8(37));
    printf("ALIGN8(38) = %zu\n", ALIGN8(38));
    printf("ALIGN8(39) = %zu\n", ALIGN8(39));
    printf("ALIGN8(40) = %zu\n", ALIGN8(40));
    printf("ALIGN8(41) = %zu\n", ALIGN8(41));
    printf("ALIGN8(50) = %zu\n", ALIGN8(50));
    printf("ALIGN8(60) = %zu\n", ALIGN8(60));
    printf("ALIGN8(64) = %zu\n", ALIGN8(64));
    printf("ALIGN8(70) = %zu\n", ALIGN8(70));
    printf("ALIGN8(80) = %zu\n", ALIGN8(80));
    printf("ALIGN8(81) = %zu\n", ALIGN8(81));
    printf("ALIGN8(82) = %zu\n", ALIGN8(82));
    printf("ALIGN8(83) = %zu\n", ALIGN8(83));
    printf("ALIGN8(84) = %zu\n", ALIGN8(84));
    printf("ALIGN8(85) = %zu\n", ALIGN8(85));
    printf("ALIGN8(86) = %zu\n", ALIGN8(86));
    printf("ALIGN8(87) = %zu\n", ALIGN8(87));
    printf("ALIGN8(88) = %zu\n", ALIGN8(88));
    printf("ALIGN8(89) = %zu\n", ALIGN8(89));

    printf("ALIGN8(90) = %zu\n", ALIGN8(90));
    printf("ALIGN8(100) = %zu\n", ALIGN8(100));
    printf("ALIGN8(120) = %zu\n", ALIGN8(120));
    printf("ALIGN8(121) = %zu\n", ALIGN8(121));
    printf("ALIGN8(122) = %zu\n", ALIGN8(122));
    printf("ALIGN8(123) = %zu\n", ALIGN8(123));
    printf("ALIGN8(128) = %zu\n", ALIGN8(128));
    printf("ALIGN8(129) = %zu\n", ALIGN8(129));
    printf("ALIGN8(130) = %zu\n", ALIGN8(130));
    printf("ALIGN8(131) = %zu\n", ALIGN8(131));
    printf("ALIGN8(132) = %zu\n", ALIGN8(132));
    printf("ALIGN8(133) = %zu\n", ALIGN8(133));
    printf("ALIGN8(134) = %zu\n", ALIGN8(134));
    printf("ALIGN8(135) = %zu\n", ALIGN8(135));
    printf("ALIGN8(136) = %zu\n", ALIGN8(136));
    printf("ALIGN8(137) = %zu\n", ALIGN8(137));
    printf("ALIGN8(138) = %zu\n", ALIGN8(138));
    printf("ALIGN8(139) = %zu\n", ALIGN8(139));
    printf("ALIGN8(140) = %zu\n", ALIGN8(140));
    printf("ALIGN8(141) = %zu\n", ALIGN8(141));
    printf("ALIGN8(142) = %zu\n", ALIGN8(142));
    printf("ALIGN8(143) = %zu\n", ALIGN8(143));
    printf("ALIGN8(144) = %zu\n", ALIGN8(144));
    printf("ALIGN8(145) = %zu\n", ALIGN8(145));
    printf("ALIGN8(150) = %zu\n", ALIGN8(150));
    printf("ALIGN8(160) = %zu\n", ALIGN8(160));
    printf("ALIGN8(170) = %zu\n", ALIGN8(170));
    printf("ALIGN8(180) = %zu\n", ALIGN8(180));
    printf("ALIGN8(190) = %zu\n", ALIGN8(190));
    printf("ALIGN8(200) = %zu\n", ALIGN8(200));
    printf("ALIGN8(210) = %zu\n", ALIGN8(210));
    printf("ALIGN8(220) = %zu\n", ALIGN8(220));
    printf("ALIGN8(230) = %zu\n", ALIGN8(230));
    printf("ALIGN8(481) = %zu\n", ALIGN8(481));
    printf("ALIGN8(500) = %zu\n", ALIGN8(500));
    printf("ALIGN8(504) = %zu\n", ALIGN8(504));
    printf("ALIGN8(512) = %zu\n", ALIGN8(512));
    printf("ALIGN8(550) = %zu\n", ALIGN8(550));
    printf("ALIGN8(600) = %zu\n", ALIGN8(600));
    printf("ALIGN8(614) = %zu\n", ALIGN8(614));
    printf("ALIGN8(615) = %zu\n", ALIGN8(615));
    printf("ALIGN8(650) = %zu\n", ALIGN8(650));
    printf("ALIGN8(700) = %zu\n", ALIGN8(700));
    printf("ALIGN8(750) = %zu\n", ALIGN8(750));
    printf("ALIGN8(800) = %zu\n", ALIGN8(800));
    printf("ALIGN8(1024) = %zu\n", ALIGN8(1024));



    return 0;
}

/*
c = a / b

2 = 6 / 3 

3 = 6 / 2

b = a / c
*/