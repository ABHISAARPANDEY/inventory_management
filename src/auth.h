/**
 * @file auth.h
 * @brief User authentication and authorization
 * @author Inventory Management System
 * @date 2025
 */

#ifndef AUTH_H
#define AUTH_H

#include "utils.h"

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100
#define HASH_LENGTH 65  // SHA-256 produces 64 hex chars + null terminator

#define ROLE_ADMIN "ADMIN"
#define ROLE_STAFF "STAFF"

/**
 * @brief User structure
 */
typedef struct {
    char username[MAX_USERNAME_LEN];    ///< Username
    char password_hash[HASH_LENGTH];    ///< SHA-256 hash of password
    char role[10];                      ///< "ADMIN" or "STAFF"
} User;

/**
 * @brief User list structure
 */
typedef struct {
    User users[MAX_USERS];
    int count;
} UserList;

/**
 * @brief Current session information
 */
typedef struct {
    User *user;         ///< Pointer to logged-in user
    int is_logged_in;   ///< 1 if logged in, 0 otherwise
} Session;

/**
 * @brief Initialize user list
 * @param list Pointer to UserList structure
 */
void user_list_init(UserList *list);

/**
 * @brief Add a new user
 * @param list Pointer to UserList
 * @param user User to add
 * @return 1 on success, 0 on failure
 */
int user_add(UserList *list, const User *user);

/**
 * @brief Find user by username
 * @param list Pointer to UserList
 * @param username Username to search for
 * @return Pointer to user if found, NULL otherwise
 */
User* user_find_by_username(UserList *list, const char *username);

/**
 * @brief Hash a password using SHA-256 (simple implementation)
 * @param password Plain text password
 * @param hash_output Output buffer for hash (must be at least HASH_LENGTH)
 * @return 1 on success, 0 on failure
 */
int hash_password(const char *password, char *hash_output);

/**
 * @brief Verify password against hash
 * @param password Plain text password
 * @param hash Stored password hash
 * @return 1 if match, 0 otherwise
 */
int verify_password(const char *password, const char *hash);

/**
 * @brief Authenticate user login
 * @param list Pointer to UserList
 * @param username Username
 * @param password Plain text password
 * @return Pointer to user if authenticated, NULL otherwise
 */
User* authenticate_user(UserList *list, const char *username, const char *password);

/**
 * @brief Check if user has admin role
 * @param user User to check
 * @return 1 if admin, 0 otherwise
 */
int is_admin(const User *user);

/**
 * @brief Check if user has staff role
 * @param user User to check
 * @return 1 if staff, 0 otherwise
 */
int is_staff(const User *user);

/**
 * @brief Initialize session
 * @param session Pointer to Session structure
 */
void session_init(Session *session);

/**
 * @brief Login user
 * @param session Pointer to Session
 * @param user User to login
 */
void session_login(Session *session, User *user);

/**
 * @brief Logout user
 * @param session Pointer to Session
 */
void session_logout(Session *session);

/**
 * @brief Check if session is active
 * @param session Pointer to Session
 * @return 1 if logged in, 0 otherwise
 */
int session_is_active(const Session *session);

#endif /* AUTH_H */

