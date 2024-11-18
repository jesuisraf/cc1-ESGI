#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"   

int main() {
    char query[256];  // Tableau pour stocker la requête entrée par l'utilisateur

    while (1) {
        printf("Entrez une requete SQL (ou 'exit' pour quitter) :\n");
        fgets(query, sizeof(query), stdin); 
        query[strcspn(query, "\n")] = 0;  // Supprimer le retour à la ligne à la fin de la chaîne

        if (strcmp(query, "exit") == 0) {
            break;
        }

        executeSQL(query);
    }

    return 0;
}
