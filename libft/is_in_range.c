
#include "libft.h"

#include<stdio.h>

bool is_in_range(int value, int lower_bound, int upper_bound) {
    return (value >= lower_bound) && (value <= upper_bound);
}

// int main() {
//     int x = 4;
//     int lower = 5;
//     int upper = 15;
    
//     if (is_in_range(x, lower, upper)) {
//         printf("%d is in the range [%d, %d]\n", x, lower, upper);
//     } else {
//         printf("%d is not in the range [%d, %d]\n", x, lower, upper);
//     }
    
//     return 0;
// }