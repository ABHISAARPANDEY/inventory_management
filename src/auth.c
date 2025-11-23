/**
 * @file auth.c
 * @brief Implementation of authentication functions
 */

#include "auth.h"
#include <string.h>

// Simple hash function (djb2 algorithm with salt)
// Note: This is a basic hash for educational purposes, not cryptographically secure
static void simple_hash(const char *input, char *output) {
    unsigned long hash = 5381;
    unsigned long hash2 = 0;
    int c;
    const char *p = input;
    
    // First pass: djb2 algorithm
    while ((c = *p++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    // Second pass: additional mixing
    p = input;
    while ((c = *p++)) {
        hash2 = hash2 * 31 + c;
    }
    
    // Combine and convert to hex string (64 chars)
    sprintf(output, "%016lx%016lx%016lx%016lx", 
            hash, hash2, hash ^ hash2, (hash << 16) | (hash2 & 0xFFFF));
    output[HASH_LENGTH - 1] = '\0';
}

int hash_password(const char *password, char *hash_output) {
    if (password == NULL || hash_output == NULL) return 0;
    
    // Use simple hash for portability (no external dependencies)
    simple_hash(password, hash_output);
    
    return 1;
}

int verify_password(const char *password, const char *hash) {
    if (password == NULL || hash == NULL) return 0;
    
    char computed_hash[HASH_LENGTH];
    if (!hash_password(password, computed_hash)) {
        return 0;
    }
    
    return (strcmp(computed_hash, hash) == 0);
}

void user_list_init(UserList *list) {
    if (list == NULL) return;
    list->count = 0;
    memset(list->users, 0, sizeof(list->users));
}

int user_add(UserList *list, const User *user) {
    if (list == NULL || user == NULL) return 0;
    
    if (list->count >= MAX_USERS) {
        return 0;  // List is full
    }
    
    if (user_find_by_username(list, user->username) != NULL) {
        return 0;  // Username already exists
    }
    
    list->users[list->count] = *user;
    list->count++;
    return 1;
}

User* user_find_by_username(UserList *list, const char *username) {
    if (list == NULL || username == NULL) return NULL;
    
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->users[i].username, username) == 0) {
            return &list->users[i];
        }
    }
    
    return NULL;
}

User* authenticate_user(UserList *list, const char *username, const char *password) {
    if (list == NULL || username == NULL || password == NULL) {
        return NULL;
    }
    
    User *user = user_find_by_username(list, username);
    if (user == NULL) {
        return NULL;  // User not found
    }
    
    if (!verify_password(password, user->password_hash)) {
        return NULL;  // Invalid password
    }
    
    return user;
}

int is_admin(const User *user) {
    if (user == NULL) return 0;
    return (strcmp(user->role, ROLE_ADMIN) == 0);
}

int is_staff(const User *user) {
    if (user == NULL) return 0;
    return (strcmp(user->role, ROLE_STAFF) == 0);
}

void session_init(Session *session) {
    if (session == NULL) return;
    session->user = NULL;
    session->is_logged_in = 0;
}

void session_login(Session *session, User *user) {
    if (session == NULL || user == NULL) return;
    session->user = user;
    session->is_logged_in = 1;
}

void session_logout(Session *session) {
    if (session == NULL) return;
    session->user = NULL;
    session->is_logged_in = 0;
}

int session_is_active(const Session *session) {
    if (session == NULL) return 0;
    return session->is_logged_in;
}

