#ifndef STUDENT_H
#define STUDENT_H

// Déclaration de la structure Student
typedef struct {
    int id;               
    char name[50];       
    float grade;          
} Student;

// Prototypes des fonctions de gestion des étudiants
void insertStudent(Student student);  
void selectAllStudents();             
void deleteStudent(int id);            

#endif
