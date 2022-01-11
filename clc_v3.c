#include <stdio.h>
#include <math.h>
#include <ctype.h>

//declaring functions
char showOptions(int startPrompt);
int inArray(char val, char arr[], int size);
void prompts(int promptType);
char validateChar(char arr[], int size, int promptType);
double validateNum(int numType, char adv, int promptType);
void inputB();
void inputU();
void inputV();
void inputA();
void inputAB();
void inputAU();
void inputM();
void erase();
double calculateB(double x, double y, char operation);
double calculateU(double x, char operation);

//arrays to use for checking validity
char mainOps[7] = {'B','U','V','A','M','R','X'};
char bOps[6] = {'+','-','*','/','%','^'};
char uOps[5] = {'S','L','E','C','F'};
char varChs[5] = {'A','B','C','D','E'};
char aOps[3] = {'B','U','X'};
char memOps[2] = {'M','X'};

double vars[5] = {0,0,0,0,0}; //array to hold variables
double calcs[100000]; //array to hold previous calculations
int count = 0; //memory counter

//defining error names to use to check validity
#define normal 1
#define divide 2
#define powerZero 3
#define powerNeg 4
#define sq 5
#define log 6
#define mem 7

int main()
{
    int startPrompt = 1;
    int X = 1;
    while (X==1)
    {
        switch (showOptions(startPrompt))
        {
        case 'B':
            inputB();
            break;
        case 'U':
            inputU();
            break;
        case 'V':
            inputV();
            break;
        case 'A':
            inputA();
            break;
        case 'M':
            inputM();
            break;
        case 'R':
            erase();
            break;
        case 'X':
            X=0;
            break;
        }
        startPrompt = 0;
    }
    puts("Thanks for using my Simple Calculator. Hope to see you soon again, Goodbye!");
    return 0;
}

char showOptions(int startPrompt)
{
    if(startPrompt==1) //the first time it shows the intro statements, and after that just the options
    {
        printf("Welcome to my Command-Line Calculator (CLC)\nDeveloper: Nafiz Hasan\nVersion: 3, Assignment 3\nDate: 12/01/2021\n-------------------------------------------------\n");
        printf("Please select one of the following items:\nB) - Binary Mathematical Operations such as addition and subtraction.\nU) - Unary Mathematical Operations, such as square root, and log.\nA) - Advances Mathematical Operations, using variables, arrays.\nV) - Define variables and assign them values.\nM) - To see the memory\nR) - To erase the memory\nX) - Exit\n");
    }
    else
    {
        puts("Please select your option ( B (Binary operation), U (Unary operation) , A (Advanced), V (Variables), M (Memory), R (Erase Memory), X (Exit))");
    }
    return(validateChar(mainOps, 7, 1));
}

int inArray(char val, char arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == val)
        {
            return i+1; //if it is found in the array, return that position + 1 so if it is in position 0 it will still be considered true
        }
    }
    return 0; //if not in array
}

