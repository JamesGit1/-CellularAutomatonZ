/*
    AUTOMATON GROUP Z
    JAMES, JESSE, ANDREW
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

// Converts decimal number into binary value which is stored in binArray
int dectobin(int dec, int* binArray){
    int og_dec;
    double bin_Div = 128;
    double binarySum = (bin_Div / dec);
    double currentDec = (dec - bin_Div);

    og_dec = dec;

    //loop for all 8 bits 
    for (int i = 0; i < 8; ++i){
        //Adds a 1 to the array
        if ((og_dec / bin_Div) >= 1 && (og_dec / bin_Div) < 2){
            og_dec = (og_dec - bin_Div);
            bin_Div = (bin_Div / 2);
            binArray[i]=1;
        }
        //Adds a 0 to the array
        else{
            bin_Div = (bin_Div / 2);
            binArray[i]=0;
        }
    }
}

// Displays the menu
int displayMenu()
{
    printf("\nWhat would you like to select\n");
    printf("[1] Rule 30 Automaton \n");
    printf("[2] Rule 60 Automaton \n");
    printf("[3] Custom Rule Automaton \n");
    printf("[4] Game of Life \n");
    printf("[5] Binary Conversion \n");
    printf("[0] Exit\n");
}


void delay(int milli_seconds) 
{  
    int useconds = milli_seconds*1000;
    usleep(useconds);

    /*THIS BIT WORKS FOR WINDOWS
    // https://www.geeksforgeeks.org/time-delay-c/
    // Stroing start time 
    clock_t start_time = clock(); 

    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) ; 
    */
} 

