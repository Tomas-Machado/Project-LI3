#ifndef GESTOR_ALBUM_H
#define GESTOR_ALBUM_H

#include <glib.h>
#include "albuns.h"
#include <stdbool.h>

typedef struct Gestor_Album *Gestor_Album;

/**
 * @brief Cria um novo gestor de álbuns
 *
 * Esta função inicializa uma tabela hash para armazenar os álbuns, utilizando o ID do álbum como chave.
 *
 * @return Um ponteiro para o Gestor_Album recém-criado.
 */
Gestor_Album create_gestor_album();


/**
 * @brief Insere um novo álbum no gestor de álbuns.
 *
 * Esta função cria um álbum a partir dos campos fornecidos e o insere na tabela hash.
 *
 * @param gestor Ponteiro para o Gestor_Album.
 * @param album_fields Array de strings representando os campos do álbum.
 */
void insert_album_gestor(Gestor_Album gestor, char **album_fields);

// Getters

/**
 * @brief Vai buscar o título de um álbum pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_Album.
 * @param album_id O ID do álbum.
 * @return Uma string alocada dinamicamente contendo o título do álbum, ou NULL se o álbum não for encontrado.
 */
char *get_album_title_by_id(Gestor_Album gestor, int album_id);

/**
 * @brief Recupera o ID do artista de um álbum pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_Album.
 * @param album_id O ID do álbum.
 * @return O ID do artista, ou 0 se o álbum não for encontrado.
 */
int get_album_artist_id_by_id(Gestor_Album gestor, int album_id);

/**
 * @brief Recupera o ano de lançamento de um álbum pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_Album.
 * @param album_id O ID do álbum.
 * @return O ano de lançamento, ou 0 se o álbum não for encontrado.
 */
//int get_album_year_by_id(Gestor_Album gestor, int album_id);


/**
 * @brief Recupera os produtores de um álbum pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_Album.
 * @param album_id O ID do álbum.
 * @return Uma string alocada dinamicamente contendo os produtores, ou NULL se o álbum não for encontrado.
 */
//char *get_album_producers_by_id(Gestor_Album gestor, int album_id);


/**
 * @brief Destroi o gestor de álbuns e liberta a memória previamente alocada.
 *
 * Esta função destrói a tabela hash e liberta toda a memória alocada dinamicamente associada aos álbuns.
 *
 * @param gestor Ponteiro para o Gestor_Album a ser destruído.
 */
void destroy_gestor_album(Gestor_Album gestor);

/**
 * @brief Verifica se um álbum existe no gestor de álbuns.
 *
 * @param album_id O ID do álbum a ser verificado.
 * @param gestor Ponteiro para o Gestor_Album.
 * @return true se o álbum existir, false caso contrário.
 */
bool album_exists(int album_id, Gestor_Album gestor);

#endif // GESTOR_ALBUM_H