Think of Redis like a giant cupboard.

Inside the cupboard, every item has:

* a **key** (its name)
* a **value** (the actual data)

Example

```
Key ---------> Value
"name" ------> "John"
```

Here,

```
Key = "name"
Value = "John"
```

But Redis doesn't only store strings.

It can store **5 different kinds of values** because different problems need different data structures.

---

# 1. REDIS_STRING

The simplest type.

One key stores one value.

Example

```
Key
username

Value
John
```

Another example

```
age -> "22"

country -> "India"

salary -> "50000"
```

Commands

```
SET username John
GET username
```

Result

```
John
```

This is used for

* usernames
* passwords
* emails
* counters
* tokens
* JSON strings

Basically anything that's just one value.

---

# 2. REDIS_LIST

A list stores **multiple values in order**.

Think of it like a train.

```
Head

↓

Apple -> Mango -> Banana -> Orange

↑

Tail
```

One key owns the whole list.

Example

```
shopping_list
```

contains

```
Milk
Eggs
Bread
Butter
```

So Redis stores

```
shopping_list

↓

Milk
Eggs
Bread
Butter
```

Commands

```
LPUSH shopping_list Milk
LPUSH shopping_list Eggs
RPUSH shopping_list Butter
```

Result

```
Eggs
Milk
Butter
```

Notice

Order matters.

---

### Real example

Imagine WhatsApp.

Your recent messages

```
Hello

How are you?

See you.
```

are naturally a list.

Or

YouTube watch history

```
Video A
Video B
Video C
```

Again, a list.

---

# 3. REDIS_HASH

A hash is like a dictionary.

Instead of storing one value,

it stores many

```
field → value
```

pairs.

Example

Key

```
user:101
```

Inside it

```
name -> John

age -> 22

city -> Mumbai

email -> john@gmail.com
```

Picture it like this

```
user:101

↓

-------------------------
name    | John
age     | 22
city    | Mumbai
email   | john@gmail.com
-------------------------
```

Commands

```
HSET user:101 name John

HSET user:101 age 22

HGET user:101 age
```

Result

```
22
```

---

### Why not use strings?

Instead of

```
user_name

user_age

user_city

user_email
```

as four separate keys,

everything stays together.

Much cleaner.

---

### Real example

Instagram user

```
Username

Followers

Bio

Email

Password

Profile picture
```

All belong to one user.

Perfect for a hash.

---

# 4. REDIS_SET

A set stores **unique values**.

Duplicates are automatically ignored.

Imagine a bag where every item can appear only once.

Example

```
online_users

↓

John

Alice

Bob
```

Now someone adds

```
John
```

again.

Result

```
John

Alice

Bob
```

Nothing changes.

John was already there.

---

Commands

```
SADD online_users John

SADD online_users Alice

SADD online_users John
```

Still

```
John

Alice
```

---

### Real example

People who liked a post.

```
Post #50

↓

John

Alice

David
```

If John presses Like again,

nothing happens.

A person can like only once.

Another example

Students enrolled in a class.

Each student should appear only once.

---

# 5. REDIS_ZSET (Sorted Set)

This is one of Redis's most powerful data types.

A sorted set is like a normal set,

but every member has a **score**.

Example

```
John -> 1500

Alice -> 900

Bob -> 2000
```

Redis automatically keeps them sorted by score.

```
Alice -> 900

John -> 1500

Bob -> 2000
```

Notice

You never sort manually.

Redis always keeps the order correct.

---

Commands

```
ZADD leaderboard 1500 John

ZADD leaderboard 900 Alice

ZADD leaderboard 2000 Bob
```

Leaderboard becomes

```
1 Alice 900

2 John 1500

3 Bob 2000
```

---

### Real example

Game leaderboard

```
Player

Score
```

```
John -> 2500

Alice -> 1800

Bob -> 4000
```

Or

Music rankings

```
Song A -> 98

Song B -> 45

Song C -> 77
```

Or

Product popularity

```
iPhone -> 5000 sales

Laptop -> 2100 sales

TV -> 900 sales
```

All are naturally sorted by their score.

---

# Why does Redis have so many types?

Imagine building Instagram using only strings.

A user profile would look like

```
user_name

user_age

user_email

user_followers

user_following

user_bio
```

Every piece of data becomes a separate key, making related information harder to manage.

Instead:

* **String** → one value (username, token, counter)
* **List** → ordered collection (messages, notifications, history)
* **Hash** → object with fields (user profile, product details)
* **Set** → unique collection (liked posts, online users, tags)
* **Sorted Set (ZSet)** → unique collection with scores (leaderboards, rankings, priority queues)

Each data type is optimized for a different pattern of data, so Redis can perform operations on them very efficiently.
