#ifndef HISTORY_H
#define HISTORY_H

#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct History *History;

/**
 * @brief Cria um novo objeto do tipo History.
 *
 * @param fields Vetor de strings contendo os campos necessários para inicializar o objeto.
 *               Espera-se que os campos estejam organizados na seguinte ordem:
 *               - fields[0]: ID do histórico
 *               - fields[1]: ID do user
 *               - fields[2]: ID da música
 *               - fields[3]: Timestamp
 *               - fields[4]: Duração
 *               - fields[5]: Plataforma
 *
 * @return Um ponteiro para o objeto History criado.
 */
History Create_History(char **fields);

/**
 * @brief Obtém o ID do histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return O ID do histórico.
 */
int get_history_id(History history);

/**
 * @brief Obtém o ID do user associado ao histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return O ID do usuário.
 */
int get_history_user_id(History history);


/**
 * @brief Obtém o ID da música associada ao histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return O ID da música.
 */
int get_history_music_id(History history);

/**
 * @brief Obtém o timestamp do histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return Uma cópia do timestamp associado ao histórico.
 */
char *get_history_timestamp(History history);


/**
 * @brief Obtém a duração do histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return Uma cópia da duração associada ao histórico.
 */
char *get_history_duration(History history);

/**
 * @brief Obtém a plataforma associada ao histórico.
 *
 * @param history Ponteiro para o objeto History.
 * @return Uma cópia da plataforma associada ao histórico.
 */
char *get_history_platform(History history);

/**
 * @brief Obtém a hora associada a um histórico.
 *
 * @param history Ponteiro para a estrutura do histórico cuja hora será obtida.
 * 
 * @return Uma cópia da string contendo a hora do histórico. 
 */
char *get_history_hour(History history);


/**
 * @brief Libera a memória associada a um objeto History.
 *
 * @param data Ponteiro para o objeto History a ser destruído.
 */
void destroy_history(gpointer data);

#endif //HISTORY_H
