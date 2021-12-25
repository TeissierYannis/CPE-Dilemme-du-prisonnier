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
void writefile(party party)
{
    if (access("./results/results.csv", F_OK) == -1)
    {
        FILE *new_file;
        new_file = fopen("./results/results.csv", "w");
        fprintf(new_file, "Partie; Round; Choix J1; Choix J2; Temps de décision J1; Temps de décision J2; Solde J1; Solde J2\n");
        fclose(new_file);
    }
    if (access("./results/results.csv", F_OK) != -1)
    {
        FILE *file_result = fopen("./results/results.csv", "a+");

        for (int i = 0; i < rules0.nb_round; i++)
        {
            fprintf(file_result, "%d;%d;%d;%d;%d;%d;%d;%d\n",
                    party.id,
                    party.round[i].round_number,
                    party.round[i].p1_result,
                    party.round[i].p2_result,
                    party.round[i].p1_decision_time,
                    party.round[i].p2_decision_time,
                    party.round[i].p1_wallet,
                    party.round[i].p2_wallet);
        }
        fclose(file_result);
    }
}