
#include "libft.h"

char* ft_strpbrk(const char* str, const char* chars) 
{
    const char* p = str;
    const char* q;

    while (*p != '\0') {
        q = chars;
        while (*q != '\0') {
            if (*p == *q) {
                return (char*)p;
            }
            q++;
        }
        p++;
    }

    return NULL;
}

// int main() {
//     const char* str = "x";
//     const char* chars = "RWwDBUTA";
//     char* pos;

//     pos = ft_strpbrk(str, chars);

//     if (pos) {
//         printf("First occurrence found at position %ld.\n", pos - str);
//     } else {
//         printf("No occurrence found.\n");
//     }

//     return 0;
// }

