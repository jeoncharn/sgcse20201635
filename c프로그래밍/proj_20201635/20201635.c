//
//  main.c
//  project
//
//  Created by Jeon Charn on 2020/12/07.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum Sex { Male = 0, Female };
enum PClass { First = 1, Second, Third };
typedef struct {
    int passengerId;
    int survival;
    char* name;
    enum Sex sex;
    float age;
    int sibsp;
    int parch;
    char* ticket;
    char* cabin;
    char* embarked;
    double fare;
    enum PClass pclass;
} SUVData;

int ReadData(SUVData*** dataset, char* filename);
void StatsBySex(SUVData** data, int N);
void StatsByFamily(SUVData** dataset, int N);
void StatsByAge(SUVData** dataset, int N);
void CalCorrelationMatrix(SUVData** dataset, int N);
void KNN(SUVData** dataset, int N, int K);
void KFoldValidation(SUVData** dataset, int N, int nFolds, int K);

int main(int argc, char** argv)
{
    int menu;
    int number;
    int K;
    int nF;
    SUVData** alldata = NULL;
    number = ReadData(&alldata, *(argv + 1));
    
    printf("[타이타닉 생존자 데이터 분석 - 메뉴를 선택하시오]\n");
    printf("1. 성별 기준 생존자 수 비율\n");
    printf("2. 가족 관계 별 생존자 수 비율\n");
    printf("3. 나이대 별 생존자 수 비율\n");
    printf("4. Correlation Matrix 계산하기\n");
    printf("5. 최근접 이웃 알고리즘으로 생존자 수 예측하기\n");
    printf("6. K-Fold Validation\n");
    printf("7. 프로그램 종료\n");
    
    while(1)
    {
        printf("\n\n[명령 입력] > ");
        scanf("%d", &menu);
        
        if(menu == 7)  // while 문으로 구성
        {
            printf("program ended\n");
            break;
        }
            
        else
        {
            switch(menu)
            {
                case 1:
                    StatsBySex(alldata, number);
                    break;
    
                case 2:
                    StatsByFamily(alldata, number);
                    break;
            
                case 3:
                    StatsByAge(alldata, number);
                    break;
                    
                case 4:
                    CalCorrelationMatrix(alldata, number);
                    break;
            
                case 5:
                    printf("Input K: ");
                    scanf("%d", &K);
                    
                    if(K<=0)
                    {
                        printf("Input Error!\n");
                    }
                    else
                    {
                        KNN(alldata, number, K);
                        break;
                    }
                case 6:
                    printf("Input nFolds and K: ");
                    scanf("%d %d", &nF, &K);
                    if(nF<=0 || K<=0)
                    {
                        printf("Input Error!\n");
                    }
                    else
                    {
                        KFoldValidation(alldata, number, nF, K);
                    }
            }
        }
    }

    return 0;
}

int ReadData(SUVData*** dataset, char* filename)
{
    int i=1;
    int count=0;
    int pclass_save;
    int sursave;
    FILE* fp;
    char* sex_save = (char*)calloc(10, sizeof(char));
    (*dataset) = (SUVData**)calloc(1, sizeof(SUVData*));
    fp = fopen(filename, "r");

    while (1)
    {
        if (i <= (count+1))
        {
            i = 2 * i;
            *dataset = (SUVData**)realloc((*dataset), i*sizeof(SUVData*));
        }

        *(*dataset + count) = (SUVData*)calloc(1, sizeof(SUVData));
        ((*(*dataset + count))->name) = (char*)calloc(50, sizeof(char));
        ((*(*dataset + count))->ticket) = (char*)calloc(50, sizeof(char));
        ((*(*dataset + count))->cabin) = (char*)calloc(50, sizeof(char));
        ((*(*dataset + count))->embarked) = (char*)calloc(50, sizeof(char));

        if (EOF != fscanf(fp, "%d,%d,%d,%[^,],%[^,],%f,%d,%d,%[^,], %lf, %[^,],%[^\n]", &((*(*dataset + count))->passengerId), &sursave, &pclass_save,((*(*dataset + count))->name), sex_save, &((*(*dataset + count))->age), &((*(*dataset + count))->sibsp), &((*(*dataset + count))->parch), ((*(*dataset + count))->ticket), &((*(*dataset + count))->fare), ((*(*dataset + count))->cabin), ((*(*dataset + count))->embarked)))
        {
            
            if(strcmp(sex_save, "male")==0)
            {
                (*(*dataset + (count)))->sex = 0;
            }

            else
            {
                (*(*dataset + count))->sex = 1;
            }

            if(pclass_save == 1)
            {
                (*(*dataset + count))->pclass = 1;
            }

            else if(pclass_save == 2)
            {
                (*(*dataset + count))->pclass = 2;
            }

            else
            {
                (*(*dataset + count))->pclass = 3;
            }
            ((*(*dataset + count))->survival) = sursave;
        }

        else
        {
            break;
        }
        
        count = count + 1;
    }

    return count;
}

