#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/music.h"

#include "users.h"
#include "Utils.h"

typedef struct Music {

    int id;
    //char  *title;
    GArray  *artistId;
    int albunId;
    char  *duration;
    char  *genre;
    int album_id;
    //char  *year;
    //char  *lyrics;
    int reproductions;

} *Musics;


Musics create_Music(char **fields) {
    Musics music = malloc(sizeof(struct Music));

    music->id = atoi(fields[0] +1);
    //music->title = g_strdup(fields[1]);
    music->artistId = parse_liked_musics_id(fields[2]);
    music->albunId = atoi(fields[3] + 2);
    music->duration = g_strdup(fields[4]);
    music->genre = g_strdup(fields[5]);
    music->album_id= atoi(fields[6]+1);
    //music->year = g_strdup(fields[6]);
    //music->lyrics = g_strdup(fields[7]);
    music->reproductions = 0;


    return music;
}

int get_music_id(Musics music) {
    return music->id;
}

char *get_music_genre(Musics music) {
    return g_strdup(music->genre);
}

GArray *get_music_artist_id(Musics music) {
    return g_array_ref(music->artistId);
}

char *get_music_duration(Musics music) {
    return g_strdup(music->duration);
}

int get_music_album_id(Musics music) {
    return music->album_id;
}

int get_music_reproductions(Musics music) {
    return music->reproductions;
}

void set_music_reproductions(Musics music, int reproductions) {
    music->reproductions = reproductions;
}


void destroy_music(gpointer data) {
    Musics music = (Musics)data;

    // Liberando cada campo alocado dinamicamente
    //g_free(music->title);
    g_array_free(music->artistId, TRUE);
    g_free(music->duration);
    g_free(music->genre);
    //g_free(music->year);
   // g_free(music->lyrics);

    // Liberando a própria struct
    g_free(music);
}