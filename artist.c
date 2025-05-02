#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/artist.h"
#include "../include/Utils.h"


typedef struct Artists {

    int id;
    char *name;
    //char *description;
    double recipe_per_stream;
    GArray *id_constituent;
    char *country;
    char *type;
    int discography_duration;
    int num_albums;
    double total_recipes;
    int count_top10;
    GArray *weeks_duration; // key = week number, value = Total Duration of the week

} *Artist;

Artist create_artist(char **fields)
{
    Artist artist = malloc(sizeof(struct Artists));

    artist->id = atoi(fields[0] + 1);
    artist->name = g_strdup(fields[1]);
    //artist->description = g_strdup(fields[2]);
    artist->recipe_per_stream = atof(fields[3]);
    artist->id_constituent = parse_artist_ids(fields[4]);
    artist->country = g_strdup(fields[5]);
    artist->type = g_strdup(fields[6]);
    artist->discography_duration = 0;
    artist->num_albums = 0;
    artist->total_recipes = 0;
    artist->count_top10 = 0;
    artist->weeks_duration = g_array_sized_new(FALSE, TRUE, sizeof(int),524);
    g_array_set_size(artist->weeks_duration, 524);
    for (int i = 0; i < 524; i++) {
        g_array_index(artist->weeks_duration, int, i) = 0;
    }

    return artist;

}
int get_artist_id(Artist artist)
{
    return artist->id;
}

char *get_artist_name(Artist artist)
{
    return g_strdup(artist->name);
}

GArray *get_artist_id_constituent(Artist artist)
{
    return artist->id_constituent;
}

int get_artist_num_members(Artist artist)
{
    return artist->id_constituent->len;
}

char *get_artist_country(Artist artist)
{
    return g_strdup(artist->country);
}

char *get_artist_type(Artist artist)
{
    return g_strdup(artist->type);
}

int get_artist_discography_duration(Artist artist)
{
    return artist->discography_duration;
}

int get_artist_albums(Artist artist)
{
    return artist->num_albums;
}

double get_artist_rate_per_stream(Artist artist)
{
    return artist->recipe_per_stream;
}

double get_artist_total_recipes(Artist artist)
{
    return artist->total_recipes;
}
int get_artist_count_top10(Artist artist)
{
    return artist->count_top10;
}

GArray *get_artist_weeks_duration(Artist artist)
{
    return artist->weeks_duration;
}


/////////////////////////////////////////SETTERS///////////////////////////////////////////
void set_artist_discography_duration(Artist artist, int duration)
{
    artist->discography_duration = duration;
}

void set_artist_num_albums(Artist artist, int num_albums)
{
    artist->num_albums = num_albums;
}

void set_artist_total_recipes(Artist artist, double total_recipes)
{
    artist->total_recipes = total_recipes;
}

void set_artist_count_top10(Artist artist, int count_top10)
{
    artist->count_top10 = count_top10;
}


void destroy_artist(gpointer data) {
    Artist artist = (Artist)data;

    // Liberando cada campo alocado dinamicamente
    g_free(artist->name);
    //g_free(artist->description);
    g_array_free(artist->id_constituent, TRUE);
    g_free(artist->country);
    g_free(artist->type);
    g_array_free(artist->weeks_duration, TRUE);

    // Liberando a própria struct
    g_free(artist);
}



