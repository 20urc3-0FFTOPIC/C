// Dependencies: libssl-dev
// Compile with: gcc MPT.c -lssl -lcrypto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define HASH_LENGTH SHA256_DIGEST_LENGTH

// Struct for MPT nodes
typedef struct mpt_node {
    char *key;
    char *value;
    int is_leaf;
    unsigned char hash[HASH_LENGTH];
    struct mpt_node *children[16]; // maximum of 16 child nodes per parent
} mpt_node_t;

// Function to create a new MPT node
mpt_node_t *mpt_node_create(char *key, char *value) {
    mpt_node_t *node = malloc(sizeof(mpt_node_t));
    node->key = strdup(key);
    node->value = strdup(value);
    node->is_leaf = 1;
    memset(node->hash, 0, HASH_LENGTH);
    memset(node->children, 0, sizeof(node->children));
    return node;
}

// Function to calculate the hash of an MPT node
void mpt_node_hash(mpt_node_t *node) {
    unsigned char *hash_data = malloc(strlen(node->key) + strlen(node->value) + 1);
    sprintf(hash_data, "%s%s", node->key, node->value);
    SHA256(hash_data, strlen(hash_data), node->hash);
    free(hash_data);
}

// Function to insert a key-value pair into an MPT
void mpt_insert(mpt_node_t *root, char *key, char *value) {
    // Convert key to nibbles (4-bit chunks)
    int key_len = strlen(key);
    unsigned char *nibbles = malloc(key_len * 2);
    for (int i = 0; i < key_len; i++) {
        nibbles[i * 2] = (key[i] >> 4) & 0x0f;
        nibbles[i * 2 + 1] = key[i] & 0x0f;
    }
    // Traverse MPT and insert new node as necessary
    mpt_node_t *node = root;
    int i = 0;
    while (i < key_len * 2) {
        int nibble = nibbles[i];
        if (!node->children[nibble]) {
            node->children[nibble] = mpt_node_create("", "");
            node->is_leaf = 0;
        }
        node = node->children[nibble];
        i++;
    }
    // Create new leaf node for value
    mpt_node_t *leaf = mpt_node_create(key, value);
    node->children[nibbles[i - 1]] = leaf;
    node->is_leaf = 0;
    // Update hashes of nodes along path from root to new leaf
    while (node) {
        int updated = 0;
        for (int j = 0; j < 16; j++) {
            if (node->children[j]) {
                mpt_node_hash(node->children[j]);
                updated = 1;
            }
        }
        if (!updated) {
            break;
        }
        if (node == root) {
            break;
        }
        node = node->children[15]; // go up to parent node
    }
    free(nibbles);
}

// MPT and return its value
char *mpt_search(mpt_node_t *root, char *key) {
    // Convert key to nibbles (4-bit chunks)
    int key_len = strlen(key);
    unsigned char *nibbles = malloc(key_len * 2);
    for (int i = 0; i < key_len; i++) {
        nibbles[i * 2] = (key[i] >> 4) & 0x0f;
        nibbles[i * 2 + 1] = key[i] & 0x0f;
    }
    // Traverse MPT and return value if found
    mpt_node_t *node = root;
    int i = 0;
    while (i < key_len * 2) {
        int nibble = nibbles[i];
        if (!node->children[nibble]) {
            break;
        }
        node = node->children[nibble];
        i++;
    }
    free(nibbles);
    if (i == key_len * 2 && node->is_leaf) {
        return node->value;
    } else {
        return NULL;
    }
}

// Function to print an MPT (for debugging purposes)
void mpt_print(mpt_node_t *root, int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    printf("- hash: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", root->hash[i]);
    }
    printf("\n");
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    printf("- key: %s\n", root->key);
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    printf("- value: %s\n", root->value);
    for (int i = 0; i < 16; i++) {
        if (root->children[i]) {
            for (int j = 0; j < indent; j++) {
                printf("  ");
            }
            printf("- nibble: %d\n", i);
            mpt_print(root->children[i], indent + 1);
        }
    }
}

// Main function to test the MPT implementation
int main() {
    // Create root node
    mpt_node_t *root = mpt_node_create("", "");
    // Insert some key-value pairs
    mpt_insert(root, "hello", "world");
    mpt_insert(root, "goodbye", "moon");
    mpt_insert(root, "foo", "bar");
    // Search for a key and print the result
    char *value = mpt_search(root, "hello");
    printf("Value for key 'hello': %s\n", value);
    // Print the MPT
    mpt_print(root, 0);
    // Clean up memory
    // (in practice, you'd probably want to reuse the MPT or persist it to disk)
    free(root->key);
    free(root->value);
    free(root);
    return 0;
}
