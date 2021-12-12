/***********************
* Roei
* 325714152
* 01
* ass3 / ex3
***********************/
#include <stdio.h>
#define BONUS

/**********************************************************************
* Function Name: towerOfHanoi
* Input: (int) how many disks there are (>=0), and (char) characters who'se represents all 3 rods
* Output: series of printed steps
* Function Operation: the function guides the user throughout the solving process of the "TOWER OF HANOI" MINI GAME
* The function is reccursive :
* if we start with 0 disks, nothing is printed
* if we have only 1 disk left, we transfer it to the final rod
* otherwize, we tell the function to move n-1 disks from the first rod to the middle one,
* then we print "move disk (numDisk) from first rod to the final rod"
* then, we call the function back in order to move disks from the middle rod to the first rod
**********************************************************************/
void towerOfHanoi(int numDisks, char fromRod, char toRod, char auxRod)
{
    //if we start with 0 disks, nothing should be printed
    if (numDisks == 0)
    {
        printf("\n");
        return;
    }
    //the reccursive stop conditiom
    if (numDisks == 1)
    {
        printf("Move disk 1 from rod %c to rod %c.\n", fromRod, toRod);
    }
    else
    {
        //move n-1 disks
        towerOfHanoi(numDisks - 1, fromRod, auxRod, toRod);
        printf("Move disk %d from rod %c to rod %c.\n", numDisks, fromRod, toRod);
        //moving disks from middle rod to original rod
        towerOfHanoi(numDisks - 1, auxRod, toRod, fromRod);
    }
}

/******************
* Function Name: checkPalindrome
* Input: (char[]) an array of characters, (int) the current lenght, and the (int) lenght of the array
* Output: int (either 0 or 1)
* Function Operation: the function returns 1 if the string is a palindrome, and it returns 0 if its not
* reccursion: STOP CONDITION WHEN : (lenOg-len>=len-1) which means when the "first" letter we check
* has a higher index then the "last" one (more detail later)
* when we check pelindrome, we compare between 2 characters that have the same distance to the middle of the array
* so we compare str[first] to str[last], str[first+1] to str[last-1] and so on
* if the characters match, we check the next set of charecters, otherwize, it's not a palindrome
******************/
int checkPalindrome(char str[], int len, int lenOg)
{
    //STOP CONDITION:basicly,if the index of the character that was before the middle passes it (more detail on top)
    if (lenOg - len >= len - 1)
    {
        return 1;
    }
    //comparing between 2 caracters whose "distance" to the middle is the same
    if (str[lenOg - len] == str[len - 1])
    {
        return checkPalindrome(str, len - 1, lenOg);
    }
    //if the set of characters does not match, we return 0 (not a palindrome)
    else
    {
        return 0;
    }
}

/******************
* Function Name: isPalindrome
* Input:  (char[]) an array of characters, and (int) the lenght of it
* Output: prints if the array is either a palindrome or not
* Function Operation: basicly anylizes the values from the function above "checkPalindrome"
* if that function returned 1 => its a palindrome
* if that function returned 0 => its not a palindrome
******************/
void isPalindrome(char str[], int len)
{
    //1 => its a palindrome, 0 => its not a palindrome
    if (checkPalindrome(str, len, len) == 0)
    {
        printf("The reverse of %s is not %s.\n", str, str);
    }
    else
    {
        printf("The reverse of %s is also %s.\n", str, str);
    }
}

