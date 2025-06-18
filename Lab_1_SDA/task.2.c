#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define MAX_NAME_SIZE 100
#define MAX_STUDENTS 100

int main() {
    List_Of_Students group;
    group.student_nr = 0;

    int choice = 0;

    while (choice != 12) {
        char search_name[MAX_NAME_SIZE];
        char search_surname[MAX_NAME_SIZE];
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_STUDENTS:
                read_students(&group);
                break;
            case PRINT_STUDENTS:
                print_students(&group);
                break;
            case SEARCH_STUDENTS_NAME:
                printf("Enter search name: ");
                scanf(" %s", search_name);
                int index_name = search_student_by_name(&group, search_name);
                if (index_name != -1) {
                    printf("Found student '%s' at position %d.\n", search_name, index_name + 1);
                } else {
                    printf("Student '%s' not found.\n", search_name);
                }
                break;
            case SEARCH_STUDENTS_SURNAME:
                printf("Enter search surname: ");
                scanf(" %s", search_surname);
                int index_surname = search_student_by_surname(&group, search_surname);
                if (index_surname != -1) {
                    printf("Found student '%s' at position %d.\n", search_surname, index_surname + 1);
                } else {
                    printf("Student '%s' not found.\n", search_surname);
                }
                break;
            case SEARCH_STUDENTS_AGE:
                int search_age;
                printf("Enter search age: ");
                scanf("%d", &search_age);
                int index_age = search_student_by_age(&group, search_age);
                if (index_age != -1) {
                    printf("Found student with age %d at position %d.\n", search_age, index_age + 1);
                } else {
                    printf("No student found with age %d.\n", search_age);
                }
                break;
            case SEARCH_STUDENTS_GRADE:
                float search_grade;
                printf("Enter search grade: ");
                scanf("%f", &search_grade);
                int index_grade = search_student_by_grade(&group, search_grade);
                if (index_grade != -1) {
                    printf("Found student with grade %.2f at position %d.\n", search_grade, index_grade + 1);
                } else {
                    printf("No student found with grade %.2f.\n", search_grade);
                }
                break;
            case SORT_STUDENTS: {
                int sort_choice = 0;
                printf("1. Sort by name: \n");
                printf("2. Sort by surname: \n");
                printf("3. Sort by age: \n");
                printf("4. Sort by grade:\n");
                scanf("%d", &sort_choice);
                switch (sort_choice) {
                    case 1:
                        sort_students(&group, 1);
                    printf("Students sorted by name:\n");
                    print_students(&group);
                    break;
                    case 2:
                        sort_students(&group, 2);
                    printf("Students sorted by surname:\n");
                    print_students(&group);
                    break;
                    case 3:
                        sort_students(&group, 3);
                    printf("Students sorted by age:\n");
                    print_students(&group);
                    break;
                    case 4:
                        sort_students(&group, 4);
                    printf("Students sorted by grade:\n");
                    print_students(&group);
                    break;
                    default:printf("Invalid sort choice.\n");
                }
                choice = 0;
                break;
            }
            case PUSH_FRONT:
                push_front(&group);
            break;
            case PUSH_BACK:
                push_back(&group);
            break;
            case INSERT_AT_INDEX:
                int position = 0;
            printf("Enter position: ");
            scanf("%d", &position);
                insert_student_at_position(&group, position);
            position = 0;
            printf("Student inserted successful\n");
            break;
            case REMOVE_AT_INDEX:
                printf("Enter position: ");
            scanf("%d", &position);
                remove_student_at_position(&group, position);
            printf("Student deleted successful\n");
            break;
            case EXIT:
                printf("Exit successful\n");
                for (int i = 0; i < group.student_nr; i++) {
                    free(group.list[i]);
                }
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}
