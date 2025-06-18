#include "functions.h"
StudentComparator comparator = nullptr;

void print_menu() {
    printf("\n1. Read student data\n");
    printf("2. Print students list\n");
    printf("3. Search student by name\n");
    printf("4. Search student by surname\n");
    printf("5. Search student by age\n");
    printf("6. Search student by grade\n");
    printf("7. Sort students\n");
    printf("8. Push front\n");
    printf("9. Push back\n");
    printf("10. Insert student at given position\n");
    printf("11. Remove student at given position\n");
    printf("12. Exit\n");
}

Student *alloc_student() {
    Student *s = (Student *)malloc(sizeof(Student));
    if (s == NULL) {
        return nullptr;
    }
    return s;
}

void free_students(List_Of_Students *students) {
    for (int i = 0; i < students->student_nr; i++) {
        free(students->list[i]);
        students->list[i] = nullptr;
    }
    students->student_nr = 0;
}

void read_student(Student *student) {
    printf("Enter student data:\n");
    printf("Name: ");
    scanf(" %s", student->name);

    printf("Surname: ");
    scanf(" %s", student->surname);

    printf("Age: ");
    scanf("%d", &student->age);

    printf("Grade: ");
    scanf("%f", &student->grade);
}

void print_student(const Student *student) {
    printf("Name: %s, Surname: %s, Age: %d, Grade: %.2f\n",
           student->name, student->surname, student->age, student->grade);
}

void print_students(const List_Of_Students *students) {
    if (students->student_nr == 0) {
        return;
    }

    for (int i = 0; i < students->student_nr; i++) {
        print_student(students->list[i]);
    }
}

void read_students(List_Of_Students *students) {
    free_students(students);

    printf("How many students to enter? ");
    scanf("%d", &students->student_nr);

    for (int i = 0; i < MAX_STUDENTS; i++) {
        students->list[i] = nullptr;
    }

    for (int i = 0; i < students->student_nr; i++) {
        students->list[i] = alloc_student();
        if (students->list[i] == NULL) {
            free_students(students);
            exit(1);
        }
        printf("\nEnter data for student %d:\n", i + 1);
        read_student(students->list[i]);
    }
}
int search_student_by_name(const List_Of_Students *students, const char *name) {
    for (int i = 0; i < students->student_nr; i++) {
        if (strcmp(students->list[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int search_student_by_surname(const List_Of_Students *students, const char *surname) {
    for (int i = 0; i < students->student_nr; i++) {
        if (strcmp(students->list[i]->surname, surname) == 0) {
            return i;
        }
    }
    return -1;
}

int search_student_by_age(const List_Of_Students *students, int age) {
    for (int i = 0; i < students->student_nr; i++) {
        if (students->list[i]->age == age) {
            return i;
        }
    }
    return -1;
}

int search_student_by_grade(const List_Of_Students *students, float grade) {
    for (int i = 0; i < students->student_nr; i++) {
        if (students->list[i]->grade == grade) {
            return i;
        }
    }
    return -1;
}

int compare_by_name(const Student *a, const Student *b) {
    return strcmp(a->name, b->name);
}

int compare_by_surname(const Student *a, const Student *b) {
    return strcmp(a->surname, b->surname);
}

int compare_by_age(const Student *a, const Student *b) {
    return a->age - b->age;
}

int compare_by_grade(const Student *a, const Student *b) {
    if (a->grade > b->grade) return 1;
    if (a->grade < b->grade) return -1;
    return 0;
}


void set_comparator(int sort_by) {
    switch (sort_by) {
        case 1:
            comparator = compare_by_name;
        break;
        case 2:
            comparator = compare_by_surname;
        break;
        case 3:
            comparator = compare_by_age;
        break;
        case 4:
            comparator = compare_by_grade;
        break;
        default:
            comparator = nullptr;
        break;
    }
}


int compare_students(const void *a, const void *b) {
    Student *student_a = *(Student **)a;
    Student *student_b = *(Student **)b;

    if (comparator) {
        return comparator(student_a, student_b);
    }
    return 0;
}

void sort_students(List_Of_Students *students, int sort_by) {
    set_comparator(sort_by);
    qsort(students->list, students->student_nr, sizeof(Student *), compare_students);
}



void push_front(List_Of_Students *students) {
    if (students->student_nr >= MAX_STUDENTS) {
        return;
    }

    Student *new_student = alloc_student();
    if (new_student == NULL) {
        exit(1);
    }
    read_student(new_student);

    for (int i = students->student_nr; i > 0; i--) {
        students->list[i] = students->list[i - 1];
    }

    students->list[0] = new_student;
    students->student_nr++;
}

void push_back(List_Of_Students *students) {
    if (students->student_nr >= MAX_STUDENTS) {
        return;
    }

    Student *new_student = alloc_student();
    if (new_student == NULL) {
        exit(1);
    }
    read_student(new_student);

    students->list[students->student_nr] = new_student;
    students->student_nr++;
}

void insert_student_at_position(List_Of_Students *students, int position) {
    if (position < 0 || position > students->student_nr || students->student_nr >= MAX_STUDENTS) {
        return;
    }

    Student *new_student = alloc_student();
    if (new_student == NULL) {
        return;
    }
    read_student(new_student);

    for (int i = students->student_nr; i > position; i--) {
        students->list[i] = students->list[i - 1];
    }

    students->list[position] = new_student;
    students->student_nr++;
}


void remove_student_at_position(List_Of_Students *students, int position) {
    if (position < 0 || position >= students->student_nr) {
        return ;
    }

    free(students->list[position]);

    for (int i = position; i < students->student_nr - 1; i++) {
        students->list[i] = students->list[i + 1];
    }

    students->student_nr--;
}