void StatsBySex(SUVData** data, int N)
{
    int male_num = 0;
    int male_survive = 0;
    int female_num = 0;
    int female_survive = 0;

    for(int i=0; i<N; i++)
    {
        if(((*(data + i))->sex)==Male)
        {
            male_num++;
            if(((*(data + i))->survival)==1)
            {
                male_survive++;
            }
            
        }
        else
        {
            female_num++;
            if(((*(data + i))->survival)==1)
            {
                female_survive++;
            }
        }
        
    }
    
    printf("%-15s%-15s\n", " ", "Sex");
    printf("%-15s%-15s%-15s\n", " ", "Female", "Male");
    printf("%-15s%-15d%-15d\n", "Survived", female_survive, male_survive);
    printf("%-15s%-15d%-15d\n", "Dead", female_num-female_survive, male_num-male_survive);
    printf("%-15s%-15.2f%-15.2f (%%)\n", "ratio", 100*((float)female_survive)/female_num, 100*((float)male_survive)/male_num);

    return;
}

void StatsByFamily(SUVData** dataset, int N)
{
    int per0=0, per1=0, per2=0, per3=0, per4=0, per5=0, per6=0, per7=0, per_else=0;
    int sur0=0, sur1=0, sur2=0, sur3=0, sur4=0, sur5=0, sur6=0, sur7=0, sur_else=0;
    for(int i=0; i<N; i++)
    {
        switch(((*(dataset + i))->sibsp)+((*(dataset + i))->parch))
        {
            case 0:
                per0++;
                if((*(dataset + i))->survival==1)
                {
                    sur0++;
                }
                break;
            
            case 1:
                per1++;
                if((*(dataset + i))->survival==1)
                {
                    sur1++;
                }
                break;
                
            case 2:
                per2++;
                if((*(dataset + i))->survival==1)
                {
                    sur2++;
                }
                break;
                
            case 3:
                per3++;
                if((*(dataset + i))->survival==1)
                {
                    sur3++;
                }
                break;
                
            case 4:
                per4++;
                if((*(dataset + i))->survival==1)
                {
                    sur4++;
                }
                break;
                
            case 5:
                per5++;
                if((*(dataset + i))->survival==1)
                {
                    sur5++;
                }
                break;
                
            case 6:
                per6++;
                if((*(dataset + i))->survival==1)
                {
                    sur6++;
                }
                break;
                
            case 7:
                per7++;
                if((*(dataset + i))->survival==1)
                {
                    sur7++;
                }
                break;
                
            default:
                per_else++;
                if((*(dataset + i))->survival==1)
                {
                    sur_else++;
                }
                break;
                
        }
    }
    printf("%-15s%-s\n", " ", "Family Size");
    printf("%-15s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n", "", "0", "1", "2", "3", "4", "5", "6", "7", ">7");
    printf("%-15s%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n", "Survived", sur0, sur1, sur2, sur3, sur4, sur5, sur6, sur7, sur_else);
    printf("%-15s%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d%-10d\n", "Dead", per0-sur0, per1-sur1, per2-sur2, per3-sur3, per4-sur4, per5-sur5, per6-sur6, per7-sur7, per_else-sur_else);
    printf("%-15s", "ratio");
    if(per0==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur0/per0);
    }
    
    if(per1==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur1/per1);
    }
    
    if(per2==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur2/per2);
    }
    
    if(per3==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur3/per3);
    }
    
    if(per4==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur4/per4);
    }
    
    if(per5==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur5/per5);
    }
    
    if(per6==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur6/per6);
    }
    
    if(per7==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur7/per7);
    }
    
    if(per_else==0)
    {
        printf("%-10.2f", 0.0);
    }
    else
    {
        printf("%-10.2f", 100*(float)sur_else/per_else);
    }
    printf(" (%%)\n");
    
    return;
}

