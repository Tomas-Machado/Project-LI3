#include "artist.h"
#include <stdio.h>
#include <stdlib.h>
#include "Gestor_Artist.h"
#include <glib.h>
#include "catalog.h"
#include "Utils.h"

typedef struct Gestor_Artist {
    GHashTable *artist_table;
} *Gestor_Artist;

Gestor_Artist create_gestor_artist() {
    // Create the artist hash table
    Gestor_Artist gestor = malloc(sizeof(struct Gestor_Artist));
    gestor->artist_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, destroy_artist);
    return gestor;
}

void insert_artist_gestor(Gestor_Artist gestor, char **artist_fields) {
    Artist artist = create_artist(artist_fields);
    int *key = malloc(sizeof(int));
    *key = get_artist_id(artist);

    // Insert into the hash table
    g_hash_table_insert(gestor->artist_table, key, artist);
}

// Getters
char *get_artist_name_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_name(artist) : NULL;
}

char *get_artist_type_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_type(artist) : NULL;
}

char *get_artist_country_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_country(artist) : NULL;
}

int get_artist_discography_duration_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_discography_duration(artist) : 0;
}

double get_artist_rate_per_stream_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_rate_per_stream(artist) : 0;
}

GArray* get_artist_weeks_by_id(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    return artist ? get_artist_weeks_duration(artist) : NULL;
}


//////////////////////////////////////////////////////////SETTERS//////////////////////////////////////////////////////////
// Compare function for sorting artist discography duration
int compare_artist_discography(const void *a, const void *b, Gestor_Artist gestor) {
    int id_a = *(int *)a;
    int id_b = *(int *)b;

    int discography_duration_a = get_artist_discography_duration_by_id(gestor, id_a);
    int discography_duration_b = get_artist_discography_duration_by_id(gestor, id_b);

    // Compare by discography duration first, then by ID if tied
    if (discography_duration_b != discography_duration_a) {
        return discography_duration_b - discography_duration_a;
    }
    return id_a - id_b;
}

// Update the discography duration of an artist
void update_artist_discography_duration(Gestor_Artist gestor, int artist_id, int duration) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    // Update the discography duration if the artist exists
    if (artist) {
        int current_duration = get_artist_discography_duration(artist);
        set_artist_discography_duration(artist, current_duration + duration);
    }
}
//Update the number of albums of an artist
void update_artist_albums(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    // Update the discography duration if the artist exists
    if (artist) {
        int current_albums = get_artist_albums(artist);
        set_artist_num_albums(artist, current_albums + 1);
    }
}

void add_revenue(Gestor_Artist gestor, int artist_id, double revenue) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    // Update the revenue if the artist exists
    if (artist) {
        double current_revenue = get_artist_total_recipes(artist);
        set_artist_total_recipes(artist, current_revenue + revenue);
    }
}


void destroy_gestor_artist(Gestor_Artist gestor) {
    // Free the hash table and its contents
    g_hash_table_destroy(gestor->artist_table);
    free(gestor);
}
//////////////////////////////////////////////Auxiliary//////////////////////////////////////////////

int get_num_members(Gestor_Artist gestor,int artist_id){
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    if (artist) {
        return get_artist_num_members(artist);
    }
    return 0;
}

int get_members_id(Gestor_Artist gestor,int artist_id,int index){
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    if (artist) {
        GArray *id_constituent = get_artist_id_constituent(artist);
        return g_array_index(id_constituent, int, index);
    }
    return 0;
}

bool is_artist_group(Gestor_Artist gestor, int artist_id) {
    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    if (artist) {
        char *artist_type = get_artist_type(artist);
        bool is_group = artist_type[0] == 'g' || artist_type[0] == 'G';
        g_free(artist_type);
        return is_group;
    }
    return false;
}

void update_artist_revenue(Gestor_Artist gestor_artist, int artist_id,  double rate_per_stream) {
    // Calculate the artist's revenue directly from reproductions and rate per stream
    double receitaArtista =  rate_per_stream;

    // Check if the artist is part of a collective or an individual artist
    if (is_artist_group(gestor_artist, artist_id)) {
        // Retrieve the number of members in the collective group
        int num_members = get_num_members(gestor_artist, artist_id);

        //add revenue for Original artist
        add_revenue(gestor_artist, artist_id, receitaArtista);
        // Divide the revenue equally among all members of the group
        for (int i = 0; i < num_members; i++) {

            int member_id = get_members_id(gestor_artist, artist_id, i);
            double individual_share = receitaArtista / num_members  ;
            add_revenue(gestor_artist, member_id, individual_share);

        }
    } else {
        // Add revenue directly for individual artists
        add_revenue(gestor_artist, artist_id, receitaArtista);
    }
}










