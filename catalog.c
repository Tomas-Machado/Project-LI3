#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/Utils.h"
#include "../include/catalog.h"

#include "../include/Gestor_Artist.h"
#include "../include/Gestor_Music.h"
#include "../include/Gestor_User.h"
#include "../include/Gestor_Album.h"
#include "../include/Gestor_History.h"

typedef struct Catalog {
    Gestor_Artist gestor_artist;
    Gestor_Album gestor_album;
    Gestor_Music gestor_music;
    Gestor_User gestor_user;
    Gestor_History gestor_history;
} *Catalog;

Catalog create_catalog() {
    Catalog catalog = malloc(sizeof(struct Catalog));

    catalog->gestor_artist = create_gestor_artist();
    catalog->gestor_album = create_gestor_album();
    catalog->gestor_music = create_gestor_music();
    catalog->gestor_user = create_gestor_user();
    catalog->gestor_history = create_gestor_history();
    return catalog;
}

Gestor_Music get_musics(Catalog catalog) {
    return catalog->gestor_music;
}

Gestor_Artist get_artists(Catalog catalog) {
    return catalog->gestor_artist;
}

Gestor_User get_users(Catalog catalog) {
    return catalog->gestor_user;
}

Gestor_Album get_albums(Catalog catalog) {
    return catalog->gestor_album;
}

Gestor_History get_history(Catalog catalog) {
    return catalog->gestor_history;
}

void destroy_catalog(Catalog catalog) {
    destroy_gestor_artist(catalog->gestor_artist);
    destroy_gestor_album(catalog->gestor_album);
    destroy_gestor_music(catalog->gestor_music);
    destroy_gestor_user(catalog->gestor_user);
    destroy_gestor_history(catalog->gestor_history);
    free(catalog);
}

///////////////////////////////////////////AUXILIARY///////////////////////////////////////////

void load_genre_counts_for_user(Catalog catalog, int user_id) {
    int age = get_user_age_by_id(catalog->gestor_user, user_id);
    GArray *liked_musics_id = get_user_like_musics_id_by_id(catalog->gestor_user, user_id);

    for (guint i = 0; i < liked_musics_id->len; i++) {
        int music_id = g_array_index(liked_musics_id, int, i);
        char *genre_name = get_music_genre_by_id(catalog->gestor_music, music_id);
        int genre_index = genre_to_index(genre_name);

        if (genre_index != -1 && age >= 0 && age < 100) {
            auxiliar_genre_count(catalog->gestor_user, age, genre_index);
        }
        g_free(genre_name);
    }
}



void calculate_artists_discography_for_music(Catalog catalog, int music_id) {
    Gestor_Music gestor_music = catalog->gestor_music;      // Retrieve the music manager
    Gestor_Artist gestor_artist = catalog->gestor_artist;   // Retrieve the artist manager

    // Retrieve artist IDs associated with the music
    GArray *artist_ids = get_music_artist_id_by_id(gestor_music, music_id);

    // Retrieve and convert the music duration
    char *music_duration_str = get_music_duration_by_id(gestor_music, music_id);
    int music_duration = duration_to_seconds(music_duration_str);
    g_free(music_duration_str);



    // Process each associated artist
    for (guint j = 0; j < artist_ids->len; j++) {
        int artist_id = g_array_index(artist_ids, int, j);


        update_artist_discography_duration(gestor_artist, artist_id, music_duration);
    }

    g_array_unref(artist_ids);

}

void calculate_revenue_for_history(Catalog catalog,int music_id) {
    Gestor_Music gestor_music = catalog->gestor_music;
    Gestor_Artist gestor_artist = catalog->gestor_artist;

    // Retrieve artist IDs associated with the music
    GArray *artist_ids = get_music_artist_id_by_id(gestor_music, music_id);


    // Process each associated artist
    for (guint j = 0; j < artist_ids->len; j++) {

        int artist_id = g_array_index(artist_ids, int, j);

        // Retrieve the artist's rate_per_stream
        double rate_per_stream = get_artist_rate_per_stream_by_id(gestor_artist, artist_id);

        // Update the artist's revenue
        update_artist_revenue(gestor_artist, artist_id, rate_per_stream);


    }
    g_array_unref(artist_ids);

}


///////////////////////////////////////////////////////////////////////////////////////////////