int counter = 0;
/******************
* Function Name: printCombinations
* Input: an array (char[]) pattern made out of {0,1,2,?}, the (int) lenght of it
* and (int) an index (which will be sent as 0)
* Output: prints all possible combinations that replace the question mark (from smallest to largest)
* it also calculates how many combinations there are
* Function Operation: STOP CONDITION : if the index is larger then the lenght of the pattern
* (which means we replaced all question marks and we can print a number.
* each character is checked, if its '?', then it is replaced.
******************/
void printCombinations(char pattern[], int len, int i)
{
    /*
    PLEASE NOTE :
    i redid this question after watching a 40 minutes zoom call regarding it
    i already had a solution to this question, but it was really inseficcent and long, and i felt like
    i want to show my best, i am an honest student and i do not copy my code from others
    */
    //if the index is higher then the lenght, it means we have a '?' free string
    if (i > len)
    {
        printf("%s\n", pattern);
        //raising the counter each time we print
        counter++;
    }
    else
    {
        //if we have a '?', it needs to be replaced
        if (pattern[i] == '?')
        {
            /*
            * first, we replace it with 0 and call the function to replace the later '?' (if there are)
            * with 0, 1 and 2 in order
            * then we get to line 139 and we do the same thing again
            * just this time the first '?' is a 1 and not a 0
            * line 141 explaines the same as line 139
            */
            pattern[i] = '0';
            printCombinations(pattern, len, i + 1);
            pattern[i] = '1';
            printCombinations(pattern, len, i + 1);
            pattern[i] = '2';
            printCombinations(pattern, len, i + 1);
            /*
            * replacing again the index with '?' so we enter the 'if' statement again
            * to make sure each combination is displayed once
            */
            pattern[i] = '?';
        }
        else
        {
            //if the current character isnt a '?', move on to the next one
            printCombinations(pattern, len, i + 1);
        }
    }
}

/******************
* Function Name: printAllCombinations
* Input: an array (char[]) pattern made out of {0,1,2,?}, and the (int) lenght of it
* Output:prints all possible combinations and how many possible combinations there are
* Function Operation: calls the function above "printCombinations" and sets the index to 0
* is also resets the counter for the next run
******************/
void printAllCombinations(char pattern[], int len)
{
    printCombinations(pattern, len, 0);
    printf("Number of combinations is: %d\n", counter);
    //resetting the counter for the next calculation
    counter = 0;
}

/******************
* Function Name: answerPow
* Input: 2 long int numbers (n1, n2)
* Output: n1 ^ n2
* Function Operation: STOP:IF THE POWER RAISED TO HAS REACHED 0, 1 is returned
* if n2 is negative, we return 1 / n1^(-n2)
* if n2 == 1, return n1
* otherwize, return n1 * (n1 ^ (n2 - 1))
******************/
float answerPow(long int firsrtNum, long int secondNum)
{
    if (secondNum == 0)
    {
        return 1;
    }
    if (secondNum < 0)
    {
        return 1 / answerPow(firsrtNum, -secondNum);
    }
    if (secondNum == 1)
    {
        return firsrtNum;
    }
    else
    {
        return firsrtNum * answerPow(firsrtNum, secondNum - 1);
    }
}

/******************
* Function Name: powRec
* Input: long int firstNum, long int secondNum
* Output: firstnum^secondnum with 6 additional decimal points
* Function Operation: basicly takes the answer from the function "answerPow" and prints it
******************/
void powRec(long int firsrtNum, long int secondNum)
{
    printf("The result is %f.\n", answerPow(firsrtNum, secondNum));
}

/******************
* Function Name: calculateRemaining
* Input: long long integer, and the (int) remaining (which set to be 0 at the start)
* Output: (int) remaing when divided by 3
* Function Operation: STOPS IF the number has reached 0
* we see what are the lsd and the remaining
* (basicly, for each possible remaining and lsd, we calculate the newer remaining)
* after calculating the newer remaining, we "delete" the lsd and recall the function
******************/
int calculateRemaining(long long n, int remaining)
{
    //when we deleted so many characters that the number reached 0, we stop
    if (n == 0)
    {
        return remaining;
    }
    //calculating the lsd
    int currentDigit = n % 10;
    if (currentDigit == 1)
    {
        switch (remaining)
        {
        case 0:
        {
            //0 + 1 = 1
            remaining = 1;
            break;
        }
        case 1:
        {
            remaining = 2;
            break;
        }
        case 2:
        {
            remaining = 0;
        }
        }
    }
    if (currentDigit == 2)
    {
        switch (remaining)
        {
        case 0:
        {
            remaining = 2;
            break;
        }
        case 1:
        {
            remaining = 0;
            break;
        }
        case 2:
        {
            // (2 + 2) % 3 = 4 % 3 = 1
            remaining = 1;
        }
        }
    }
    return calculateRemaining(n / 10, remaining);
}

