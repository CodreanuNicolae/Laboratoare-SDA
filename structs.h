
#ifndef STUDENTS_H
#define STUDENTS_H

#define MAX_NAME_SIZE 100
#define MAX_STUDENTS 100

typedef struct {
    char *name[MAX_NAME_SIZE];
    char *surname[MAX_NAME_SIZE];
    int age;
    float grade;
} Student;

typedef struct {
    Student *list[MAX_STUDENTS];
    int student_nr;
} List_Of_Students;

typedef enum {
    READ_STUDENTS = 1,
    PRINT_STUDENTS = 2,
    SEARCH_STUDENTS_NAME = 3,
    SEARCH_STUDENTS_SURNAME = 4,
    SEARCH_STUDENTS_AGE = 5,
    SEARCH_STUDENTS_GRADE = 6,
    SORT_STUDENTS = 7,
    PUSH_FRONT = 8,
    PUSH_BACK = 9,
    INSERT_AT_INDEX = 10,
    REMOVE_AT_INDEX = 11,
    EXIT = 12

} Case;

typedef int (*StudentComparator)(const Student *, const Student *);

#endif
