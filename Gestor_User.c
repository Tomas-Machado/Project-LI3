#include "users.h"
#include "Gestor_User.h"
#include "Gestor_Artist.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Gestor_User {
    GHashTable *user_table;
    GArray *countsG[100];
} *Gestor_User;

///////////////////////////////////////Getters///////////////////////////////////////////

void auxiliar_genre_count(Gestor_User gestor_user, int age, int genre_index) {
    int *count_ptr = &g_array_index(gestor_user->countsG[age], int, genre_index);
    if (count_ptr) {
        (*count_ptr)++;
    }
}


///////////////////////////////////////Create and Destroy///////////////////////////////////////////
Gestor_User create_gestor_user() {
    Gestor_User gestor = malloc(sizeof(struct Gestor_User));

    // Create the user hash table
    gestor->user_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, destroy_user);

    // Initialize the genre counts array with 0s
    for (int i = 0; i < 100; i++) {
        gestor->countsG[i] = g_array_new(FALSE, FALSE, sizeof(int));
        for (int j = 0; j < 10; j++) {
            gint zero = 0;
            g_array_append_val(gestor->countsG[i], zero);
        }
    }

    return gestor;
}

///////////////////////////////////////Insert///////////////////////////////////////////
// Creates a new user and inserts it into the user hash table
void insert_user_gestor(Gestor_User gestor, char **user_fields, GArray *music_ids) {
    Users user = create_User(user_fields, music_ids);
    int *key = malloc(sizeof(int));
    *key = get_user_username(user);

    // Insert into the hash table
    g_hash_table_insert(gestor->user_table, key, user);
}

void destroy_gestor_user(Gestor_User gestor) {
    // Free the hash table and its contents
    g_hash_table_destroy(gestor->user_table);

    // Free the countsG array
    for (int i = 0; i < 100; i++) {
        if (gestor->countsG[i]) {
            g_array_free(gestor->countsG[i], TRUE);
        }
    }

    free(gestor);
}

///////////////////////////////////////Getters///////////////////////////////////////////
int get_user_age_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_age(user) : 0;
}

GArray *get_user_like_musics_id_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_like_musics_id(user) : NULL;
}

char *get_user_email_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_email(user) : NULL;
}

char *get_user_first_name_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_first_name(user) : NULL;
}

char *get_user_last_name_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_last_name(user) : NULL;
}

char *get_user_country_by_id(Gestor_User gestor, int user_id) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_country(user) : NULL;
}
/*
GArray *get_user_historicUser_by_id(Gestor_User gestor, int user_id, int index) {
    Users user = g_hash_table_lookup(gestor->user_table, &user_id);
    return user ? get_user_historicUser(user, index) : NULL;
}
*/
///////////////////////////////////////AUXILIARY///////////////////////////////////////////

//////////////////////////////////////QUERY1///////////////////////////////////////////
void get_query1_User(const char *user_id, Gestor_User gestor, char *result, char separator, int interativo) {
    int user_id_int = atoi(user_id + 1);

    // Check if the user ID is valid else print a new line
    if (user_id_int >= 0) {
        // Check if the user exists else print a new line
        Users user = g_hash_table_lookup(gestor->user_table, &user_id_int);
        if (user) {
            // Retrieve user information
            char *email = get_user_email_by_id(gestor, user_id_int);
            char *first_name = get_user_first_name_by_id(gestor, user_id_int);
            char *last_name = get_user_last_name_by_id(gestor, user_id_int);
            int age = get_user_age_by_id(gestor, user_id_int);
            char *country = get_user_country_by_id(gestor, user_id_int);

            // Output the user information to the file
            if (interativo == 0) {
            snprintf(result, 1024, "%s%c%s%c%s%c%d%c%s\n",
                email,separator,
                first_name,separator,
                last_name,separator,
                age,separator, country);
            } else
            {
                printf("%s%c%s%c%s%c%d%c%s\n",
                email,separator,
                first_name,separator,
                last_name,separator,
                age,separator, country);
            }
            // Free the strings
            g_free(email);
            g_free(first_name);
            g_free(last_name);
            g_free(country);
        } else {
            if (interativo == 0)
            {
                snprintf(result, 1024, "\n");
            } else
            {
                printf("\n");
            }
        }
    } else {
        snprintf(result, 1024, "\n");
    }

}

/////////////////////////////////////QUERY3/////////////////////////////////////////////////////////////////////
// Struct to hold genre counts for sorting
typedef struct GenreCount {
    char *genre;
    int count;
} GenreCount;

// Array to map indices to genre names for output
const char *genre_names[10] = {
    "Rock", "Jazz", "Pop", "Classical", "Hip Hop",
    "Country", "Electronic", "Blues", "Metal", "Reggae"
};

// Compare function for sorting genre counts Auxiliary function
int compare_genre_count(const void *a, const void *b) {
    GenreCount *genreA = (GenreCount *)a;
    GenreCount *genreB = (GenreCount *)b;

    if (genreB->count != genreA->count) {
        return genreB->count - genreA->count;
    }
    return strcmp(genreA->genre, genreB->genre);
}

void get_query3(int age1, int age2, Gestor_User gestor_user, char *result, char separator, int interativo) {
    // Initialize the result buffer
    memset(result, 0, 2048);

    int aggregated_genre_counts[10] = {0};  // Array for aggregating counts across age groups
    // Aggregate genre counts across age groups
    for (int age = age1; age <= age2 && age < 100; age++) {
        GArray *age_genre_counts = gestor_user->countsG[age];
        if (age_genre_counts) {
            for (int genre_index = 0; genre_index < 10; genre_index++) {
                int *count_ptr = &g_array_index(age_genre_counts, int, genre_index);
                if (count_ptr) {
                    aggregated_genre_counts[genre_index] += *count_ptr;
                }
            }
        }
    }

    // Sort and output the aggregated genre counts
    GenreCount genre_counts[10];
    for (int i = 0; i < 10; i++) {
        genre_counts[i].genre = (char *)genre_names[i];
        genre_counts[i].count = aggregated_genre_counts[i];
    }

    qsort(genre_counts, 10, sizeof(GenreCount), compare_genre_count);

    // Output the genre counts to the file, check if the genre count is empty
    int is_empty = 1;
    for (int i = 0; i < 10; i++) {
        if (genre_counts[i].count > 0) {
            is_empty = 0;
            break;
        }
    }
    if (is_empty) {
        snprintf(result, 2048, "\n");
    } else {
        for (int i = 0; i < 10; i++) {
            if (genre_counts[i].count > 0) {
                char line[256];
                if (interativo == 0)
                {
                    snprintf(line, sizeof(line), "%s%c%d\n", genre_counts[i].genre, separator, genre_counts[i].count);
                    strncat(result, line, 2048 - strlen(result) - 1);
                } else
                {
                    printf("%s%c%d\n", genre_counts[i].genre, separator, genre_counts[i].count);
                    strncat(result, line, 2048 - strlen(result) - 1);
                }
            }
        }
    }
}