#include <stdio.h>
#include <string.h>
#include "student.h"
#include "sql.h" 

void executeSQL(const char *query) {
    if (strncmp(query, "SELECT", 6) == 0) {
        selectAllStudents();
    }
    else if (strncmp(query, "INSERT", 6) == 0) {
        int id;
        char name[50];
        float grade;
        // Parse la requête pour obtenir les valeurs id, name et grade
        if (sscanf(query, "INSERT INTO students (id, name, grade) VALUES (%d, '%49[^']', %f);", &id, name, &grade) == 3) {
            Student newStudent;
            newStudent.id = id;
            strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);  
            newStudent.name[sizeof(newStudent.name) - 1] = '\0';  
            newStudent.grade = grade;
            insertStudent(newStudent);  
        } else {
            printf("Erreur dans la syntaxe de la requête INSERT.\n");
        }
    }
    else if (strncmp(query, "DELETE", 6) == 0) {
        int id;
        // Parse la requête DELETE pour obtenir l'id
        if (sscanf(query, "DELETE FROM students WHERE id = %d;", &id) == 1) {
            deleteStudent(id);
        } else {
            printf("Erreur dans la syntaxe de la requête DELETE.\n");
        }
    } else {
        printf("Requête SQL non reconnue.\n");
    }
}
