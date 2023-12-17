what is Virtual Memory? https://youtu.be/A9WLYbE0p-I

https://manybutfinite.com/post/anatomy-of-a-program-in-memory/

the articles in this blog are all great: https://manybutfinite.com/archives/

First-Fit vs. Best-Fit https://courses.engr.illinois.edu/cs240/fa2020/notes/heapMemoryAllocation.html#:~:text=First%2Dfit%20is%20faster%2C%20allowing,every%20free%20block%20in%20memory.

check heap rules: https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/

subheap via mmap
```
When the heap manager wants to create a subheap, it first asks the kernel to reserve a region of memory that the subheap can grow into by calling mmap*. Reserving this region does not directly allocate memory into the subheap; it just asks the kernel to refrain from allocating things like thread stacks, mmap regions and other allocations inside this region.

his is done by asking mmap for pages that are marked PROT_NONE, which acts as a hint to the kernel that it only needs to reserve the address range for the region; it doesn’t yet need the kernel to attach memory to it.
``` [source](https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/)

```