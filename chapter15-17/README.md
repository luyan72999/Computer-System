How to use the allocator simulator:
------------------------------------------------------------------------------------
First, create an allocator object with (base, size)
e.g. Allocator* a = new Allocator(1000, 500);
-------------------------------------------------------------------------------------
To allocate 10 bytes, a header pointer is returned to the caller:
e.g. Header* h = a->alloc(10);
--------------------------------------------------------------------------------------
To free the allocated memory, just pass the returned header pointer to the free method:
e.g. a->free(h);
--------------------------------------------------------------------------------------
You can print free list anytime:
e.g.  a->print_list(a->free_list);
----------------------------------------------------------------------------------------
