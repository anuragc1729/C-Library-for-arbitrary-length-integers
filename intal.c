//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);
	
	if( (str[0] == '+') || (str[0] == '-') ) {
		n--;//it has a sign        
		// Field n represents the number of decimal digits **excluding** the sign.
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	} else {
		//it doesn't have a sign and hence it's positive
		//n++; //one extra for the + sign                                         
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy(i->s + 1, str);
	}
	i->n = n;                                                                     
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}

//adds zeroes to the number which has less digits so as to make them of equal length
char * padZero(intal* a,int len)
{
	int i = 0;
	char *zero = (char *)malloc((len+1)*sizeof(char));
	for(i = 1;i < len+1;i++)
	{
		//strcat(zeroes,"0");
		zero[i] = '0';	
	}
	zero[0] = a->s[0];
	strcat(zero,a->s+1);
	//for(i = 1 ; i < strlen(a->s)+len ; i++)
	
	a->s = zero;	
	
	return a->s;
}

//removes padded zeroes for smaller number
char * remove_zero(char * a)
{
	int i=1,n = 0;
	while(a[i] == '0')
	{
		n++;
		i++;
	}
	char *newchar = (char *)malloc((strlen(a) - n)*sizeof(char));
	newchar[0] = a[0];
	for(i = 1;i < strlen(a) - n;i++)
	{
		newchar[i] = a[i+n];
	}
	a = newchar;
	return newchar;
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	intal* result = create_intal(); //creating a result intal variable to hold the result
	int i=0;
	int j;
	int noOfZero;
	int sum ;
	int carry = 0;
	char * c;       
	if(!(strcmp(a->s+1 , "0")) && (!strcmp(b->s+1 , "0")))
	{
		read_intal(result , "0");
		return result;
	}

	if(a->n > b->n)
	{
		noOfZero = a->n - b->n;
		b->s = padZero(b , noOfZero);
		b->n = strlen(b->s)-1;	
	}			
	else if(a->n < b->n) //cant have else condtion , as we have to care of equal length condtion
	{
		noOfZero = b->n - a->n;
		a->s = padZero(a , noOfZero);
		a->n = strlen(a->s)-1;
	}

	//if the signs of the intals are not the same , then we need to redirect it to subtract function
	if(a->s[0] == '+' && b->s[0] == '-')
	{	
		b->s[0] = '+';
		result = subtract_intal(a,b);
		return result;
	}

	else if(a->s[0] == '-' && b->s[0] == '+')
	{
		b->s[0] = '-';
		result = subtract_intal(b,a);
		return result;
	}
	c = (char *)malloc((sizeof(char))*(strlen(a->s) + 1));
	// one extar digit should be assigned for carry
	//sign of result can either be positive or negative(both no are -ve)
	if (a->s[0] == '-' && b->s[0] == '-')
	{
		c[0] = '-';
	}
	else 
		c[0] = '+';
	for (i = strlen(a->s) - 1 , j = strlen(a->s); i >= 1; i-- , j--)
	{
		sum = a->s[i] + b->s[i] + carry - '0' - '0';
		carry = sum/10;
		sum = sum%10;
		c[j] = sum + '0';
	}
	c[1] = carry + '0';
	if(carry == 0)
		c = remove_zero(c); 

	read_intal(result , c); 

	return result;
}

int cmp(char *a , char *b)
{
	int i =0;
	//if (a)
	//{
		/* code */
	//}
	
	for( i = 1 ; i<strlen(a) ; i++)
	{	
		if (a[i] > b[i])
		{
			return 1;
		}
		if(b[i] > a[i])
			return 0;

	}
	return -1;
}	
// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){

	intal* result = create_intal(); //creating a result intal variable to hold the result
	int noOfZero;
	int diff ;
	int i;
	if(a->n > b->n)
	{
		noOfZero = a->n - b->n;
		b->s = padZero(b , noOfZero);
		b->n = strlen(b->s)-1;	
	}			
	else if(a->n < b->n) //cant have else condtion , as we have to care of equal length condtion
	{
		noOfZero = b->n - a->n;
		a->s = padZero(a , noOfZero);
		a->n = strlen(a->s)-1;
	}
	char *temp = (char *)malloc(sizeof(char)*a->n);
	for( i=0 ; i < a->n ;i++)
	{
	    temp[i]='0';
	}
	char *var1 = a->s;
	char *var2 = b->s;
	int res = cmp(a->s , b->s); //directly checking whether sign is positive or negative
	if(res == 1) //a > b
	{
		temp[0] = a->s[0];
	}
	else if (res == 0) // b > a
	{
		temp[0] = '-';
		var1 = b->s;
		var2 = a->s;
	}
	else {
		read_intal(result , "0");
		return result;
	}
	//if the signs of the intals are not the same , then we need to redirect it to add function
	
	if(a->s[0] == '+' && b->s[0] == '-')
	{	
		b->s[0] = '+'; //changing signs , as a- (-b) = a+b
		result = add_intal(a,b);
		return result;
	}
	else if(a->s[0] == '-' && b->s[0] == '+')
	{	
		b->s[0]='-';//changing signs , as -a + (-b) = -a-b
		result = add_intal(b,a);
		return result;
	}
	int j;
	j = a->n;
	for(i = b->n;i >=1;i--)
	{

		diff = (var1[j] - '0') - (var2[i] - '0');
		if(diff < 0)
		{
			var1[j - 1] = ((var1[j - 1] - 48) - 1) + 48;	
			diff = diff + 10;
		}
		temp[j] = diff + 48;
		j--;
	}
	temp = remove_zero(temp);
	read_intal(result , temp);
	
	return result;
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b){
	intal* result = create_intal();
	int i,j,tmp;
	int *i1 = (int *)malloc(sizeof(int)*a->n);
	int *i2 = (int *)malloc(sizeof(int)*b->n);
	char * s1 = a->s+1;
	char * s2 = b->s+1;
	int *ans = (int *)malloc(sizeof(int)*(a->n+b->n));
	char *res = (char *)malloc(sizeof(char)*(a->n+b->n));  
   
    if(a->s[0] != b->s[0])
	{	
		res[0] = '-';
	}
	else
	{	
		res[0]='+';
	}

    for(i = a->n-1 , j=0 ; i>=0 ;i-- , j++)
    {
        i1[j] = s1[i]-'0';
    }

    for(i = b->n-1 , j=0 ; i>=0 ; i-- , j++)
    {
        i2[j] = s2[i]-'0';
    }
    if (!strcmp(s1,"0") || !strcmp(s2 , "0"))
    {
    	read_intal(result , "0");
    	return result;
    }
    //printf("s1 = %s\n",s1);
    //printf("s2 = %s\n",s2);
    for(i = 0;i < b->n;i++)
    {
        for(j = 0;j < a->n;j++)
        {
            ans[i+j] += i2[i]*i1[j];
        }
    }

    for(i = 0;i < a->n + b->n;i++)
    {
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }    
    for( i = 0,j= a->n + b->n;j>=1;i++ , j--)
    {
        res[j] = ans[i] + '0';
    }
    
	res = remove_zero(res);
	read_intal(result , res);
	return result;
}

