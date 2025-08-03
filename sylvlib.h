#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Student class for student details and schedule restrictions
typedef struct student {
    char * name;
    int subjects;
    int stuId;
    int * notWith;
    int notWithAmt;
    int mustBeWith;
    char * desc;
} student;

// Student node structure for table's linked list
typedef struct studentNode {
    student * data;
    struct studentNode * next;
} studentNode;

// Table class for students
typedef struct table {
    studentNode * atTable;
} table;

typedef struct tableNode {
    table * data;
    struct tableNode * next;
} tableNode;

// Table hours class for the several hours tables are open
typedef struct table_hours {
    bool isBr;
    tableNode * tablesByHour;
} table_hours;

// Day class of different table schedules
typedef struct day {
    table_hours tables[10];
} day;

// Schedule class for all possible days open with student and teacher 
typedef struct weekly_schedule {
    day * mon;
    day * tue;
    day * wed;
    day * thur;
    day * fri;
    day * sat;
    int totalStudentHours;
    int totalTeacherHours;
} weekly_schedule;

student * new_student(char * name, int subjects, int id, int notWithAmount, int mustBeWith, char * desc);

void add_student_to_table(student * std, table * t);

void add_table_to_schedule(table_hours * tblHrs, table * t);