#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stdbool.h>
#include <tgmath.h>
#include <time.h>


void remove_last_char(char *str) {
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0';
    }

}




// Function to trim leading and trailing spaces, quotes, and newline characters
char *trim(char *str) {
    // Trim leading spaces, quotes, and newlines
    while (*str == ' ' || *str == '\'' || *str == '\n' || *str == '"') str++;

    // Trim trailing spaces, quotes, and newlines
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\'' || *end == '\n' || *end == '"')) {
        *end = '\0';
        end--;
    }

    return str;
}

char *trim_quotes(char *str) {
    // Trim leading and trailing quotes
    if (str[0] == '\"') {
        str++;
    }
    if (str[strlen(str) - 1] == '\"') {
        str[strlen(str) - 1] = '\0';
    }

    return str;
}

void remove_quotes_from_fields(char **fields) {
    int i = 0;

    // Loop through the fields array until a NULL pointer is found
    while (fields[i] != NULL) {
        char *field = fields[i];
        int len = strlen(field);
        int j = 0;

        // Iterate over each character, skipping quotes
        for (int k = 0; k < len; k++) {
            if (field[k] != '\"') {
                field[j++] = field[k];
            }
        }
        field[j] = '\0';  // Null-terminate the modified string
        i++;
    }
}

// Function to calculate age
int calculate_age(const char *birthdate) {
    int birth_year, birth_month, birth_day;
    int current_year = 2024, current_month = 9, current_day = 9;

    // Parse the birthdate string
    sscanf(birthdate, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

    // Calculate the age
    int age = current_year - birth_year;

    // Adjust the age if the current date is before the birthdate in the current year
    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
        age--;
    }

    return age;
}



int duration_to_seconds(const char *duration) {
    int hours, minutes, seconds;
    if (sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds) != 3) {
        fprintf(stderr, "Invalid duration format: %s\n", duration);
        return -1; // Return an error code if the format is invalid
    }
    return hours * 3600 + minutes * 60 + seconds;
}


// Function to convert total seconds to a duration string in the format "HH:MM:SS"
char* seconds_to_duration(int total_seconds) {
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Allocate memory for the duration string
    char *duration = malloc(25); // "HH:MM:SS" + null terminator
    if (duration == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    // Format the duration string
    snprintf(duration,25, "%02d:%02d:%02d", hours, minutes, seconds);
    return duration;
}


void trim_newline(char *str) {
    char *p = str;
    while (*p) {
        if (*p == '\n' || *p == '\r') {
            *p = '\0';  // Substitui por um terminador nulo
        }
        p++;
    }
}

char* format_id(int number) {
    // Allocate memory for the formatted string
    char *formatted_id = malloc(10); // "A" + 7 digits + null terminator
    if (formatted_id == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    // Format the number with leading zeros
    snprintf(formatted_id, 10, "A%07d", number);
    return formatted_id;
}


// Helper function to map genre name to Genre enum index
int genre_to_index(const char *genre_name) {
    if (strcmp(genre_name, "Rock") == 0) return 0;
    if (strcmp(genre_name, "Jazz") == 0) return 1;
    if (strcmp(genre_name, "Pop") == 0) return 2;
    if (strcmp(genre_name, "Classical") == 0) return 3;
    if (strcmp(genre_name, "Hip Hop") == 0) return 4;
    if (strcmp(genre_name, "Country") == 0) return 5;
    if (strcmp(genre_name, "Electronic") == 0) return 6;
    if (strcmp(genre_name, "Blues") == 0) return 7;
    if (strcmp(genre_name, "Metal") == 0) return 8;
    if (strcmp(genre_name, "Reggae") == 0) return 9;
    return -1;
}

GArray* parse_liked_musics_id(const char *liked_musics_id) {
    GArray *array = g_array_new(FALSE, FALSE, sizeof(int));
    char cleaned_liked_musics_id[4096];
    strncpy(cleaned_liked_musics_id, liked_musics_id, sizeof(cleaned_liked_musics_id) - 1);
    cleaned_liked_musics_id[sizeof(cleaned_liked_musics_id) - 1] = '\0';

    for (char *p = cleaned_liked_musics_id; *p; p++) {
        if (*p == '[' || *p == ']') {
            *p = ' ';
        }
    }

    char *token = strtok(cleaned_liked_musics_id, ",");
    while (token != NULL) {
        token = trim(token);
        int id = atoi(token + 1);
        g_array_append_val(array, id);
        token = strtok(NULL, ",");
    }

    return array;
}



GArray* parse_artist_ids(const char *artist_ids) {
    GArray *array = g_array_new(FALSE, FALSE, sizeof(int));
    char cleaned_artist_ids[4096];
    strncpy(cleaned_artist_ids, artist_ids, sizeof(cleaned_artist_ids) - 1);
    cleaned_artist_ids[sizeof(cleaned_artist_ids) - 1] = '\0';

    for (char *p = cleaned_artist_ids; *p; p++) {
        if (*p == '[' || *p == ']') {
            *p = ' ';
        }
    }

    char *token = strtok(cleaned_artist_ids, ",");
    while (token != NULL) {
        token = trim(token);
        int id = atoi(token + 1);
        g_array_append_val(array, id);
        token = strtok(NULL, ",");
    }

    return array;
}

//////////////////////////////////////////////////////TESTE////////////////////////////////////////////////////
// Reference date: 7 September 2024 (Week 0)
#define REFERENCE_YEAR 2024
#define REFERENCE_MONTH 9
#define REFERENCE_DAY 14

int calculate_week_position(char *date) {
    struct tm reference_date = {0};
    reference_date.tm_year = REFERENCE_YEAR - 1900; // Adjust year for tm_year
    reference_date.tm_mon = REFERENCE_MONTH - 1;   // Adjust month for tm_mon
    reference_date.tm_mday = REFERENCE_DAY;

    struct tm input_date = {0};
    sscanf(date, "%d/%d/%d", &input_date.tm_year, &input_date.tm_mon, &input_date.tm_mday);
    input_date.tm_year -= 1900; // Adjust year
    input_date.tm_mon -= 1;     // Adjust month

    // Convert dates to time_t for comparison
    time_t ref_time = mktime(&reference_date);
    time_t input_time = mktime(&input_date);

    if (ref_time == -1 || input_time == -1) {
        fprintf(stderr, "Error parsing dates.\n");
        return -1;
    }

    // Calculate difference in days and convert to week index
    double difference_in_days = difftime(ref_time, input_time) / (60 * 60 * 24);
     return (int)(difference_in_days / 7);
}