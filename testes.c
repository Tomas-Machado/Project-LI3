#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/catalog.h"
#include "../include/parser.h"
#include <sys/resource.h>
#include <time.h>
#include <dirent.h>

#include "Queries.h"
#include "Utils.h"

// Globals to track results
int total_files = 0;
int identical_files = 0;
int different_files = 0;

int q1_correct = 0, q1_total = 0;
int q2_correct = 0, q2_total = 0;
int q3_correct = 0, q3_total = 0;
int q4_correct = 0, q4_total = 0;


// Function to compare two files line by line
void compare_files(const char *file1, const char *file2, int query_type, int query_num) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return;
    }

    char line1[1024], line2[1024];
    int differences = 0;
    int line_num = 1;
    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Descrepância na query %d: \"%s\"\n", query_num, file1);
            printf("Obtido: %s\n", line1);
            printf("Esperado: %s\n", line2);
            printf("Na linha %d\n", line_num);
            differences++;
        }
        line_num++;
    }
    if (differences) printf("\n");

    if (differences == 0) {
        if (query_type == 1) q1_correct++;
        if (query_type == 2) q2_correct++;
        if (query_type == 3) q3_correct++;
    }
    fclose(f1);
    fclose(f2);
}

// Memory usage reporting
void print_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("%ld MB\n", usage.ru_maxrss / 1024);
}

// Helper function to handle each query
void handle_query1(const char *line, Catalog catalog, double *q1_time, double *q2_time, double *q3_time, const char *expected_dir,int num) {
    char query_str[256];
    char arg1[256], arg2[256];
    int int_arg1, int_arg2;
    char output_file_path[256];
    char expected_file_path[256];
    char separator = ';';
    clock_t start, end;

    if (sscanf(line, "%s %s %[^\n]", query_str, arg1, arg2) >= 1) {
        int query_number = query_str[0] - '0';

        if (query_str[1] == 'S') separator = '=';

        sprintf(output_file_path, "resultados/command%d_output.txt", num);
        sprintf(expected_file_path, "%s/command%d_output.txt", expected_dir, num);

        switch (query_number) {
            case 1:
                q1_total++;  // Track total count for Q1
                start = clock();
                print_query1(arg1,get_artists(catalog) ,get_users(catalog), output_file_path, separator,1);
                end = clock();
                *q1_time += (double)(end - start) / CLOCKS_PER_SEC;
                compare_files(output_file_path, expected_file_path, 1, query_number);
                break;

            case 2:
                q2_total++;  // Track total count for Q2
                int_arg1 = atoi(arg1);
                if (sscanf(line, "%d %s %[^\n]", &query_number, arg1, arg2) == 3) {
                    trim_quotes(arg2);
                    start = clock();

                    print_query2(int_arg1, arg2, get_artists(catalog), output_file_path, separator,1);

                    end = clock();
                } else {
                    start = clock();

                    print_query2(int_arg1, NULL, get_artists(catalog), output_file_path, separator,1);

                    end = clock();
                }
                *q2_time += (double)(end - start) / CLOCKS_PER_SEC;
                compare_files(output_file_path, expected_file_path, 2, query_number);
                break;

            case 3:
                q3_total++;  // Track total count for Q3
                if (sscanf(line, "%d %d %d", &query_number, &int_arg1, &int_arg2) == 3) {
                    start = clock();

                    print_query3(int_arg1, int_arg2, get_users(catalog), output_file_path, separator,1);

                    end = clock();
                    *q3_time += (double)(end - start) / CLOCKS_PER_SEC;
                    compare_files(output_file_path, expected_file_path, 3, query_number);
                } else {
                    fprintf(stderr, "Invalid query 3 arguments\n");
                }
                break;

            default:
                fprintf(stderr, "Unknown query number: %d\n", query_number);
                break;
        }

    }
}

// Parsing function to process each query and accumulate timing and correctness data
void parse_query1(const char *input_file_path, Catalog catalog, const char *expected_dir) {
    FILE *input_file = fopen(input_file_path, "r");
    if (!input_file) {
        fprintf(stderr, "Error opening file: %s\n", input_file_path);
        return;
    }

    int query_num = 1;
    int num = 1;
    double q1_time = 0.0, q2_time = 0.0, q3_time = 0.0;
    char line[1024];

    while (fgets(line, sizeof(line), input_file)) {
        handle_query1(line, catalog, &q1_time, &q2_time, &q3_time, expected_dir,num);
        num++;
        query_num++;
    }
    fclose(input_file);

    // Print timing and accuracy summary
    printf("\nQuery Results:\n");
    printf("Q1: %d de %d testes ok!\n", q1_correct, q1_total);
    printf("Q2: %d de %d testes ok!\n", q2_correct, q2_total);
    printf("Q3: %d de %d testes ok!\n", q3_correct, q3_total);

    printf("\nMemória utilizada: ");
    print_memory_usage();

    printf("\nTempos de execução:\n");
    printf("Q1: %.1f ms\n", q1_time * 1000);
    printf("Q2: %.1f ms\n", q2_time * 1000);
    printf("Q3: %.1f ms\n", q3_time * 1000);
    printf("Tempo total: %.1f ms\n", (q1_time + q2_time + q3_time) * 1000);
}

// Main function
int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <dataset_path> <input_file> <expected_output_dir>\n", argv[0]);
        return 1;
    }
    clock_t start_time = clock();

    char *dataset = argv[1];
    char *input = argv[2];
    char *expected_dir = argv[3];
    char dataset_path[1024];

    ////////////////////////// Create Catalog //////////////////////////
    Catalog catalog = create_catalog();

    ////////////////////////// Load Dataset //////////////////////////
    sprintf(dataset_path, "%s/artists.csv", dataset);
    process_file(dataset_path, "resultados/artists_errors.csv", catalog);

    ///////////////////////////Albums///////////////////////////
    sprintf(dataset_path, "%s/albums.csv", dataset);
    process_file(dataset_path, "resultados/albums_errors.csv", catalog);

    ///////////////////////////Musics///////////////////////////
    sprintf(dataset_path, "%s/musics.csv", dataset);
    process_file(dataset_path, "resultados/musics_errors.csv", catalog);

    ///////////////////////////Users////////////////////////////
    sprintf(dataset_path, "%s/users.csv", dataset);
    process_file(dataset_path, "resultados/users_errors.csv", catalog);

    ///////////////////////////History///////////////////////////
    sprintf(dataset_path, "%s/history.csv", dataset);
    process_file(dataset_path, "resultados/history_errors.csv", catalog);

    ////////////////////////// Run Queries //////////////////////////
    parse_query1(input, catalog, expected_dir);

    ////////////////////////// Destroy Catalog //////////////////////////
    clock_t start_destroy_time = clock();
    destroy_catalog(catalog);
    clock_t end_destroy_time = clock();
    double destroy_time = (double)(end_destroy_time - start_destroy_time) / CLOCKS_PER_SEC;
    printf("Time taken to destroy catalog: %.2f seconds\n", destroy_time);

    ////////////////////////// Total Time //////////////////////////
    clock_t end_time = clock();
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Total elapsed time: %.2f seconds\n", total_time);

    return 0;
}