// checks all neighbouring cells
int checks(int p[], int c[],int current, int size)
{
    int left;
    int right;

    // Checks if it's at the end or start and loops around cyclic
    if(current == 0)
    {
        left = (size-1);
        right = 1;
    }
    else if(current == (size-1))
    { 
        left = current-1 ;
        right = 0;
    }
    else
    {
        left = current -1 ;
        right = current + 1;
    }

    // Checks neighbour and returns value of the ruleset
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

// Initialise the file
FILE* initfile(){
char filename[11] ="output.txt";
FILE *fp;

    fp = fopen(filename, "w");
    return fp;
}

// ask the user if they want to output it to an external file
int optionOutput(){
    printf("Would you like to write the output into a file [y/n]: ");
    int check = 0;
    char answer;
    while(check == 0)
    {

        scanf("%c", &answer);
        while(getchar() != '\n');
        if((!(answer=='y' || answer=='Y' || answer=='n' || answer=='N')))
        {
            printf("Invalid output please write [y/n]:  \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
    }

    if(answer=='y' || answer=='Y' ){
        return 1;
    }
    else{
      return 0;  
    }
}

// Runs the automaton
int runAutomaton(int gen,int rule[],int size)
{
  
    int parent[size];
    FILE* fp;

    // ask the user for the first gen
    printf("\nPlease define the first generation, with size %d \n",size);
    for (int i=0; i<size; ++i){
        int answer=-1; 
        while(!(answer==1 || answer==0)){
            printf("Please enter 1 or 0:\n[%d]: ",i);
            scanf("%d", &answer);
            while(getchar() != '\n');
        }

        parent[i] = answer;  
    }

    // Opens the file only if they want to output
    int fileOption = optionOutput();
    if(fileOption == 1){
    fp = initfile();
    }

    int child[size];
    int state;
    int counter = 0;

    // checks neighbours adds the rules to the child and prints the parent 
    do
    {
        // Size of parent
        for(int i = 0 ; i < size; i++)
        {
            state = checks(parent,child,i,size);
            child[i] = rule[state];
             if(fileOption == 1){
                fprintf(fp, "%d",parent[i]);
            }
            printf("%d",parent[i]);

        }
        // Newline
        printf("\n");
        counter++;  

         if(fileOption == 1){
                   fprintf(fp,"\n");
            }
        // sets parent to child and clears child array
        for(int j = 0; j < size; j++)
        {
            parent[j] = child[j];
            child[j] = 0;
        }
    }
    // Does everything until it reaches user generations
    while(gen != counter);
         if(fileOption == 1){
    fclose(fp);
    }
}

// asks for generations vertical
int askGen()
{
    int gen;
    int check = 0;

    while(check == 0)
    {
        printf("How many generations would you like to run?: ");
        if(scanf("%d", &gen) != 1)
        {
            printf("Invalid out put please type a number between 2 and 256 \n");
        }
        else if(gen < 2 || gen > 256)
        {
            printf("Invalid out put please type a number between 2 and 256 \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
        while(getchar() != '\n');
    }

    return gen;
}

// Asks for generation size horizontal
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

//Print array contents to screen
int printGameArray(int arrayToPrint[][50], int size){
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

// Function that counts up alive cells around current cell
int checkNumSurrounding(int current[][50],int i, int j,int size){
    int liveSurrounding = 0;
    
    //Check top left
    if((i>0)&&(j>0)){
        if(current[(i-1)][(j-1)]==1)
            liveSurrounding++;
    }

    //Check left
    if(j>0){
        if(current[i][(j-1)]==1)
            liveSurrounding++;
    }

    //Check bottom left
    if((i<(size-1))&&(j>0)){
        if(current[(i+1)][(j-1)]==1)
            liveSurrounding++;
    }

    //Check top
    if(i>0){
        if(current[(i-1)][(j)]==1)
            liveSurrounding++;
    }

    //Check bottom
    if((i<(size-1))){
        if(current[(i+1)][(j)]==1)
            liveSurrounding++; 
    }

    //Check bottom right
    if((i>0)&&(j<(size-1))){
        if(current[(i-1)][(j+1)]==1)
            liveSurrounding++;
    }

    //Check right
    if(j<(size-1)){ 
        if(current[(i)][(j+1)]==1)
            liveSurrounding++;
    }

    //Check top right
    if((i<(size-1))&&(j<(size-1))){
        if(current[(i+1)][(j+1)]==1)
            liveSurrounding++;
    }

    return liveSurrounding;
}

//Runs main game of life function
int runGameOfLife(){
    int ticks;
    int check = 0;

    //loops until correct value is input
    while(check == 0)
    {
        printf("How big do you want each generation to be: ");
        if(scanf("%d", &ticks) != 1)
        {
            printf("Invalid input, please enter a value greater than 1 \n");
        }
        else if(ticks<2)
        {
            printf("Invalid input, please enter a value greater than 1 \n");
            check = 0;
        }
        else
        {
            check = 1;
        }
        while(getchar() != '\n');
    }

    //The set size of the 2D array. This could be input by user but seemed simpler to leave
    //it at 30 so looked okay in the teminal 
    int size = 50;

    //Initialise the 2 2D arrays
    int current[size][size];
    int next[size][size];
    char answer;

    //Asks if the user would like a randomized array or the pre defined shape that should
    //result in infinte growth
    printf("\nWould you like to randomize the first array [y/n]: ");
    scanf(" %c", &answer);
    while (!(answer=='y' || answer=='Y' || answer=='n' || answer=='N')){
        printf("\nPlease enter y/n: ");
        scanf(" %c", &answer);
    }
    
    if(answer=='n' || answer=='N'){
        // Setup which should result in infinite growth if it was unrestricted by range
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
    else // Otherwise create random array
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

    //Run for the desired runtime
    for (int runtime = 1; runtime <= ticks; runtime++){
        delay(500);

        printf("\n\n====================================================================================================\n");
        printf("RUNTIME=%d",runtime);

        //Print out the current tick
        printGameArray(current,size);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                //If the cell is alive
                if (current[i][j] == 1){
                    int liveSurrounding = checkNumSurrounding(current,i,j,size);
                    //Check if the cell will die due to underpopulation
                    if(liveSurrounding<2){
                        next[i][j] = 0;
                    }
                    //Check if the cell will live on
                    if(liveSurrounding==2 || liveSurrounding==3){
                        next[i][j] = 1;
                    }
                    //Check if the cell will die due to overpopulation
                    if(liveSurrounding>3){
                        next[i][j] = 0;
                    }
                }
                //Otherwise if the cell is dead
                else{
                    //Check if it will be repopulated
                    int liveSurrounding = checkNumSurrounding(current,i,j,size);
                    if(liveSurrounding==3){
                        next[i][j] = 1;   
                    }
                }
            }
        
        }

        //Set current to next array
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                current[i][j] = next[i][j];
            }
        }
        
    }
}
void binaryConversion()
{
    int select;

    printf("\nWhat would you like to select?\n1. Binary to Decimal\n2. Decimal to Binary\n3. Back\n\nSelect Number: ");
    scanf("%d", &select);
    if (select == 1)
    {    
        //Source: https://www.sanfoundry.com/c-program-binary-number-into-decimal/
        int  input;
        int  og_decimal = 0;
        int  binary;
        int  remainder;
        int  base = 1;

        //collects the binary
        printf("\nCovert Binary to Decimal (To 10 bits)\n");
        printf("\nPlease input binary: ");
        scanf("%d", &input);

        binary = input;

        //Converts the binary to a decimal using the workings seen below
        while (input > 0)
        {

            remainder = (input % 10);
            og_decimal = (og_decimal + (remainder * base));
            input = (input / 10) ;
            base = (base * 2);
        }

        //Outputs the decimal number
        printf("%d is %d when converted to binary. \n", binary, og_decimal);

    }
    else if (select == 2)
    {
        //Sets up all required inputs, such as setting it as 32 bit
        int input;
        int og_dec;
        double bin_Div = 2147483648;
        double binarySum = (bin_Div / input);
        double currentDec = (input - bin_Div);
        int start = 0;

        // Asks the user for the input decimal
        printf("\nCovert Decimal to Binary\n");
        printf("\nPlease input decimal: ");
        scanf("%d", &input);

        og_dec = input;
        start = 0;

        //Prints the original decimal input
        printf("\n%d is ", og_dec);

        for (int i = 0; i < 32; ++i)
        {
            //the workings for the decimal to binary conversion
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
            //Ignores the starter 0's of the binary number
            //More presentable
            else if (start == 0)
            {
                bin_Div = (bin_Div / 2);
            }
            //Error check
            else
            {
                printf("\nWhoops\n");
            }
        }
        //Prints the binary number
            printf(" in binary.\ndone\n");

    }
    else if (select == 3)
    {
        printf("\nBack\n");
    }
}

// Gets the rules and sets the gensize and gen and display the menu
int rules()
{
    
    int option = -1;
    int generations;
    int rule30[8] = {0,0,0,1,1,1,1,0};
    int rule60[8] = {0,0,1,1,1,1,0,0};
    int ruleUser[8];
    int size;
    do
    {
        //re initialise option
        option = -1;
        // Displays menu
        displayMenu();
        scanf("%d", &option);
        while(getchar() != '\n');


        // gets user options and does something diffrerent depend on each size
        switch (option)
        {
            // Rule 30 ask gen and applies that rule
        case 1:
            printf("You have selected rule 30\n");
            size = askGenSize();
            generations = askGen();
            runAutomaton(generations,rule30,size);
            break;
             // Rule 60 ask gen and applies that rule
        case 2:
            printf("You have selected rule 60\n");
            size = askGenSize();
            generations = askGen();
            runAutomaton(generations,rule60,size);
            break;
        case 3: // Custom ruleset ask gen and applies that rule
            printf("You have selected custom rule\n");
            size = askGenSize();
            generations = askGen();

            int check = 0;
            int decIn;

            //Runs until correct input satisfied
            while(check == 0){
                printf("What Ruleset would you like to use i.e. 30: ");
                if(scanf("%d", &decIn) != 1){
                    printf("Invalid input put please type a number between 0 and 256 \n");
                }
                else if(decIn < 0 || decIn > 255){
                    printf("Invalid input put please type a number between 0 and 256 \n");
                    check = 0;
                }
                else{
                    check = 1;
                }
                while(getchar() != '\n');
            }

            //intialise array and fill with binary converted integer
            int ruleUser[8];
            dectobin(decIn,ruleUser);

            for (int i = 0; i < 8; ++i){
                printf("%d",ruleUser[i]);   
            }
            printf("\n");

            printf("Rule Set %d\n", decIn);

            runAutomaton(generations,ruleUser,size);
            break;
        case 4:
            runGameOfLife();
            break;
        case 5:
            binaryConversion();
            break;
        case 0:
            printf("\nGoodbye\n");
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
    //Run main menu
    rules();
}
