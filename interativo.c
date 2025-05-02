#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "catalog.h"
#include "parser.h"
#include "Queries.h"
#include "Utils.h"

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

int main() {
            printf("Bem-vindo ao nosso programa!\n");
            printf("Para correr o programa, por favor insira o seguinte comando:\n");
            printf("Indique o Caminho para o Dataset: \n");
            char *dataset = malloc(100 * sizeof(char));
            scanf("%s", dataset);
            printf("\n");
            //if (!dataset) dataset = "Dataset-errors";
            char *dataset_path = malloc(strlen(dataset) + 20);

            // Create the catalog
            Catalog catalog = create_catalog();
            ///////////////////////////Artists///////////////////////////
            sprintf(dataset_path, "%s/artists.csv", dataset);
            process_file(dataset_path, "resultados/artists_errors.csv", catalog);
            if (!file_exists(dataset)) {
                printf("Erro ao processar o ficheiro artists.csv\n");
                return 1;
            }
            ///////////////////////////Albums///////////////////////////
            sprintf(dataset_path, "%s/albums.csv", dataset);
            process_file(dataset_path, "resultados/albums_errors.csv", catalog);
            if (!file_exists(dataset)) {
                printf("Erro ao processar o ficheiro albums.csv\n");
                return 1;
            }

            ///////////////////////////Musics///////////////////////////
            sprintf(dataset_path, "%s/musics.csv", dataset);
            process_file(dataset_path, "resultados/musics_errors.csv", catalog);
            if (!file_exists(dataset)) {
                printf("Erro ao processar o ficheiro musics.csv\n");
                return 1;
            }
            ///////////////////////////Users////////////////////////////
            sprintf(dataset_path, "%s/users.csv", dataset);
            process_file(dataset_path, "resultados/users_errors.csv", catalog);
            if (!file_exists(dataset)) {
                printf("Erro ao processar o ficheiro users.csv\n");
                return 1;
            }
            ///////////////////////////History///////////////////////////
            sprintf(dataset_path, "%s/history.csv", dataset);
            process_file(dataset_path, "resultados/history_errors.csv", catalog);
            if (!file_exists(dataset)) {
                printf("Erro ao processar o ficheiro history.csv\n");
                return 1;
            }
            //////////////////////////Parse_Querys////////////////////////
            int exit = 1;
            char *query = malloc(100);
            char *args = malloc(100);
            char separator = ';';
            while (true) {
                printf("Indique o número da query que pretende correr\n(Se prentede sair do programa indique o 0)\n");

                scanf("%s", query);
                if (query[1] == 'S') {
                    separator = '=';
                }
                if (atoi(query) == 0) {
                    break;
                }
                if (atoi(query) == 1) {
                    printf("Indique o id do artista ou Username Desejado\n");
                    scanf("%s", args);
                   if (args[0] != 'A' || args[0] != 'U' ) print_query1(args, get_artists(catalog), get_users(catalog), NULL, separator, 1);
                    else printf("Id mal inserido\n");
                }
                if (atoi(query) == 2) {
                    printf("Indique o número de artistas que pretende ver e o país\n");
                    scanf("%s", args);
                    printf("Queres inserir o país? (S/N)\n");
                    char *in = malloc(100);
                    scanf("%s", in);
                    if (in[0] == 'S') {
                        char *country = malloc(100);
                        int N = atoi(args);
                        printf("Por favor inserir País entre aspas \" \n");
                        scanf("%s", country);
                        trim_quotes(country);
                        print_query2(N, country, get_artists(catalog), NULL, separator, 1);
                        free(country);
                    } else {
                        int N = atoi(args);
                        printf("Doing query2 with N = %d\n", N);
                        print_query2(N, NULL, get_artists(catalog), NULL, separator, 1);
                    }
                    free(in);
                }

                if (atoi(query) == 3) {
                    printf("Indique a idade minima e a idade maxima\n");
                    scanf("%s", args);
                    int age1 = atoi(args);
                    scanf("%s", args);
                    int age2 = atoi(args);
                    print_query3(age1, age2, get_users(catalog), NULL, separator, 1);
                }
                if (atoi(query) == 4) {
                    printf("Deseja inserir a data de inicio e a data de fim? (S/N)\n");
                    char *in = malloc(100);
                    scanf("%s", in);
                    if (in[0] == 'N') {
                        print_query4(get_artists(catalog), NULL, NULL, NULL, separator, 1);
                        free(in);
                    } else {

                    printf("Indique a data de inicio e a data de fim\n");
                    scanf("%s", args);
                    char *begin_date = malloc(100);
                    strcpy(begin_date, args);
                    scanf("%s", args);
                    char *end_date = malloc(100);
                    strcpy(end_date, args);
                    print_query4(get_artists(catalog), begin_date, end_date, NULL, separator, 1);
                    free(begin_date);
                    free(end_date);
                    free(in);
                    }
                }

            }

            printf("A sair do programa...\n");

    // Free memory
    destroy_catalog(catalog);
    free(dataset);
    free(query);
    free(args);
    return 0;
}