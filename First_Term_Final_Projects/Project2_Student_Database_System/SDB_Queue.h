/*
 * SDB_Queue.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Mahmoud Essam
 */

#ifndef SDB_QUEUE_H_
#define SDB_QUEUE_H_
#define element_type SData_t
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DPRINTF(...)	{fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}

// Data types Definition
typedef struct
{
	int ID;
	float GPA;
	char FName[40];
	char LName[40];
	int course_id[5];
}SData_t;

typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type* head;
	element_type* base;
	element_type* tail;
}DataBase_t;

typedef enum
{
	DataBase_no_error,
	DataBase_full,
	DataBase_empty,
	DataBase_null
}DataBase_status;

// APIs

DataBase_status DataBase_init(DataBase_t* Database,element_type* arr);
DataBase_status Add_Student_Manually(DataBase_t* Database);
DataBase_status Add_Students_From_File(DataBase_t* Database);
DataBase_status Find_Student_By_ID(DataBase_t* Database);
DataBase_status Find_Student_By_FName(DataBase_t* Database);
DataBase_status Find_Students_in_Course(DataBase_t* Database);
DataBase_status view_All(DataBase_t* Database);
DataBase_status print_student_count(DataBase_t* Database);
DataBase_status Update_Student(DataBase_t* Database);
DataBase_status Delete_Student(DataBase_t* Database,element_type* arr);
#endif /* SDB_QUEUE_H_ */
