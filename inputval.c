#include <stdio.h>

int askGen()
{
    int gen;
    int check = 0;

    while(check == 0)
    {

        printf("How many generations would you like to run: \n");
        scanf("%d", &gen);
        while(getchar() != '\n');
        if(gen < 2 || gen > 256)
        {
            printf("Invalid out put please type a number between 2 and 256 \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
    }

    return gen;
}

int askGenSize()
{

    int size =0;
    int check = 0;

    while(check == 0)
    {
        printf("How big do you want each generation size to be: \n");
        if(scanf("%d", &size) != 1)
        {
            size = 10;
            printf("Invalid out put please type a number between 1 and 256 \n");
            break;
        }
        else if(size < 3 || size > 256)
        {
            printf("Invalid out put please type a number between 1 and 256 \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
        while(getchar() != '\n');
    }

    return size;
}


int main(){

askGenSize();

}
    




