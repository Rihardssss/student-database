#include <stdio.h>
#include <string.h>
#include "database.h"
#include <stdlib.h>


static Student groups[GROUP_COUNT][MAX_STUDENTS_PER_GROUP];
static int groupSizes[GROUP_COUNT] = {0, 0, 0}; 

static const char *groupNames[GROUP_COUNT] = {"px22", "px23", "px24"};

static int getGroupIndex(const char *groupName) {
    for (int i = 0; i < GROUP_COUNT; i++) {
        if (strcmp(groupNames[i], groupName) == 0) {
            return i;
        }
    }
    return -1;
}

int loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return 0;
    }

    if (fread(groupSizes, sizeof(int), GROUP_COUNT, fp) != GROUP_COUNT) {
        fclose(fp);
        return -1; 
    }

    for (int i = 0; i < GROUP_COUNT; i++) {
        if (fread(groups[i], sizeof(Student), groupSizes[i], fp) != (size_t)groupSizes[i]) {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

int saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1;

    if (fwrite(groupSizes, sizeof(int), GROUP_COUNT, fp) != GROUP_COUNT) {
        fclose(fp);
        return -1;
    }

    for (int i = 0; i < GROUP_COUNT; i++) {
        if (fwrite(groups[i], sizeof(Student), groupSizes[i], fp) != (size_t)groupSizes[i]) {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

int addStudent(const char *groupName, const char *firstName, const char *lastName, int age) {
    int gIndex = getGroupIndex(groupName);
    if (gIndex == -1) {
        fprintf(stderr, "Invalid group name: %s\n", groupName);
        return -1;
    }

    if (groupSizes[gIndex] >= MAX_STUDENTS_PER_GROUP) {
        fprintf(stderr, "Group %s is full.\n", groupName);
        return -1;
    }

    Student newStudent;
    strncpy(newStudent.firstName, firstName, MAX_FIRST_NAME - 1);
    newStudent.firstName[MAX_FIRST_NAME - 1] = '\0';
    strncpy(newStudent.lastName, lastName, MAX_LAST_NAME - 1);
    newStudent.lastName[MAX_LAST_NAME - 1] = '\0';
    newStudent.age = age;
    strncpy(newStudent.classGroup, groupName, MAX_GROUP_NAME - 1);
    newStudent.classGroup[MAX_GROUP_NAME - 1] = '\0';

    groups[gIndex][groupSizes[gIndex]] = newStudent;
    groupSizes[gIndex]++;
    return 0;
}

int modifyStudent(const char *groupName, const char *oldFirstName, const char *oldLastName,
                  const char *newFirstName, const char *newLastName, int newAge) {
    int gIndex = getGroupIndex(groupName);
    if (gIndex == -1) {
        fprintf(stderr, "Invalid group name: %s\n", groupName);
        return -1;
    }

    for (int i = 0; i < groupSizes[gIndex]; i++) {
        Student *s = &groups[gIndex][i];
        if (strcmp(s->firstName, oldFirstName) == 0 && strcmp(s->lastName, oldLastName) == 0) {
            strncpy(s->firstName, newFirstName, MAX_FIRST_NAME - 1);
            s->firstName[MAX_FIRST_NAME - 1] = '\0';
            strncpy(s->lastName, newLastName, MAX_LAST_NAME - 1);
            s->lastName[MAX_LAST_NAME - 1] = '\0';
            s->age = newAge;
            return 0;
        }
    }

    fprintf(stderr, "Student not found in group %s.\n", groupName);
    return -1;
}



//https://www.youtube.com/watch?v=KXsQbKQyfFA






int deleteStudent(const char *groupName, const char *firstName, const char *lastName) {
    int gIndex = getGroupIndex(groupName);
    if (gIndex == -1) {
        fprintf(stderr, "Invalid group name: %s\n", groupName);
        return -1;
    }

    for (int i = 0; i < groupSizes[gIndex]; i++) {
        Student *s = &groups[gIndex][i];
        if (strcmp(s->firstName, firstName) == 0 && strcmp(s->lastName, lastName) == 0) {
            for (int j = i; j < groupSizes[gIndex] - 1; j++) {
                groups[gIndex][j] = groups[gIndex][j + 1];
            }
            groupSizes[gIndex]--;
            return 0;
        }
    }

    fprintf(stderr, "Student not found in group %s.\n", groupName);
    return -1;
}

static int compareByAge(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    return s1->age - s2->age;
}

static int compareByLastName(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    return strcmp(s1->lastName, s2->lastName);
}

int printStudents(const char *groupName, int sortByAge, int sortByLastName) {
    int gIndex = getGroupIndex(groupName);
    if (gIndex == -1) {
        fprintf(stderr, "Invalid group name: %s\n", groupName);
        return -1;
    }

    if (groupSizes[gIndex] == 0) {
        printf("No students in group %s.\n", groupName);
        return 0;
    }


    //https://www.youtube.com/watch?v=7YUVdCx4wr0

    
    Student tempArr[MAX_STUDENTS_PER_GROUP];
    memcpy(tempArr, groups[gIndex], sizeof(Student)*groupSizes[gIndex]);

    if (sortByAge) {
        qsort(tempArr, groupSizes[gIndex], sizeof(Student), compareByAge);
    } else if (sortByLastName) {
        qsort(tempArr, groupSizes[gIndex], sizeof(Student), compareByLastName);
    }

    for (int i = 0; i < groupSizes[gIndex]; i++) {
        printf("%d. %s %s, Age: %d\n", i+1, tempArr[i].firstName, tempArr[i].lastName, tempArr[i].age);
    }

    return 0;
}

