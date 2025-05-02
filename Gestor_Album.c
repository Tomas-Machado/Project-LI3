
#include <albuns.h>
#include <stdbool.h>

typedef struct Gestor_Album {
    GHashTable *album_table;
} *Gestor_Album;

Gestor_Album create_gestor_album() {
    // Create the album hash table
    Gestor_Album gestor = malloc(sizeof(struct Gestor_Album));
    gestor->album_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, destroy_album);
    return gestor;
}

void insert_album_gestor(Gestor_Album gestor, char **album_fields) {
    Albuns album = create_album(album_fields);
    int *key = malloc(sizeof(int));
    *key = get_album_id(album);

    // Insert into the hash table
    g_hash_table_insert(gestor->album_table, key, album);
}

// Getters
char *get_album_title_by_id(Gestor_Album gestor, int album_id) {
    Albuns album = g_hash_table_lookup(gestor->album_table, &album_id);
    return album ? get_album_title(album) : NULL;
}

int get_album_artist_id_by_id(Gestor_Album gestor, int album_id) {
    Albuns album = g_hash_table_lookup(gestor->album_table, &album_id);
    return album ? get_album_artist_id(album) : 0;
}

int get_album_year_by_id(Gestor_Album gestor, int album_id) {
    Albuns album = g_hash_table_lookup(gestor->album_table, &album_id);
    return album ? get_album_year(album) : 0;
}

char *get_album_producers_by_id(Gestor_Album gestor, int album_id) {
    Albuns album = g_hash_table_lookup(gestor->album_table, &album_id);
    return album ? get_album_producers(album) : NULL;
}

void destroy_gestor_album(Gestor_Album gestor) {
    g_hash_table_destroy(gestor->album_table);
    free(gestor);
}

/////////////////////////////AUXILIARY///////////////////////////////

bool album_exists(int album_id, Gestor_Album gestor) {
    return g_hash_table_contains(gestor->album_table, &album_id);
}
