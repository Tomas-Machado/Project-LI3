#ifndef ALBUNS_H
#define ALBUNS_H

#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct Albuns *Albuns;

/**
 * @brief Cria um novo objeto do tipo Albuns.
 *
 * @param fields Vetor de strings contendo os campos necessários para inicializar o objeto.
 *               Espera-se que os campos estejam organizados na seguinte ordem:
 *               - fields[0]: ID do álbum
 *               - fields[1]: Título do álbum
 *               - fields[2]: ID do artista
 *               - fields[3]: Ano de lançamento
 *               - fields[4]: Produtores do álbum
 *
 * @return Um ponteiro para o objeto Albuns criado.
 */
Albuns create_album(char **fields);

/**
 * @brief Obtém o ID do álbum.
 *
 * @param album Ponteiro para o objeto Albuns.
 * @return O ID do álbum.
 */
int get_album_id(Albuns album);

/**
 * @brief Obtém o título do álbum.
 *
 * @param album Ponteiro para o objeto Albuns.
 * @return Uma cópia do título do álbum.
 */
char *get_album_title(Albuns album);

/**
 * @brief Obtém o ID do artista associado ao álbum.
 *
 * @param album Ponteiro para o objeto Albuns.
 * @return O ID do artista.
 */
int get_album_artist_id(Albuns album);

/**
 * @brief Obtém o ano de lançamento do álbum.
 *
 * @param album Ponteiro para o objeto Albuns.
 * @return O ano de lançamento do álbum.
 */
int get_album_year(Albuns album);

/**
 * @brief Obtém os produtores do álbum.
 *
 * @param album Ponteiro para o objeto Albuns.
 * @return Uma cópia da string com os produtores do álbum.
 */
char *get_album_producers(Albuns album);


/**
 * @brief Libera a memória associada a um objeto Albuns.
 *
 * @param data Ponteiro para o objeto Albuns a ser destruído.
 */
void destroy_album(gpointer data);

#endif //ALBUNS_H
