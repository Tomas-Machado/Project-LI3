#include <glib.h>
#include <stdio.h>

#include "history.h"
#include "Utils.h"


typedef struct Gestor_History {
    GHashTable *history_table;
    int MatrizClassificacaoMusicas[1000000][10];
} *Gestor_History;

Gestor_History create_gestor_history() {
    Gestor_History gestor = malloc(sizeof(struct Gestor_History));
    gestor->history_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, destroy_history);
    return gestor;
}

void insert_history_gestor(Gestor_History gestor, char **history_fields) {
    History history = Create_History(history_fields);
    int *key = malloc(sizeof(int));
    *key = get_history_id(history);
    g_hash_table_insert(gestor->history_table, key, history);

}

// Getters
History get_history_by_id(Gestor_History gestor, int history_id) {
    return g_hash_table_lookup(gestor->history_table, &history_id);
}

int get_history_user_id_by_id(Gestor_History gestor, int history_id) {
    History history = get_history_by_id(gestor, history_id);
    return history ? get_history_user_id(history) : 0;
}

int get_history_music_id_by_id(Gestor_History gestor, int history_id) {
    History history = get_history_by_id(gestor, history_id);
    return history ? get_history_music_id(history) : 0;
}

char *get_history_timestamp_by_id(Gestor_History gestor, int history_id) {
    History history = get_history_by_id(gestor, history_id);
    return history ? get_history_timestamp(history) : NULL;
}

char *get_history_duration_by_id(Gestor_History gestor, int history_id) {
    History history = get_history_by_id(gestor, history_id);
    return history ? get_history_duration(history) : NULL;
}

char *get_history_platform_by_id(Gestor_History gestor, int history_id) {
    History history = get_history_by_id(gestor, history_id);
    return history ? get_history_platform(history) : NULL;
}

void destroy_gestor_history(Gestor_History gestor) {
    g_hash_table_destroy(gestor->history_table);
    free(gestor);
}
///////////////////////////////////////////////AUXILIARY///////////////////////////////////////////



void loadA_MatrizClassifacaoMusica(Gestor_History gestor, int genre_index,int user_id) {
    // Check if the user has non-zero values in the matrix
    bool has_non_zero = false;
    for (int i = 0; i < 10; i++) {
        if (gestor->MatrizClassificacaoMusicas[user_id][i] != 0) {
            has_non_zero = true;
            break;
        }
    }

    // If the user has zero values, initialize the row
    if (!has_non_zero) {
        for (int i = 0; i < 10; i++) {
            gestor->MatrizClassificacaoMusicas[user_id][i] = 0;
        }
    }

    // Increment the genre counter for the user
    gestor->MatrizClassificacaoMusicas[user_id][genre_index]++;
}

const char *nomesGeneros[10] = {
    "Rock",
    "Jazz",
    "Pop",
    "Classical",
    "Hip Hop",
    "Country",
    "Electronic",
    "Blues",
    "Metal",
    "Reggae"
};
void query_5(Gestor_History gestor,int user_id,int nr_recomendar,char *output_file){
    char **idsUtilizadores = malloc(1000000 * sizeof(char *));

    for (int i = 0; i < 1000000; i++) {
        idsUtilizadores[i] = malloc (25 * sizeof(char));
    }

    // Populate the idsUtilizadores array
    for (int i = 0; i < 1000000; i++) {
        idsUtilizadores[i] = format_id(i); // Assuming a function to get user ID by index
    }

    char **recomendaçoes = malloc (nr_recomendar * sizeof(char *));
    for (int i = 0; i < nr_recomendar; i++) {
        recomendaçoes[i] = malloc (25 * sizeof(char));
    }

    //recomendaçoes = recomendaUtilizadores(user_id, gestor->MatrizClassificacaoMusicas,
     //   idsUtilizadores, nomesGeneros, 1000000, 10, nr_recomendar);

    FILE *output = fopen(output_file, "w");

    while (nr_recomendar > 0) {
        fprintf(output, "%s\n", idsUtilizadores[nr_recomendar - 1]);
        nr_recomendar--;
    }

}