void StatsByAge(SUVData** dataset, int N)
{
    int sizediv;
    
    printf("Input division: ");
    scanf("%d", &sizediv);
    
    int* arr_alive = (int*)malloc(sizeof(int)*sizediv);
    int* arr_per = (int*)malloc(sizeof(int)*sizediv);
    
    for(int i=0; i<sizediv; i++)
    {
        *(arr_alive + i) = 0;
        *(arr_per + i) = 0;
    }
    
    for(int i=0; i<sizediv; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(((*(dataset + j))->age>=(100*i/sizediv))&&((*(dataset + j))->age<(100*(i+1)/sizediv)))
            {
                *(arr_per + i) = *(arr_per + i) + 1;
                if((*(dataset + j))->survival == 1)
                {
                    *(arr_alive + i) = *(arr_alive + i) + 1;
                }
            }
        }
    }
    printf("%15s%s\n", "", "aboutage");
    printf("%-15s", "Survived");
    for(int i=0; i<sizediv; i++)
    {
        printf("%-10d", arr_alive[i]);
    }
    printf("\n");
    printf("%-15s", "Dead");
    for(int i=0; i<sizediv; i++)
    {
        printf("%-10d", arr_per[i]-arr_alive[i]);
    }
    printf("\n");
    printf("%-15s", "ratio");
    for(int i=0; i<sizediv; i++) //바꾸기
    {
        if(arr_per[i]==0)
        {
            printf("%-10.2f", 0.0);
        }
        else
        {
            printf("%-10.2f", 100*(float)(arr_alive[i])/arr_per[i]);
        }
    }
    printf("(%%)");
    printf("\n");
    
    return;
}

void CalCorrelationMatrix(SUVData** dataset, int N)
{
    double** corr_matrix;
    corr_matrix = (double**)malloc(sizeof(double*)*7);
    for(int i=0; i<7; i++)
    {
        *(corr_matrix + i) = (double*)malloc(sizeof(double)*7);
        *(*(corr_matrix + i)) = 0;
    }
    double** savedata;
    savedata = (double**)malloc(sizeof(double*)*7);
    for(int i=0; i<N; i++)
    {
        *(savedata + i) = (double*)malloc(sizeof(double)*N);
    }
    
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 0) + i) =(double)(*(dataset + i))->survival;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 1) + i) =(double)(*(dataset + i))->pclass;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 2) + i) =(double)(*(dataset + i))->sex;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 3) + i) =(double)(*(dataset + i))->age;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 4) + i) =(double)(*(dataset + i))->sibsp;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 5) + i) =(double)(*(dataset + i))->parch;
    }
    for(int i=0; i<N; i++)
    {
        *(*(savedata + 6) + i) =(double)(*(dataset + i))->fare;
    }
    
    double* matrix_mean;
    matrix_mean = (double*)malloc(sizeof(double)*7);
    *matrix_mean=0;
    
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 0)) += (double)(*(dataset + i))->survival/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 1)) += (double)(*(dataset + i))->pclass/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 2)) += (double)(*(dataset + i))->sex/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 3)) += (double)(*(dataset + i))->age/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 4)) += (double)(*(dataset + i))->sibsp/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 5)) += (double)(*(dataset + i))->parch/N;
    }
    for(int i=0; i<N; i++)
    {
        (*(matrix_mean + 6)) += (double)(*(dataset + i))->fare/N;
    }
    
    double* stdev;
    stdev = (double*)malloc(sizeof(double)*7);
    *stdev=0;
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<N; j++)
        {
            *(stdev + i) += pow(*(*(savedata + i) + j) - *(matrix_mean + i), 2);
        }
        *(stdev + i) = sqrt(*(stdev + i));
    }
    
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<7; j++)
        {
            for(int k=0; k<N; k++)
            {
                *(*(corr_matrix + i) + j) += (*(*(savedata + i) + k) - *(matrix_mean + i)) * (*(*(savedata + j) + k) - *(matrix_mean + j))/((*(stdev + i))*(*(stdev + j)));
            }
        }
    }
    
    printf("Survival = a, Pclass = b, Sex = c, Age = d, Sibsp = e, Parch = f, Fare = g\n\n");
    printf("%-7s%-7s%-7s%-7s%-7s%-7s%-7s%-7s\n", " ", "a", "b", "c", "d", "e", "f", "g");
    
    printf("%-7s", "a");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 0) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 0) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 0) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "b");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 1) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 1) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 1) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "c");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 2) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 2) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 2) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "d");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 3) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 3) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 3) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "e");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 4) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 4) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 4) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "f");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 5) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 5) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 5) + i));
        }
    }
    printf("\n");
    
    printf("%-7s", "g");
    for(int i=0; i<7; i++)
    {
        if(*(*(corr_matrix + 6) + i)>0)
        {
            printf("+");
            printf("%-6.2lf", *(*(corr_matrix + 6) + i));
        }
        else
        {
            printf("%-7.2lf", *(*(corr_matrix + 6) + i));
        }
    }
    printf("\n");
    
    return;
}

