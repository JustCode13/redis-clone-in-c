`allocator.h` is responsible for **memory management** in your Redis clone.

Think of it as the project's **memory manager**.

Instead of calling `malloc()` and `free()` everywhere, different parts of Redis ask the allocator to give or release memory.

---

# Why do we need allocator.h?

Without it, every file would do something like:

```c
char *ptr = malloc(100);
```

or

```c
free(ptr);
```

all over the project.

Instead, they use functions from `allocator.h`.

```
Database
      │
Hash Table
      │
Skip List
      │
Objects
      │
      ▼
 allocator.h
      │
      ▼
 malloc() / free()
```

This keeps memory management organized.

---

# Libraries

## common.h

Provides

* typedefs (`u8`)
* macros
* constants
* bool

---

## stddef.h

Provides

```
size_t
```

which is used for

```
capacity
offset
alignment
object size
```

---

# Structs

---

# Arena

```c
typedef struct Arena {
    u8 *memory;
    size_t capacity;
    size_t offset;
    size_t alignment;
} Arena;
```

An **Arena** is one large block of memory.

Imagine buying one huge notebook.

```
+--------------------------------------+
|                                      |
|                                      |
|                                      |
|                                      |
+--------------------------------------+
```

Instead of buying a new notebook every time.

---

## memory

```c
u8 *memory;
```

Points to the beginning of that big memory block.

Example

```
memory
   │
   ▼
+--------------------------------+
|                                |
+--------------------------------+
```

---

## capacity

```c
size_t capacity;
```

How big the arena is.

Example

```
1 MB

10 MB

100 MB
```

---

## offset

```c
size_t offset;
```

Shows how much memory has already been used.

Example

```
capacity = 1000 bytes

offset = 300
```

means

```
300 bytes used

700 bytes free
```

---

## alignment

```c
size_t alignment;
```

Some CPUs work faster when data starts at certain byte boundaries (for example, 8-byte alignment). This field stores the alignment requirement so allocations can be adjusted correctly.

---

# Arena picture

Initially

```
+--------------------------------------+
^
memory

offset = 0
```

After allocating 100 bytes

```
+----------+---------------------------+
|   used   |          free             |
+----------+---------------------------+
           ^
         offset
```

Another allocation

```
+---------------------+----------------+
|        used         |      free      |
+---------------------+----------------+
                      ^
                    offset
```

The offset simply moves forward.

---

# FreeBlock

```c
typedef struct FreeBlock {
    size_t size;
    FreeBlock *next;
} FreeBlock;
```

This represents one free chunk of memory.

Imagine memory like this:

```
+------+-------+------+-------+
| Used | Free  | Used | Free  |
+------+-------+------+-------+
```

Each free part is a `FreeBlock`.

---

## size

How many bytes are free.

Example

```
128 bytes
```

---

## next

Points to the next free block.

```
Free1 ---> Free2 ---> Free3 ---> NULL
```

This is called a **free list**.

---

# PoolAllocator

```c
typedef struct PoolAllocator
```

A pool allocator is used when every object has the **same size**.

Example

Suppose every client object is exactly **128 bytes**.

Instead of

```
malloc()

malloc()

malloc()

malloc()
```

we create one big pool.

```
+-----+-----+-----+-----+-----+
| Obj | Obj | Obj | Obj | Obj |
+-----+-----+-----+-----+-----+
```

Every allocation just takes the next free slot.

Very fast.

---

## memory

Beginning of the pool.

```
memory
   │
   ▼

+-----+-----+-----+
```

---

## free_list

Points to available objects.

Example

```
Object3
   │
   ▼

Object5
   │
   ▼

Object8
```

When you need one,

take the first.

---

## object_size

Size of every object.

Example

```
128 bytes
```

Every slot has exactly this size.

---

## object_count

How many objects exist.

Example

```
1024
```

means

```
1024 available slots
```

---

## alignment

Stores the alignment requirement for each object in the pool so every allocated object starts at a properly aligned address.

---

# Functions

---

## arena_create()

```c
Arena *arena_create(size_t capacity);
```

Creates a new arena.

Example

```
arena_create(1 MB)
```

Result

```
+-----------------------------------+
|             1 MB                  |
+-----------------------------------+
```

---

## arena_alloc()

```c
void *arena_alloc(...)
```

Allocates memory from the arena.

Example

Need

```
64 bytes
```

It returns

```
memory + offset
```

Then

```
offset += 64
```

No searching.

No free list.

Just move forward.

This is extremely fast.

---

## arena_reset()

```c
arena_reset(arena);
```

Instead of freeing every object,

it simply does

```
offset = 0;
```

Everything becomes available again.

---

## arena_destroy()

Destroys the arena.

Internally it eventually frees the large memory block.

---

## pool_create()

Creates a pool allocator.

Example

```
1000 objects

each object = 64 bytes
```

Memory looks like

```
+----+----+----+----+
|Obj |Obj |Obj |Obj |
+----+----+----+----+
```

---

## pool_alloc()

Returns one free object.

Before

```
Free

↓

Obj1

↓

Obj2

↓

Obj3
```

After allocation

```
Free

↓

Obj2

↓

Obj3
```

The first object is handed to the caller.

---

## pool_free()

Returns an object back to the pool.

Example

```
Application finished using Obj1
```

Instead of calling `free()`, it puts `Obj1` back into the free list.

```
Obj1

↓

Obj2

↓

Obj3
```

---

## pool_destroy()

Destroys the entire pool and releases all of its memory.

---

# Why Redis uses Arena

Arena allocation is ideal for **temporary allocations**.

Example

```
Client sends command

SET name John
```

While parsing,

Redis creates temporary strings and arrays.

After the command finishes,

all temporary memory can be discarded at once with

```
arena_reset()
```

instead of freeing each object individually.

---

# Why Redis uses PoolAllocator

Pool allocation is ideal when many objects have the **same size**.

Examples include

* client structures
* list nodes
* hash entries

Instead of thousands of `malloc()` calls, Redis allocates one large block and reuses fixed-size slots, reducing overhead and fragmentation.

---

## In one sentence

`allocator.h` provides two specialized memory allocators: an **Arena** for very fast temporary allocations that are discarded all at once, and a **PoolAllocator** for efficiently allocating and reusing many fixed-size objects.
