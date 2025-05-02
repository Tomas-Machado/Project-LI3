#include <string.h>
#include "../include/parser.h"
#include "../include/validation.h"
#include "../include/Gestor_Artist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>
#include <time.h>

#include "Gestor_Album.h"
#include "../include/catalog.h"
#include "Utils.h"
#include "Gestor_Music.h"
#include "Gestor_User.h"
#include "Queries.h"

// Global Parser
void parse_csv_line(char *line, char **fields) {
    int field_count = 0;
    int in_quotes = 0;
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\"') {
            in_quotes = !in_quotes;
        } else if (line[i] == ';' && !in_quotes) {
            fields[field_count][j] = '\0';
            field_count++;
            j = 0;
        } else {
            fields[field_count][j++] = line[i];
        }
    }
    fields[field_count][j] = '\0';
}

void process_file(const char *input_file, const char *error_output_file, Catalog catalog) {
    int *counter = malloc(sizeof(int));
    *counter = 0;
    int type; // 0 - artist, 1 - music, 2 - user

    FILE *input = fopen(input_file, "r");
    FILE *error_output = fopen(error_output_file, "w");

    if (!input || !error_output) {
        fprintf(stderr, "Error opening files.\n");
        return;
    }
    char *line = NULL;
    size_t line_size = 0;
    ssize_t read;
    // Read and discard the first line
    read = getline(&line, &line_size, input);
    if (read != -1) {
        fprintf(error_output, "%s", line);
    }

    // Start the clock
    clock_t start_time = clock();

    // Allocate memory for the fields
    char **fields = malloc(9 * sizeof(char *));
    for (int i = 0; i < 9; i++) {
        fields[i] = malloc(1500 * sizeof(char));
    }

    // Read the second line forward
    while ((read = getline(&line, &line_size, input)) != -1) {
        // Parse the line
        parse_csv_line(line, fields);

        // Check what type of line it is
        type = indetify_type(line);

        // For Artist -> Independent
        if (type == 0) if (!Parse_Artist(fields, catalog, counter)) fprintf(error_output, "%s", line);
        // For Music -> Dependent of Artist
        if (type == 1) if (!Parse_Music(fields, catalog, counter)) fprintf(error_output, "%s", line);
        // For User -> Dependent of Music and Artist
        if (type == 2) if (!Parse_User(fields, catalog, counter)) fprintf(error_output, "%s", line);
        // For Album -> Dependent of Artist, must be before Music
        if (type == 3) if (!Parse_Album(fields, catalog, counter)) fprintf(error_output, "%s", line);
        // For History -> Dependent of User and Music
        if (type == 4) if (!Parse_History(fields, catalog, counter)) fprintf(error_output, "%s", line);
    }



    printf("%d\n", *counter);
    // Free memory
    for (int i = 0; i < 9; i++) free(fields[i]);
    free(fields);
    free(line);
    free(counter);

    // Stop the clock
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to process %s: %f seconds\n", input_file, time_taken);

    // Close the files
    fclose(input);
    fclose(error_output);
}

void parse_query(const char *input_file_path, Catalog catalog) {
    FILE *input_file = fopen(input_file_path, "r");
    if (!input_file) {
        fprintf(stderr, "Error opening file: %s\n", input_file_path);
        return;
    }
    // Start the query counter
    int query = 1;

    char line[1024];
    // Read each line of the input file
    while (fgets(line, sizeof(line), input_file)) {
        char query_str[256];
        char arg1[256], arg2[256];
        int int_arg1, int_arg2;
        char separator = ';';

        // Parse the line to determine the query number and arguments
        if (sscanf(line, "%s %s %[^\n]", query_str, arg1, arg2) >= 1) {
            int query_number = query_str[0] - '0';

            if (query_str[1] == 'S') separator = '=';

            //if (query_number == 1) printf("%d %c %s\n", query_number, separator, arg1);
            //if (query_number == 2) printf("%d %c %s %s\n", query_number, separator, arg1, arg2);
            //if (query_number == 3) printf("%d %c %s %s\n", query_number, separator, arg1, arg2);
            //if (query_number == 4) printf("%d %c \n", query_number, separator);
            switch (query_number) {
                case 1: {
                    char output_file_path[256];
                    sprintf(output_file_path, "resultados/command%d_output.txt", query);

                    print_query1(arg1,get_artists(catalog) ,get_users(catalog), output_file_path, separator, 0);
                    break;
                }
                case 2: {
                    int_arg1 = atoi(arg1);
                    char output_file_path[256];
                    sprintf(output_file_path, "resultados/command%d_output.txt", query);
                    if (sscanf(line, "%s %s %[^\n]", query_str, arg1, arg2) == 3) {
                        trim_quotes(arg2);
                        print_query2(int_arg1, arg2, get_artists(catalog), output_file_path, separator, 0);
                    } else {
                        print_query2(int_arg1, NULL, get_artists(catalog), output_file_path, separator, 0);
                    }

                    break;
                }
                case 3: {
                    if (sscanf(line, "%s %d %d", query_str, &int_arg1, &int_arg2) == 3) {
                        char output_file_path[256];
                        sprintf(output_file_path, "resultados/command%d_output.txt", query);
                        print_query3(int_arg1, int_arg2, get_users(catalog), output_file_path, separator, 0);
                    } else {
                        fprintf(stderr, "Invalid query 3 arguments\n");
                    }
                    break;
                }
                case 4: {
                    char output_file_path[256];
                    sprintf(output_file_path, "resultados/command%d_output.txt", query);

                    if (sscanf(line, "%s %s %s", query_str, arg1, arg2) == 3) {
                        print_query4(get_artists(catalog), arg1, arg2, output_file_path, separator, 0);
                    } else {
                        print_query4(get_artists(catalog), NULL, NULL, output_file_path, separator, 0);
                    }
                    break;
                }
                case 5: {
                    int_arg2 = atoi(arg2);
                    char output_file_path[256];
                    sprintf(output_file_path, "resultados/command%d_output.txt", query);

                    if (sscanf(line, "%s %s %s", query_str, arg1, arg2) == 3) {

                        //query_5(get_history(catalog), atoi(arg1 + 1), int_arg2, output_file_path);
                    }



                }
                default:
                    fprintf(stderr, "Unknown query number: %d\n", query_number);
                    break;
            }
        }
        query++;
    }
    fclose(input_file);
}

