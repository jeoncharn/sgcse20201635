#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef float* Vector_Comp;
typedef float Comp;

typedef struct{
	Vector_Comp comps;
	int vec_size;
} Vector;

Comp DistVector(Vector v1, Vector v2);
Comp innerProduct(Vector v1, Vector v2);
Comp vectorSize(Vector v);

int main()
{
	int size1, size2;
	Vector v1, v2;

	printf("Input vec1 size:");
	scanf("%d", &size1);
	v1.vec_size = size1;

	v1.comps = (Vector_Comp)malloc(sizeof(Comp)*size1);

	printf("Input vec1 value:");
	
	for(int i=0; i<size1; i++)
	{
		scanf("%f", &v1.comps[i]);
	}

	printf("Input vec2 size:");
	scanf("%d", &size2);
	v2.vec_size = size2;

	v2.comps = (Vector_Comp)malloc(sizeof(Comp)*size2);

	printf("Input vec2 value:");

	for(int i=0; i<size2; i++)
	{
		scanf("%f", &v2.comps[i]);
	}

	printf("\n<result>\n");
	
	printf("Size : %.2f\n", vectorSize(v1));
	printf("Size : %.2f\n", vectorSize(v2));

	if(size1 == size2)
	{
		printf("Dist : %.2f\n", DistVector(v1, v2));
		printf("Inner : %.2f\n", innerProduct(v1, v2));
	}

	return 0;
}

Comp DistVector(Vector v1, Vector v2)
{
	int size = v1.vec_size;
	int sum = 0;

	for(int i=0; i<size; i++)
	{
		sum += (v1.comps[i] - v2.comps[i])*(v1.comps[i] - v2.comps[i]);
	}

	return sqrt(sum);
}

Comp innerProduct(Vector v1, Vector v2)
{
	int size = v1.vec_size;
	int sum = 0;
	
	for(int i=0; i<size; i++)
	{
		sum += (v1.comps[i])*(v2.comps[i]);
	}

	return sum;
}

Comp vectorSize(Vector v)
{
	int size = v.vec_size;
	int sum = 0;

	for(int i=0; i<size; i++)
	{
		sum += (v.comps[i])*(v.comps[i]);
	}

	return sqrt(sum);
}
