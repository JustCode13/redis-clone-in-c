#include "../include/common.h"
#include "../include/hash.h"

#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

u64 fnv1a_hash(const char *key);
u64 djb2_hash(const char *key);
size_t probe_next(size_t index, size_t capacity);
HashEntry *find_slot(HashTable *table,const char *key, u64 hash);
bool rehash_table(HashTable *table, size_t new_capacity);


// Creates and initializes a new hash table.
// Allocates memory for both the table and its entry array.
HashTable *hash_create(size_t capacity) {

    // A hash table must have at least one slot.
    if (capacity == 0) {
        return NULL;
    }

    // Allocate memory for the hash table structure.
    HashTable *table = malloc(sizeof(*table));

    if (table == NULL) {
        return NULL;
    }

    // Prevent integer overflow before allocating the entry array.
    if (capacity > SIZE_MAX / sizeof(HashEntry)) {
        free(table);
        return NULL;
    }

    // Allocate and zero-initialize the entry array.
    // All entries start in the EMPTY state.
    HashEntry *hash_entry = calloc(capacity, sizeof(HashEntry));

    if (hash_entry == NULL) {
        free(table);
        return NULL;
    }

    // Initialize the hash table fields.
    table->entries = hash_entry;
    table->capacity = capacity;
    table->size = 0;
    table->tombstones = 0;
    table->load_factor = HASH_LOAD_FACTOR;

    // Return the initialized hash table.
    return table;
}


// Inserts a key-value pair into the hash table.
// Updates the value if the key already exists.
bool hash_insert(HashTable *table, const char *key, void *value) {

    // Validate the input.
    if (table == NULL || key == NULL) {
        return false;
    }

    // Reject empty keys.
    if (key[0] == '\0') {
        return false;
    }

    // Calculate the load factor after this insertion.
    float future_load =
        (float)(table->size + table->tombstones + 1) /
        (float)table->capacity;

    // Grow the table if the load factor would become too high.
    if (future_load > table->load_factor) {

        // Prevent capacity overflow.
        if (table->capacity > SIZE_MAX / 2) {
            return false;
        }

        // Double the table capacity.
        size_t new_capacity = table->capacity * 2;

        // Resize the table.
        if (!hash_resize(table, new_capacity)) {
            return false;
        }
    }

    // Compute the hash for the key.
    u64 hash = fnv1a_hash(key);

    // Find the slot where the key belongs.
    HashEntry *entry = find_slot(table, key, hash);

    if (entry == NULL) {
        return false;
    }

    // If the key already exists, update its value.
    if (entry->state == OCCUPIED) {
        entry->value = value;
        return true;
    }

    // Reusing a tombstone removes one deleted entry.
    if (entry->state == TOMBSTONE) {
        table->tombstones--;
    }

    // Make a copy of the key for the table to own.
    entry->key = strdup(key);

    if (entry->key == NULL) {
        return false;
    }

    // Store the entry data.
    entry->value = value;
    entry->hash = hash;
    entry->state = OCCUPIED;

    // Record the successful insertion.
    table->size++;

    return true;
}



// Searches for a key in the hash table.
// Returns the associated value if the key exists.
void *hash_find(HashTable *table, const char *key) {

    // Validate the input.
    if (table == NULL || key == NULL) {
        return NULL;
    }

    // Reject empty keys.
    if (key[0] == '\0') {
        return NULL;
    }

    // Compute the hash for the key.
    u64 hash = fnv1a_hash(key);

    // Compute the starting index.
    size_t index = hash % table->capacity;

    // Track how many slots have been checked.
    size_t visited = 0;

    // Probe until every slot has been checked.
    while (visited < table->capacity) {

        // Get the current entry.
        HashEntry *entry = &table->entries[index];

        // An empty slot means the key does not exist.
        if (entry->state == EMPTY) {
            return NULL;
        }

        // Check for a matching key.
        if (entry->state == OCCUPIED) {

            // Compare the hash first to avoid unnecessary string comparisons.
            if (entry->hash == hash) {

                // Compare the actual keys.
                if (strcmp(entry->key, key) == 0) {
                    return entry->value;
                }
            }
        }

        // Move to the next slot using linear probing.
        index = probe_next(index, table->capacity);

        // Count this slot as visited.
        visited++;
    }

    // The key was not found.
    return NULL;
}


