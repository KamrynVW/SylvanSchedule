#include <stdio.h>
#include <stdlib.h>

// Student class for student details and schedule restrictions
typedef struct {
    char * name;
    int subjects;
    int stuId;
    int * notWith;
    int mustBeWith;
    char * desc;
} student;

// Table class for students
typedef struct {
    student * atTable;
    int id;
} table;

// Table hours class for the several hours tables are open
typedef struct {
    int id;
    bool isBr;
    table * hrs;
} table_hours;

// Day class of different table schedules
typedef struct {
    table_hours * tables;
} day;

// Schedule class for all possible days open with student and teacher 
typedef struct {
    day * mon;
    day * tue;
    day * wed;
    day * thur;
    day * fri;
    day * sat;
    int totalStudentHours;
    int totalTeacherHours;
} weekly_schedule;