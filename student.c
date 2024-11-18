#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define DATABASE_FILE "students.csv"

// Fonction pour insérer un étudiant dans le fichier
void insertStudent(Student student) {
    FILE *file = fopen(DATABASE_FILE, "a");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "%d,%s,%.2f\n", student.id, student.name, student.grade);
    fclose(file);
    printf("Étudiant ajouté: %s\n", student.name);
}

// Fonction pour afficher tous les étudiants présents dans le fichier
void selectAllStudents() {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("Aucun étudiant trouvé.\n");
        return;
    }
    char line[256];
    printf("Liste des étudiants:\n");
    while (fgets(line, sizeof(line), file)) {
        Student student;

        if (sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade) == 3) {
            printf("ID: %d, Nom: %s, Note: %.2f\n", student.id, student.name, student.grade);
        } else {

            fprintf(stderr, "Ligne malformée dans le fichier: %s", line);
        }
    }
    fclose(file);
}

// Fonction pour supprimer un étudiant basé sur son ID
void deleteStudent(int id) {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL) {
        printf("Aucun étudiant trouvé pour suppression.\n");
        return;
    }

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        fprintf(stderr, "Erreur lors de la création du fichier temporaire.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        Student student;
        if (sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade) == 3) {
            if (student.id != id) {
                fprintf(tempFile, "%d,%s,%.2f\n", student.id, student.name, student.grade);
            } else {
                found = 1;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    // Si l'étudiant a été trouvé et supprimé, remplacer l'ancien fichier par le nouveau
    if (found) {
        if (remove(DATABASE_FILE) == 0) {
            rename("temp.csv", DATABASE_FILE);
            printf("Étudiant supprimé avec succès (ID: %d)\n", id);
        } else {
            printf("Erreur lors de la suppression du fichier d'origine.\n");
        }
    } else {
        // Si l'étudiant n'a pas été trouvé, supprimer le fichier temporaire
        remove("temp.csv");
        printf("Aucun étudiant trouvé avec cet ID.\n");
    }
}