// Removes a key from the hash table.
// Marks the slot as a tombstone so probing continues to work.
bool hash_remove(HashTable *table, const char *key) {

    // Validate the input.
    if (table == NULL || key == NULL) {
        return false;
    }

    // Reject empty keys.
    if (key[0] == '\0') {
        return false;
    }

    // Compute the hash for the key.
    u64 hash = fnv1a_hash(key);

    // Compute the starting index.
    size_t index = hash % table->capacity;

    // Track how many slots have been checked.
    size_t visited = 0;

    // Probe until every slot has been checked.
    while (visited < table->capacity) {

        // Get the current entry.
        HashEntry *entry = &table->entries[index];

        // An empty slot means the key does not exist.
        if (entry->state == EMPTY) {
            return false;
        }

        // Check for a matching key.
        if (entry->state == OCCUPIED) {

            // Compare the hash first to avoid unnecessary string comparisons.
            if (entry->hash == hash) {

                // Compare the actual keys.
                if (strcmp(entry->key, key) == 0) {

                    // Free the owned key before removing it.
                    free(entry->key);

                    // Clear the entry and mark it as deleted.
                    entry->key = NULL;
                    entry->value = NULL;
                    entry->hash = 0;
                    entry->state = TOMBSTONE;

                    // Update the table statistics.
                    table->size--;
                    table->tombstones++;

                    return true;
                }
            }
        }

        // Move to the next slot using linear probing.
        index = probe_next(index, table->capacity);

        // Count this slot as visited.
        visited++;
    }

    // The key was not found.
    return false;
}

// Resizes the hash table and rehashes all occupied entries.
// Existing keys and values are moved into a new entry array.
bool hash_resize(HashTable *table, size_t new_capacity) {

    // Validate the input.
    if (table == NULL || new_capacity == 0) {
        return false;
    }

    // Prevent integer overflow before allocation.
    if (new_capacity > SIZE_MAX / sizeof(HashEntry)) {
        return false;
    }

    // Allocate and zero-initialize the new entry array.
    HashEntry *new_entries = calloc(new_capacity, sizeof(HashEntry));

    if (new_entries == NULL) {
        return false;
    }

    // Count the number of occupied entries after rehashing.
    size_t size = 0;

    // Rehash every occupied entry into the new table.
    for (size_t i = 0; i < table->capacity; i++) {

        // Get the current entry.
        HashEntry *entry = &table->entries[i];

        // Skip empty and deleted entries.
        if (entry->state == EMPTY || entry->state == TOMBSTONE) {
            continue;
        }

        // Compute the new starting index.
        size_t index = entry->hash % new_capacity;

        // Find an available slot using linear probing.
        while (new_entries[index].state == OCCUPIED) {
            index = probe_next(index, new_capacity);
        }

        // Move the entry into the new table.
        new_entries[index].key = entry->key;
        new_entries[index].value = entry->value;
        new_entries[index].hash = entry->hash;
        new_entries[index].state = OCCUPIED;

        size++;
    }

    // Free the old entry array.
    free(table->entries);

    // Update the table to use the new storage.
    table->entries = new_entries;
    table->capacity = new_capacity;
    table->size = size;
    table->tombstones = 0;

    return true;
}


// Destroys the hash table and releases all allocated memory.
void hash_destroy(HashTable *table) {

    // Nothing to destroy.
    if (table == NULL) {
        return;
    }

    // Free every key owned by the table.
    for (size_t i = 0; i < table->capacity; i++) {

        if (table->entries[i].state == OCCUPIED) {
            free(table->entries[i].key);
        }
    }

    // Free the entry array.
    free(table->entries);

    // Free the hash table structure.
    free(table);
}


// Computes a 64-bit FNV-1a hash for a null-terminated string.
// FNV-1a is a fast, non-cryptographic hash function commonly used
// for hash tables because it provides good key distribution.
u64 fnv1a_hash(const char *key) {

    // Optional safety check.
    // if (key == NULL) {
    //     return 0;
    // }

    // Get the length of the input string.
    size_t len = strlen(key);

    // Start with the FNV offset basis.
    // This is the standard initial value defined by the FNV algorithm.
    u64 hash = FNV_OFFSET_BASIS;

    // Process each character in the string.
    for (size_t i = 0; i < len; i++) {

        // Convert the current character to an unsigned 64-bit value
        // so every byte is treated consistently.
        hash ^= (u64)(unsigned char)key[i];

        // Multiply by the FNV prime to spread the bits.
        // This helps produce a well-distributed hash value.
        hash *= FNV_PRIME;
    }

    // Return the final hash value.
    return hash;
}


// Computes a 64-bit djb2 hash for a null-terminated string.
// djb2 is a simple, fast, non-cryptographic hash function
// commonly used for hash tables.
u64 djb2_hash(const char *key) {

    // Optional safety check.
    // if (key == NULL) {
    //     return 0;
    // }

    // Get the length of the input string.
    size_t len = strlen(key);

    // Initialize the hash with the standard djb2 starting value.
    // The value 5381 is part of the original djb2 algorithm.
    u64 hash = 5381;

    // Process each character in the string.
    for (size_t i = 0; i < len; i++) {

        // Convert the current character to an unsigned 64-bit value
        // so every byte is treated consistently.
        u64 current = (u64)(unsigned char)key[i];

        // Multiply the current hash by 33 and add the current character.
        // (hash << 5) + hash is equivalent to hash * 33.
        hash = ((hash << 5) + hash) + current;
    }

    // Return the final hash value.
    return hash;
}

