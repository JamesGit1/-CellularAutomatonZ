#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int displayMenu()
{
    printf("What would you like to select\n\n");
    printf("Option 1. Rule 30 Automaton \n");
    printf("Option 2. Rule 60 Automaton \n");
    printf("Option 3. Custom Rule Automaton \n");
    printf("0. Exit\n");
}
// checks all neighbouring cells
// TODO add generation size to be custom
int checks(int p[], int c[],int current, int size)
{
// checks all neighbouring cells
// outputs it to child
    int left;
    int right;

// Checks if it's at the end or start and loops around cyclic
// Need to pass in size so i can cycle     
    if(current == 0)
    {
        left = size--;
        right = 1;
    }
    else if(current == size--)
    {
        left = current--;
        right = 0;
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

int runAutomaton(int gen,int rule[],int size)
{
    // TODO Make it so the One is at a random spot or let user pick
    // TODO ask for user how big the array is
    int parent[size];

    printf("\nPlease define the first generation, with size %d \n",size);
    for (int i=0; i<size; ++i){
        int answer=-1; 
        while(!(answer==1 || answer==0)){
            printf("Please enter 1 or 0:\n[%d]: ",i);
            scanf("%d", &answer);
        }

        parent[i] = answer;  
    }

    int child[size];
    int state;
    int counter = 0;

    do
    {
        // Size of parent
        for(int i = 0 ; i < size; i++)
        {
                // Write binary in here
            state = checks(parent,child,i,size);
            child[i] = rule[state];
            printf("%d",parent[i]);

        }
        // Newline
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

int rules()
{
    int option = -1;

    int generations;
    // TODO add extra rules
    int rule30[8] = {0,0,0,1,1,1,1,0};
    int rule60[8] = {0,0,1,1,1,1,0,0};
    int ruleUser[8];
    int size;
// TODO Input Validation
    do
    {
        displayMenu();
        scanf("%d", &option);


        switch (option)
        {
        case 1:
            printf("You have selected rule 30\n");
            printf("Please enter the size of each generation:");
            scanf("%d", &size);
            //TODO Input validation
            printf("How many generations would you like to run: ");
            scanf("%d", &generations);
            runAutomaton(generations,rule30,size);
            break;
        case 2:
            printf("You have selected rule 60\n");
            printf("Please enter the size of each generation:");
            scanf("%d", &size);
            //TODO Input validation
            printf("How many generations would you like to run: ");
            scanf("%d", &generations);
            runAutomaton(generations,rule60,size);
            break;
        case 3:
            printf("You have selected custom rule\n");
            printf("Please enter the size of each generation:");
            scanf("%d", &size);

            // TODO ask for each bit while loop won't increemnt until valid number or he presse 9 exit
            // TODO ask for gen between 2 and 256
            // TODO also checks what rule it is by converting the binary vaule of the array by using Andrews thing and by concat the user input into 2 variables
            printf("How many generations would you like to run\n");
            scanf("%d", &generations);

            printf("Please enter the custom rule 1 or 0s \n");
            printf("e.g. 010101101 \n\n");
            for (int i=0; i<8; ++i)
            {
                int answer=-1; 
                while(!(answer==1 || answer==0)){
                    printf("Please enter 1 or 0:\n[%d]: ",i);
                    scanf("%d", &answer);
                }

                ruleUser[i] = answer;
            }
            printf("Rule Set:\n");
            for (int i=0; i<8; ++i)
                printf("%d",ruleUser[i]);

            printf("\n\nAUTOMATON\n");
            runAutomaton(generations,ruleUser,size);
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

int main()
{
    rules();
}
