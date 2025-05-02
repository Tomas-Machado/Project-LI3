#ifndef GESTOR_HISTORY_H
#define GESTOR_HISTORY_H

#include <glib.h>
#include "history.h"

typedef struct Gestor_History *Gestor_History;


/**
 * @brief Cria um novo gestor de históricos.
 *
 * Esta função inicializa uma tabela hash para armazenar os históricos, utilizando o ID do histórico como chave.
 *
 * @return Um ponteiro para o Gestor_History criado.
 */
Gestor_History create_gestor_history();


/**
 * @brief Insere um novo histórico no gestor de históricos.
 *
 * Esta função cria um histórico a partir dos campos fornecidos e o insere na tabela hash.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_fields Array de strings representando os campos do histórico.
 */
void insert_history_gestor(Gestor_History gestor, char **history_fields);

// Getters

/**
 * @brief Recupera um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return Um ponteiro para o histórico, ou NULL se não encontrado.
 */
History get_history_by_id(Gestor_History gestor, int history_id);

/**
 * @brief Recupera o ID do usuário associado a um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return O ID do usuário, ou 0 se o histórico não for encontrado.
 */
int get_history_user_id_by_id(Gestor_History gestor, int history_id);

/**
 * @brief Recupera o ID da música associada a um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return O ID da música, ou 0 se o histórico não for encontrado.
 */
int get_history_music_id_by_id(Gestor_History gestor, int history_id);

/**
 * @brief Recupera o timestamp de um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return Uma string alocada dinamicamente contendo o timestamp, ou NULL se não encontrado.
 */
char *get_history_timestamp_by_id(Gestor_History gestor, int history_id);

/**
 * @brief Recupera a duração de um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return Uma string alocada dinamicamente contendo a duração, ou NULL se não encontrado.
 */
char *get_history_duration_by_id(Gestor_History gestor, int history_id);

/**
 * @brief Obtém a hora de um histórico com base no seu id.
 *
 * @param gestor Ponteiro para o gestor de históricos (`Gestor_History`).
 * @param history_id Identificador único do histórico.
 * 
 * @return Ponteiro para uma string contendo a hora do histórico, ou `NULL` se o histórico
 *         não for encontrado.
 */
char *get_history_hour_by_id(Gestor_History gestor, int history_id);


/**
 * @brief Recupera a plataforma de reprodução de um histórico pelo seu ID.
 *
 * @param gestor Ponteiro para o Gestor_History.
 * @param history_id O ID do histórico.
 * @return Uma string alocada dinamicamente contendo a plataforma, ou NULL se não encontrado.
 */
//char *get_history_platform_by_id(Gestor_History gestor, int history_id);



/**
 * @brief Destroi o gestor de históricos e liberta a memória previamente alocada.
 *
 * Esta função destrói a tabela hash e liberta toda a memória alocada dinamicamente associada aos históricos.
 *
 * @param gestor Ponteiro para o Gestor_History a ser destruído.
 */
void destroy_gestor_history(Gestor_History gestor);

#endif // GESTOR_HISTORY_H