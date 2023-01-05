#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union utemp {
    int i;
    float f;
    double d;
};

typedef struct {
    int type;
    char name[10];
    union utemp a;
    union utemp b;
} stemp;

void multiply(stemp* s);

int main()
{
    int n;
    int a_1, b_1;
    float a_2, b_2;
    double a_3, b_3;
    stemp* data;

    printf("Number of Iterations : ");
    scanf("%d", &n);

    data = (stemp*)malloc(sizeof(stemp)*n);

    for(int i=0; i<n; i++)
    {
        printf("Type [1 for int, 2 for float, 3 for double] : ");
        scanf("%d", &(data[i].type));
        if(data[i].type == 1)
        {
            printf("Enter an integer value : ");
            scanf("%d %d", &(data[i].a.i), &(data[i].b.i));
            strcpy(data[i].name, "Integer:");
            multiply(&(data[i]));
        }
        else if(data[i].type == 2)
        {
            printf("Enter an float value : ");
            scanf("%f %f", &(data[i].a.f), &(data[i].b.f));
            strcpy(data[i].name, "Float:");
            multiply(&(data[i]));
        }
        else
        {
            printf("Enter an double value : ");
            scanf("%lf %lf", &(data[i].a.d), &(data[i].b.d));
            strcpy(data[i].name, "Double:");
            multiply(&(data[i]));
        }
    }

    printf("\n------------ Result -----------\n");
    for(int i=0; i<n; i++)
    {
        printf("%-10s ", data[i].name);
        if(data[i].type == 1)
        {
            printf("%d\n", data[i].b.i);
        }

        else if(data[i].type == 2)
        {
            printf("%.4f\n", data[i].b.f);
        }

        else
        {
            printf("%.4lf\n", data[i].b.d);
        }
    }

    return 0;
}

void multiply(stemp* s)
{
    if((*s).type == 1)
    {
        (*s).b.i *= (*s).a.i;
    }

    else if((*s).type == 2)
    {
        (*s).b.f *= (*s).a.f;
    }
    
    else
    {
        (*s).b.d *= (*s).a.d;
    }

    return; 
}
