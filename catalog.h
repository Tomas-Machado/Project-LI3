
#ifndef CATALOG_H
#define CATALOG_H
#include <glib.h>

#include "Gestor_Album.h"
#include "music.h"
#include "users.h"
#include "Gestor_Artist.h"
#include "Gestor_History.h"
#include "Gestor_Music.h"
#include "Gestor_User.h"
typedef struct Catalog *Catalog;


/**
 * @brief Cria um novo catálogo.
 *
 * Inicializa os gestores para artistas, álbuns, músicas, usuários e históricos.
 *
 * @return Um ponteiro para o objeto Catalog criado.
 */
Catalog create_catalog();

/**
 * @brief Obtém o gestor de artistas
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @return O gestor de artistas associado ao catálogo.
 */
Gestor_Artist get_artists(Catalog catalog);

/**
 * @brief Obtém o gestor de músicas
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @return O gestor de músicas associado ao catálogo.
 */
Gestor_Music get_musics(Catalog catalog);

/**
 * @brief Obtém o gestor de users
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @return O gestor de users associado ao catálogo.
 */
Gestor_User get_users(Catalog catalog);

/**
 * @brief Obtém o gestor de álbuns
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @return O gestor de álbuns associado ao catálogo.
 */
Gestor_Album get_albums(Catalog catalog);

/**
 * @brief Obtém o gestor de histórico
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @return O gestor de históricos associado ao catálogo.
 */
Gestor_History get_history(Catalog catalog);

/**
 * @brief Destroi o catálogo e libera a memória associada.
 *
 * @param catalog Ponteiro para o objeto Catalog a ser destruído.
 */
void destroy_catalog(Catalog catalog);



//////////////////////////////////AUXILIARY///////////////////////////////////////////

/**
 * @brief 
 *
 * 
 * POR ACABAR
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @param user_id ID do user cujas contagens de gêneros serão atualizadas.
 */
void load_genre_counts_for_user(Catalog catalog, int user_id);


/**
 * @brief Atualiza a duração total da discografia de artistas dado uma nova música.
 *
 * Atualiza a duração da discografia de cada artista com base na duração da música associada.
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @param music_id ID da música cujos artistas terão suas discografias atualizadas.
 */
void calculate_artists_discography_for_music(Catalog catalog,int music_id);


/**
 * @brief Calcula a receita gerada para os artistas com base no histórico de reprodução de uma música.
 *
 * Atualiza a receita total dos artistas associados a uma música com base na taxa por stream.
 *
 * @param catalog Ponteiro para o objeto Catalog.
 * @param music_id ID da música cujos artistas terão suas receitas atualizadas.
 */
void calculate_revenue_for_history(Catalog catalog,int music_id);

/**
 * @brief Atualiza a duração de reprodução semanal de uma música na tabela de semanas dos artistas.
 *
 * Esta função adiciona a duração de reprodução de uma música a uma posição específica na tabela
 * de semanas associada a cada artista relacionado à música. A posição é determinada com base na data
 * fornecida, calculada em relação à data de referência.
 *
 * @param catalog Ponteiro para o catálogo contendo os gestores de músicas e artistas.
 * @param music_id Identificador único da música.
 * @param date String representando a data de reprodução no formato "AAAA/MM/DD".
 * @param duration String representando a duração da reprodução no formato "HH:MM:SS".
 *
 * @note A função assume que a data e a duração estão no formato correto. A tabela de semanas (`weeks`)
 * dos artistas será automaticamente redimensionada se necessário para incluir a posição da semana calculada.
 */
void update_artist_weeks_duration(Catalog catalog, int music_id,  char *date, char *time);






/////////////////////////////////Query5/////////////////////////////////////////
//void load_MatrizClassifacaoMusica(Catalog catalog, int music_id,int user_id);
//void insert_historic_id(Catalog catalog, int historic_id, int user_id, const char *date);


///////////////////////////////////////////QUERY6//////////////////////////////////////////////////////////////////

/*
typedef struct {
    int id;
    int listening_time;
} ArtistInfo;

void query_6(Catalog catalog, int user_id, int year, int N, char *output_file);
void list_top_n_artists(GHashTable *artist_times, Gestor_Music gestor_music,Gestor_Artist gestor_artist ,FILE *output, int N);
void sort_artists_by_listening_time( ArtistInfo *artists, int artist_count);
int compare_artists(const void *a, const void *b);
*/
#endif //CATALOG_H
