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

int main() {
    student * student1 = new_student("Joe", 1, 22, 1, 7, "Cool dude!");
    student * student2 = new_student("Harry", 2, 32, 6, 7, "Cool dude!");
    student * student3 = new_student("Ben", 3, 25, 1, 5, "Cool dude!");

    table * exampleTable = (table*)malloc(sizeof(table));
    exampleTable->atTable = NULL;

    add_student_to_table(student1, exampleTable);
    add_student_to_table(student2, exampleTable);
    add_student_to_table(student3, exampleTable);

    student * student4 = new_student("Kent", 1, 22, 1, 7, "Cool dude!");
    student * student5 = new_student("Barry", 2, 32, 6, 7, "Cool dude!");
    student * student6 = new_student("Todd", 3, 25, 1, 5, "Cool dude!");

    table * exampleTable2 = (table*)malloc(sizeof(table));
    exampleTable2->atTable = NULL;

    add_student_to_table(student4, exampleTable2);
    add_student_to_table(student5, exampleTable2);
    add_student_to_table(student6, exampleTable2);

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

    // Free all used memory currently allocated in the main process
    tableNode *free_ptr = exampleHours->tablesByHour;
    while (free_ptr != NULL) {
        tableNode *table_next = free_ptr->next;

        // Free all students in this table
        studentNode *student_curr = free_ptr->data->atTable;
        while (student_curr != NULL) {
            studentNode *student_next = student_curr->next;

            free(student_curr->data->name);
            free(student_curr->data->desc);
            free(student_curr->data);
            free(student_curr);

            student_curr = student_next;
        }

        free(free_ptr->data);
        free(free_ptr);

        free_ptr = table_next;
    }

    free(exampleHours);

    return 0;
}