





















// malloc_consolidate()/coalesced;

// requests >= mmap_threshold that are serviced via mmap()

// malloc_getpagesize         default: derive from system includes, or 4096.

// REALLOC_ZERO_BYTES_FREES    default: not defined
//   This should be set if a call to realloc with zero bytes should
//   be the same as a call to free. Some people think it should. Otherwise,
//   since this malloc returns a unique pointer for malloc(0), so does
//   realloc(p, 0).

// MALLOC_ALIGNMENT         default: (size_t)(2 * sizeof(void *))
//   Controls the minimum alignment for malloced chunks.  It must be a
//   power of two and at least 8, even on machines for which smaller
//   alignments would suffice. It may be defined as larger than this
//   though. Note however that code and data structures are optimized for
//   the case of 8-byte alignment.

//   ```
//   DEFAULT_MMAP_THRESHOLD       default: 256K
//       Also settable using mallopt(M_MMAP_THRESHOLD, x)
//   The request size threshold for using MMAP to directly service a
//   request. Requests of at least this size that cannot be allocated
//   using already-existing space will be serviced via mmap.  (If enough
//   normal freed space already exists it is used instead.)  Using mmap
//   segregates relatively large chunks of memory so that they can be
//   individually obtained and released from the host system. A request
//   serviced through mmap is never reused by any other request (at least
//   not directly; the system may just so happen to remap successive
//   requests to the same locations).  Segregating space in this way has
//   the benefits that: Mmapped space can always be individually released
//   back to the system, which helps keep the system level memory demands
//   of a long-lived program low.
//   ``` 

  