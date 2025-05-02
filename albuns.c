#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "Utils.h"

#include "albuns.h"

typedef struct Albuns
{
    int id;
    char *title;
    int artists_id;
    int year;
    char *producers;
} *Albuns;

Albuns create_album(char **fields)
{
    Albuns album = malloc(sizeof(struct Albuns));

    album->id = atoi(fields[0] + 2);
    album->title = g_strdup(fields[1]);
    album->artists_id = atoi(fields[2] + 1);
    album->year = atoi(fields[3]);
    album->producers = g_strdup(fields[4]);

    return album;
}

int get_album_id(Albuns album)
{
    return album->id;
}

char *get_album_title(Albuns album)
{
    return g_strdup(album->title);
}

int get_album_artist_id(Albuns album)
{
    return album->artists_id;
}

int get_album_year(Albuns album)
{
    return album->year;
}

char *get_album_producers(Albuns album)
{
    return g_strdup(album->producers);
}

void destroy_album(gpointer data)
{
    Albuns album = (Albuns)data;

    // Liberando cada campo alocado dinamicamente
    g_free(album->title);
    g_free(album->producers);
    free(album);
}