/////////////////////////////////////////AUXILIARY FUNCTIONS///////////////////////////

// Function to identify the type of line
int indetify_type(const char *line) {
    if (line[1] == 'A' && line[2] == 'L') return 3; // Album
    if (line[1] == 'A') return 0; // Artist
    if (line[1] == 'S') return 1; // Music
    if (line[1] == 'U') return 2; // User
    if (line[1] == 'H') return 4; // History
    return -1;
}

// Function to parse the Artist fields and insert them into the Artist table
bool Parse_Artist(char **fields, Catalog catalog, int *counter) {
    bool valid = true;
    if ((fields[4][1] != ']' && ((fields[6][0] == 'i') || fields[6][0] == 'I'))) {
        valid = false;
    }

    if (valid) {
        insert_artist_gestor(get_artists(catalog), fields);
        (*counter)++;
        return true;
    }
    return false;
}

bool Parse_Album(char **fields, Catalog catalog, int *counter) {
        insert_album_gestor(get_albums(catalog), fields);

    // Parse the artist IDs from the field
    GArray *artist_ids = parse_artist_ids(fields[2]);

    // Update the number of albums for each artist
    for (guint i = 0; i < artist_ids->len; i++) {
        int artist_id = g_array_index(artist_ids, int, i);
        update_artist_albums(get_artists(catalog), artist_id);
    }

    g_array_free(artist_ids, TRUE); // Free the GArray



        (*counter)++;
        return true;
}



// Function to parse the Music fields and insert them into the Music table
bool Parse_Music(char **fields, Catalog catalog, int *counter) {
    // Extract the album ID by skipping the first two characters
    int album_id = atoi(fields[3] + 2);

    if (artist_exists(fields[2], get_artists(catalog))
        && validate_duration(fields[4])
        && album_exists(album_id, get_albums(catalog))
        ) {


        insert_music_gestor(get_musics(catalog), fields);

        ///////////////////////AUXILIARY///////////////////////////
        int music_id = atoi(fields[0] + 1);
        calculate_artists_discography_for_music(catalog, music_id);

        (*counter)++;
        return true;
    }
    return false;
}

// Function to parse the User fields and insert them into the User table
bool Parse_User(char **fields, Catalog catalog, int *counter) {
    bool valid = true;
    valid = validate_email(fields[1]);
    // Short-circuit evaluation (Not worth it?)

    if (valid) valid = validate_date(fields[4]);
    if (valid) valid = validate_subscription(fields[6]);
    GArray *musics_id = parse_liked_musics_id(fields[7]);

    if (valid && validate_liked_musics_ids(get_musics(catalog), musics_id)) {
        insert_user_gestor(get_users(catalog), fields, musics_id); // Insert user into the user table

        ///////////////////////////////////////////AUXILIARY///////////////////////////////////////////

        int user_id = atoi(fields[0] + 1); // Get the user ID
        load_genre_counts_for_user(catalog, user_id); // Update genre count for the user
        g_array_free(musics_id, TRUE); // Free the GArray
        (*counter)++;

        return true;
    }
    g_array_free(musics_id, TRUE);

    return false;
}

bool Parse_History(char **fields, Catalog catalog, int *counter) {
    if (fields[5][0] == 'M' || fields[5][0] == 'D' || fields[5][0] == 'm' || fields[5][0] == 'd') {
        insert_history_gestor(get_history(catalog), fields);

        update_music_reproductions(get_musics(catalog),atoi(fields[2] + 1 ));

        calculate_revenue_for_history(catalog,atoi(fields[2] + 1));

        char *date = strndup(fields[3], 10);
        //update_artist_weeks_duration(catalog, atoi(fields[2] + 1), date, fields[4]);
        free(date);

        //load_MatrizClassifacaoMusica(catalog, atoi(fields[2] + 1), atoi(fields[1] + 1));


        (*counter)++;
        return true;
    }
    return false;
}






////////////////////////////////////////A MERDA BATE FORTE /////////////////////////////////////////







