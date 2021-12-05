
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../headers/results/writefile.h"

void writefile()
{
    if(access("../results/results.csv", F_OK) == -1)
    {
        //printf("Error: result.csv not found\n\n");
        FILE *new_file;
        new_file  = fopen ("../results/results.csv", "w");
        fclose(new_file);
        //TODO: create CSV
    } 
    if(access("../results/results.csv", F_OK) != -1)
    {
        printf("File open\n");
        FILE * file_result = fopen("../results/results.csv", "w+");
        fputs("Partie; Round; Choix J1; Choix J2; Temps de décision J1; Temps de décision J2; Solde J1; Solde J2", file_result);
        
        fclose(file_result);
    }
} 

/* void addData(int partie, int round, int ChoixJ1, int ChoixJ2, int TimeJ1, int TimeJ2, int SoldeJ1, int SoldeJ2)
{

} */