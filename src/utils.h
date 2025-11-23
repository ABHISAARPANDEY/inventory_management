/**
 * @file utils.h
 * @brief Utility functions for input validation, string operations, and common helpers
 * @author Inventory Management System
 * @date 2025
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_STRING_LEN 200
#define MAX_NAME_LEN 100
#define MAX_EMAIL_LEN 100
#define MAX_PHONE_LEN 20
#define MAX_ADDRESS_LEN 200
#define MAX_NOTES_LEN 200

/**
 * @brief Get current date and time as a formatted string
 * @param buffer Output buffer to store the date-time string
 * @param size Size of the buffer
 */
void get_current_datetime(char *buffer, size_t size);

/**
 * @brief Clear the input buffer
 */
void clear_input_buffer(void);

/**
 * @brief Read a string from stdin with size limit
 * @param str Buffer to store the string
 * @param size Maximum size of the buffer
 * @return 1 on success, 0 on failure
 */
int read_string(char *str, size_t size);

/**
 * @brief Read an integer from stdin with validation
 * @param value Pointer to store the integer value
 * @return 1 on success, 0 on failure
 */
int read_integer(int *value);

/**
 * @brief Read a double from stdin with validation
 * @param value Pointer to store the double value
 * @return 1 on success, 0 on failure
 */
int read_double(double *value);

/**
 * @brief Trim whitespace from both ends of a string
 * @param str String to trim (modified in place)
 */
void trim_string(char *str);

/**
 * @brief Validate email format (basic validation)
 * @param email Email string to validate
 * @return 1 if valid, 0 otherwise
 */
int validate_email(const char *email);

/**
 * @brief Validate phone number format (basic validation)
 * @param phone Phone string to validate
 * @return 1 if valid, 0 otherwise
 */
int validate_phone(const char *phone);

/**
 * @brief Convert string to lowercase
 * @param str String to convert (modified in place)
 */
void to_lowercase(char *str);

/**
 * @brief Check if a string contains only digits
 * @param str String to check
 * @return 1 if all digits, 0 otherwise
 */
int is_all_digits(const char *str);

/**
 * @brief Print a separator line
 * @param length Length of the separator
 * @param character Character to use for separator
 */
void print_separator(int length, char character);

/**
 * @brief Pause and wait for user to press Enter
 */
void pause_screen(void);

#endif /* UTILS_H */

