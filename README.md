design a memory allocator


```
Virtual memory is a memory management technique that provides each process with its own isolated address space, 
allowing it to operate as if it has access to a large, contiguous block of memory. However, the physical memory (RAM) available to the system may be limited.
```

```
Each process in a multi-tasking OS runs in its own memory sandbox.
 This sandbox is the virtual address space, which in 32-bit mode is always a 4GB block of memory addresses.
These virtual addresses are mapped to physical memory by page tables, which are maintained by the operating
system kernel and consulted by the processor. Each process has its own set of page tables, but there is a catch.
Once virtual addresses are enabled, they apply to all software running in the machine, including the kernel itself.

 kernel space is constantly present and maps the same physical memory in all processes. 
```


PCB (Process Control Block) is a data structure that contains information about a process in the OS. https://youtu.be/4s2MKuVYKV8

{PID, PC, SP, registers, MMU, open files, etc.}

task_struct is the name of the PCB in Linux.


```
The 4GB virtual address space is divided into pages.
x86 processors in 32-bit mode support page sizes of 4KB, 2MB, and 4MB.
Both Linux and Windows map the user portion of the virtual address space using 4KB pages.
Bytes 0-4095 fall in page 0, bytes 4096-8191 fall in page 1, and so on. The size of a VMA must be a multiple of page size
```




the program break is the first location after the end of the uninitialized data segment

This is done via the brk() system call, which changes the point where the data segment "breaks"/ends.
malloc-s use sbrk for small allocations, mmap for large ones.


Resizing the heap (allocating or deallocating memory) is actually as simple as telling the kernel to adjust its idea of where the process’s program break is. Initially, the program break lies just past the end of the uninitialized data segment (the same location as &end, shown in Figure2

The current limit of the heap is referred to as the program break.

https://github.com/shichao-an/notes/blob/master/docs/tlpi/ch7.md

The program break is the address of the first location beyond the current end of the data region of the program in the virual memory.

```
sbrk() increments the program's data space  by  increment  bytes.  
Calling sbrk()  with  an increment of 0 can be used to find the current location of
the program break.
```


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


```
   0x000055ada8136152 <+13>:	callq  0x55ada8136040 <sbrk@plt>
   0x000055ada8136157 <+18>:	mov    %rax,-0x8(%rbp)
=> 0x000055ada813615b <+22>:	lea    0x2ed6(%rip),%rax
```

analyse the result

```
(gdb) i r rax
rax 0x55ada9156000

(gdb) print &_edata
$9 = (<data variable, no debug info> *) 0x55ada8139038 <completed>

(gdb) p 0x55ada9156000 - 0x55ada8139038
$11 = 16895944
```

From the GDB output, we can analyze the results as follows:
```
(gdb) info registers rax
The value stored in the %rax register is 0x55ada9156000. This value represents the address returned by the brk system call.
```
```
(gdb) print &_edata
The address of the _edata symbol is 0x55ada8139038. This symbol typically represents the end of the data section in the program's memory layout.
```
```
(gdb) p 0x55ada9156000 - 0x55ada8139038
The result of subtracting the address of _edata from the value in %rax is 16895944. This difference indicates the amount of memory that was dynamically allocated using the brk system call.

Based on the analysis, it appears that the brk system call was used to allocate approximately 16,895,944 bytes (or 16.1 MB) of memory. This memory was allocated beyond the end of the data section represented by the _edata symbol.
```

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


======================== some more digging using Pwndbg ========================

after malloc(10)

```
pwndbg> heap
Allocated chunk | PREV_INUSE
Addr: 0x555b76fdd000
Size: 0x250 (with flag bits: 0x251)

Allocated chunk | PREV_INUSE
Addr: 0x555b76fdd250
Size: 0x20 (with flag bits: 0x21)

Top chunk | PREV_INUSE
Addr: 0x555b76fdd270
Size: 0x20d90 (with flag bits: 0x20d91)
```

```
pwndbg> x/10wx 0x555b76fdd250
0x555b76fdd250:	0x00000000	0x00000000	0x00000021	0x00000000
0x555b76fdd260:	0x00000000	0x00000000	0x00000000	0x00000000
```

after first memset(ptr1, 'A', 10);

```
pwndbg> arena 0x555b76fdd250
{
  mutex = 0,
  flags = 0,
  have_fastchunks = 33,
  fastbinsY = {0x4141414141414141, 0x4141, 0x0, 0x20d91, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  top = 0x0,
  last_remainder = 0x0,
  bins = {0x0 <repeats 254 times>},
  binmap = {0, 0, 0, 0},
  next = 0x0,
  next_free = 0x0,
  attached_threads = 0,
  system_mem = 0,
  max_system_mem = 0,
}

pwndbg> x/10wx 0x555b76fdd250
0x555b76fdd250:	0x00000000	0x00000000	0x00000021	0x00000000
0x555b76fdd260:	0x41414141	0x41414141	0x00004141	0x00000000
```
