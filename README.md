design a memory allocator


the program break is the first location after the end of the uninitialized data segment

This is done via the brk() system call, which changes the point where the data segment "breaks"/ends.
malloc-s use sbrk for small allocations, mmap for large ones.

[figure1]

Resizing the heap (allocating or deallocating memory) is actually as simple as telling the kernel to adjust its idea of where the process’s program break is. Initially, the program break lies just past the end of the uninitialized data segment (the same location as &end, shown in Figure2

The current limit of the heap is referred to as the program break.

https://github.com/shichao-an/notes/blob/master/docs/tlpi/ch7.md

The program break is the address of the first location beyond the current end of the data region of the program in the virual memory.

sbrk() increments the program's data space  by  increment  bytes.   Calling
       sbrk()  with  an increment of 0 can be used to find the current location of
       the program break.


```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char etext, edata, end; // Symbols defined by the linker

int main() {
    void* current_brk = sbrk(0);
    void* data_end = &edata; // Address of the end of the data section

    printf("Current program break: %p\n", current_brk);
    printf("End of data section: %p\n", data_end);
    printf("End of program (end symbol): %p\n", &end);

    return 0;
}
```



   0x000055ada8136152 <+13>:	callq  0x55ada8136040 <sbrk@plt>
   0x000055ada8136157 <+18>:	mov    %rax,-0x8(%rbp)
=> 0x000055ada813615b <+22>:	lea    0x2ed6(%rip),%rax


analyse the result

(gdb) i r rax
rax 0x55ada9156000

(gdb) print &_edata
$9 = (<data variable, no debug info> *) 0x55ada8139038 <completed>

(gdb) p 0x55ada9156000 - 0x55ada8139038
$11 = 16895944

From the GDB output you provided, we can analyze the results as follows:

(gdb) info registers rax
The value stored in the %rax register is 0x55ada9156000. This value represents the address returned by the brk system call.

(gdb) print &_edata
The address of the _edata symbol is 0x55ada8139038. This symbol typically represents the end of the data section in the program's memory layout.

(gdb) p 0x55ada9156000 - 0x55ada8139038
The result of subtracting the address of _edata from the value in %rax is 16895944. This difference indicates the amount of memory that was dynamically allocated using the brk system call.

Based on the analysis, it appears that the brk system call was used to allocate approximately 16,895,944 bytes (or 16.1 MB) of memory. This memory was allocated beyond the end of the data section represented by the _edata symbol.

*******

```
char* str = (char*) malloc(10);  
	memset(str, 'A', 9);
```
heap

1 word size here = 4 bytes = 32 bits = x/1wx = 0x00000000

```
(gdb) x/4wx 0x55b28adc8260
0x55b28adc8260:	0x41414141	0x41414141	0x00000041	0x00000000
```



```
FTSE: we can solve any prob by introducing an extra lvl of indirection = MMU in this case
```

watch Chris Kanich's playlist on youtube on Systems

```
ptr = malloc(Z)

ptr - 1 = X

X - (4 * 2Headers) = Z   (Z is the size of the block) => malloc(Z)
```


```
char *ptr1 = (char *)malloc(10);
memset(ptr1, 'A', 10);

char *ptr2 = (char *)malloc(15);
memset(ptr2, 'B', 15);

   0x0000561d9a2bf172 <+13>:    callq  0x561d9a2bf060 <malloc@plt>
=> 0x0000561d9a2bf177 <+18>:    mov    %rax,-0x8(%rbp)

(gdb) i r $rax
rax            0x561d9a9a6260      94685147849312
(gdb) x/40wx 0x561d9a9a6260 - 8
0x561d9a9a6258: 0x00000021      0x00000000      0x00000000      0x00000000
0x561d9a9a6268: 0x00000000      0x00000000      0x00000000      0x00000000

p (0x21 - 1)/4 = 8 words
```

```
0x561d9a9a6258: 0x00000021      0x00000000      0x41414141      0x41414141
0x561d9a9a6268: 0x00004141      0x00000000      0x00000000      0x00000000
0x561d9a9a6278: 0x00000411      0x00000000      0x6f6c6c41      0x65746163

(gdb) x/wx 0x561d9a9a6258+(0x21-1)
0x561d9a9a6278: 0x00000411

tail of the first allocation = 0x561d9a9a6278 - 4 = 0x561d9a9a6274

head of the second allocation = 0x561d9a9a6274 + 0x411 = 0x561d9a9a6685

(gdb) x/4wx 0x561d9a9a6274+0x411
0x561d9a9a6685: 0x21000000      0x00000000      0x42000000      0x42424242

```



```
between the two allocations

Breakpoint 2, 0x000055f29442a181 in main ()
(gdb) x/12wx 0x55f296090260 - 8
0x55f296090258: 0x00000021      0x00000000      0x41414141      0x41414141
0x55f296090268: 0x00004141      0x00000000      0x00000000      0x00000000
0x55f296090278: 0x00020d91      0x00000000      0x00000000      0x00000000
(gdb) c
Continuing.

Breakpoint 3, 0x000055f29442a18b in main ()
(gdb) x/12wx 0x55f296090260 - 8
0x55f296090258: 0x00000021      0x00000000      0x41414141      0x41414141
0x55f296090268: 0x00004141      0x00000000      0x00000000      0x00000000
0x55f296090278: 0x00000021      0x00000000      0x00000000      0x00000000
```

```
(gdb) x/20wx 0x55f296090258
0x55f296090258: 0x00000021      0x00000000      0x41414141      0x41414141
0x55f296090268: 0x00004141      0x00000000      0x00000000      0x00000000
0x55f296090278: 0x00000021      0x00000000      0x42424242      0x42424242
0x55f296090288: 0x42424242      0x00424242      0x00000000      0x00000000
0x55f296090298: 0x00020d71      0x00000000      0x00000000      0x00000000
(gdb) x/20wx 0x55f296090258+0x20
0x55f296090278: 0x00000021      0x00000000      0x42424242      0x42424242
0x55f296090288: 0x42424242      0x00424242      0x00000000      0x00000000
0x55f296090298: 0x00020d71      0x00000000      0x00000000      0x00000000
0x55f2960902a8: 0x00000000      0x00000000      0x00000000      0x00000000
0x55f2960902b8: 0x00000000      0x00000000      0x00000000      0x00000000
(gdb) x/20wx 0x55f296090258+0x20+0x20
0x55f296090298: 0x00020d71      0x00000000      0x00000000      0x00000000
0x55f2960902a8: 0x00000000      0x00000000      0x00000000      0x00000000
0x55f2960902b8: 0x00000000      0x00000000      0x00000000      0x00000000
0x55f2960902c8: 0x00000000      0x00000000      0x00000000      0x00000000
0x55f2960902d8: 0x00000000      0x00000000      0x00000000      0x00000000
```

0x00020d71 marks the end of the heap