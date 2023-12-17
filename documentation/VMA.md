
A VMA is like a contract between your program and the kernel. You ask for something to be done (memory allocated, a file mapped, etc.),
the kernel says "sure", and it creates or updates the appropriate VMA. But it does not actually honor the request right away,
it waits until a page fault happens to do real work. The kernel is a lazy, deceitful sack of scum; 
this is the fundamental principle of virtual memory. It applies in most situations, some familiar and some surprising,
but the rule is that VMAs record what has been agreed upon, while PTEs reflect what has actually been done by the lazy kernel.
These two data structures together manage a program's memory; both play a role in resolving page faults, freeing memory,
 swapping memory out, and so on. Let's take the simple case of memory allocation:

https://manybutfinite.com/post/how-the-kernel-manages-your-memory/
