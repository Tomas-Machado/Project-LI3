#ifndef MUSIC_H_
#define MUSIC_H_
#include "artist.h"
#include <glib.h>
#include <stdbool.h>

typedef struct Music *Musics;

/**
 * @brief Cria uma nova música com base nos campos fornecidos.
 * 
 * Os campos devem estar organizados num array:
 * - `fields[0]`: ID da música
 * - `fields[2]`: IDs dos artistas associados (num formato compatível com `parse_liked_musics_id`)
 * - `fields[3]`: ID do álbum associado
 * - `fields[4]`: Duração da música
 * - `fields[5]`: Gênero musical
 * - `fields[6]`: ID do álbum
 * 
 * @param fields Array de strings contendo os campos da música.
 * @return Ponteiro para a nova música criada.
 * 
 */
Musics create_Music(char **fields);


/**
 * @brief Obtém o ID de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return ID da música.
 */
int get_music_id(Musics music);

/**
 * @brief Obtém o gênero de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return String contendo o gênero da música
 */
char *get_music_genre(Musics music);

/**
 * @brief Obtém os IDs dos artistas associados a uma música.
 * 
 * @param music Ponteiro para a música.
 * @return Ponteiro para um GArray contendo os IDs dos artistas.
 *
 */
GArray *get_music_artist_id(Musics music);

/**
 * @brief Obtém a duração de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return String contendo a duração da música
 */
char *get_music_duration(Musics music);

/**
 * @brief Obtém o ID do álbum associado a uma música.
 * 
 * @param music Ponteiro para a música.
 * @return ID do álbum associado.
 */
int get_music_album_id(Musics music);

/**
 * @brief Obtém o número de reproduções de uma música.
 * 
 * @param music Ponteiro para a música.
 * @return Número de reproduções da música.
 */
int get_music_reproductions(Musics music);

/**
 * @brief Define o número de reproduções de uma música.
 * 
 * @param music Ponteiro para a música.
 * @param reproductions Novo número de reproduções.
 */
void set_music_reproductions(Musics music, int reproductions);

/**
 * @brief Libera a memória alocada para uma música.
 * 
 * Esta função libera todos os campos dinâmicos da estrutura, bem como a própria estrutura.
 * 
 * @param data Ponteiro para a música a ser destruída.
 * 
 */
void destroy_music(gpointer data);

#endif