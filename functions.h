#ifndef STUDENTS_FUNCTIONS_H
#define STUDENTS_FUNCTIONS_H

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_menu();
void free_students(List_Of_Students *students);
Student*alloc_student();
void read_student(Student *student);
void print_student(const Student *student);
void print_students(const List_Of_Students *students);
void read_students(List_Of_Students *students);
int search_student_by_name(const List_Of_Students *students, const char *name);
int search_student_by_surname(const List_Of_Students *students, const char *surname);
int search_student_by_age(const List_Of_Students *students, int age);
int search_student_by_grade(const List_Of_Students *students, float grade);
int compare_by_name(const Student *a, const Student *b);
int compare_by_surname(const Student *a, const Student *b);
int compare_by_age(const Student *a, const Student *b);
int compare_by_grade(const Student *a, const Student *b);
void set_comparator(int sort_by);
int compare_students(const void *a, const void *b);
void sort_students(List_Of_Students *students, int sort_by);
void push_front(List_Of_Students *students);
void push_back(List_Of_Students *students);
void insert_student_at_position(List_Of_Students *students, int position);
void remove_student_at_position(List_Of_Students *students, int position);


#endif
