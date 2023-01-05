#include <stdio.h>

void addition(char op, void *num1, void *num2);

int main() {
    char op;

    printf("Input operator: ");
    scanf("%c", &op);

    if(op == 'i') {
        printf("You choose <integer> type\n\n");
        int a, b;
        printf("Input numbers: ");
        scanf("%d %d", &a, &b);
        addition(op, &a, &b);
    } else {
        printf("You choose <float> type\n\n");
        float a, b;
        printf("Input numbers: ");
        scanf("%f %f", &a, &b);
        addition(op, &a, &b);
    }
}

void addition(char op, void *num1, void *num2) {
    if(op == 'i')
	{
		printf("Result: %d\n", *(int*)num1+*(int*)num2);
	}
	else
	{
		printf("Result: %f\n", *(float*)num1+*(float*)num2);
	}

	return;
}
