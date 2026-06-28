Think of **`object.h` as the file that defines what a Redis value looks like**.

Whenever someone does

```text
SET name Tanmaya
LPUSH numbers 10
HSET user age 21
```

the database cannot store these directly.

Instead, every value is wrapped inside a **RedisObject**.

So this file answers one question:

> **"What does one value inside our Redis database look like?"**

---

# Overall picture

```
SET name "Tanmaya"

        │
        ▼
RedisObject
    │
    ├── type = OBJ_STRING
    ├── value = "Tanmaya"
    ├── expire_at = 0
    ├── refcount = 1
    └── lru_node = pointer
```

---

# Libraries

## common.h

Provides

* u64
* u32
* bool
* macros
* common constants

---

## list.h

Needed because

```c
ListNode *lru_node;
```

comes from

```c
list.h
```

Redis uses this pointer for its **LRU cache**.

---

## hash.h

Needed because

A Redis hash object stores a hash table.

Example

```
HSET user age 20
```

internally

```
RedisObject
      │
      ▼
 HashTable
```

---

## skiplist.h

Needed because

Sorted Sets use a skip list.

Example

```
ZADD scores 100 Alice
```

The value points to a SkipList.

---

# RedisObjectType

This tells Redis what kind of object this is.

```
OBJ_STRING
```

Example

```
SET name Tanmaya
```

---

```
OBJ_LIST
```

Example

```
LPUSH numbers 10
```

---

```
OBJ_HASH
```

Example

```
HSET user age 20
```

---

```
OBJ_SET
```

Example

```
SADD fruits apple
```

---

```
OBJ_ZSET
```

Example

```
ZADD ranking 95 Alice
```

Instead of guessing,

Redis simply checks

```c
obj->type
```

---

# RedisObject

This is the heart of the file.

```c
typedef struct RedisObject
```

Every value stored inside Redis becomes one of these.

---

## type

```c
RedisObjectType type;
```

Tells Redis

"What kind of object am I?"

Example

```
OBJ_STRING
```

or

```
OBJ_HASH
```

---

## value

```c
void *value;
```

This points to the **actual data**.

Example

```
OBJ_STRING
```

```
value
   │
   ▼
"Hello"
```

---

Example

```
OBJ_LIST
```

```
value
   │
   ▼
List
```

---

Example

```
OBJ_HASH
```

```
value
   │
   ▼
HashTable
```

---

Example

```
OBJ_ZSET
```

```
value
   │
   ▼
SkipList
```

Notice that the type changes, but the field is always

```c
void *
```

That makes one structure capable of storing every Redis data type.

---

## expire_at

```c
u64 expire_at;
```

Stores the expiration time.

Example

```
SET name Tanmaya EX 10
```

Suppose current time is

```
1000
```

Redis stores

```
expire_at = 1010
```

Later

```
current_time >= expire_at
```

means

```
Delete this key.
```

---

## refcount

```c
u32 refcount;
```

Reference count.

It tells Redis

"How many things are currently using this object?"

Example

```
Object
   │
refcount = 1
```

One owner.

Another pointer starts using it.

```
refcount = 2
```

One owner stops using it.

```
refcount = 1
```

When it becomes

```
0
```

Redis can safely free the object.

This prevents freeing memory while it is still in use.

---

## lru_node

```c
ListNode *lru_node;
```

Redis keeps objects in an LRU list.

Imagine

```
You access

A

then

B

then

C
```

The list becomes

```
Front

C

↓

B

↓

A

Back
```

If memory becomes full,

Redis removes

```
A
```

because it hasn't been used recently.

Instead of searching the list every time, each object stores a pointer directly to its own node.

That makes moving it to the front an O(1) operation.

---

# Functions

---

## object_create_string()

Creates a Redis object that stores a string.

Example

```
SET name Tanmaya
```

Creates

```
RedisObject
      │
      ▼
type = OBJ_STRING

value = "Tanmaya"
```

Returns

```
RedisObject *
```

---

## object_create_list()

Creates an empty list object.

Example

```
LPUSH numbers 10
```

Before pushing,

Redis creates

```
RedisObject
      │
      ▼
Empty List
```

---

## object_create_hash()

Creates a hash object.

Example

```
HSET user age 20
```

Creates

```
RedisObject
      │
      ▼
HashTable
```

---

## object_create_set()

Creates a set object.

Example

```
SADD fruits apple
```

---

## object_create_zset()

Creates a sorted set object.

Example

```
ZADD score 100 Alice
```

Creates

```
RedisObject
      │
      ▼
SkipList
```

---

## object_retain()

```c
object_retain(obj);
```

Increases

```
refcount
```

Example

Before

```
refcount = 1
```

After

```
refcount = 2
```

---

## object_release()

Decreases

```
refcount
```

Example

Before

```
refcount = 2
```

After

```
refcount = 1
```

If the count reaches zero, it typically triggers destruction of the object.

---

## object_destroy()

Actually frees everything owned by the object.

For example, if the object is a hash, it frees the hash table. If it's a list, it frees the list. Finally, it frees the `RedisObject` itself.

---

# Contribution to the project

Without `object.h`, your database could only store one specific type of value, such as strings.

With `object.h`, every key in the database stores a **`RedisObject`**, and that object can represent:

* a string
* a list
* a hash
* a set
* a sorted set

This gives your Redis clone the flexibility to support multiple data types while using a single, consistent interface for storing values.