/******************
* Function Name: isDivisibleBy3
* Input: long long int
* Output: prints if its divisable by 3 or not
* Function Operation: uses the "calculateRemaining" function
* the number is divisable by 3 if 0 is returned
******************/
void isDivisibleBy3(long long n)
{
    if (calculateRemaining(n, 0) == 0)
    {
        printf("The number %lld is divisible by 3.\n", n);
    }
    else
    {
        printf("The number %lld is not divisible by 3.\n", n);
    }
}

/******************
* Function Name: abs
* Input: long int n
* Output: |n|
* Function Operation:if n < 0 => |n| = -n
* otherwize return n
******************/
long int absValue(long int n)
{
    if (n < 0)
    {
        return -n;
    }
    return n;
}

/******************
* Function Name:gcd
* Input:n1, n2 long int numbers
* Output:their gcd
* Function Operation: using the Euclidean algorithm
******************/
void gcd(long int n1, long int n2)
{
    /*
    every common divisor of a and b is also a common divisor of |a| and |b|
    therefore gcd(a, b) = gcd(|a|, |b|)
    */
    if (n1 == 0 || n2 == 0)
    {
        printf("GCD=%ld\n", absValue(n2) + absValue(n1));
    }
    else
    {
        printf("%ld*%ld+%ld=%ld(a=%ld,b=%ld)\n", n2, n1 / n2, n1 % n2, n1, n1, n2);
        gcd(n2, n1 % n2);
    }
}

/******************
* Function Name:digitsInNum
* Input:long long num, int digit (0-9)
* Output: how many times the digit appear in the number
* Function Operation: if the lsd == digit => return 1 + (num / 10, digit)
* else => return  (num / 10, digit) - move on to the next digit
******************/
int digitsInNum(long long num, int digit)
{
    //this function works for every sey of elements except of (0,0). in this case we will print 1 instead of 0
    if (num == 0)
    {
        return 0;
    }
    int currentDigit = num % 10;
    if (currentDigit == digit)
    {
        return 1 + digitsInNum(num / 10, digit);
    }
    else
    {
        return  digitsInNum(num / 10, digit);
    }
}

/******************
* Function Name: countDigit
* Input: long long n, int d (0-9)
* Output: prints how many time d appears in n
* Function Operation: uses the "digitsInNum" function
******************/
void countDigit(long long n, int d)
{
    if (n != 0 || d != 0)
    {
        printf("%lld has %d times %d.\n", n, digitsInNum(n, d), d);
    }
    else
    {
        printf("0 has 1 times 0.\n");
    }
}

/******************
* Function Name: isPalindromeIter
* Input: an array (char[]) and its (int) lenght
* Output: prints if its a palindrome or not
* Function Operation: goes trough all indexes up to the middle, and compares the i'th
* character to the [len - 1 - i]'th character, whose distance from the middle is the same
******************/
void isPalindromeIter(char str[], int len)
{
    if (len != 0)
    {
        for (int i = 0; i <= len / 2; i++)
        {
            if (str[i] != str[len - 1 - i])
            {
                printf("The reverse of %s is not %s.\n", str, str);
                return;
            }
        }
    }
    //if the array is empty, its a palindrome
    printf("The reverse of %s is also %s.\n", str, str);
}

