#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CONVERT_SIZE 20

static int	nbase_length(t_ull nbr, int shift)
{
	t_ull	nb;
	int		len;

	nb = nbr;
	len = 1;
	while (nb >>= shift)
		len++;
	return (len);
}

char		*shift_bits(t_ull nbr, int mask, int shift)
{
	 static char convert[MAX_CONVERT_SIZE];
    int			len;
	char *str = "0123456789abcdef";

    for (int i = 0; i < MAX_CONVERT_SIZE; i++)
        convert[i] = '\0';

	len = nbase_length(nbr, shift);

    len = (mask == 1) ? len : len + 2;
    convert[len] = '\0';
	while (len--)
	{
        convert[len] = str[nbr & mask];
		nbr >>= shift;
	}
    if (mask == 15)
    {
        convert[0] = '0';
        convert[1] = 'x';
    }
    return (convert);
}

char	*to_hexa(t_ull nbr)
{
	int		shift;
	int		mask;

	mask = 15;
	shift = 4;

	return (shift_bits(nbr, mask, shift));
}

char	*to_binary(t_ull nbr)
{
	int		shift;
	int		mask;

	mask = 1;
	shift = 1;

	return (shift_bits(nbr, mask, shift));
}

unsigned int generateMagicNumber(t_arena *parent_arena) {
    uintptr_t ptr = (uintptr_t)parent_arena;
    // uintptr_t ptr = (uintptr_t)89745682;
    

    char *binaryStr = to_binary(ptr);
    unsigned int hash = 2166136261U;

    // printf("%s\n", binaryStr);
    // char *hexaStr = to_hexa(ptr);
    // printf("%s\n", hexaStr);

    for (size_t i = 0; i < ft_strlen(binaryStr); i++) {
        hash ^= binaryStr[i];
        hash *= 16777619;
    }

    return ptr ^ hash;
}

// int main(){
   
//     generateMagicNumber(NULL);
   
// }