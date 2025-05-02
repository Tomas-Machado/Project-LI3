#ifndef GESTOR_MUSIC_H
#define GESTOR_MUSIC_H

#include "music.h"

typedef struct Gestor_Music *Gestor_Music;


/**
 * @brief Cria um novo gestor de músicas.
 *
 * Esta função inicializa uma tabela hash para armazenar as músicas, utilizando o ID da música como chave.
 *
 * @return Um ponteiro para o Gestor_Music recém-criado.
 */
Gestor_Music create_gestor_music();

/**
 * @brief Insere uma nova música no gestor de músicas.
 *
 * Esta função cria uma música a partir dos campos fornecidos e a insere na tabela hash.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param Music_fields Array de strings representando os campos da música.
 */
void insert_music_gestor(Gestor_Music gestor_music, char **Music_fields);

/**
 * @brief Destroi o gestor de músicas e liberta a memória previamente alocada.
 *
 * Esta função destrói a tabela hash e liberta toda a memória alocada dinamicamente associada às músicas.
 *
 * @param gestor_music Ponteiro para o Gestor_Music a ser destruído.
 */
void destroy_gestor_music(Gestor_Music gestor_music);



///////////////////////////////////////GETTERS///////////////////////////////////////////

/**
 * @brief Recupera o gênero de uma música pelo seu ID.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 * @return Uma string alocada dinamicamente contendo o gênero, ou NULL se a música não for encontrada.
 */
char *get_music_genre_by_id(Gestor_Music gestor_music, int music_id);

/**
 * @brief Recupera os IDs dos artistas de uma música pelo seu ID.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 * @return Um ponteiro para um GArray contendo os IDs dos artistas, ou NULL se a música não for encontrada.
 */
GArray *get_music_artist_id_by_id(Gestor_Music gestor_music, int music_id);

/**
 * @brief Recupera a duração de uma música pelo seu ID.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 * @return Uma string alocada dinamicamente contendo a duração, ou NULL se a música não for encontrada.
 */
char *get_music_duration_by_id(Gestor_Music gestor_music, int music_id);


/**
 * @brief Recupera o ID do álbum ao qual a musica pertence pelo seu ID.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 * @return O ID do álbum, ou 0 se a música não for encontrada.
 */
int get_music_album_id_by_id(Gestor_Music gestor_music, int music_id);

/**
 * @brief Recupera o número de reproduções de uma música pelo seu ID.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 * @return O número de reproduções, ou -1 se a música não for encontrada.
 */
int get_music_reproductions_by_id(Gestor_Music gestor_music, int music_id);

/**
 * @brief Incrementa o contador de reproduções de uma música específica.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param music_id O ID da música.
 */
void update_music_reproductions(Gestor_Music gestor_music, int music_id);

/**
 * @brief Valida os IDs de músicas curtidas.
 *
 * Verifica se todos os IDs fornecidos existem no gestor de músicas.
 *
 * @param gestor_music Ponteiro para o Gestor_Music.
 * @param liked_musics_ids Ponteiro para um GArray contendo os IDs das músicas curtidas.
 * @return true se todos os IDs forem válidos, false caso contrário.
 */
bool validate_liked_musics_ids(Gestor_Music gestor_music, GArray *liked_musics_ids);


/**
 * @brief Verifica o número de músicas associadas a um artista específico.
 *
 * Percorre a tabela de músicas no gestor de músicas (`gestor_music`) e conta
 * quantas músicas estão associadas ao artista especificado pelo id de artista
 *
 * @param gestor_music Ponteiro para o gestor de músicas (`Gestor_Music`).
 * @param artist_id Identificador do artista.
 * 
 * @return O número de músicas associadas ao artista. Retorna 0 se o artista não
 *         tiver músicas ou se o gestor de músicas estiver vazio.
 */
int verify_artist_songs(Gestor_Music gestor_music, int artist_id);

#endif //GESTOR_MUSIC_H