void KNN(SUVData** dataset, int N, int K)
{
    typedef struct {
        float distance;
        int index;
    } Dist;
    
    int number;
    int survive_num=0;
    int predict_num=0;
    
    Dist** dists;
    
    SUVData** P; // 테스트 데이터
    SUVData** Q; // 학습 데이터
    
    
    
    double* min;
    double* max;
    
    min = (double*)malloc(sizeof(double)*6);
    max = (double*)malloc(sizeof(double)*6);
    
    *(min + 0) = (*(dataset + 0))->pclass;
    *(min + 1) = (*(dataset + 0))->sex;
    *(min + 2) = (*(dataset + 0))->age;
    *(min + 3) = (*(dataset + 0))->sibsp;
    *(min + 4) = (*(dataset + 0))->parch;
    *(min + 5) = (*(dataset + 0))->fare;
    
    *(max + 0) = (*(dataset + 0))->pclass;
    *(max + 1) = (*(dataset + 0))->sex;
    *(max + 2) = (*(dataset + 0))->age;
    *(max + 3) = (*(dataset + 0))->sibsp;
    *(max + 4) = (*(dataset + 0))->parch;
    *(max + 5) = (*(dataset + 0))->fare;
    
    for(int i=0; i<N; i++)
    {
        if((*(max + 0))<(*(dataset + i))->pclass)
        {
            *(max + 0) = (*(dataset + i))->pclass;
        }
        if((*(max + 1))<(*(dataset + i))->sex)
        {
            *(max + 1) = (*(dataset + i))->sex;
        }
        if((*(max + 2))<(*(dataset + i))->age)
        {
            *(max + 2) = (*(dataset + i))->age;
        }
        if((*(max + 3))<(*(dataset + i))->sibsp)
        {
            *(max + 3) = (*(dataset + i))->sibsp;
        }
        if((*(max + 4))<(*(dataset + i))->parch)
        {
            *(max + 4) = (*(dataset + i))->parch;
        }
        if((*(max + 5))<(*(dataset + i))->fare)
        {
            *(max + 5) = (*(dataset + i))->fare;
        }
        
        if((*(min + 0))>(*(dataset + i))->pclass)
        {
            *(min + 0) = (*(dataset + i))->pclass;
        }
        if((*(min + 1))>(*(dataset + i))->sex)
        {
            *(min + 1) = (*(dataset + i))->sex;
        }
        if((*(min + 2))>(*(dataset + i))->age)
        {
            *(min + 2) = (*(dataset + i))->age;
        }
        if((*(min + 3))>(*(dataset + i))->sibsp)
        {
            *(min + 3) = (*(dataset + i))->sibsp;
        }
        if((*(min + 4))>(*(dataset + i))->parch)
        {
            *(min + 4) = (*(dataset + i))->parch;
        }
        if((*(min + 5))>(*(dataset + i))->fare)
        {
            *(min + 5) = (*(dataset + i))->fare;
        }
    }
    
    if((float)N*4/5>N*4/5)
    {
        number = N*4/5+1;
        Q = (SUVData**)malloc(sizeof(SUVData*)*(N*4/5+1));
        for(int i=0; i<N*4/5+1; i++)
        {
            *(Q + i) = (SUVData*)malloc(sizeof(SUVData));
            (*(Q + i))->pclass = (*(dataset + i))->pclass;
            (*(Q + i))->sex = (*(dataset + i))->sex;
            (*(Q + i))->age = (*(dataset + i))->age;
            (*(Q + i))->sibsp = (*(dataset + i))->sibsp;
            (*(Q + i))->parch = (*(dataset + i))->parch;
            (*(Q + i))->fare = (*(dataset + i))->fare;
            (*(Q + i))->survival = (*(dataset + i))->survival;
        }
        
        P = (SUVData**)malloc(sizeof(SUVData*)*(N/4));
        for(int i=0; i<N*1/5; i++)
        {
            *(P + i) = (SUVData*)malloc(sizeof(SUVData));
            (*(P + i))->pclass = (*(dataset + N*4/5+1 + i))->pclass;
            (*(P + i))->sex = (*(dataset + N*4/5+1 + i))->sex;
            (*(P + i))->age = (*(dataset + N*4/5+1 + i))->age;
            (*(P + i))->sibsp = (*(dataset + N*4/5+1 + i))->sibsp;
            (*(P + i))->parch = (*(dataset + N*4/5+1 + i))->parch;
            (*(P + i))->fare = (*(dataset + N*4/5+1 + i))->fare;
            (*(P + i))->survival = (*(dataset + N*4/5+1 + i))->survival;
        }
        
        dists = (Dist**)malloc(sizeof(Dist*)*(N*4/5+1));
        for(int i=0; i<N*4/5+1; i++)
        {
            *(dists + i) = (Dist*)malloc(sizeof(Dist));
        }
    }
    else
    {
        number = N*4/5;
        Q = (SUVData**)malloc(sizeof(SUVData*)*(N*4/5));
        for(int i=0; i<N*4/5; i++)
        {
            *(Q + i) = (SUVData*)malloc(sizeof(SUVData));
            (*(Q + i))->pclass = (*(dataset + i))->pclass;
            (*(Q + i))->sex = (*(dataset + i))->sex;
            (*(Q + i))->age = (*(dataset + i))->age;
            (*(Q + i))->sibsp = (*(dataset + i))->sibsp;
            (*(Q + i))->parch = (*(dataset + i))->parch;
            (*(Q + i))->fare = (*(dataset + i))->fare;
            (*(Q + i))->survival = (*(dataset + i))->survival;
        }
        P = (SUVData**)malloc(sizeof(SUVData*)*(N/4));
        for(int i=0; i<N/5; i++)
        {
            *(P + i) = (SUVData*)malloc(sizeof(SUVData));
            (*(P + i))->pclass = (*(dataset + N*4/5 + i))->pclass;
            (*(P + i))->sex = (*(dataset + N*4/5 + i))->sex;
            (*(P + i))->age = (*(dataset + N*4/5 + i))->age;
            (*(P + i))->sibsp = (*(dataset + N*4/5 + i))->sibsp;
            (*(P + i))->parch = (*(dataset + N*4/5 + i))->parch;
            (*(P + i))->fare = (*(dataset + N*4/5 + i))->fare;
            (*(P + i))->survival = (*(dataset + N*4/5 + i))->survival;

        }
        dists = (Dist**)malloc(sizeof(Dist*)*(N*4/5));
        for(int i=0; i<N*4/5; i++)
        {
            *(dists + i) = (Dist*)malloc(sizeof(Dist));
        }
    }
    
    for(int i=0; i<N-number; i++)
    {
        survive_num = 0;
        for(int j=0; j<number; j++)
        {
            ((*(dists + j))->distance) = sqrt(pow(((double)((*(Q + j))->pclass)-*(min + 0))/((*(max + 0)) - (*(min + 0))) - ((double)((*(P + i))->pclass)-*(min + 0))/((*(max + 0)) - (*(min + 0))), 2) + pow(((double)((*(Q + j))-> sex)-*(min + 1))/((*(max + 1)) - (*(min + 1))) - ((double)((*(P + i))->sex)-*(min + 1))/((*(max + 1)) - (*(min + 1))), 2) + pow(((double)((*(Q + j))->age)-*(min + 2))/((*(max + 2)) - (*(min + 2))) - ((double)((*(P + i))->age)-*(min + 2))/((*(max + 2)) - (*(min + 2))), 2) + pow(((double)((*(Q + j))->sibsp)-*(min + 3))/((*(max + 3)) - (*(min + 3))) - ((double)((*(P + i))->sibsp)-*(min + 3))/((*(max + 3)) - (*(min + 3))), 2) + pow(((double)((*(Q + j))->parch)-*(min + 4))/((*(max + 4)) - (*(min + 4))) - ((double)((*(P + i))->parch)-*(min + 4))/((*(max + 4)) - (*(min + 4))), 2) + pow(((double)((*(Q + j))->fare)-*(min + 5))/((*(max + 5)) - (*(min + 5))) - ((double)((*(P + i))->fare)-*(min + 5))/((*(max + 5)) - (*(min + 5))), 2));
            (*(dists + j))->index = j;
        }
        for(int p=0; p<number; p++)
        {
            for(int j=0; j<number-p-1; j++)
            {
                if(((*(dists + j))->distance)>((*(dists + j+1))->distance))
                {
                    double save_1;
                    int save_2;
                    save_1 = (*(dists + j))->distance;
                    save_2 = (*(dists + j))->index;
                    (*(dists + j))->distance = (*(dists + j+1))->distance;
                    (*(dists + j))->index = (*(dists + j+1))->index;
                    (*(dists + j+1))->distance = save_1;
                    (*(dists + j+1))->distance = save_2;
                }
            }
        }

        for(int j=1; j<K+1; j++)
        {
            survive_num += ((*(Q + (*(dists + j))->index)))->survival;
        }
        
        if((float)survive_num/K>=0.5)
        {
            if(((*(P + i))->survival) == 1)
            {
                predict_num++;
            }
        }
        else
        {
            if(((*(P + i))->survival) == 0)
            {
                predict_num++;
            }
        }
        for(int j=1; j<=5; j++)
        {
            if(i==(((N-number)/5)*j))
            {
                printf("[----------%4d/%-4d %4d%%  completed  ----------]\n", (int)(((float)(N-number)/5)*j), N-number, j*20);
            }
        }
    }
    printf("\n");
    printf("Prediction Score: %.2f%%\n", (((float)predict_num)/(N-number))*100);
    
    return;
}

