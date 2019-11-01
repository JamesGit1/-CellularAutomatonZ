#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int displayMenu()
{
    printf("What would you like to select\n\n");
    printf("Option 1. ----- \n");
    printf("Option 2. ----- \n");
    printf("Option 3. ----- \n");
    printf("4. Add more options\n");
    printf("0. Exit\n");
}

int rules()
{
    int option = -1;

    int generations;
    // TODO add extra rules
    int rule30[8] = {0,0,0,1,1,1,1,0};
    int rule60[8] = {0,0,1,1,1,1,0,0};
    int ruleUser[8];
// TODO Input Validation
    do
    {
        displayMenu();
        scanf("%d", &option);


        switch (option)
        {
        case 1:
            printf("You have selected rule 30\n");
            //TODO Input validation
            printf("How many generations would you like to run\n");
            scanf("%d", &generations);
            runAutomaton(generations,rule30);
            break;
        case 2:
            printf("You have selected rule 60\n");
            //TODO Input validation
            printf("How many generations would you like to run\n");
            scanf("%d", &generations);
            runAutomaton(generations,rule60);
            break;
        case 3:
            printf("You have selected custom rule\n");

            // TODO ask for each bit while loop won't increemnt until valid number or he presse 9 exit
            // TODO ask for gen between 2 and 256
            // TODO also checks what rule it is by converting the binary vaule of the array by using Andrews thing and by concat the user input into 2 variables
            printf("How many generations would you like to run\n");
            scanf("%d", &generations);
            runAutomaton(generations,ruleUser);
            break;
        case 0:
            printf("Goodbye");
            break;
        default:
            printf("Please type in a valid number\n");
            break;
        }
    }
    while(option!=0);
}

// checks all neighbouring cells
int checks(int p[], int c[],int current)
{
// checks all neighbouring cells
// outputs it to child
    int left;
    int right;

// Checks if it's at the end or start and loops around cyclic
    if(current == 0)
    {
        left = 7;
        right = 1;
    }
    else if(current == 7)
    {
        left = 6;
        right = 1;
    }
    else
    {
        left = current - 1 ;
        right = current + 1;
    }

    // Checks neighbour and returns value
    if(p[left] == 1 && p[current] == 1 && p[right] == 1)
    {
        return 0;
    }
    if(p[left] == 1 && p[current] == 1 && p[right] == 0)
    {
        return 1;
    }
    if(p[left] == 1 && p[current] == 0 && p[right] == 1)
    {
        return 2;
    }
    if(p[left] == 1 && p[current] == 0 && p[right] == 0)
    {
        return 3;
    }
    if(p[left] == 0 && p[current] == 1 && p[right] == 1)
    {
        return 4;
    }
    if(p[left] == 0 && p[current] == 1 && p[right] == 0)
    {
        return 5;
    }
    if(p[left] == 0 && p[current] == 0 && p[right] == 1)
    {
        return 6;
    }
    if(p[left] == 0 && p[current] == 0 && p[right] == 0)
    {
        return 7;
    }




}
int runAutomaton(int gen,int rule[])
{
    // TODO Make it so the One is at a random spot or let user pick
    // TODO ask for user how big the array is
    int	parent[8] = {0,0,0,0,1,0,0,0};
    int	child[8] = {0};
    int state;
    int counter = 0;

    do
    {
        for(int i = 0 ; i <=7; i++)
        {

            state = checks(parent,child,i);
            child[i] = rule[state];
            printf("%d",parent[i]);
        }
        printf("\n");
        counter++;

        for(int j = 0; j <= 7; j++)
        {
            //TODO make a print nicely
            //TODO maybe print it to a text file
            parent[j] = child[j];
            child[j] = 0;

        }
    }
    while(gen != counter);

}

int main()
{
    rules();
}