// Função para atualizar a duração da música na hashtable weeks do gestor_artist// Function to update the duration of the music in the weeks array of gestor_artist
void update_artist_weeks_duration(Catalog catalog, int music_id, char *date, char *duration) {
    Gestor_Music gestor_music = catalog->gestor_music;
    Gestor_Artist gestor_artist = catalog->gestor_artist;

    // Convert playback duration to seconds
    int playback_seconds = duration_to_seconds(duration);

    // Determine week index
    int week_index = calculate_week_position(date);
    //printf("%s\n",date);
    //printf ("%d\n",week_index);


    // Get artist IDs for the music
    GArray *artist_ids = get_music_artist_id_by_id(gestor_music, music_id);

    // Update weekly playback durations for all associated artists
    for (guint i = 0; i < artist_ids->len; i++) {
        int artist_id = g_array_index(artist_ids, int, i);
        GArray *weeks = get_artist_weeks_by_id(gestor_artist, artist_id);

        // Ensure the weeks array is large enough to include the current week
        if (week_index >= weeks->len) {
            g_array_set_size(weeks, week_index + 1);
        }

        // Add playback seconds to the week's total duration
        g_array_index(weeks, int, week_index) += playback_seconds;
    }

    // Cleanup
    g_array_unref(artist_ids);
}

////////////////////////////////////////////////Auxiliary//////////////////////////////////////////////

