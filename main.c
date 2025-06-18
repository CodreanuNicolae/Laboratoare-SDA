#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 100
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME_SIZE];
    char surname[MAX_NAME_SIZE];
    int age;
    float grade;
} Student;

typedef struct {
    Student list[MAX_STUDENTS];
    int student_nr;
} List_Of_Students;

typedef enum {
  PRINT_STUDENTS = 1,
  SEARCH_BY_NAME = 2,
  SEARCH_BY_SURNAME = 3,
  SEARCH_BY_AGE = 4,
  SEARCH_BY_GRADE = 5,
  EXIT = 6,
} Enum;

void print_menu(int choice){
    printf("1. Print students list\n");
    printf("2. Search student by name\n");
    printf("3. Search student by surname\n");
    printf("4. Search student by age\n");
    printf("5. Search student by grade\n");
    printf("6. Exit\n");
}

void read_students(List_Of_Students *students) {
    printf("How many students to enter?");
    scanf("%d", &students->student_nr);

    if (students->student_nr > MAX_STUDENTS) {
        printf("Too many students!");
        students->student_nr = MAX_STUDENTS;
    }

    for (int i = 0; i < students->student_nr; i++) {
        printf("Enter data for student %d:\n", i + 1);

        printf("Name: ");
        scanf(" %s", students->list[i].name);

        printf("Surname: ");
        scanf(" %s", students->list[i].surname);

        printf("Age: ");
        scanf("%d", &students->list[i].age);

        printf("Grade: ");
        scanf("%f", &students->list[i].grade);
    }
}

void print_students(const List_Of_Students *students) {
    printf("\nStudents list:\n");
    for (int i = 0; i < students->student_nr; i++) {
        printf("Name: %s, Surname: %s, Age: %d, Grade: %.2f\n",
               students->list[i].name, students->list[i].surname, students->list[i].age, students->list[i].grade);
    }
}

int search_student_by_name(const List_Of_Students *students, const char *name) {
    for (int i = 0; i < students->student_nr; i++) {
        if (strcmp(students->list[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int search_student_by_surname(const List_Of_Students *students, const char *surname) {
    for (int i = 0; i < students->student_nr; i++) {
        if (strcmp(students->list[i].surname, surname) == 0) {
            return i;
        }
    }
    return -1;
}

int search_student_by_age(const List_Of_Students *students, int age) {
    for (int i = 0; i < students->student_nr; i++) {
        if (students->list[i].age == age) {
            return i;
        }
    }
    return -1;
}

int search_student_by_grade(const List_Of_Students *students, float grade) {
    for (int i = 0; i < students->student_nr; i++) {
        if (students->list[i].grade == grade) {
            return i;
        }
    }
    return -1;
}

int main() {
    List_Of_Students group;
    group.student_nr = 0;

    read_students(&group);

    float search_grade;
    int search_age;
    int choice = 0;
    print_menu(choice);

    while (choice != 6) {
        char search_name[MAX_NAME_SIZE];
        char search_surname[MAX_NAME_SIZE];

        scanf("%d", &choice);

        switch (choice) {
            case PRINT_STUDENTS:
                print_students(&group);
            printf("\n");
            break;
            case SEARCH_BY_NAME:
                printf("Enter search name: ");
                scanf(" %s", search_name);
                int index_name = search_student_by_name(&group, search_name);
                if (index_name != -1) {
                    printf("Found student '%s' at position %d.\n", search_name, index_name + 1);
                } else {
                    printf("Student '%s' not found.\n", search_name);
                }
            printf("\n");
            break;
            case SEARCH_BY_SURNAME:
                printf("Enter search surname: ");
                scanf(" %s", search_surname);
                int index_surname = search_student_by_surname(&group, search_surname);
                if (index_surname != -1) {
                    printf("Found student '%s' at position %d.\n", search_surname, index_surname + 1);
                } else {
                    printf("Student '%s' not found.\n", search_surname);
                }
            printf("\n");
            break;
            case SEARCH_BY_AGE:
                printf("Enter search age: ");
                scanf("%d", &search_age);
                int index_age = search_student_by_age(&group, search_age);
                if (index_age != -1) {
                    printf("Found student with age %d at position %d.\n", search_age, index_age + 1);
                } else {
                    printf("No student found with age %d.\n", search_age);
                }
            printf("\n");
            break;
            case SEARCH_BY_GRADE:
                printf("Enter search grade: ");
                scanf("%f", &search_grade);
                int index_grade = search_student_by_grade(&group, search_grade);
                if (index_grade != -1) {
                    printf("Found student with grade %.2f at position %d.\n", search_grade, index_grade + 1);
                } else {
                    printf("No student found with grade %.2f.\n", search_grade);
                }
            printf("\n");
            break;
            case EXIT:
                printf("Exit successful\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