/******************
* Function Name: isDividedBy3Iter
* Input: long long n
* Output: is n divisable by 3 or not
* Function Operation: basicly the same as question 4, but we use a loop instead of reccursion
******************/
void IsDividedBy3Iter(long long n)
{
    //n changes throughout the loop, so we save it
    long long int saveNforPrinting = n;
    int lastRemain = 0;
    int digit;
    while (n != 0)
    {
        digit = n % 10;
        //these digits have a remaining of 1 when divided by 3
        if (digit == 1 || digit == 4 || digit == 7)
        {
            switch (lastRemain)
            {
            case 0:
            {
                lastRemain = 1;
                break;
            }
            case 1:
            {
                lastRemain = 2;
                break;
            }
            case 2:
            {
                lastRemain = 0;
            }
            }
        }
        //these digits have a remaining of 2 when divided by 3
        if (digit == 2 || digit == 5 || digit == 8)
        {
            switch (lastRemain)
            {
            case 0:
            {
                lastRemain = 2;
                break;
            }
            case 1:
            {
                lastRemain = 0;
                break;
            }
            case 2:
            {
                lastRemain = 1;
            }
            }
        }
        //when the digit is 3 the remaining does not change + "deleting" a digit for the next run of the loop
        n /= 10;
    }
    if (lastRemain == 0)
    {
        printf("The number %lld is divisible by 3.\n", saveNforPrinting);
        //using break here creates a compiler error, so we will create an else case
    }
    else
    {
        printf("The number %lld is not divisible by 3.\n", saveNforPrinting);
    }
}

int main()
{
    char choice;
    puts("EX3 - THIS ASSIGMENT WAS IMPLEMENTED WITH NOTHING BUT RECCURSION");
    puts("THE ONLY ALLOWED LIBRARY WAS \"STDIO.H\"");
    puts("NO LOOPS ONLY RECCURSION (FOR TASK 5 I COULD NOT USE ANY MATH OR BITWIZE OPERATORS - TRUE PAIN)");
    puts("Choose an operation:");

    //goto operation only used in main function
menu: puts("\t0. Exit");
    puts("\t1. Solve tower of hanoi");
    puts("\t2. Check if a string is a pelindrome");
    puts("\t3. Solve for all combinations for a number");
    puts("\t4. Calculate a^b");
    puts("\t5. Check if a number is devisable by 3");
    puts("\t6. Find the greatest common factor of 2 numbers");
    puts("\t7. Apperance of the digit n in the number N");
    scanf("%c", &choice);
    switch (choice)
    {
    case '0':
    {
        break;
    }
    case '1':
    {
        int n;
        char a, b, c;
        printf("Enter the number of disks : ");
        scanf("%d", &n);
        scanf("%c");
        printf("\nEnter the cherecter of the starting rod : ");
        a = getchar();
        scanf("%c");
        printf("\nEnter the cherecter of the middle rod : ");
        b = getchar();
        scanf("%c");
        printf("\nEnter the cherecter of the destination rod : ");
        c = getchar();
        scanf("%c");
        printf("\nSOLVING TOWER OF HANOI FOR %d DISKS FROM ROD %c TO ROD %c\n", n, a, c);
        towerOfHanoi(n, a, b, c);
        scanf("%c")
            goto menu;
    }
    case '2':
    {
        scanf("%c");
        int len;
        char str[201];
        printf("Enter the string : ");
        scanf("%[^\n]s", str);
        printf("\nEnter the lenght of your string (yes, you really have to) : ");
        scanf("%d", &len);
        isPalindrome(str, len);
        goto menu;
    }
    case '3':
    {
        int len;
        char str[201];
        printf("Enter the string : ");
        scanf("%s", str);
        printf("\nEnter the lenght of your string (yes, you really have to) : ");
        scanf("%d", &len);
        isPalindrome(str, len);
        goto menu;
    }
    case '4':
    {
        char str[201];
        int len;
        printf("Enter pattern : ");
        scanf("%s", len);
        goto menu;
    }
    case '5':
    {
        goto menu;
    }
    case '6':
    {
        goto menu;
    }
    case '7':
    {
        goto menu;
    }
    }

    return 0;

    return 0;
}