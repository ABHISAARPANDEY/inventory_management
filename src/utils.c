/**
 * @file utils.c
 * @brief Implementation of utility functions
 */

#include "utils.h"

void get_current_datetime(char *buffer, size_t size) {
    time_t rawtime;
    struct tm *timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_string(char *str, size_t size) {
    if (fgets(str, (int)size, stdin) == NULL) {
        return 0;
    }
    
    // Remove newline if present
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    trim_string(str);
    return 1;
}

int read_integer(int *value) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    char *endptr;
    long int result = strtol(buffer, &endptr, 10);
    
    // Check if conversion was successful
    if (*endptr != '\n' && *endptr != '\0' && *endptr != ' ') {
        return 0;  // Invalid input
    }
    
    *value = (int)result;
    return 1;
}

int read_double(double *value) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    char *endptr;
    double result = strtod(buffer, &endptr);
    
    // Check if conversion was successful
    if (*endptr != '\n' && *endptr != '\0' && *endptr != ' ') {
        return 0;  // Invalid input
    }
    
    *value = result;
    return 1;
}

void trim_string(char *str) {
    if (str == NULL) return;
    
    // Trim leading whitespace
    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    // Trim trailing whitespace
    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    // Write new null terminator
    end[1] = '\0';
    
    // Move trimmed string to beginning
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

int validate_email(const char *email) {
    if (email == NULL || strlen(email) == 0) {
        return 0;
    }
    
    int at_found = 0;
    int dot_after_at = 0;
    
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            if (at_found) return 0;  // Multiple @ symbols
            at_found = 1;
        } else if (at_found && email[i] == '.') {
            dot_after_at = 1;
        }
    }
    
    return (at_found && dot_after_at);
}

int validate_phone(const char *phone) {
    if (phone == NULL || strlen(phone) == 0) {
        return 0;
    }
    
    // Basic validation: should contain digits, may have +, -, spaces, parentheses
    int digit_count = 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char)phone[i])) {
            digit_count++;
        } else if (phone[i] != '+' && phone[i] != '-' && 
                   phone[i] != ' ' && phone[i] != '(' && phone[i] != ')') {
            return 0;
        }
    }
    
    return (digit_count >= 7);  // At least 7 digits
}

void to_lowercase(char *str) {
    if (str == NULL) return;
    
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int is_all_digits(const char *str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    
    return 1;
}

void print_separator(int length, char character) {
    for (int i = 0; i < length; i++) {
        putchar(character);
    }
    putchar('\n');
}

void pause_screen(void) {
    printf("\nPress Enter to continue...");
    clear_input_buffer();
    getchar();
}

