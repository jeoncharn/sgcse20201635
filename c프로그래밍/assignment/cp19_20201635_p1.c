#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char dept_name[25];
    int dept_no;
} dept;

enum Gender {Male = 0, Female};

typedef struct {
    int employee_id;
    char name[40];
    enum Gender gender;
    dept department;
    double salary;
} employee_data;

int search(employee_data* e, int num, int keyword);
employee_data update(employee_data e, int n);

int main()
{
    int n, id, depart, i;
    char contin ='y';
    char temp[10];
    employee_data* data;
    
    char* filename = "19_input.txt";
    FILE* stream = fopen(filename, "r");
	fscanf(stream, "%d", &n);
    data = (employee_data*)malloc(sizeof(employee_data)*n);

    for(int i=0; i<n; i++)
    {
        fscanf(stream, "\n%d / %40[^/]/ %s / %s / %d / %lf", &(data[i].employee_id), (data[i].name), temp, (data[i].department.dept_name), &(data[i].department.dept_no), &(data[i].salary));
        
        if(strcmp(temp, "Male")==0)
        {
            data[i].gender = Male;
        } 
        else 
        {
            data[i].gender = Female;
        }
    }
    
    while(contin=='y')
    {
        printf("Employee ID : ");
        scanf("%d", &id);
		printf("%d\n", id);
        i=search(data, n, id);
        
		if(i!=-1)
        {
            printf("------Enmployee Data------\n");
            printf("%d / %s / ", data[i].employee_id, data[i].name);
            
			if((data[i].gender) == 0)
            {
                printf("%s / %s / %d / %.2lf\n", "Male", data[i].department.dept_name, data[i].department.dept_no, data[i].salary);
            }
            else
            {
                printf("%s / %s / %d / %.2lf\n", "Female", data[i].department.dept_name, data[i].department.dept_no, data[i].salary);
            }
        
            printf("------Update Information------\n");
            printf("Input the department Number : ");
            scanf("%d", &depart);
            update(data[i], depart);

            data[i].department.dept_no = depart;

	        if(depart==1)
	        {
		    strcpy(data[i].department.dept_name, "FINANCE");
    	    }

	        else if(depart==2)
	        {
		        strcpy(data[i].department.dept_name, "SALES");
	        }

        	else if(depart==3)
        	{
        		strcpy(data[i].department.dept_name, "RESEARCH");
        	}

        	else if(depart==4)
        	{
        		strcpy(data[i].department.dept_name, "PLANNING");
            }

            printf("------Updated employee data------\n");
            printf("%d / %s / ", data[i].employee_id, data[i].name);
            
			if((data[i].gender) == 0)
			{
                printf("%s / %s / %d / %.2lf\n", "Male", data[i].department.dept_name, data[i].department.dept_no, data[i].salary);
            }
            else
            {
                printf("%s / %s / %d / %.2lf\n", "Female", data[i].department.dept_name, data[i].department.dept_no, data[i].salary);
            }
        }

        else
        {
            printf("No employee\n");
        }

		getc(stdin);
        printf("Continue? (y/n) : ");
        scanf("%c", &contin);
	}
}

int search(employee_data* e, int num, int keyword)
{
    for(int i=0; i<num; i++)
    {
        if(e[i].employee_id == keyword)
        {
            return i;
        }
    }

    return -1;
}

employee_data update(employee_data e, int n)
{
	e.department.dept_no = n;

	if(n==1)
	{
		strcpy(e.department.dept_name, "FINANCE");
	}

	else if(n==2)
	{
		strcpy(e.department.dept_name, "SALES");
	}

	else if(n==3)
	{
		strcpy(e.department.dept_name, "RESEARCH");
	}

	else if(n==4)
	{
		strcpy(e.department.dept_name, "PLANNING");
	}



	return e;
}
