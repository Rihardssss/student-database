#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

int main(int argc, char *argv[]) {
    const char *dbFile = "students.db";
    if (loadDatabase(dbFile) != 0) {
        fprintf(stderr, "Could not load database.\n");
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: ./database <command> [arguments]\n");
        fprintf(stderr, "Commands:\n");
        fprintf(stderr, "  add <group> <firstName> <lastName> <age>\n");
        fprintf(stderr, "  modify <group> <oldFirstName> <oldLastName> <newFirstName> <newLastName> <newAge>\n");
        fprintf(stderr, "  delete <group> <firstName> <lastName>\n");
        fprintf(stderr, "  print <group> [sorted age|sorted lastName]\n");
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "add") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Usage: ./database add <group> <firstName> <lastName> <age>\n");
            return 1;
        }
        const char *group = argv[2];
        const char *firstName = argv[3];
        const char *lastName = argv[4];
        int age = atoi(argv[5]);
        if (addStudent(group, firstName, lastName, age) == 0) {
            saveDatabase(dbFile);
        }
    } else if (strcmp(command, "modify") == 0) {
        if (argc != 8) {
            fprintf(stderr, "Usage: ./database modify <group> <oldFirstName> <oldLastName> <newFirstName> <newLastName> <newAge>\n");
            return 1;
        }
        const char *group = argv[2];
        const char *oldFirstName = argv[3];
        const char *oldLastName = argv[4];
        const char *newFirstName = argv[5];
        const char *newLastName = argv[6];
        int newAge = atoi(argv[7]);
        if (modifyStudent(group, oldFirstName, oldLastName, newFirstName, newLastName, newAge) == 0) {
            saveDatabase(dbFile);
        }
    } else if (strcmp(command, "delete") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Usage: ./database delete <group> <firstName> <lastName>\n");
            return 1;
        }
        const char *group = argv[2];
        const char *firstName = argv[3];
        const char *lastName = argv[4];
        if (deleteStudent(group, firstName, lastName) == 0) {
            saveDatabase(dbFile);
        }
    } else if (strcmp(command, "print") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: ./database print <group> [sorted age|sorted lastName]\n");
            return 1;
        }
        const char *group = argv[2];
        int sortByAge = 0;
        int sortByLastName = 0;
        if (argc == 5 && strcmp(argv[3], "sorted") == 0) {
            if (strcmp(argv[4], "age") == 0) {
                sortByAge = 1;
            } else if (strcmp(argv[4], "lastName") == 0) {
                sortByLastName = 1;
            }
        }

        printStudents(group, sortByAge, sortByLastName);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
    }

    return 0;
}
