#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Sex { Male=0, Female };
typedef struct {
    float mid, final, proj; 
} Points;

typedef struct {
    int studentId;
    char name[40];
    enum Sex sex;
    Points subject;
    double gd;
    char grade[3];
} Grades;

typedef struct {
    Grades gr;
} Ranking;

int main(){
    int cnt, i, j, A_temp, B_temp;

    float a_grade, b_grade;
    char temp[1024], name_temp[30];
    Grades* grade;
    Grades gtemp;
    Ranking* ranks;

    scanf("%d", &cnt);

    A_temp = cnt * 0.3 - 1;
    B_temp = cnt * 0.7 - 1;

    grade = (Grades*)malloc(sizeof(Grades)*cnt);
    ranks = (Ranking*)malloc(sizeof(Ranking)*cnt);

    for(i=0; i<cnt; i++){
        scanf("%d / %s %s / %s / %f / %f / %f\n", &grade[i].studentId, grade[i].name, name_temp, temp, &((grade[i].subject).mid), &(grade[i].subject).final, &(grade[i].subject).proj);
        strcat(grade[i].name, " ");
        strcat(grade[i].name, name_temp);
        grade[i].gd = (grade[i].subject).mid*0.3 + (grade[i].subject).final*0.3 + (grade[i].subject).proj*0.4;

        if(strcmp(temp, "Male")==0){
            grade[i].sex = Male;
        } else {
            grade[i].sex = Female;
        }
    }

    for(int i=0; i<cnt; i++)
    {
        ranks[i].gr = grade[i];
    }

    for(int i=0; i<cnt; i++)
    {
        for(int j=0; j<cnt-i-1; j++)
        {
            if(ranks[j].gr.gd<ranks[j+1].gr.gd)
            {
                Grades gdchange = ranks[j].gr;
                ranks[j].gr = ranks[j+1].gr;
                ranks[j+1].gr = gdchange;
            }
        }
    }

    for(i=0; i<cnt; i++){
        grade[i] = ranks[i].gr;
		
		if(i<=A_temp)
		{
			strcpy(grade[i].grade, "A+");
		}
		else if(i<=B_temp)
		{
			strcpy(grade[i].grade, "B+");
		}
		else
		{
			strcpy(grade[i].grade, "C+");
		}

		if(grade[i].gd<50)
		{
			strcpy(grade[i].grade, "F");
		}

    }

    printf("-- Student List --\n");
    for(i=0; i<cnt; i++){
        printf("    Id : %d\n", grade[i].studentId);
        if(grade[i].sex == 0) 
            printf("    Name : %s (%s)\n", grade[i].name, "Male");
        else 
            printf("    Name : %s (%s)\n", grade[i].name, "Female");

        printf("    Grade(mid) : %.02f\n", (grade[i].subject).mid);
        printf("    Grade(final) : %.02f\n", (grade[i].subject).final);
        printf("    Grade(project) : %.02f\n", (grade[i].subject).proj);
        printf("    Grade : %s(%.02f %d)\n", grade[i].grade, grade[i].gd, i);
        printf("\n");

    }

}