void prompts(int promptType) //used to display the correct prompt in the loop
{
    switch (promptType)
    {
    case 1:
        puts("Please select your option ( B (Binary operation), U (Unary operation) , A (Advanced), V (Variables), M (Memory), R (Erase Memory), X (Exit))");
        break;
    case 2:
        puts("Please enter the first number:");
        break;
    case 3:
        puts("Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
        break;
    case 4:
        puts("Please enter the second number:");
        break;
    case 5:
        puts("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):");
        break;
    case 6:
        puts("Enter zero or a positive value:");
        break;
    case 7:
        puts("Enter a positive value:");
        break;
    case 8:
        puts("Please enter a number:");
        break;
    case 9:
        puts("Please enter the name of the variable ( A single character between 'a' to 'e' ):");
        break;
    case 10:
        puts("Please enter a value to assign to the variable:");
        break;
    case 11:
        puts("Please select your option ( B (Binary operation), U (Unary operation), X (Exit and back to the main menu))");
        break;
    case 12:
        puts("Please enter the first number or a variable name ('a' to 'e'):");
        break;
    case 13:
        puts("Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
        break;
    case 14:
        puts("Please enter the second number or a variable name ('a' to 'e'):");
        break;
    case 15:
        puts("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):");
        break;
    case 16:
        puts("Enter zero or a positive value or a variable name ('a' to 'e'):");
        break;
    case 17:
        puts("Enter a positive value or a variable name ('a' to 'e'):");
        break;
    case 18:
        puts("Please enter a number or a variable name ('a' to 'e'):");
        break;
    case 19:
        printf("Enter a number from 1-%d, or 0 to see the entire list\n",count);
        break;
    case 20:
        puts("Please select your option ( M (To see another item in memory), X (Exit back to the main menu))");
        break;
    }
}

char validateChar(char arr[],int size, int promptType) //loops until valid character is entered
{
    char selection;
    while(1)
    {
        scanf("%c", &selection);
        selection = toupper(selection); //so both lowercase and uppercase are valid
        while(getchar()!='\n'); //clearing input buffer
        if(inArray(selection,arr,size)) //checking if the selection is in the array
        {
            break; //if it is, break out of the loop
        }
        else
        {
            puts("Invalid input"); //if not, display error
        }
        prompts(promptType); //displaying correct prompt
    }
    return selection;
}

double validateNum(int numType, char adv, int promptType) //loops until valid number is entered
{
    double num;
    char var;
    int check;
    while(1)
    {
        if(adv == 'N') //if it is not in advanced mode, only check if a valid number is entered
        {
            check = (scanf("%lf", &num));
            while(getchar()!='\n');
        }
        else if(adv == 'Y') //if it is advanced mode
        {
            if (scanf("%lf", &num)) //first check if a valid number is entered
            {
                check = 1;
            }
            else if (scanf("%c", &var)) //then check if a valid variable is entered
            {
                var = toupper(var);
                if(inArray(var,varChs,5))
                {
                    num = vars[inArray(var,varChs,5)-1]; //get the number in the variable by using inArray and -1 because it will return the position +1
                    check = 1;
                }
            }
            while(getchar()!='\n');
        }

        if(check==1) //if valid input is entered
        {
            //check for special cases
            if(numType == divide) //cannot divide by 0
            {
                if(num==0)
                {
                    puts("Denominator can't be zero");
                }
                else
                {
                    break;
                }
            }
            else if(numType == powerZero) //if first number = 0, second cannot be <=0
            {
                if(num<=0)
                {
                    puts("Number must be positive");
                }
                else
                {
                    break;
                }
            }
            else if(numType == powerNeg) //if first number is <0, second has to be integer
            {
                if((ceil(num)!=num))
                {
                    puts("Number must be an integer");
                }
                else
                {
                    break;
                }
            }
            else if(numType == sq) //must be >=0 for square root
            {
                if(num<0)
                {
                    puts("Number must be zero or a positive value");
                }
                else
                {
                    break;
                }
            }
            else if(numType == log) //must be >0 for log
            {
                if(num<=0)
                {
                    puts("Number must be a positive value");
                }
                else
                {
                    break;
                }
            }
            else if(numType == mem) //must be in the range of the memory and be an integer
            {
                if((ceil(num)!=num))
                {
                    puts("Number must be an integer");
                }
                else if(num>count || num<0)
                {
                    puts("Number is not in range");
                }
                else
                {
                    break;
                }
            }
            else //if it is not a special case
            {
                break;
            }
        }
        else //if valid input is not entered
        {
            puts("Invalid input");
        }
        check = 0;
        prompts(promptType); //displaying correct prompt
    }
    return num;
}

void inputB()
{
    double x;
    double y;
    char operation;
    double result;
    puts("Please enter the first number:");
    x = validateNum(normal,'N', 2);
    puts("Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
    operation = validateChar(bOps,6, 3);
    puts("Please enter the second number:");
    if(operation == '/' || operation == '%')
    {
        y=validateNum(divide,'N',4);
    }
    else if(operation == '^')
    {
        if(x==0)
        {
            y=validateNum(powerZero,'N',4);
        }
        else if(x<0)
        {
            y=validateNum(powerNeg,'N',4);
        }
        else
        {
            y=validateNum(normal,'N',4);
        }
    }
    else
    {
        y=validateNum(normal,'N',4);
    }
    result = calculateB(x,y,operation); //used to calculate after getting correct inputs
    printf("The result is: %lf\n",result);
    calcs[count] = result; //store the result in the memory array
    count = count+1; //add 1 to the memory count for the next result
}

double calculateB(double x, double y, char operation)
{
    switch (operation)
    {
    case '+':
        return (x + y);
        break;
    case '-':
        return (x - y);
        break;
    case '*':
        return (x * y);
        break;
    case '/':
        return (x / y);
        break;
    case '%':
        return (fmod(x, y));
        break;
    case '^':
        return (pow(x, y));
        break;
    }
}

void inputU()
{
    double result;
    double x;
    char operation;
    puts("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):");
    operation = validateChar(uOps,5,5);
    if(operation == 'S')
    {
        puts("Enter zero or a positive value:");
        x=validateNum(sq,'N',6);
    }
    else if(operation == 'L')
    {
        puts("Enter a positive value:");
        x=validateNum(log,'N',7);
    }
    else
    {
        puts("Please enter a number:");
        x=validateNum(normal,'N',8);
    }
    result = calculateU(x,operation);
    printf("The result is: %lf\n",result);
    calcs[count] = result;
    count = count+1;
}

double calculateU(double x, char operation)
{
    switch (operation)
    {
    case 'S':
        return (sqrt(x));
        break;
    case 'L':
        return (log10(x));
        break;
    case 'E':
        return (exp(x));
        break;
    case 'C':
        return (ceil(x));
        break;
    case 'F':
        return (floor(x));
        break;
    }
}

void inputV()
{
    char variable;
    double x;
    int pos;
    puts("Please enter the name of the variable ( A single character between 'a' to 'e' ):");
    variable=(validateChar(varChs,5,9));
    puts("Please enter a value to assign to the variable:");
    x=(validateNum(normal,'N',10));
    pos = inArray(variable,varChs,5)-1; //-1 because inArray will return the position +1
    printf("variable %c is set to: %lf\n", variable,x);
    vars[pos] = x; //after getting the position from the variable, set the number in the variables array
}

void inputA()
{
    char selection;
    printf("Select one of the following items:\nB) - Binary Mathematical Operations, such as addition and subtraction.\nU) - Unary Mathematical Operations, such as square root, and log.\nX) - Exit and back to the main menu\n");
    while(1)
    {
        selection = validateChar(aOps,3,11);
        if(selection == 'B')
        {
            inputAB();
        }
        else if (selection == 'U')
        {
            inputAU();
        }
        else if (selection == 'X')
        {
            break;
        }
        puts("Please select your option ( B (Binary operation), U (Unary operation), X (Exit and back to the main menu))");
    }
}

void inputAB()
{
    double x;
    double y;
    char operation;
    double result;
    puts("Please enter the first number or a variable name ('a' to 'e'):");
    x = validateNum(normal,'Y',12); //'Y' for advanced mode
    puts("Please enter the operation ( + , - , * , / , % , ^ (for power) ):");
    operation = validateChar(bOps,6,13);
    puts("Please enter the second number or a variable name ('a' to 'e'):");
    if(operation == '/' || operation == '%')
    {
        y=validateNum(divide,'Y',14);
    }
    else if(operation == '^')
    {
        if(x==0)
        {
            y=validateNum(powerZero,'Y',14);
        }
        else if(x<0)
        {
            y=validateNum(powerNeg,'Y',14);
        }
        else
        {
            y=validateNum(normal,'Y',14);
        }
    }
    else
    {
        y=validateNum(normal,'Y',14);
    }
    result = calculateB(x,y,operation);
    printf("The result is: %lf\n",result);
    calcs[count] = result;
    count = count+1;
}

void inputAU()
{
    double x;
    char operation;
    double result;
    puts("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):");
    operation = validateChar(uOps,5,15);
    if(operation == 'S')
    {
        puts("Enter zero or a positive value or a variable name ('a' to 'e'):");
        x=validateNum(sq,'Y',16);
    }
    else if(operation == 'L')
    {
        puts("Enter a positive value or a variable name ('a' to 'e'):");
        x=validateNum(log,'Y',17);
    }
    else
    {
        puts("Please enter a number or a variable name ('a' to 'e'):");
        x=validateNum(normal,'Y',18);
    }
    result = calculateU(x,operation);
    printf("The result is: %lf\n",result);
    calcs[count] = result;
    count = count+1;
}

void inputM()
{
    int mX = 1;
    int num;
    char selection;
    if(count>100000) //if memory is larger than array size
    {
        puts("Memory is full, only showing the first 100000 items");
        count = 100000;
    }
    printf("There are %d items available in memory\n",count);
    if(count!=0) //only execute if there are more than 0 items in memory
    {
        while(mX==1)
        {
            printf("Enter a number from 1-%d, or 0 to see the entire list\n",count);
            num = validateNum(mem,'N',19);
            if(num==0)
            {
                for(int i=0; i<count; i++)
                {
                    printf("[%d] = %lf\n",i+1,calcs[i]); //print all the items
                }
            }
            else
            {
                printf("[%d] = %lf\n",num,calcs[num-1]); //print specific item asked
            }
            puts("Please select your option ( M (To see another item in memory), X (Exit back to the main menu))");
            selection=validateChar(memOps,2,20);
            if(selection=='X')
            {
                mX=0;
            }
        }
    }
}

void erase()
{
    count = 0; //set count to 0, restarting the memory items
    puts("Memory has been erased.");
}

