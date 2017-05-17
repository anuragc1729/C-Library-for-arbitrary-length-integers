//Demo program for the "intal" library of integers of arbitrary length.

#include <stdio.h>
#include "intal.h"

int main() {
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	

	read_intal(i1, "140");
	read_intal(i2, "25");

	
	printf("i1 = ");
	print_intal(i1);
	printf("\n");

	printf("i2 = ");
	print_intal(i2);
	printf("\n");

	printf("\n1.Addition \n\n2.Subtraction \n\n3.Multiplication \n\n4.Division \n\n5.Exponentiation \n\n");

	int option;
	printf("Enter your choice...");	
	scanf("%d",&option);

	switch(option)
	{
		case 1:
			printf("\nThe addition of two intals gives \n");
			print_intal(add_intal(i1,i2));
			printf("\n");
			break;

		case 2:
			printf("\nThe subtraction of two intals gives \n");
			print_intal(subtract_intal(i1,i2));
			printf("\n");
			break;


		case 3:
			printf("\nThe multiplication of two intals gives \n");
			print_intal(multiply_intal(i1,i2));
			printf("\n");
			break;

		case 4:
			printf("\nThe division of two intals gives \n");
			print_intal(divide_intal(i1,i2));
			printf("\n");
			break;

		case 5:
			printf("\nThe exponentiation of two intals gives \n");
			print_intal(pow_intal(i1,i2));
			printf("\n");
			break;
	
	}
	delete_intal(&i1);
	delete_intal(&i2);


	return 0;
}


