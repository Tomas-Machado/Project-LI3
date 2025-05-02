#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "../include/validation.h"
#include "stdlib.h"

//! Validação de sintaxe apenas

// Helper function to check if a string is a number
bool is_number(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


// Validate date in the format yyyy/mm/dd
bool validate_date(const char *date) {
    if (strlen(date) != 10 || date[4] != '/' || date[7] != '/') {
        return false;
    }

    char year[5], month[3], day[3];
    strncpy(year, date, 4);
    year[4] = '\0';
    strncpy(month, date + 5, 2);
    month[2] = '\0';
    strncpy(day, date + 8, 2);
    day[2] = '\0';

    if (!is_number(year) || !is_number(month) || !is_number(day)) {
        return false;
    }

    int year_num = atoi(year);
    int month_num = atoi(month);
    int day_num = atoi(day);

    if (month_num < 1 || month_num > 12 || day_num < 1 || day_num > 31) {
        return false;
    }

    // Check if the date is not more recent than today
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (year_num > (tm.tm_year + 1900) ||
        (year_num == (tm.tm_year + 1900) && month_num > (tm.tm_mon + 1)) ||
        (year_num == (tm.tm_year + 1900) && month_num == (tm.tm_mon + 1) && day_num > tm.tm_mday)) {
        return false;
        }

    return true;
}

// Validate duration in the format hh:mm:ss
bool validate_duration(const char *duration) {
    if (strlen(duration) != 8 || duration[2] != ':' || duration[5] != ':') {
        return false;
    }

    char hours[3], minutes[3], seconds[3];
    strncpy(hours, duration, 2);
    hours[2] = '\0';
    strncpy(minutes, duration + 3, 2);
    minutes[2] = '\0';
    strncpy(seconds, duration + 6, 2);
    seconds[2] = '\0';

    if (!is_number(hours) || !is_number(minutes) || !is_number(seconds)) {
        return false;
    }

    int hours_num = atoi(hours);
    int minutes_num = atoi(minutes);
    int seconds_num = atoi(seconds);

    if (hours_num < 0 || hours_num > 99 || minutes_num < 0 || minutes_num > 59 || seconds_num < 0 || seconds_num > 59) {
        return false;
    }

    return true;
}

bool validate_email(const char *email) {
    // Check if there is exactly one '@' character in the email
    const char *at = strchr(email, '@');
    if (!at) {
        return false; // No '@' character found
    }

    // Find the last '.' after the '@' to validate the domain and TLD structure
    const char *dot = strrchr(at, '.');
    if (!dot || dot == at + 1 || dot[1] == '\0') {
        return false; // '.' is either missing, right after '@', or there's nothing after it
    }

    // Loop 1: Check if the username part (before '@') only contains alphanumeric characters
    for (const char *p = email; p < at; p++) {
        if (!isalnum(*p)) {
            return false; // Invalid character in username
        }
    }

    // Loop 2: Check if the domain part (between '@' and last '.') contains only lowercase letters
    for (const char *p = at + 1; p < dot; p++) {
        if (!islower(*p)) {
            return false; // Non-lowercase letter found in domain part
        }
    }

    // Loop 3: Check if the TLD part (after the last '.') contains only lowercase letters
    for (const char *p = dot + 1; p < email + strlen(email); p++) {
        if (!islower(*p)) {
            return false; // Non-lowercase letter found in TLD part
        }
    }

    // Check if the TLD part has a valid length (2 to 3 characters)
    if (strlen(dot + 1) < 2 || strlen(dot + 1) > 3) {
        return false;
    }

    return true; // Email is valid if all checks passed
}
// Validate subscription type
bool validate_subscription(const char *subscription_type) {
    return strcmp(subscription_type, "normal") == 0 || strcmp(subscription_type, "premium") == 0;
}