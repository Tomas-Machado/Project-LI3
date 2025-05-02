#ifndef USERS_H_
#define USERS_H_
#include <glib.h>
#include <stdio.h>


typedef struct User *Users;

/**
 * @brief Cria um novo user com os dados fornecidos.
 * 
 * @param fields Vetor de strings contendo os campos do user (ID, email, nome, etc.).
 * @param liked_musics_id Ponteiro para um GArray contendo os IDs das músicas que o user gostou.
 * @return Um ponteiro para a estrutura `Users` criada.
 */
Users create_User(char **fields,GArray *liked_musics_id);

/**
 * @brief Obtém o username de um usuário.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return O username como um inteiro.
 */
int get_user_username(Users user);

/**
 * @brief Obtém o primeiro nome de um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Uma cópia da string contendo o primeiro nome do user.
 */
char *get_user_first_name(Users user);

/**
 * @brief Obtém o sobrenome de um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Uma cópia da string contendo o sobrenome do user.
 */
char *get_user_last_name(Users user);

/**
 * @brief Obtém o email de um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Uma cópia da string contendo o email do user.
 */
char *get_user_email(Users user);

/**
 * @brief Obtém a data de nascimento de um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Uma cópia da string contendo a data de nascimento do user.
 */
char *get_user_birth_date(Users user);

/**
 * @brief Obtém os IDs das músicas curtidas por um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Um ponteiro para um GArray contendo os IDs das músicas curtidas.
 */
GArray *get_user_like_musics_id(Users user);

/**
 * @brief Obtém o país de origem de um user.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return Uma cópia da string contendo o país do user.
 */
char *get_user_country(Users user);

/**
 * @brief Libera a memória alocada para um user.
 * 
 * A função liberta todos os campos dinamicamente alocados dentro da estrutura, 
 * bem como a própria estrutura `Users`.
 * 
 * @param data Ponteiro genérico que deve ser convertido para a estrutura `Users`.
 */
void destroy_user(gpointer data);

/**
 * @brief Calcula a idade de um user com base na data de nascimento.
 * 
 * @param user Ponteiro para a estrutura `Users`.
 * @return A idade do user como um inteiro.
 */
int get_user_age(Users user);


//char *get_user_subscription_type(Users user);

/**
 * @brief Obtém o histórico de um usuário num índice específico.
 *
 * @param user Ponteiro para a estrutura do usuário (`Users`) cujo histórico será acessado.
 * @param index Índice do histórico a ser retornado.
 * 
 * @return Um ponteiro para o `GArray` correspondente ao histórico no índice especificado.
 */
GArray *get_user_historicUser(Users user, int index); 



#endif