void KFoldValidation(SUVData** dataset, int N, int nFolds, int K)
{
    typedef struct {
        float distance;
        int index;
    } Dist;
    
    int number;
    int survive_num=0;
    int predict_num=0;
    
    Dist** dists;
    SUVData** P; // 테스트 데이터
    SUVData** Q; // 학습 데이터
    
    double* min; // array
    double* max; // array
    
    min = (double*)malloc(sizeof(double)*6);
    max = (double*)malloc(sizeof(double)*6);
    
    *(min + 0) = (*(dataset + 0))->pclass;
    *(min + 1) = (*(dataset + 0))->sex;
    *(min + 2) = (*(dataset + 0))->age;
    *(min + 3) = (*(dataset + 0))->sibsp;
    *(min + 4) = (*(dataset + 0))->parch;
    *(min + 5) = (*(dataset + 0))->fare;
    
    *(max + 0) = (*(dataset + 0))->pclass;
    *(max + 1) = (*(dataset + 0))->sex;
    *(max + 2) = (*(dataset + 0))->age;
    *(max + 3) = (*(dataset + 0))->sibsp;
    *(max + 4) = (*(dataset + 0))->parch;
    *(max + 5) = (*(dataset + 0))->fare;
    
    for(int i=0; i<N; i++)
    {
        if((*(max + 0))<(*(dataset + i))->pclass)
        {
            *(max + 0) = (*(dataset + i))->pclass;
        }
        if((*(max + 1))<(*(dataset + i))->sex)
        {
            *(max + 1) = (*(dataset + i))->sex;
        }
        if((*(max + 2))<(*(dataset + i))->age)
        {
            *(max + 2) = (*(dataset + i))->age;
        }
        if((*(max + 3))<(*(dataset + i))->sibsp)
        {
            *(max + 3) = (*(dataset + i))->sibsp;
        }
        if((*(max + 4))<(*(dataset + i))->parch)
        {
            *(max + 4) = (*(dataset + i))->parch;
        }
        if((*(max + 5))<(*(dataset + i))->fare)
        {
            *(max + 5) = (*(dataset + i))->fare;
        }
        
        if((*(min + 0))>(*(dataset + i))->pclass)
        {
            *(min + 0) = (*(dataset + i))->pclass;
        }
        if((*(min + 1))>(*(dataset + i))->sex)
        {
            *(min + 1) = (*(dataset + i))->sex;
        }
        if((*(min + 2))>(*(dataset + i))->age)
        {
            *(min + 2) = (*(dataset + i))->age;
        }
        if((*(min + 3))>(*(dataset + i))->sibsp)
        {
            *(min + 3) = (*(dataset + i))->sibsp;
        }
        if((*(min + 4))>(*(dataset + i))->parch)
        {
            *(min + 4) = (*(dataset + i))->parch;
        }
        if((*(min + 5))>(*(dataset + i))->fare)
        {
            *(min + 5) = (*(dataset + i))->fare;
        }
    }
    
    for(int r=0; r<nFolds; r++)
    {
        predict_num = 0;
        if((float)N*(nFolds-1)/nFolds > N*(nFolds-1)/nFolds)
        {
            number = (r+1)*N/nFolds - (r)*N/nFolds;
            Q = (SUVData**)malloc(sizeof(SUVData*)*(N-number));
            for(int i=0; i<r*N/nFolds; i++)
            {
                *(Q + i) = (SUVData*)malloc(sizeof(SUVData));
                (*(Q + i))->pclass = (*(dataset + i))->pclass;
                (*(Q + i))->sex = (*(dataset + i))->sex;
                (*(Q + i))->age = (*(dataset + i))->age;
                (*(Q + i))->sibsp = (*(dataset + i))->sibsp;
                (*(Q + i))->parch = (*(dataset + i))->parch;
                (*(Q + i))->fare = (*(dataset + i))->fare;
                (*(Q + i))->survival = (*(dataset + i))->survival;
            }
            
            for(int i=(r+1)*N/nFolds; i<N; i++)
            {
                *(Q + i-number) = (SUVData*)malloc(sizeof(SUVData));
                (*(Q + i-number))->pclass = (*(dataset + i))->pclass;
                (*(Q + i-number))->sex = (*(dataset + i))->sex;
                (*(Q + i-number))->age = (*(dataset + i))->age;
                (*(Q + i-number))->sibsp = (*(dataset + i))->sibsp;
                (*(Q + i-number))->parch = (*(dataset + i))->parch;
                (*(Q + i-number))->fare = (*(dataset + i))->fare;
                (*(Q + i-number))->survival = (*(dataset + i))->survival;
            }
            
            P = (SUVData**)malloc(sizeof(SUVData*)*(number));
            for(int i=r*N/nFolds; i<(r+1)*N/nFolds; i++)
            {
                *(P + i-r*N/nFolds) = (SUVData*)malloc(sizeof(SUVData));
                (*(P + i-r*N/nFolds))->pclass = (*(dataset + i))->pclass;
                (*(P + i-r*N/nFolds))->sex = (*(dataset + i))->sex;
                (*(P + i-r*N/nFolds))->age = (*(dataset + i))->age;
                (*(P + i-r*N/nFolds))->sibsp = (*(dataset + i))->sibsp;
                (*(P + i-r*N/nFolds))->parch = (*(dataset + i))->parch;
                (*(P + i-r*N/nFolds))->fare = (*(dataset  + i))->fare;
                (*(P + i-r*N/nFolds))->survival = (*(dataset + i))->survival;
            }
            
            dists = (Dist**)malloc(sizeof(Dist*)*(N*4/5+1));
            for(int i=0; i<N-number; i++) // 조건 해결
            {
                *(dists + i) = (Dist*)malloc(sizeof(Dist));
            }
        }
        else
        {
            number = N*(nFolds-1)/nFolds;
            Q = (SUVData**)malloc(sizeof(SUVData*)*(N*(nFolds-1)/nFolds));
            for(int i=0; i<r*N/nFolds; i++)
            {
                *(Q + i) = (SUVData*)malloc(sizeof(SUVData));
                (*(Q + i))->pclass = (*(dataset + i))->pclass;
                (*(Q + i))->sex = (*(dataset + i))->sex;
                (*(Q + i))->age = (*(dataset + i))->age;
                (*(Q + i))->sibsp = (*(dataset + i))->sibsp;
                (*(Q + i))->parch = (*(dataset + i))->parch;
                (*(Q + i))->fare = (*(dataset + i))->fare;
                (*(Q + i))->survival = (*(dataset + i))->survival;
            }
            
            for(int i=(r+1)*N/nFolds; i<N; i++)
            {
                *(Q + i-number) = (SUVData*)malloc(sizeof(SUVData));
                (*(Q + i-number))->pclass = (*(dataset + i))->pclass;
                (*(Q + i-number))->sex = (*(dataset + i))->sex;
                (*(Q + i-number))->age = (*(dataset + i))->age;
                (*(Q + i-number))->sibsp = (*(dataset + i))->sibsp;
                (*(Q + i-number))->parch = (*(dataset + i))->parch;
                (*(Q + i-number))->fare = (*(dataset + i))->fare;
                (*(Q + i-number))->survival = (*(dataset + i))->survival;
            }
            
            P = (SUVData**)malloc(sizeof(SUVData*)*(N/nFolds));
            for(int i=r*N/nFolds; i<(r+1)*N/nFolds; i++)
            {
                *(P + i-r*N/nFolds) = (SUVData*)malloc(sizeof(SUVData));
                (*(P + i-r*N/nFolds))->pclass = (*(dataset + i))->pclass;
                (*(P + i-r*N/nFolds))->sex = (*(dataset + i))->sex;
                (*(P + i-r*N/nFolds))->age = (*(dataset + i))->age;
                (*(P + i-r*N/nFolds))->sibsp = (*(dataset + i))->sibsp;
                (*(P + i-r*N/nFolds))->parch = (*(dataset + i))->parch;
                (*(P + i-r*N/nFolds))->fare = (*(dataset  + i))->fare;
                (*(P + i-r*N/nFolds))->survival = (*(dataset + i))->survival;
            }
            dists = (Dist**)malloc(sizeof(Dist*)*(N*4/5));
            for(int i=0; i<N*4/5; i++)
            {
                *(dists + i) = (Dist*)malloc(sizeof(Dist));
            }
        }
        
        for(int i=0; i<number; i++)
        {
            survive_num = 0;
            for(int j=0; j<N-number; j++)
            {
                ((*(dists + j))->distance) = sqrt(pow(((double)((*(Q + j))->pclass)-*(min + 0))/((*(max + 0)) - (*(min + 0))) - ((double)((*(P + i))->pclass)-*(min + 0))/((*(max + 0)) - (*(min + 0))), 2) + pow(((double)((*(Q + j))-> sex)-*(min + 1))/((*(max + 1)) - (*(min + 1))) - ((double)((*(P + i))->sex)-*(min + 1))/((*(max + 1)) - (*(min + 1))), 2) + pow(((double)((*(Q + j))->age)-*(min + 2))/((*(max + 2)) - (*(min + 2))) - ((double)((*(P + i))->age)-*(min + 2))/((*(max + 2)) - (*(min + 2))), 2) + pow(((double)((*(Q + j))->sibsp)-*(min + 3))/((*(max + 3)) - (*(min + 3))) - ((double)((*(P + i))->sibsp)-*(min + 3))/((*(max + 3)) - (*(min + 3))), 2) + pow(((double)((*(Q + j))->parch)-*(min + 4))/((*(max + 4)) - (*(min + 4))) - ((double)((*(P + i))->parch)-*(min + 4))/((*(max + 4)) - (*(min + 4))), 2) + pow(((double)((*(Q + j))->fare)-*(min + 5))/((*(max + 5)) - (*(min + 5))) - ((double)((*(P + i))->fare)-*(min + 5))/((*(max + 5)) - (*(min + 5))), 2));
                (*(dists + j))->index = j;
            }
            for(int p=0; p<N-number; p++)
            {
                for(int j=0; j<N-number-p-1; j++)
                {
                    if(((*(dists + j))->distance)>((*(dists + j+1))->distance))
                    {
                        double save_1;
                        int save_2;
                        save_1 = (*(dists + j))->distance;
                        save_2 = (*(dists + j))->index;
                        (*(dists + j))->distance = (*(dists + j+1))->distance;
                        (*(dists + j))->index = (*(dists + j+1))->index;
                        (*(dists + j+1))->distance = save_1;
                        (*(dists + j+1))->distance = save_2;
                    }
                }
            }

            for(int j=1; j<K+1; j++)
            {
                survive_num += ((*(Q + (*(dists + j))->index)))->survival;
            }
            
            if((float)survive_num/K>=0.5)
            {
                if(((*(P + i))->survival) == 1)
                {
                    predict_num++;
                }
            }
            else
            {
                if(((*(P + i))->survival) == 0)
                {
                    predict_num++;
                }
            }
            
        }
        printf("[Fold %d] ", r+1);
        printf("Prediction Score: %.2f%%\n", (((float)predict_num)/(N-number))*100);
    }
    
}
