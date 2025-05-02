#ifndef PARSER_H
#define PARSER_H
#include "artist.h"
#include "music.h"
#include <glib.h>

#include "catalog.h"

////////////////////////////MAIN FUNCTIONS////////////////////////////
/**
 * @brief Analisa uma linha de CSV em campos separados por ponto e vírgula (;).
 * 
 * Esta função processa uma linha de texto CSV e divide-a em campos com base no delimitador 
 * ponto e vírgula (;). Campos delimitados por aspas duplas (") são tratados como um único campo, 
 * mesmo que contenham delimitadores.
 * 
 * @param line A linha de texto CSV a ser analisada.
 * @param fields Um array de strings onde os campos extraídos serão armazenados.
 */
void parse_csv_line(char *line, char **fields);

/**
 * @brief Processa um arquivo de entrada e categoriza os dados, registrando erros.
 * 
 * Esta função lê um arquivo CSV linha por linha, analisa os campos usando 
 * a função `parse_csv_line` e identifica o tipo de dados com base na linha. Dependendo do tipo, 
 * os dados são processados por funções específicas (`Parse_Artist`, `Parse_Music`, etc.). 
 * Linhas inválidas são registradas em um arquivo de erro.
 * 
 * @param input_file Nome do arquivo de entrada a ser processado.
 * @param error_output_file Nome do arquivo onde linhas com erros serão registradas.
 * @param catalog Estrutura de dados onde os registros processados serão armazenados.
 */
void process_file(const char *input_file,const char *error_output_file,Catalog catalog); 

/**
 * @brief Processa um arquivo de consultas e executa as operações correspondentes no catálogo.
 *
 * A função lê um arquivo linha por linha, interpreta as consultas (1, 2, 3, etc.) e 
 * chama funções específicas para processá-las. Os resultados de cada consulta são 
 * gravados em arquivos de saída separados.
 * 
 * @param input_file_path Caminho para o arquivo de entrada contendo as consultas.
 * @param catalog Estrutura de dados do catálogo que contém artistas, músicas, usuários, etc.
 */
void parse_query(const char *input_file_path, Catalog catalog);


////////////////////////AUXILIARY FUNCTIONS///////////////////////////

/**
 * @brief Identifica o tipo de linha em um arquivo de entrada baseado no prefixo.
 * 
 * @param line Linha de texto do arquivo de entrada.
 * @return Um número inteiro representando o tipo da linha:
 * - 0: Artista
 * - 1: Música
 * - 2: Usuário
 * - 3: Álbum
 * - 4: Histórico
 * - (-1): Tipo desconhecido
 */
int indetify_type(const char *line);

/**
 * @brief Processa e insere informações sobre artistas no catálogo.
 * 
 * @param fields Vetor de strings com os campos extraídos da linha do arquivo.
 * @param catalog Estrutura do catálogo onde os artistas serão inseridos.
 * @param counter Ponteiro para o contador de elementos processados.
 * @return `true` se o artista foi inserido com sucesso, `false` caso contrário.
 */
bool Parse_Artist(char **fields, Catalog catalog, int *counter);

/**
 * @brief Processa e insere informações sobre álbuns no catálogo.
 * 
 * @param fields Vetor de strings com os campos extraídos da linha do arquivo.
 * @param catalog Estrutura do catálogo onde os álbuns serão inseridos.
 * @param counter Ponteiro para o contador de elementos processados.
 * @return `true` se o álbum foi inserido com sucesso, `false` caso contrário.
 */
bool Parse_Album(char **fields, Catalog catalog, int *counter);

/**
 * @brief Processa e insere informações sobre músicas no catálogo.
 * 
 * @param fields Vetor de strings com os campos extraídos da linha do arquivo.
 * @param catalog Estrutura do catálogo onde as músicas serão inseridas.
 * @param counter Ponteiro para o contador de elementos processados.
 * @return `true` se a música foi inserida com sucesso, `false` caso contrário.
 */
bool Parse_Music(char **fields, Catalog catalog, int *counter);

/**
 * @brief Processa e insere informações sobre users no catálogo.
 * 
 * @param fields Vetor de strings com os campos extraídos da linha do arquivo.
 * @param catalog Estrutura do catálogo onde os usuários serão inseridos.
 * @param counter Ponteiro para o contador de elementos processados.
 * @return `true` se o user foi inserido com sucesso, `false` caso contrário.
 */
bool Parse_User(char **fields, Catalog catalog, int *counter);

/**
 * @brief Processa e insere informações sobre o histórico de reproduções no catálogo.
 * 
 * @param fields Vetor de strings com os campos extraídos da linha do arquivo.
 * @param catalog Estrutura do catálogo onde o histórico será inserido.
 * @param counter Ponteiro para o contador de elementos processados.
 * @return `true` se o histórico foi inserido com sucesso, `false` caso contrário.
 */
bool Parse_History(char **fields, Catalog catalog, int *counter);

#endif