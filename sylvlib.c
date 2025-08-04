#include "sylvlib.h"
#include <string.h>

// Create a new student with passed parameters
student * new_student(char * name, int subjects, int id, int notWithAmount, int mustBeWith, char * desc) {

    student * std = (student*)malloc(sizeof(student)); // Allocate memory for new student

    if(std == NULL) return NULL; // Return if malloc fail

    // Assign values and use copy for dynamic list sizes
    std->name = malloc(strlen(name) + 1);
    if (std->name) strcpy(std->name, name);
    std->subjects = subjects;
    std->stuId = id;
    //std->notWith = notWith; //This is not currently right; will be fixed
    std->notWithAmt = notWithAmount;
    std->mustBeWith = mustBeWith;
    std->desc = malloc(strlen(desc) + 1);
    if (std->desc) strcpy(std->desc, desc);

    return std;
}

// Add a student to a table's LL
void add_student_to_table(student * std, table * t) {

    studentNode * newNode = (studentNode*)malloc(sizeof(studentNode)); // Allocate memory for new node

    if(newNode == NULL) return; // Return if malloc fail

    // Assign data to node and place at front of list
    newNode->data = std;
    newNode->next = t->atTable;
    t->atTable = newNode;
}

// Add a set up table to a schedule of tables
void add_table_to_schedule(table_hours * tblHrs, table * t) {

    tableNode * newNode = (tableNode*)malloc(sizeof(tableNode)); // Allocate memory for new node

    if(newNode == NULL) return; // Return if malloc fail

    // Assign data to node and place at front of list
    newNode->data = t;
    newNode->next = NULL;

    if(tblHrs->tablesByHour == NULL) {
        tblHrs->tablesByHour = newNode;
    } else {
        tableNode * temp = tblHrs->tablesByHour;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
}

// Add a table_hours to a day's array of hours
void add_table_hours_to_day(table_hours * tblHrs, day * d) {

    if (tblHrs == NULL || d == NULL) return;
    if (d->count >= 10) return; // prevent overflow

    // Assign the table_hours to the next available slot in the day's array
    d->tables[d->count] = *tblHrs;
    d->count++;
}

void add_day_to_schedule(weekly_schedule * ws, day * d) {
    if (ws == NULL || d == NULL) return;

    // Assign the day to the appropriate day in the weekly schedule
    switch (d->dayId) {
        case 0: ws->mon = d; break;
        case 1: ws->tue = d; break;
        case 2: ws->wed = d; break;
        case 3: ws->thur = d; break;
        case 4: ws->fri = d; break;
        case 5: ws->sat = d; break;
        default: return; // Invalid dayId
    }
}

int main() {

    student *students[] = {
        new_student("Joe", 1, 22, 1, 7, "Cool dude!"),
        new_student("Harry", 2, 32, 6, 7, "Cool dude!"),
        new_student("Ben", 3, 25, 1, 5, "Cool dude!"),
        new_student("Kent", 1, 22, 1, 7, "Cool dude!"),
        new_student("Barry", 2, 32, 6, 7, "Cool dude!"),
        new_student("Todd", 3, 25, 1, 5, "Cool dude!")
    };
    int student_count = sizeof(students) / sizeof(students[0]);

    table * exampleTable = (table*)malloc(sizeof(table));
    exampleTable->atTable = NULL;

    add_student_to_table(students[0], exampleTable);
    add_student_to_table(students[1], exampleTable);
    add_student_to_table(students[2], exampleTable);

    table * exampleTable2 = (table*)malloc(sizeof(table));
    exampleTable2->atTable = NULL;

    add_student_to_table(students[3], exampleTable2);
    add_student_to_table(students[4], exampleTable2);
    add_student_to_table(students[1], exampleTable2);

    table_hours * exampleHours = (table_hours*)malloc(sizeof(table_hours));
    exampleHours->tablesByHour = NULL;
    exampleHours->isBr = false;

    add_table_to_schedule(exampleHours, exampleTable);
    add_table_to_schedule(exampleHours, exampleTable2);

    // Print student names in table schedule without changing LL
    tableNode *print_ptr = exampleHours->tablesByHour;
    while (print_ptr != NULL) {
        studentNode *stuPtr = print_ptr->data->atTable;
        while (stuPtr != NULL) {
            printf("%s\n", stuPtr->data->name);
            stuPtr = stuPtr->next;
        }
        print_ptr = print_ptr->next;
    }


    // Create a day and add the table_hours to it
    day * exampleDay = (day*)malloc(sizeof(day));
    exampleDay->count = 0;
    exampleDay->dayId = 0; // Assuming 0 for Monday
    add_table_hours_to_day(exampleHours, exampleDay);

    weekly_schedule * ws = (weekly_schedule*)malloc(sizeof(weekly_schedule));
    add_day_to_schedule(ws, exampleDay);

    // Free all used memory currently allocated in the main process
    tableNode *free_ptr = exampleHours->tablesByHour;
    while (free_ptr != NULL) {
        tableNode *table_next = free_ptr->next;

        // Free all students in this table
        studentNode *student_curr = free_ptr->data->atTable;
        while (student_curr != NULL) {
            studentNode *student_next = student_curr->next;

            free(student_curr);

            student_curr = student_next;
        }

        free(free_ptr->data);
        free(free_ptr);

        free_ptr = table_next;
    }

    free(exampleHours);
    free(exampleDay);
    free(ws);

    for (int i = 0; i < student_count; ++i) {
        free(students[i]->name);
        free(students[i]->desc);
        free(students[i]);
    }

    return 0;
}