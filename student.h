#ifndef STUDENT_H
#define STUDENT_H

#define MAX_FIRST_NAME 60
#define MAX_LAST_NAME 60
#define MAX_GROUP_NAME 8
#define MAX_STUDENTS_PER_GROUP 30
#define GROUP_COUNT 3

typedef struct {
    char firstName[MAX_FIRST_NAME];
    char lastName[MAX_LAST_NAME];
    int age;
    char classGroup[MAX_GROUP_NAME]; 
} Student;

#endif

