#include <stdio.h>

#include "Gestor_User.h"
#include "Gestor_Artist.h"
#include "Gestor_Artist.h"
#include "Queries.h"

/* Implementation of print_query1, print_query2, print_query3
 *  Prints the query information to a file
 *  get_query1: function that gets the user information
 *  get_query1 localized in Gestor_User.c
 *  get_query2 localized in Gestor_Artist.c
 *  get_query3 localized in Gestor_User.c
*/

void print_query1(const char *id,Gestor_Artist gestorA, Gestor_User gestorU, const char *output_file_path,char separator,int iter) {
    char result[1024];
    if (id[0] == 'U') get_query1_User(id, gestorU, result, separator, iter);
    if (id[0] == 'A') get_query1_Artist(id, gestorA, result, separator, iter);


    if (iter == 0) {
        FILE *file = fopen(output_file_path, "w");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", output_file_path);
            return;
        }
        fprintf(file, "%s", result);
        fclose(file);
    } else {
        if (result[0] != '\n') {
            printf( "%s", result);
        }
        else {
            printf("Utilizador ou Artista não encontrado ou Argumentos mal inseridos\n");
        }
    }
}



// Implementation of print_query2
void print_query2(int N, char *country, Gestor_Artist gestor, const char *output_file_path,char separator,int iter) {
    char result[2048];
    get_query2(N, country, gestor, result,separator, iter);

    if (iter == 0) {
        FILE *file = fopen(output_file_path, "w");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", output_file_path);
            return;
        }
        fprintf(file, "%s", result);
        fclose(file);
    }
    if (iter == 1) {
        if (result[0] != '\n') {
            printf( "%s", result);
        }
        else {
            printf("Artista não encontrado ou País mal inserido\n");
        }
    }

}



// Implementation of print_query3
void print_query3(int age1, int age2, Gestor_User gestor_user, const char *output_file_path,char separator,int iter) {
    char result[2048];
    get_query3(age1, age2, gestor_user, result, separator, iter);


    if (iter == 0) {
        FILE *file = fopen(output_file_path, "w");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", output_file_path);
            return;
        }
        fprintf(file, "%s", result);
        fclose(file);
    }
    if (iter == 1) {
        if (result[0] != '\n') {
            printf( "%s", result);
        }
        else {
            printf("Utilizador não encontrado ou Idades mal inseridos\n");
        }
    }
}

void print_query4(Gestor_Artist gestorA,char *begin_date,char *end_date ,const char *output_file_path,char separator,int iter) {
    char result[2048];
    //query_4(gestorA, result, separator);
    query_4(gestorA, begin_date, end_date, separator,result, iter);

    if (iter == 0) {
        FILE *file = fopen(output_file_path, "w");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", output_file_path);
            return;
        }
        if (result[0] == 's') result[0] = result[0] + 1;
        fprintf(file, "%s", result);
        fclose(file);
    }

    if (iter == 1) {
        if (result[0] != '\n') {
            printf( "%s", result);
        }
        else {
            printf("Artista não encontrado ou Datas mal inseridos\n");
        }
    }

}