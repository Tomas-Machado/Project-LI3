//
// Created by manue on 15/11/2024.
//

#ifndef QUERIES_H
#define QUERIES_H




/**
 * @brief Imprime o resultado da Query1
 *
 * @param id ID do user ou artista (deve começar com 'U' para user ou 'A' para artista).
 * @param gestorA Ponteiro para o gestor de artistas.
 * @param gestorU Ponteiro para o gestor de users.
 * @param output_file_path Caminho para o arquivo onde o resultado será guardado.
 * @param separator Caractere separador usado na formatação do resultado.
 */
void print_query1(const char *id,Gestor_Artist gestorA, Gestor_User gestorU, const char *output_file_path,char separator, int inter);

/**
 * @brief Imprime o resultado da Query2
 *
 * @param N Número máximo de artistas a serem listados.
 * @param country Nome do país dos artistas a serem filtrados.
 * @param gestor Ponteiro para o gestor de artistas.
 * @param output_file_path Caminho para o arquivo onde o resultado será guardado.
 * @param separator Caractere separador usado na formatação do resultado.
 */
void print_query2(int N, char *country, Gestor_Artist gestor, const char *output_file_path,char separator, int inter);

/**
 * @brief Imprime o resultado da Query3
 *
 * @param age1 Idade mínima do intervalo.
 * @param age2 Idade máxima do intervalo.
 * @param gestor_user Ponteiro para o gestor de users.
 * @param output_file_path Caminho para o arquivo onde o resultado será guardado.
 * @param separator Caractere separador usado na formatação do resultado.
 */
void print_query3(int age1, int age2, Gestor_User gestor_user, const char *output_file_path,char separator, int inter);


void print_query4(Gestor_Artist gestorA,char *begin_date,char *end_date ,const char *output_file_path,char separator,int iter);

#endif //QUERIES_H
