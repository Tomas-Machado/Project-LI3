#ifndef ARTISTS_H_
#define ARTISTS_H_s

#include <glib.h>
#include <stdbool.h>

typedef struct Artists *Artist;

/**
 * @brief Cria um novo objeto do tipo Artist.
 *
 * @param fields Vetor de strings contendo os campos necessários para inicializar o objeto.
 *               Espera-se que os campos estejam organizados na seguinte ordem:
 *               - fields[0]: ID do artista
 *               - fields[1]: Nome do artista
 *               - fields[3]: Receita por stream
 *               - fields[4]: IDs dos constituintes (membros de uma banda)
 *               - fields[5]: País do artista
 *               - fields[6]: Tipo do artista (solo ou banda)
 *
 * @return Um ponteiro para o objeto Artist criado.
 */
Artist create_artist(char **fields);

/**
 * @brief Obtém o ID do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return O ID do artista.
 */
int get_artist_id(Artist artist);

/**
 * @brief Obtém o nome do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return Uma cópia do nome do artista.
 */
char *get_artist_name(Artist artist);

/**
 * @brief Obtém os IDs dos constituintes do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return Um ponteiro para um array contendo os IDs dos constituintes.
 */
GArray *get_artist_id_constituent(Artist artist);

/**
 * @brief Obtém o número de membros do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return O número de membros do artista.
 */
int get_artist_num_members(Artist artist);

/**
 * @brief Obtém o país do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return Uma cópia do país do artista.
 */
char *get_artist_country(Artist artist);

/**
 * @brief Obtém o tipo do artista (solo ou banda).
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return Uma cópia do tipo do artista.
 */
char *get_artist_type(Artist artist);

/**
 * @brief Obtém a duração total da discografia do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return A duração total da discografia do artista.
 */
int get_artist_discography_duration(Artist artist);

/**
 * @brief Obtém o número de álbuns do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return O número de álbuns do artista.
 */
int get_artist_albums(Artist artist);

/**
 * @brief Obtém a receita total do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return A receita total do artista.
 */
double get_artist_total_recipes(Artist artist);

/**
 * @brief Obtém a receita por stream do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @return A receita por stream do artista.
 */
double get_artist_rate_per_stream(Artist artist);

/**
 * @brief Obtém o número de vezes que o artista esteve no Top 10.
 *
 * @param artist Ponteiro para a estrutura do artista (`Artist`).
 * 
 * @return O número de vezes que o artista esteve no Top 10.
 */
int get_artist_count_top10(Artist artist);

/**
 * @brief Obtém o array de tempo ouvido semanal associado ao artista.
 *
 * @param artist Ponteiro para a estrutura do artista (`Artist`).
 * 
 * @return Um ponteiro para o `GArray` contendo o tempo ouvido semanal.
 */
GArray *get_artist_weeks_duration(Artist artist);

/**
 * @brief Define a duração total da discografia do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @param duration Duração total da discografia em anos.
 */
void set_artist_discography_duration(Artist artist, int duration);

/**
 * @brief Define o número de álbuns do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @param num_albums Número de álbuns do artista.
 */
void set_artist_num_albums(Artist artist, int num_albums);

/**
 * @brief Define a receita total do artista.
 *
 * @param artist Ponteiro para o objeto Artist.
 * @param total_recipes Receita total do artista.
 */
void set_artist_total_recipes(Artist artist, double total_recipes);


/**
 * @brief Define o número de vezes que o artista esteve no Top 10.
 *
 * @param artist Ponteiro para a estrutura do artista (`Artist`).
 * @param count_top10 O novo valor para o número de vezes no Top 10.
 */
void set_artist_count_top10(Artist artist, int count_top10);

/**
 * @brief Libera a memória associada a um objeto Artist.
 *
 * @param data Ponteiro para o objeto Artist a ser destruído.
 */  
void destroy_artist(gpointer data);

#endif
