
#ifndef UTILS_H
#define UTILS_H
#include <glib.h>
#include <stdbool.h>


/**
 * @brief Remove o último caractere de uma string.
 * 
 * Esta função reduz o comprimento de uma string em 1,
 * substituindo o último caractere por '\0', desde que a string
 * não esteja vazia.
 * 
 * @param str Ponteiro para a string cuja última posição será removida.
 *            A string deve terminadar em '\0'.
 * 
 * @note Se a string estiver vazia, a função não altera nada.
 */
void remove_last_char(char *str);

/**
 * @brief Remove espaços, aspas e quebras de linha no início e no fim de uma string.
 * 
 * Esta função ajusta a string fornecida removendo os caracteres indesejados
 * do início e do fim, como espaços, aspas simples, aspas duplas e quebras de linha.
 * 
 * @param str Ponteiro para a string a ser ajustada. Deve ser uma string terminada em '\0'.
 * 
 * @return Um ponteiro para a string ajustada, já sem os caracteres indesejados nas extremidades.
 */
char *trim(char *str);

/**
 * @brief Remove aspas no início e no fim de uma string.
 * 
 * Esta função ajusta a string fornecida removendo aspas duplas (`"`) 
 * tanto do início como do fim, caso estejam presentes.
 * 
 * @param str Ponteiro para a string a ser ajustada. Deve ser uma string terminada em '\0'.
 * 
 * @return Um ponteiro para a string ajustada, já sem as aspas no início e no fim.
 */
char *trim_quotes(char *str);

/**
 * @brief Remove todas as aspas de cada string em um array de strings.
 * 
 * Esta função percorre um array de strings, removendo todas as aspas duplas (`"`)
 * de cada string contida nele. O array deve terminar com um ponteiro NULL.
 * 
 * @param fields Array de ponteiros para strings. Cada string é modificada diretamente.
 */
void remove_quotes_from_fields(char **fields);

/**
 * @brief Calcula a idade com base na data de nascimento.
 * 
 * Esta função calcula a idade atual de uma pessoa com base na data de nascimento fornecida.
 * A data de nascimento deve estar no formato "YYYY/MM/DD".
 * 
 * @param birthdate String contendo a data de nascimento no formato "YYYY/MM/DD".
 * 
 * @return A idade calculada em anos.
 * 
 * @note A função utiliza a data atual fixa de 9 de setembro de 2024 para o cálculo.
 *       Certifique-se de ajustar essa data caso precise de cálculos dinâmicos.
 */
int calculate_age(const char *birthdate);

/**
 * @brief Converte uma duração para segundos.
 * 
 * Esta função analisa uma string de duração no formato "HH:MM:SS" e converte-a 
 * no total de segundos correspondentes.
 * 
 * @param duration String representando a duração no formato "HH:MM:SS".
 * 
 * @return O total de segundos representado pela duração. Retorna -1 se o formato for inválido.
 */
int duration_to_seconds(const char *duration);

/**
 * @brief Converte segundos totais numa string no formato "HH:MM:SS".
 * 
 * Esta função recebe um total de segundos e formata uma string representando 
 * a duração no formato "HH:MM:SS".
 * 
 * @param total_seconds O total de segundos a ser convertido.
 * 
 * @return Um ponteiro para a string formatada. Retorna NULL se ocorrer erro de alocação de memória.
 */
char* seconds_to_duration(int total_seconds);

/**
 * @brief Remove caracteres no caso de uma nova linha
 * 
 * Esta função, no caso de haver uma nova linha (\n ou \r) substitui por um 
 * terminador nulo (`\0`) na string fornecida.
 * 
 * @param str Ponteiro para a string a ser ajustada.
 */
void trim_newline(char *str);

/**
 * @brief Formata um número inteiro numa string no formato "Axxxxxxx".
 * 
 * Esta função formata um número inteiro em uma string de 8 caracteres, 
 * adicionando um prefixo "A" seguido de zeros à esquerda para completar o formato.
 * 
 * @param number O número inteiro a ser formatado.
 * 
 * @return Um ponteiro para a string formatada. Retorna NULL se ocorrer erro de alocação de memória.
 *         O chamador é responsável por liberar a memória alocada.
 */
char* format_id(int number);

/**
 * @brief Mapeia um nome de gênero para o índice correspondente.
 * 
 * Esta função converte o nome de um gênero musical para o índice correspondente 
 * em uma enumeração pré-definida.
 * 
 * @param genre_name Nome do gênero musical (e.g., "Rock", "Jazz").
 * 
 * @return O índice correspondente ao gênero. Retorna -1 se o gênero não for encontrado.
 */
int genre_to_index(const char *genre_name);

/**
 * @brief Analisa uma string contendo IDs de músicas e retorna um array de inteiros.
 * 
 * Esta função converte uma string de IDs de músicas formatada como "[ID1,ID2,...]" 
 * num array dinâmico de inteiros.
 * 
 * @param liked_musics_id String contendo os IDs das músicas.
 * 
 * @return Um ponteiro para um `GArray` contendo os IDs.
 */
GArray* parse_liked_musics_id(const char *liked_musics_id);

/**
 * @brief Analisa uma string contendo IDs de artistas e retorna um array de inteiros.
 * 
 * Esta função converte uma string de IDs de artistas formatada como "[ID1,ID2,...]" 
 * num array dinâmico de inteiros.
 * 
 * @param artist_ids String contendo os IDs dos artistas.
 * 
 * @return Um ponteiro para um `GArray` contendo os IDs. O chamador é responsável 
 *         por liberar o array retornado.
 */
GArray* parse_artist_ids(const char *artist_ids);

/**
 * @brief Formata um número como um ID de usuário com prefixo 'U' e zeros à esquerda.
 *
 * Esta função recebe um número em formato de string, converte-o para inteiro,
 * e o formata como um ID de usuário com o prefixo 'U' seguido de 7 dígitos.
 * Caso o número possua menos de 7 dígitos, ele será preenchido com zeros à esquerda.
 *
 * @param number String contendo o número a ser formatado.
 * @return Ponteiro para uma string alocada dinamicamente contendo o ID formatado,
 * ou NULL em caso de erro de alocação de memória.
 *
 * @note A string retornada deve ser libertada pelo chamador utilizando `free` para evitar leaks de memória.
 */
char* format_idU(char *number);

/**
 * @brief Calcula a posição da semana de uma data em relação à data de referência.
 *
 * Esta função determina em qual semana uma data de entrada está posicionada em relação
 * a uma data de referência fixa. A diferença é expressa como um índice de semanas, onde um valor positivo
 * indica semanas antes da data de referência e um valor negativo indica semanas depois.
 *
 * @param date String contendo a data no formato "AAAA/MM/DD".
 * @return O índice da semana em relação à data de referência, ou -1 em caso de erro no processamento.
 * @note A data de referência usada é 9 de setembro de 2024 (segunda-feira)
 */
int calculate_week_position(char *date);


int find_peak(int *count_array, int size);
char *find_most_listened_string(GHashTable *time_table);
int find_most_listened(GHashTable *time_table);
#endif //UTILS_H