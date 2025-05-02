#include "music.h"
#include "Gestor_Music.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <glib.h>

typedef struct Gestor_Music {
    GHashTable *musics_table;
} *Gestor_Music;

Gestor_Music create_gestor_music() {
    Gestor_Music gestor_music = malloc(sizeof(struct Gestor_Music));
    // Create the music hash table
    gestor_music->musics_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, destroy_music);
    return gestor_music;
}

void insert_music_gestor(Gestor_Music gestor_music, char **Music_fields) {
    int *key = malloc(sizeof(int));
    Musics music = create_Music(Music_fields);
    *key = get_music_id(music);

    // Insert into the hash table
    g_hash_table_insert(gestor_music->musics_table, key, music);
}

void destroy_gestor_music(Gestor_Music gestor_music) {
    // Free the hash table and its contents
    g_hash_table_destroy(gestor_music->musics_table);
    free(gestor_music);
}

/////////////////////////Getters///////////////////////////

char *get_music_genre_by_id(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    return music ? get_music_genre(music) : NULL;
}

GArray *get_music_artist_id_by_id(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    return music ? get_music_artist_id(music) : NULL;
}

char *get_music_duration_by_id(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    return music ? get_music_duration(music) : NULL;
}

int get_music_album_id_by_id(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    return music ? get_music_album_id(music) : 0;
}

int get_music_reproductions_by_id(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    return music ? get_music_reproductions(music) : -1;
}


void update_music_reproductions(Gestor_Music gestor_music, int music_id) {
    Musics music = g_hash_table_lookup(gestor_music->musics_table, &music_id);
    if (music) {
        set_music_reproductions(music,get_music_reproductions(music) + 1);
        //printf(" new value is:%d\n",get_music_reproductions(music));
    }
}



//////////////////////////////////LOAD FUNCTIONS////////////////////////////////////////

bool validate_liked_musics_ids(Gestor_Music gestor_music, GArray *liked_musics_ids) {
    for (guint i = 0; i < liked_musics_ids->len; i++) {
        int music_id = g_array_index(liked_musics_ids, int, i);
        if (!g_hash_table_contains(gestor_music->musics_table, &music_id)) {
            return false;
        }
    }
    return true;
}