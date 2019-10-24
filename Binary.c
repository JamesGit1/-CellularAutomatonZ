#include <stdio.h>

void binary()
{
	int select;

	printf("\nWhat would you like to select?\n1. Binary to Decimal\n2. Decimal to Binary\n3. Back\n\nSelect Number: ");
	scanf("%d", &select);
	if (select == 1)
	{    
		//Source: https://www.sanfoundry.com/c-program-binary-number-into-decimal/
		int  decimal;
		int  og_decimal = 0;
		int  binary;
		int  remainder;
		int  base = 1;

		//collects the binary
		printf("\nCovert Binary to Decimal (To 10 bits)\n");
		printf("\nPlease input binary: ");
		scanf("%d", &decimal);

	    binary = decimal;

	    while (decimal > 0)
	    {

	        remainder = (decimal % 10);
	        og_decimal = (og_decimal + (remainder * base));
	        decimal = (decimal / 10) ;
	        base = (base * 2);
	    }

	    printf("%d is %d when converted to binary. \n", binary, og_decimal);

	}
	else if (select == 2)
	{
		int dec;
		int og_dec;
		double bin_Div = 2147483648;
		double binarySum = (bin_Div / dec);
		double currentDec = (dec - bin_Div);
		int start = 0;

		printf("\nCovert Decimal to Binary\n");
		printf("\nPlease input decimal: ");
		scanf("%d", &dec);

		og_dec = dec;
		start = 0;

		printf("\n%d is ", og_dec);

		for (int i = 0; i < 32; ++i)
		{

			if ((og_dec / bin_Div) >= 1 && (og_dec / bin_Div) < 2)
			{
				og_dec = (og_dec - bin_Div);
				bin_Div = (bin_Div / 2);
				printf("1");
				start = 1;
			}
			else if (start == 1)
			{
				bin_Div = (bin_Div / 2);
				printf("0");
			}
			else if (start == 0)
			{
				bin_Div = (bin_Div / 2);
			}
			else
			{
				printf("\nWhoops\n");
			}
		}
			printf(" in binary.\ndone\n");

	}
	else if (select == 3)
	{
		printf("\nBack\n");
	}
	else
	{
		//Make an error function error();
	}
}

int main()
{
	binary();
	return 0;
}