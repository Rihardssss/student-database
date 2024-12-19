#ifndef DATABASE_H
#define DATABASE_H

#include "student.h"

int loadDatabase(const char *filename);
int saveDatabase(const char *filename);

int addStudent(const char *groupName, const char *firstName, const char *lastName, int age);
int modifyStudent(const char *groupName, const char *oldFirstName, const char *oldLastName,
                  const char *newFirstName, const char *newLastName, int newAge);
int deleteStudent(const char *groupName, const char *firstName, const char *lastName);
int printStudents(const char *groupName, int sortByAge, int sortByLastName);

#endif

