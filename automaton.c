#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int displayMenu()
{
    printf("What would you like to select\n\n");
    printf("Option 1. Rule 30 Automaton \n");
    printf("Option 2. Rule 60 Automaton \n");
    printf("Option 3. Custom Rule Automaton \n");
    printf("Option 4. Game of Life \n");
    printf("0. Exit\n");
}

// https://www.geeksforgeeks.org/time-delay-c/
void delay(int milli_seconds) 
{  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
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
        //printf("%d Current = 0 :  \n", left);
        left = (size-1);
        right = 1;
    }
    else if(current == (size-1))
    {
        //printf("%d Current = Size :  \n",left );
        left = current-1 ;
        right = 0;
    }
    else
    {
        //printf("%d %d Current = Other :  \n", left, right);
        left = current -1 ;
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

        for(int j = 0; j < size; j++)
        {
            //TODO make a print nicely
            //TODO maybe print it to a text file
            parent[j] = child[j];
            child[j] = 0;

        }
    }
    while(gen != counter);

}

int askGen()
{
    int gen;
    int check = 0;

    while(check == 0)
    {
 
        printf("How many generations would you like to run: ");
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
        printf("How big do you want each generation to be: ");
        if(scanf("%d", &size) != 1)
        {
            printf("Invalid out put please type a number between 3 and 256 \n");
        }
        else if(size < 3 || size > 256)
        {
            printf("Invalid out put please type a number between 3 and 256 \n");
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

int printGameArray(int arrayToPrint[][30], int size){
for (int i = 0; i < size; i++)
    {
        printf("\n");
        for (int j = 0; j < size; j++)
        {
            if (arrayToPrint[i][j]==0){
                printf("  ");
            }
            else{
                printf("# ");
                //printf("%d ",arrayToPrint[i][j]);
            }
        }
        
    }
    printf("\n");
}

int checkNumSurrounding(int current[][30],int i, int j){
    int liveSurrounding = 0;
    
    if((i>0)&&(j>0)){
        if(current[(i-1)][(j-1)]==1)
            liveSurrounding++;
    }
    
    if(j>0){
        if(current[(i)][(j-1)]==1)
            liveSurrounding++;
    }

    if((i<29)&&(j>0)){
        if(current[(i+1)][(j-1)]==1)
            liveSurrounding++;
    }

    if(i>0){
        if(current[(i-1)][(j)]==1)
            liveSurrounding++;
    }

    if((i<29)){
        if(current[(i+1)][(j)]==1)
            liveSurrounding++; 
    }

    if((i>0)&&(j<29)){
        if(current[(i-1)][(j+1)]==1)
            liveSurrounding++;
    }

    if(j<29){ 
        if(current[(i)][(j+1)]==1)
            liveSurrounding++;
    }

    if((i<29)&&(j<29)){
        if(current[(i+1)][(j+1)]==1)
            liveSurrounding++;
    }

    return liveSurrounding;
}


int runGameOfLife(){
    int ticks;
    int check = 0;

    while(check == 0)
    {
        printf("How long would you like to run the simulation? ");
        scanf("%d", &ticks);
        while(getchar() != '\n');
        if(ticks < 2)
        {
            printf("Invalid input please enter a value greater than 2 \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
    }

    int size = 30;

    int current[30][30] = {0};
    int next[30][30] = {0};
    char answer;

    printf("\nWould you like to randomize the first array: ");
    scanf(" %c", &answer);
    while (!(answer=='y' || answer=='Y' || answer=='n' || answer=='N')){
        printf("\nPlease enter y/n: ");
        scanf(" %c", &answer);
    }
    
    if(answer=='n' || answer=='N'){
        current[14][15] = 1;
        current[14][16] = 1;
        current[14][17] = 1;
        current[14][19] = 1;

        current[15][15] = 1;

        current[16][18] = 1;
        current[16][19] = 1;

        current[17][16] = 1;
        current[17][17] = 1;
        current[17][19] = 1;

        current[18][15] = 1;
        current[18][17] = 1;
        current[18][19] = 1;
    }
    else
    {
        srand(time(NULL));
        for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    int randomNum = rand() % 2;
                    current[i][j] = randomNum;
                }
        }
    }

    printf("\n\n===================");
    printf("RUNNING GAME OF LIFE FOR %d ticks",ticks);
    printf("===================\n\n");

    printf("3...\n");
    delay(1000);
    printf("2...\n");
    delay(1000);
    printf("1...");
    delay(1000);
    

    for (int runtime = 1; runtime <= ticks; runtime++){
        delay(500);

        printf("\n\n=========================================================\n");
        printf("RUNTIME=%d",runtime);

        printGameArray(current,size);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (current[i][j] == 1){
                    int liveSurrounding = checkNumSurrounding(current,i,j);
                    if(liveSurrounding<2){
                        next[i][j] = 0;
                    }
                    if(liveSurrounding==2 || liveSurrounding==3){
                        next[i][j] = 1;
                    }
                    if(liveSurrounding>3){
                        next[i][j] = 0;
                    }
                }
                else{
                    int liveSurrounding = checkNumSurrounding(current,i,j);
                    if(liveSurrounding==3){
                        next[i][j] = 1;   
                    }
                }
            }
        
        }

        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                current[i][j] = next[i][j];
            }
        }
        
    }
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
        while(getchar() != '\n');

        switch (option)
        {
        case 1:
            printf("You have selected rule 30\n");
            size = askGenSize();
            //TODO Input validation
            generations = askGen();
            runAutomaton(generations,rule30,size);
            break;
        case 2:
            printf("You have selected rule 60\n");
            size = askGenSize();
            //TODO Input validation
            generations = askGen();
            runAutomaton(generations,rule60,size);
            break;
        case 3:
            printf("You have selected custom rule\n");
            size = askGenSize();

            // TODO ask for each bit while loop won't increemnt until valid number or he presse 9 exit
            // TODO ask for gen between 2 and 256
            // TODO also checks what rule it is by converting the binary vaule of the array by using Andrews thing and by concat the user input into 2 variables
            generations = askGen();

            //REPLACE THIS WITH DECIMAL CONVERTER
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
        case 4:
            runGameOfLife();
            break;
        case 0:
            printf("\nGoodbye");
            break;
        default:
            printf("Please type in a valid number\n");
            break;
        }
    }
    while(option!=0);
}

int dectobin(int dec){
    int og_dec;
    double bin_Div = 2147483648;
    double binarySum = (bin_Div / dec);
    double currentDec = (dec - bin_Div);
    int start = 0;

    printf("\nCovert Decimal to Binary\n");

    og_dec = dec;
    start = 0;

    printf("\n%d is ", og_dec);

    for (int i = 0; i < 32; ++i){
        if ((og_dec / bin_Div) >= 1 && (og_dec / bin_Div) < 2){
            og_dec = (og_dec - bin_Div);
            bin_Div = (bin_Div / 2);
            printf("1");
            start = 1;
        }
        else if (start == 1){
            bin_Div = (bin_Div / 2);
            printf("0");
        }
        else if (start == 0){
            bin_Div = (bin_Div / 2);
        }
        else{
            printf("\nWhoops\n");
        }
    }

    return dec;
}

int main()
{
    rules();
}