///////////////////////////////////////////////Queries///////////////////////////////////////////////

///////////////////////////////////////////////Query 1///////////////////////////////////////////////
void get_query1_Artist(const char *id, Gestor_Artist gestor, char *result, char separator, int interativo) {
    int artist_id = atoi(id + 1);

    Artist artist = g_hash_table_lookup(gestor->artist_table, &artist_id);
    if (!artist) {
        if (interativo == 1) {
            printf("No artist found for ID: %s\n", id);
        } else {
            snprintf(result, 2048, "\n");
        }
        return;
    }

    char *name = get_artist_name(artist);
    char *type = get_artist_type(artist);
    trim_newline(type);
    char *country = get_artist_country(artist);
    int num_albums = get_artist_albums(artist);
    double total_recipes = get_artist_total_recipes(artist);

    if (interativo == 1) {
        printf("%s%c%s%c%s%c%d%c%0.2f\n", name, separator, type, separator, country, separator, num_albums, separator, total_recipes);
    } else {
        snprintf(result, 2048, "%s%c%s%c%s%c%d%c%0.2f\n", name, separator, type, separator, country, separator, num_albums, separator, total_recipes);
    }
}

///////////////////////////////////////////////Query 2///////////////////////////////////////////////
void get_query2(int N, char *country, Gestor_Artist gestor, char *result, char separator, int interativo) {
    //using [^\n] to read country with spaces
    //quotes doesn't get removed
    if (country) {
        country++; // Remove initial quotes
    }

    // Create an array of artist IDs
    GArray *artist_id_array = g_array_new(FALSE, FALSE, sizeof(int));

    // Filter artists by country and add their IDs to the array
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, gestor->artist_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist artist = (Artist)value;
        char *artist_country = get_artist_country(artist);

        if (country == NULL) {
            g_array_append_val(artist_id_array, *(int *)key);
        }

        if (country) {
            if (strcmp(artist_country, country) == 0) {
                g_array_append_val(artist_id_array, *(int *)key);
            }
        }
        g_free(artist_country);
    }

    // Sort the array of artist IDs based on their discography duration and ID
    g_array_sort_with_data(artist_id_array, (GCompareDataFunc)compare_artist_discography, gestor);
    result[0] = '\0'; // Initialize result as an empty string

    // Output the artist information
    if (N == 0 ) {
        snprintf(result, 2048, "\n");
    } else {
        for (int i = 0; i < MIN(N, artist_id_array->len); i++) {
            int artist_id = g_array_index(artist_id_array, int, i);

            // Get the artist information
            char *name = get_artist_name_by_id(gestor, artist_id);
            char *duration_str = seconds_to_duration(get_artist_discography_duration_by_id(gestor, artist_id));
            char *type = get_artist_type_by_id(gestor, artist_id);
            char *artist_country = get_artist_country_by_id(gestor, artist_id);

            // Output the artist information and remove the newline character from type another bug while parsing?
            trim_newline(type);

            char line[2048];
            snprintf(line, sizeof(line), "%s%c%s%c%s%c%s\n",
                name,separator,
                type,separator,
                duration_str,separator,
                artist_country);

            if (interativo == 1) {
                printf("%s", line);
            } else {
                strncat(result, line, 2048 - strlen(result) - 1);
            }

            // Free the strings
            g_free(name);
            g_free(duration_str);
            g_free(type);
            g_free(artist_country);
        }
    }

    // Clean up
    g_array_free(artist_id_array, TRUE);
}


///////////////////////////////////////////////////////////Query 4///////////////////////////////////////////////

