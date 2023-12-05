#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char* str = (char*) malloc(3);  
	memset(str, 'A', 3);

    if (str != NULL) {
        strcpy(str, "BBCCD");// in hex: 0x41 0x42 0x43 0x44 0x00 
		// 0x43424141
		//
        printf("Allocated string: %s\n", str);

        free(str);
    }

    return 0;
}
