#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/catalog.h"
#include <dirent.h>
#include "Utils.h"

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}
int total_files = 0;
int identical_files = 0;
int different_files = 0;

void compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (!f1 || !f2) {
        fprintf(stderr, "Error opening files: %s, %s\n", file1, file2);
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return;
    }

    char line1[1024], line2[1024];
    int line_num = 1;
    int differences = 0;

    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Difference in file %s and %s at line %d:\n", file1, file2, line_num);
            printf("File1: %s", line1);
            printf("File2: %s", line2);
            differences++;
        }
        line_num++;
    }

    if (differences == 0) {
        //printf("Files %s and %s are identical.\n", file1, file2);
        identical_files++;
    } else {
        different_files++;
    }

    total_files++;

    fclose(f1);
    fclose(f2);
}

void compare_directories(const char *dir1, const char *dir2) {
    DIR *d1 = opendir(dir1);
    DIR *d2 = opendir(dir2);

    if (!d1 || !d2) {
        fprintf(stderr, "Error opening directories: %s, %s\n", dir1, dir2);
        if (d1) closedir(d1);
        if (d2) closedir(d2);
        return;
    }

    struct dirent *entry1;
    while ((entry1 = readdir(d1)) != NULL) {
        if (entry1->d_type == DT_REG) {
            char file1[1024], file2[1024];
            snprintf(file1, sizeof(file1), "%s/%s", dir1, entry1->d_name);
            snprintf(file2, sizeof(file2), "%s/%s", dir2, entry1->d_name);

            compare_files(file1, file2);
        }
    }

    closedir(d1);
    closedir(d2);
}




int main(int argc, char **argv)
{
    if (argc == 3) {

        // Start the timer
        clock_t start_time = clock();
        ///////////////////////////Parse the input arguments///////////////////////////
        char *dataset = argv[1];
        char *dataset_path = malloc(strlen(dataset) + 20);

        // Create the catalog
        Catalog catalog = create_catalog();

        ///////////////////////////Artists///////////////////////////
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


        ///////////////////////////Parse the input file///////////////////////////
        parse_query(argv[2], catalog);

        // Free memory
        free(dataset_path);
        destroy_catalog(catalog);

        // End the timer
        clock_t end_time = clock();
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Elapsed time: %.2f seconds\n", elapsed_time);

        //////////////////////////// Compare directories ////////////////////////////
        const char *dir1 = "resultados";
        const char *dir2 = "small/outputs_esperados";

        compare_directories(dir1, dir2);

        printf("\nSummary:\n");
        printf("Total files compared: %d\n", total_files);
        printf("Identical files: %d\n", identical_files);
        printf("Different files: %d\n", different_files);

        return 0;
    }
}