// Query 4 implementation
void query_4(Gestor_Artist gestor, char *begin_date, char *end_date,  char separator,char *result, int interativo) {
    int start_week = 468, end_week = 0; // Default to full range of 10 years (52 weeks x 10)


    GHashTable *artist_table = gestor->artist_table;
    if (begin_date && end_date) {
        start_week = calculate_week_position(begin_date);
        end_week = calculate_week_position(end_date);
    }

    GArray *weekly_top10[524]; // Array of GArrays to store top 10 artists for each week
    for (int i = 0; i < 524; i++) {
        weekly_top10[i] = g_array_new(FALSE, TRUE, sizeof(Artist)); // Store Artist pointers
    }

    // Calculate weekly top 10
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, artist_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist artist = (Artist)value;

        for (int week = end_week; week <= start_week; week++) {
            GArray *weeks = get_artist_weeks_duration(artist);
            int duration = g_array_index(weeks, int, week);
            if (duration > 0) {
                add_to_top10(weekly_top10[week], artist, week);
            }
        }
    }

    // Count top 10 appearances for each artist
    g_hash_table_iter_init(&iter, artist_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist artist = (Artist)value;
        set_artist_count_top10(artist, 0); // Reset count

        for (int week = end_week; week <= start_week; week++) {
            for (guint i = 0; i < weekly_top10[week]->len; i++) {
                Artist top_artist = g_array_index(weekly_top10[week], Artist, i);
                if (  get_artist_id(top_artist) == get_artist_id(artist)) {
                    int count = get_artist_count_top10(artist);
                    set_artist_count_top10(artist, count + 1);
                    break;
                }
            }
        }
    }

    // Find the artist with the most top 10 appearances
    Artist top_artist = NULL;
    g_hash_table_iter_init(&iter, artist_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist artist = (Artist)value;

        if (!top_artist || get_artist_count_top10(artist) > get_artist_count_top10(top_artist) ||
            (get_artist_count_top10(artist) == get_artist_count_top10(top_artist) && get_artist_id(artist) < get_artist_id(top_artist))) {
            top_artist = artist;
        }
    }
    int exist = get_artist_count_top10(top_artist);
    // Output the result
    if (top_artist && exist > 0) {
        char *type = get_artist_type(top_artist);
        trim_newline(type);

        char line[2048];
        char *id = format_id(get_artist_id(top_artist));
        if (interativo == 0) {
            snprintf(result, 2048, "%s%c%s%c%d\n", id, separator,
                type, separator, get_artist_count_top10(top_artist));
        } else {
            printf("%s%c%s%c%d\n", id, separator,
                type, separator, get_artist_count_top10(top_artist));
        }
        free(id);
        free(type);
        strncat(result, line, 2048 - strlen(result) - 1);
    }
    else {
        if (interativo == 0) {
            snprintf(result, 2048, "\n");
        } else {
            printf("\n");
        }
    }

    // Clean up
    for (int i = 0; i < 524; i++) {
        g_array_unref(weekly_top10[i]);
    }

}



// Helper function to add an artist to the top 10 list
void add_to_top10(GArray *top10, Artist artist, int week) {
    g_array_append_val(top10, artist);

    g_array_sort_with_data(top10, (GCompareDataFunc)compare_artists_by_duration, &week);
    if (top10->len > 10) {
        g_array_remove_index(top10, 10); // Keep only top 10
    }
}

// Compare function for sorting artists by duration and ID
int compare_artists_by_duration(gconstpointer a, gconstpointer b, gpointer user_data) {
    const Artist artist_a = *(const Artist *)a;
    const Artist artist_b = *(const Artist *)b;
    int week = *(int *)user_data;

    GArray *weeks_a = get_artist_weeks_duration(artist_a);
    GArray *weeks_b = get_artist_weeks_duration(artist_b);
    int duration_a = g_array_index(weeks_a, int, week);
    int duration_b = g_array_index(weeks_b, int, week);

    if (duration_a != duration_b) {
        return duration_b - duration_a; // Descending by duration
    }
    return get_artist_id(artist_a) - get_artist_id(artist_b); // Ascending by ID
}

///////////////////////////////////////////////Auxiliary///////////////////////////////////////////////
bool artist_exists(const char *artist_ids, Gestor_Artist gestor) {
    // Create a copy of artist_id to modify it
    char cleaned_artist_id[4096];
    strncpy(cleaned_artist_id, artist_ids, sizeof(cleaned_artist_id) - 1);
    cleaned_artist_id[sizeof(cleaned_artist_id) - 1] = '\0';

    // Remove square brackets
    char *start = cleaned_artist_id;
    if (*start == '[') start++;
    char *end = cleaned_artist_id + strlen(cleaned_artist_id) - 1;
    if (*end == ']') *end = '\0';

    // Remove quotes and split by comma
    char *token = strtok(start, ",");
    while (token != NULL) {
        // Remove quotes
        if (*token == '\'') token++;
        if (token[strlen(token) - 1] == '\'') token[strlen(token) - 1] = '\0';
        if (*token == ' ') token++;
        if (*token == '\'') token++;

        int id = atoi(token + 1);
        // Check if the artist ID exists in the hash table
        if (g_hash_table_contains(gestor->artist_table, &id)) {
            return true;
        }

        token = strtok(NULL, ",");
    }

    return false;
}