int grtzero(intal* i){

	if(strcmp(i->s+1, "0") == 0)
		return 0;
	if(i->s[0] == '-')
		return 0;
	return 1;
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
intal* divide_intal(intal* a, intal* b){
	intal* result = create_intal();
	read_intal(result , "0");
	//int i;
	int check;
	//char *var1 = (char *)malloc(sizeof(char)*a->n)
	char *var2 = (char *)malloc(sizeof(char)*b->n);
	//char *temp = (char *)mall	oc(sizeof(char)*a->n);
	//for( i=0 ; i < a->n ;i++)
	
	   // temp[i]='0';
	
	//char *var1 = a->s;
	var2 = b->s+1;
	if (!strcmp(var2,"0"))
	{
		printf("Division by Zero is not possible\n");
		read_intal(result , "NOT DEFINED");
    	return result;
	}

	else if (!strcmp(var2,"1"))
	{
		read_intal(result , a->s);
    	return result;
	}

	int noOfZero;
	if(a->n > b->n)
	{
		noOfZero = a->n - b->n;
		b->s = padZero(b , noOfZero);
		b->n = strlen(b->s)-1;	
	}			
	else if(a->n < b->n) //cant have else condtion , as we have to care of equal length condtion
	{
		noOfZero = b->n - a->n;
		a->s = padZero(a , noOfZero);
		a->n = strlen(a->s)-1;
	}	
	check = cmp(a->s , b->s);
							
	//for checking whether b > a. if b is greater then return 0
	//check = 1 , then a >b , else lesser

	if(check == 0)
	{
		read_intal(result , "0");
    	return result;
	}

	if (check == -1)
	{
		read_intal(result , "1");
    	return result;	
	}

//	intal * diff = create_intal();

	intal * temp = create_intal();
	read_intal(temp , "1");
	if(a->s[0] == '-' && b->s[0] == '+')
	{
		result->s[0] = '-';
		a->s[0] = '+'; 
	}
	if(a->s[0] == '+' && b->s[0] == '-')
	{
		result->s[0] = '-';
		b->s[0] = '+'; 
	}
	if (a->s[0] == '-' && b->s[0] == '-')
	{
		result->s[0] = '+'; 
	}
	int seq = grtzero(a);
	//printf("%d\n",seq);
	while(seq)
	{
		intal * counter = create_intal();
		read_intal(counter , "0");
		intal * diff = create_intal();
		read_intal(diff , "0");
		counter = add_intal(result , temp);
		diff = subtract_intal(a,b);
		read_intal(a, diff->s);
		seq = grtzero(a);
		read_intal(result, counter->s);
		delete_intal(&counter);
		delete_intal(&diff);		
	}
	//printf("check\n");
	if (a->s[0]=='-')
	{
		intal * counter = create_intal();
		read_intal(counter , "0");
		counter = subtract_intal(result , temp);
		read_intal(result, counter->s);
		delete_intal(&counter);
	}

	return result;

}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {

	intal* result = create_intal();
	result = a;
	int i = 0;
	if (b->s[0] == '-')
	{
		printf("the power can't be negative, returning NULL \n");
		return NULL;
	}
	if (!strcmp(b->s+1,"0"))
	{
		read_intal(result , "1");
		return result;
	}
	char *c = b->s+1;
	i = atoi(c);
	
	printf("the base is %s\n",a->s);
	printf("the power is %d\n",i);
	while(i>1)
	{
		result = multiply_intal(result , a);
		i--;
	}

	return result;
}
