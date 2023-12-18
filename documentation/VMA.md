
A VMA is like a contract between your program and the kernel. You ask for something to be done (memory allocated, a file mapped, etc.),
the kernel says "sure", and it creates or updates the appropriate VMA. But it does not actually honor the request right away,
it waits until a page fault happens to do real work. The kernel is a lazy, deceitful sack of scum; 
this is the fundamental principle of virtual memory. It applies in most situations, some familiar and some surprising,
but the rule is that VMAs record what has been agreed upon, while PTEs reflect what has actually been done by the lazy kernel.
These two data structures together manage a program's memory; both play a role in resolving page faults, freeing memory,
 swapping memory out, and so on. Let's take the simple case of memory allocation:

https://manybutfinite.com/post/how-the-kernel-manages-your-memory/


On i386 Linux, the bottom of the address space (1G) is mapped to kernel address space, user-space can’t access it.

good read about memory layout

https://medium.com/@c0ngwang/the-art-of-exploiting-heap-overflow-part-2-1bd24a5856d0

##### every memory we access in the virtual memory space must be mapped first, otherwise would trigger a segment fault. 

mmap() could map a file into memory space too, it is typically used by dynamic linked libraries. These dynamic linked libraries are usually mapped after the traditional heap (the one right after program data), now the memory area in-between program data and stack is fragmented by these file mappings, it is hard to draw a line between these libraries and the heap area as both grows at run-time, they could mix up in the whole memory address space.

As these are sufficient to manage the memory address space, why do we need the C standard functions malloc()/free()?

sbrk() and mmap() are specific to UNIX, especially sbrk() which makes an assumption of program data segment
mmap() is over complicated, it is hard to use even though it is powerful, and it ties to the concept of virtual memory which is OS-specific.
system calls are expensive, we don’t want to call mmap() even just for a 4-bytes allocation. With a new interface, glibc also gains the freedom to “cache” the system calls behind.
So malloc()/free() provides the simplest interface to manage the heap, without even bothering the virtual memory concept, and what’s more important, you don’t even need to remember the size of memory you allocate!

https://medium.com/@c0ngwang/the-art-of-exploiting-heap-overflow-part-3-9890b01d56a2

finally a good definition:

### heap = the private anonymous memory in-between program data and stack managed by glibc. They are all from mmap() except the (optional) traditional heap which is from sbrk().