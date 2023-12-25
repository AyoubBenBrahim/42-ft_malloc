Alignment fundamentals

https://developer.ibm.com/articles/pa-dalign/

***

why alignment is important: 

```
The heap manager also needs to ensure that the allocation will be 8-byte aligned on 32-bit systems, or 16-byte aligned on 64-bit systems. Alignment of allocations doesn’t matter if the programmer just wants to store some data like a text string or a byte array, but alignment can have a big impact on the correctness and performance of programs if the programmer intends to use the allocation to store more complex data structures. Since malloc has no way to know what the programmer will store in their allocation, the heap manager must default to making sure all allocations are aligned.
``` [source](https://azeria-labs.com/heap-exploitation-part-1-understanding-the-glibc-heap-implementation/)

```
needs to ensure that the allocation is 8-byte aligned on 32-bit systems, or 16-byte aligned on 64-bit systems. This is because modern processors access memory in chunks of 4 bytes (32-bit) or 8 bytes (64-bit). 
```  

```
Alignment refers to the requirement that data be stored at memory addresses that are multiples of a specific value. In the context of memory allocation, alignment ensures that allocated blocks of memory start at addresses that are compatible with the data they will contain. The alignment requirement is dependent on the platform's architecture and the specific data types being used.

Alignment is important for several reasons:

1. Correctness: Many processors have alignment requirements for accessing certain data types. Accessing misaligned data can result in hardware exceptions, crashes, or incorrect behavior. By ensuring that allocations are properly aligned, the heap manager guarantees that the programmer can safely access and manipulate the allocated memory.

2. Performance: Accessing aligned data can be more efficient on some architectures. For example, some processors can fetch aligned data in a single memory operation, while misaligned data may require multiple operations or incur performance penalties. Aligning allocations according to the platform's requirements can improve memory access performance.

3. Compatibility: Some libraries or APIs may have alignment requirements for their data structures or function parameters. By aligning allocations, the heap manager ensures that the allocated memory can be seamlessly integrated with other components of the program or third-party libraries.

Since the `malloc` function does not have information about the programmer's intended use of the allocated memory, the heap manager defaults to ensuring that all allocations are properly aligned. This approach ensures that the allocated memory is compatible with a wide range of data types and usage scenarios, providing a consistent and reliable behavior across different programs.

It's worth noting that alignment requirements can vary depending on the platform and the specific data types being used. Common alignment values include 4 bytes, 8 bytes, or 16 bytes, but there can be other alignment requirements for specific data structures or SIMD (Single Instruction, Multiple Data) instructions.

By adhering to alignment requirements, programmers can ensure the correctness, portability, and performance of their programs when working with complex data structures or when integrating with external components.

If you have any further questions, please, let me know!
```

the nearest greater or equal multiple of four:

#define align4(x) (((((x)-1)>>2)<<2)+4)

this trick is explained in the [pdf](./Marwan_Burelle.pdf)


better malloc project:

Implementing a memory allocator https://github.com/kishan811/Better-Malloc

**

https://medium.com/howsofcoding/memory-management-aligned-malloc-and-free-9273336bd4c6

**

By using this modified `align8` macro, you can align memory addresses on a 64-bit system or macOS to the nearest greater or equal multiple of 8, which is the alignment requirement for 64-bit systems.

```c
#define align8(x) (((((x)-1)>>3)<<3)+8)
```

1. `x`: This represents the input value that you want to align.

2. `(x-1)`: By subtracting 1 from `x`, we ensure that if `x` is already a multiple of 8, the result remains the same. Otherwise, it becomes the nearest smaller multiple of 8.

3. `((x-1)>>3)`: The shift operation `(x-1)>>3` divides the value by 8. This effectively moves the bits of `(x-1)` three positions to the right, which is equivalent to integer division by 8.

4. `<<3`: The resulting value from the previous step is shifted three positions to the left, effectively multiplying it by 8. This gives us the nearest smaller or equal multiple of 8 to `x`.

5. `+8`: Finally, we add 8 to the result to obtain the nearest greater or equal multiple of 8. This ensures that the alignment requirement is met. If `x` is already a multiple of 8, the macro will still add 8 to maintain alignment.


==

`size = (size + 15) & ~0xf;` // align to 16 bytes, check the [video](https://youtu.be/CulF4YQt6zA) on Low-Level Learning ytube channel