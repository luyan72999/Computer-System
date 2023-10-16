### How to use the allocator simulator: <br/>

**First, create an allocator object with (base, size)** <br/>
e.g. Allocator* a = new Allocator(1000, 500); <br/>

**To allocate 10 bytes, a header pointer is returned to the caller:** <br/>
e.g. Header* h = a->alloc(10); <br/>

**To free the allocated memory, just pass the returned header pointer to the free method:** <br/>
e.g. a->free(h); <br/>

**You can print free list anytime:** <br/>
e.g.  a->print_list(a->free_list); <br/>