/*

void load_MatrizClassifacaoMusica(Catalog catalog, int music_id,int user_id) {
    Gestor_Music gestor_music = catalog->gestor_music;
    Gestor_History gestor_history = catalog->gestor_history;

    // Retrieve the genre of the given music ID
    char *genre_name = get_music_genre_by_id(gestor_music, music_id);
    int genre_index = genre_to_index(genre_name);
    g_free(genre_name);

    loadA_MatrizClassifacaoMusica(gestor_history, genre_index, user_id);

}

void insert_historic_id(Catalog catalog, int historic_id, int user_id, const char *date) {
    // Retrieve the user from the catalog
    Gestor_User gestor=  catalog->gestor_user;

    // Calculate the year difference from 2024
    int year;
    sscanf(date, "%4d", &year);
    int year_diff = 2024 - year;

    // Ensure the year difference is within bounds
    if (year_diff < 0 || year_diff >= 16) {
        fprintf(stderr, "Year %d out of bounds\n", year);
        return;
    }

    // Insert the historic ID into the historicUsers array
    GArray *historic_array = get_user_historicUser_by_id(gestor,user_id ,year_diff);
    g_array_append_val(historic_array, historic_id);

    g_array_unref(historic_array);
}

////////////////////////////////////////////////////////////QUERY6//////////////////////////////////////////////////////////////////


void query_6(Catalog catalog, int user_id, int year, int N, char *output_file) {
    Gestor_History gestor_history = get_history(catalog);
    Gestor_User gestor_user = get_users(catalog);
    Gestor_Music gestor_music = get_musics(catalog);
    Gestor_Album gestor_album = get_albums(catalog);
    Gestor_Artist gestor_artist = get_artists(catalog);

    // Step 1: Validate year and retrieve user history
    int year_diff = 2024 - year;
    if (year_diff < 0 || year_diff >= 16) {
        fprintf(stderr, "Year %d out of bounds.\n", year);
        return;
    }

    GArray *user_history = get_user_historicUser_by_id(gestor_user, user_id, year_diff);
    if (!user_history || user_history->len == 0) {
        // No history for the given year
        FILE *output = fopen(output_file, "w");
        fprintf(output, "\n");
        fclose(output);
        return;
    }

    // Step 2: Initialize variables for statistics
    int total_listening_time = 0; // In seconds
    GHashTable *distinct_songs = g_hash_table_new(g_int_hash, g_int_equal);
    GHashTable *artist_times = g_hash_table_new(g_int_hash, g_int_equal);
    GHashTable *genre_times = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    GHashTable *album_times = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    int day_play_count[365] = {0};
    int hour_play_count[24] = {0};

    for (guint i = 0; i < user_history->len; i++) {
        int history_id = g_array_index(user_history, int, i);

        int music_id = get_history_music_id_by_id(gestor_history, history_id);

        char *duration = get_history_duration_by_id(gestor_history, history_id);

        // Parse and calculate listening time
        int duration_seconds = duration_to_seconds(duration);
        total_listening_time += duration_seconds;

        // Count distinct songs
        if (!g_hash_table_contains(distinct_songs, &music_id)) {
            int *music_key = malloc(sizeof(int));
            *music_key = music_id;
            g_hash_table_add(distinct_songs, music_key);
        }

        // Increment artist listening time
        GArray *artist_ids = get_music_artist_id_by_id(gestor_music, music_id);
        for (guint j = 0; j < artist_ids->len; j++) {
            int artist_id = g_array_index(artist_ids, int, j);
            int *current_time = g_hash_table_lookup(artist_times, &artist_id);
            if (!current_time) {
                int *new_time = malloc(sizeof(int));
                *new_time = duration_seconds;
                g_hash_table_insert(artist_times, g_memdup2(&artist_id, sizeof(int)), new_time);
            } else {
                *current_time += duration_seconds;
            }
        }
        g_array_unref(artist_ids);

        // Increment genre listening time
        char *genre = get_music_genre_by_id(gestor_music, music_id);
        int *genre_time = g_hash_table_lookup(genre_times, genre);
        if (!genre_time) {
            char *genre_key = g_strdup(genre);
            int *new_time = malloc(sizeof(int));
            *new_time = duration_seconds;
            g_hash_table_insert(genre_times, genre_key, new_time);
        } else {
            *genre_time += duration_seconds;
        }
        g_free(genre);

        // Increment album listening time
        char *album_name = get_album_title_by_id(gestor_album, get_music_album_id_by_id(gestor_music, music_id));
        int *album_time = g_hash_table_lookup(album_times, album_name);
        if (!album_time) {
            char *album_key = g_strdup(album_name);
            int *new_time = malloc(sizeof(int));
            *new_time = duration_seconds;
            g_hash_table_insert(album_times, album_key, new_time);
        } else {
            *album_time += duration_seconds;
        }
        g_free(album_name);

        // Count day and hour activity
        char *timestamp = get_history_timestamp_by_id(gestor_history, history_id);
        char *hour = get_history_hour_by_id(gestor_history, history_id);
        char * complete = g_strconcat(timestamp, " ", hour, NULL);

        struct tm tm = {0};
        sscanf(complete, "%4d-%2d-%2d %2d:%2d:%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
        tm.tm_year -= 1900; // Adjust year
        tm.tm_mon -= 1;     // Adjust month
        day_play_count[tm.tm_yday]++;
        hour_play_count[tm.tm_hour]++;

        g_free(timestamp);
        g_free(duration);
    }

    // Step 3: Calculate final statistics
    // Total listening time
    char listening_time[16];
    snprintf(listening_time, sizeof(listening_time), "%02d:%02d:%02d",
             total_listening_time / 3600,
             (total_listening_time % 3600) / 60,
             total_listening_time % 60);

    // Number of distinct songs
    int distinct_song_count = g_hash_table_size(distinct_songs);

    // Find most listened artist, genre, album, and activity times
    int most_listened_artist = find_most_listened(artist_times);
    char *most_listened_genre = find_most_listened_string(genre_times);
    char *favorite_album = find_most_listened_string(album_times);
    int peak_day = find_peak(day_play_count, 365);
    int peak_hour = find_peak(hour_play_count, 24);

    // Step 4: Output the summary
    FILE *output = fopen(output_file, "w");
    fprintf(output, "%s;%d;%d;%d;%s;%s;%02d\n",
            listening_time, distinct_song_count, most_listened_artist, peak_day,
            most_listened_genre, favorite_album, peak_hour);

    // Step 5: If N is provided, list top N artists
    if (N > 0) {
        list_top_n_artists(artist_times, gestor_music,gestor_artist ,output, N);
    }

    fclose(output);

    // Step 6: Cleanup
    g_hash_table_destroy(distinct_songs);
    g_hash_table_destroy(artist_times);
    g_hash_table_destroy(genre_times);
    g_hash_table_destroy(album_times);
}

///////////////////////////////////////////////////////////QUERY6AUX//////////////////////////////////////////////


void list_top_n_artists(GHashTable *artist_times, Gestor_Music gestor_music,Gestor_Artist gestor_artist ,FILE *output, int N) {
    // Step 1: Store artists and their listening times in an array
    int artist_count = g_hash_table_size(artist_times);
    if (artist_count == 0) return;
    ArtistInfo *artists = malloc(artist_count * sizeof(ArtistInfo));
    if (!artists) {
        fprintf(stderr, "Error: Failed to allocate memory for artists.\n");
        return;
    }

    GHashTableIter iter;
    gpointer key, value;
    int index = 0;

    g_hash_table_iter_init(&iter, artist_times);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        artists[index].id = *(int *)key;
        artists[index].listening_time = *(int *)value;
        index++;
    }

    // Step 2: Sort artists by listening time (descending) and ID (ascending)
    sort_artists_by_listening_time(artists, artist_count);

    // Step 3: Write the top N artists to the output
    for (int i = 0; i < N && i < artist_count; i++) {
        int artist_id = artists[i].id;
        int listening_time = artists[i].listening_time;

        char *artist_name = get_artist_name_by_id(gestor_artist, artist_id);
        fprintf(output, "%s;%d;%d\n", artist_name,
                verify_artist_songs(gestor_music, artist_id),
                listening_time);

        g_free(artist_name); // Free dynamically allocated artist name
    }

    free(artists);
}


void sort_artists_by_listening_time(ArtistInfo *artists, int artist_count) {
    qsort(artists, artist_count, sizeof(ArtistInfo), compare_artists);
}

int compare_artists(const void *a, const void *b) {
    ArtistInfo *artistA = (ArtistInfo *)a;
    ArtistInfo *artistB = (ArtistInfo *)b;

    if (artistA->listening_time != artistB->listening_time)
        return artistB->listening_time - artistA->listening_time;
    return artistA->id - artistB->id;
}
*/