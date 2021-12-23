/**
 * @file writefile.h
 */

#include <stdio.h>
#include <unistd.h>

#include "../../headers/results/writefile.h"

/**
 * @brief Store result data in the file result.csv
 *
 */
void writefile() {
    if (access("../results/results.csv", F_OK) == -1) {
        //printf("Error: result.csv not found\n\n");
        FILE *new_file;
        new_file = fopen("../results/results.csv", "w");
        fclose(new_file);
        //TODO: create CSV
    }
    if (access("../results/results.csv", F_OK) != -1) {
        printf("File open\n");
        FILE *file_result = fopen("../results/results.csv", "w+");
        fputs("Partie; Round; Choix J1; Choix J2; Temps de décision J1; Temps de décision J2; Solde J1; Solde J2",
              file_result);

        fclose(file_result);
    }
} 