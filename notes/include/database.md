`database.h` is the **heart of your Redis clone**.

If `hash.h`, `list.h`, and `object.h` are individual tools, then **`database.h` combines them into one complete database**.

Think of it like this:

```
Client
   │
   ▼
Database
   │
   ├── Stores keys
   ├── Stores values
   ├── Tracks memory
   ├── Removes expired keys
   ├── Maintains LRU order
   └── Uses arena allocator
```

---

# Included Libraries

## common.h

Provides

* common types
* constants
* macros

Used everywhere.

---

## hash.h

Provides the hash table.

This is where every key is stored.

Example

```
SET name John
```

becomes

```
Hash Table

name  ---> RedisObject
```

Without the hash table,

Redis couldn't quickly find keys.

---

## list.h

Provides the doubly linked list.

Used for the **LRU cache**.

Example

```
Most Recently Used

Front

A -> B -> C -> D

Least Recently Used

Back
```

Whenever someone reads

```
GET B
```

the list becomes

```
B -> A -> C -> D
```

---

## object.h

Every value inside Redis is stored as a `RedisObject`.

Example

```
SET name John
```

The value isn't stored as

```
"John"
```

Instead it's stored as

```
RedisObject

type = STRING
value = "John"
expire = ...
refcount = ...
```

---

## allocator.h

Provides the arena allocator.

Instead of calling

```
malloc()
```

thousands of times,

Redis can allocate memory from one large block.

---

# Database Structure

```c
typedef struct Database
```

This structure represents **the entire Redis database**.

Think of it as one big box.

```
Database
│
├── Hash Table
├── LRU List
├── Arena
├── Memory Info
└── Statistics
```

---

## HashTable *dict

```
HashTable *dict;
```

This is where all keys live.

Example

```
SET name John
SET age 20
SET city Mumbai
```

Internally

```
dict

name ---> RedisObject

age ----> RedisObject

city ---> RedisObject
```

Whenever someone does

```
GET age
```

Redis searches here.

This is the most important member.

---

## List lru

```
List lru;
```

Stores keys by recent usage.

Example

Initially

```
A

B

C

D
```

If someone accesses

```
GET C
```

the list becomes

```
C

A

B

D
```

Newest keys stay at the front.

Oldest keys move toward the back.

If memory becomes full,

Redis removes the key at the back.

---

## size_t max_memory

```
size_t max_memory;
```

Maximum memory allowed.

Example

```
512 MB
```

If memory exceeds this,

Redis starts removing old keys.

---

## size_t used_memory

```
size_t used_memory;
```

Tracks how much memory is currently used.

Example

```
Maximum

512 MB

Currently

230 MB
```

After every allocation,

this value increases.

After deleting,

it decreases.

---

## Arena *arena

```
Arena *arena;
```

Points to the arena allocator.

Instead of

```
malloc()

malloc()

malloc()

malloc()
```

Redis allocates from one big memory block.

Much faster.

---

## u64 key_count

```
u64 key_count;
```

Tracks how many keys exist.

Example

Initially

```
0
```

After

```
SET name John
```

```
1
```

After

```
SET age 20
```

```
2
```

After

```
DEL name
```

```
1
```

Useful for statistics and management.

---

# Functions

---

## db_create()

Creates a new database.

Example

```c
Database *db = db_create(512 * 1024 * 1024);
```

It usually performs tasks like:

* allocating the `Database` structure
* creating the hash table
* initializing the LRU list
* creating the arena allocator
* setting memory limits
* initializing counters

After this, the database is ready to accept commands.

---

## db_set()

Stores a key-value pair.

Example

```
SET name John
```

Internally

```
Hash Table

name

↓

RedisObject("John")
```

If the key already exists,

it updates the value.

---

## db_get()

Retrieves a value.

Example

```
GET name
```

Flow

```
User

↓

Hash Table

↓

RedisObject

↓

Return "John"
```

It will also usually update the LRU list because the key was just used.

---

## db_delete()

Deletes a key.

Example

```
DEL name
```

It removes the key from:

* the hash table
* the LRU list

Then frees or releases the associated object.

---

## db_exists()

Checks whether a key exists.

Example

```
EXISTS name
```

Returns

```
true
```

or

```
false
```

without returning the value itself.

---

## db_expire()

Assigns an expiration time to a key.

Example

```
SET name John EX 10
```

The object stores an expiration timestamp.

After the specified time passes, the key is considered expired and can be removed.

---

## db_touch_lru()

Updates the LRU order.

Suppose the current list is

```
Front

A

B

C

D

Back
```

Then someone executes

```
GET C
```

The list becomes

```
Front

C

A

B

D

Back
```

This records that `C` was recently used.

---

## db_evict_lru()

Called when memory is full.

Example

```
Front

A

B

C

D

Back
```

If `D` is the least recently used key, it is removed to free memory.

This implements the LRU eviction policy.

---

## db_cleanup_expired()

Scans the database and removes keys whose expiration time has passed.

Example

```
SET token abc EX 5
```

After five seconds,

`db_cleanup_expired()` deletes that key automatically.

---

## db_destroy()

Destroys the entire database.

It typically:

* frees every stored object
* destroys the hash table
* destroys the LRU list
* destroys the arena allocator
* frees the `Database` structure itself

This is usually called when the server shuts down.

---

# Overall picture

```
                Database
                    │
     ┌──────────────┼──────────────┐
     │              │              │
     ▼              ▼              ▼
 Hash Table     LRU List        Arena
     │              │              │
     │              │              │
Stores keys   Tracks usage   Fast memory allocation
     │
     ▼
RedisObject
     │
     ▼
String / List / Hash / Set / Sorted Set
```

In short, **`database.h` defines the central data structure and operations that make your Redis clone behave like a database**. It coordinates key storage (hash table), value representation (`RedisObject`), memory management (arena), eviction (LRU list), expiration, and overall database lifecycle.