// Returns the next index for linear probing.
// Wraps back to the beginning when the end of the table is reached.
size_t probe_next(size_t index, size_t capacity) {

    // Avoid division by zero.
    if (capacity == 0) {
        return 0;
    }

    // Move to the next slot and wrap around if needed.
    size_t next_index = (index + 1) % capacity; 

    // Return the next index.
    return next_index;
}


// Finds the slot for a given key in the hash table.
// Returns the existing entry if the key is found.
// Otherwise, returns the first available slot for insertion.
HashEntry *find_slot(HashTable *table, const char *key, u64 hash) {

    // Validate the input.
    if (table == NULL || key == NULL) {
        return NULL;
    }

    // Ensure the table has allocated storage.
    if (table->entries == NULL || table->capacity == 0) {
        return NULL;
    }

    // Compute the starting index from the hash value.
    size_t index = hash % table->capacity;

    // Track how many slots have been checked.
    size_t visited = 0;

    // Remember the first tombstone so it can be reused.
    HashEntry *first_tombstone = NULL;

    // Probe until every slot has been checked.
    while (visited < table->capacity) {

        // Get the current entry.
        HashEntry *const entry = &table->entries[index];

        // An empty slot means the key does not exist.
        // Return the first tombstone if one was found,
        // otherwise return the empty slot.
        if (entry->state == EMPTY) {

            if (first_tombstone != NULL) {
                return first_tombstone;
            }

            return entry;
        }

        // Check for a matching key in an occupied entry.
        if (entry->state == OCCUPIED) {

            // Compare the hash first to avoid unnecessary string comparisons.
            if (hash == entry->hash) {

                // Compare the actual keys.
                if (strcmp(entry->key, key) == 0) {
                    return entry;
                }
            }
        }

        // Remember the first tombstone encountered.
        if (entry->state == TOMBSTONE && first_tombstone == NULL) {
            first_tombstone = entry;
        }

        // Move to the next slot using linear probing.
        index = probe_next(index, table->capacity);

        // Count this slot as visited.
        visited++;
    }

    // The table is full. Reuse a tombstone if one exists.
    if (first_tombstone != NULL) {
        return first_tombstone;
    }

    // No suitable slot was found.
    return NULL;
}


// Rebuilds the hash table with a new capacity.
// Existing entries are reinserted into a new table so they
// are placed at their correct positions for the new size.
bool rehash_table(HashTable *table, size_t new_capacity) {

    // Validate the input.
    if (table == NULL || new_capacity == 0) {
        return false;
    }

    // Ensure the table has allocated storage.
    if (table->entries == NULL) {
        return false;
    }

    // The new table must be large enough to hold all entries.
    if (new_capacity < table->size) {
        return false;
    }

    // Prevent overflow when calculating the allocation size.
    if (new_capacity > SIZE_MAX / sizeof(HashEntry)) {
        return false;
    }

    // Temporary table used during rehashing.
    HashTable new_hashtable = {0};

    // Allocate storage for the new table.
    HashEntry *new_entries = malloc(new_capacity * sizeof(HashEntry));

    if (new_entries == NULL) {
        return false;
    }

    // Initialize every entry to zero.
    memset(new_entries, 0, new_capacity * sizeof(HashEntry));

    // Initialize the temporary table.
    new_hashtable.entries = new_entries;
    new_hashtable.capacity = new_capacity;
    new_hashtable.size = 0;

    // Reinsert every occupied entry into the new table.
    for (size_t i = 0; i < table->capacity; i++) {

        HashEntry *entry = &table->entries[i];

        // Skip unused and deleted entries.
        if (entry->state == EMPTY || entry->state == TOMBSTONE) {
            continue;
        }

        // Find the correct slot in the new table.
        HashEntry *new_entry = find_slot(&new_hashtable, entry->key, entry->hash);

        if (new_entry == NULL) {
            free(new_entries);
            return false;
        }

        // Copy the entry into the new table.
        new_entry->hash = entry->hash;
        new_entry->key = entry->key;
        new_entry->value = entry->value;
        new_entry->state = OCCUPIED;

        new_hashtable.size++;
    }

    // Verify that every entry was reinserted successfully.
    if (new_hashtable.size != table->size) {
        free(new_entries);
        return false;
    }

    // Free the old storage.
    free(table->entries);

    // Replace the old table with the new one.
    table->entries = new_entries;
    table->capacity = new_capacity;
    table->size = new_hashtable.size;

    return true;
}