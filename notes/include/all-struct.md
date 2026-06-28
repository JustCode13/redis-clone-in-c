This is actually one of the biggest mindset shifts in systems programming.

You're thinking:

> "Why do we need so many structs? Can't we just use one or two?"

The answer is **each struct represents one real-world thing in the Redis server.**

Think of building a car.

You don't have one giant "Car" part.

You have

* Engine
* Steering
* Wheels
* Brakes
* Fuel Tank
* Battery

Each has one job.

Your Redis project is exactly the same.

---

# Big Picture

```
                   Redis Server
                        │
        ┌───────────────┼────────────────┐
        │               │                │
     Memory         Data Storage      Networking
        │               │                │
     Arena         HashTable         RespParser
     Pool          SkipList
                   List
```

Every struct is responsible for **one subsystem**.

---

# 1. Arena / PoolAllocator / FreeBlock

## Purpose

**Manage memory.**

They answer questions like:

```
Where should I allocate memory?

How much memory is left?

Can I reuse old memory?

How do I free memory quickly?
```

Without them,

nothing in Redis can even exist.

Think of them as

```
Memory Manager
```

---

# 2. HashEntry / HashTable

## Purpose

**Store all Redis keys.**

Whenever someone writes

```
SET name John
```

the database must remember

```
name → John
```

HashTable's only responsibility is

```
Store
Find
Delete
Resize
```

Think of it as

```
Database Shelf
```

---

# 3. ListNode / List

## Purpose

**Keep things in order.**

Many Redis features need ordering.

Examples

```
LRU cache

Redis LIST

Queue

History
```

A linked list's responsibility is simply

```
Connect objects together
```

Think of it as

```
Chain
```

---

# 4. SkipNode / SkipList

## Purpose

**Keep data sorted.**

Example

```
Player A → 100

Player B → 200

Player C → 150
```

SkipList makes

```
highest score

lowest score

range queries

ranking
```

very fast.

Think of it as

```
Sorted Shelf
```

---

# 5. RedisObject

## Purpose

**Represent one Redis value.**

Redis stores many kinds of values.

```
String

Hash

List

Set

Sorted Set
```

RedisObject says

> "I don't care what type this is."

It simply wraps every value into one common format.

Think of it as

```
Container
```

---

# 6. Database

## Purpose

**Control the whole database.**

It owns

```
HashTable

LRU list

Arena

Memory usage

Statistics
```

Everything ultimately belongs to Database.

Think of it as

```
Manager
```

---

# 7. RespParser

## Purpose

**Understand what the client is saying.**

Client sends

```
SET name John
```

The network only delivers bytes.

RespParser converts

```
Raw bytes
```

into

```
Command
Arguments
```

Think of it as

```
Translator
```

---

# 8. Command

## Purpose

**Know how to execute commands.**

When parser says

```
SET
```

Command tells Redis

```
Run this function.
```

Think of it as

```
Command Directory
```

---

# Everything together

```
                Client
                   │
                   ▼
             RespParser
                   │
          "SET name John"
                   │
                   ▼
               Command
                   │
                   ▼
              Database
                   │
        ┌──────────┴──────────┐
        ▼                     ▼
    HashTable             RedisObject
        │
        ▼
   "name" → Object
                   │
                   ▼
              Arena Memory
```

---

# One sentence for each

| Struct                                | Purpose in the project                               |
| ------------------------------------- | ---------------------------------------------------- |
| **Arena / PoolAllocator / FreeBlock** | Manage memory efficiently.                           |
| **HashTable / HashEntry**             | Store and find keys quickly.                         |
| **List / ListNode**                   | Maintain ordered sequences of objects.               |
| **SkipList / SkipNode**               | Keep data sorted for fast ranking and range queries. |
| **RedisObject**                       | Represent any Redis value in a common format.        |
| **Database**                          | Own and coordinate the entire in-memory database.    |
| **RespParser**                        | Convert incoming network bytes into Redis commands.  |
| **Command**                           | Map command names to the code that executes them.    |

The key idea is that **each struct models a different responsibility**. Rather than one huge struct that tries to do everything, the project is divided into focused components: one for memory, one for storage, one for ordering, one for parsing, one for command dispatch, and one to coordinate them all. This separation keeps the code easier to understand, test, and extend.
