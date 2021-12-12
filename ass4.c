/***********
* Roei Cohen
* 325714152
* 01
* ass4
***********/
#include <stdio.h>
#include <string.h>
#include <math.h>
// defines the geomatrical value of a character
#define CHARACTER_VALUE(n) (int)n - 'a' + 1;
// defines the ascii value of an int type digit
#define DIGIT_TO_CHAR(n) (char)n + '0'
// outputs the digit instead of its ascii value (FOR EXAMPLE: F('3') = 3)
#define CHAR_DIGIT_TO_INT_VALUE(n) n - '0'

/******************
* Function Name: dupBoard
* Input: A set of 2D arrays that represent soduku boards boards
* Output: Copys the values from the right board to the left board
* Function Operation: Goes trough all indexes in the right board 
* using 2 nested for loops, and saves the values to the second board
* This is crucial in case the input is bad and we need to revent all changes we made
******************/
void dupBoard(char saveTo[][SIZE * SIZE], char saveFrom[][SIZE * SIZE])
{
	//in case we encountered an error in some functions, we need to reverse all changes we made to the board
	for (int row = 0; row < SIZE * SIZE; row++)
		for (int i = 0; i < SIZE * SIZE; i++)
			saveTo[row][i] = saveFrom[row][i];
}

/******************
* Function Name: countLines
* Input: An array that represents a soduku board
* Output: How many lines there are in the input provided
* Function Operation: The function goes trough all the characters in the input
* Every time we meet a '/' (character the represents a new line), we raise the counter
* At the end, we return "counter + 1" because the last line does not end with a slash
******************/
int countLines(char str[])
{
	//count will store the amount of lines in the input string
	int count = 0;
	//this for loop goes through the array and counts the number of '/' to calculate the amount of lines
	for (int i = 0; i < strlen(str); i++)
		//checking if have a new line
		if (str[i] == '/')
			count++;
	//the last line does not have a '/' at the end of it so we add +1
	return count + 1;
}

/******************
* Function Name: createBoard
* Input: An uninitilized board, and a string
* Output: A set up 2D array that represents a soduku board
* Function Operation: We transfer the values from "str" to "board" and play by the following rules:
* -The character '/' means "fill the current line with spaces, and go to the next line"
* -Small case characters up to a certain point (a, b,...) represent spaces (a = one space, b = two spaces...)
* -The characters '1' - '9' (or '1'-'4', depending on size), are the numbers prefilled on the soduku board
* -All other characters are "variables"
******************/
void createBoard(char board[][SIZE * SIZE], char str[])
{
	//The size of each row/column
	const int sizeSqr = SIZE * SIZE;
	//the largest character that represents "spacebars"
	const char largestCharacter = 'a' + sizeSqr - 1;
	//Checking if we have the correct amount of lines in our input
	if (countLines(str) != sizeSqr)
	{
		//If we dont have EXACLY SIZE^2 lines in our input we print an error massage and stop the proccess
		printf("Error\n");
		return;
	}
	//stores an index of str whose represents the last place in the N'th line currently
	int lastIndexInLine;
	//Stores the current index in str needed to be transfered to the board
	int currentIndex;
	//Stores the current line index of the board, so now we do : BOARD[ROW][LINE_INDEX] = STR[CURRENT_INDEX]
	int lineIndex = 0;
	/*
	* Adds the amount of spaces every time we get 'a', 'b' etc. it helps us sync
	* The currentIndex and the lineIndex correctly
	* For example if we get the letter 'b', we need to increase the lineIndex by 2
	*/
	int totalSpaces = 0;
	//This variable counts the CURRENT AMOUNT of spaces needed to be printed each time
	int spaces;
	/*
	* This variable indicates if we got '/' after going assining 9 characters to the board in the current line
	* If we didnt get '/', it means we have more then 9 characters assined to 1 row in the board
	* so we print an error massage
	*/
	int didWeGetSlash;
	//We may get an error massage, so we need to save the board before we make any changes to it
	char saveBoard[SIZE * SIZE][SIZE * SIZE];
	//Now we save the board in case the input is bad
	dupBoard(saveBoard, board);
	/*
	* This for loop goes through all rows
	* each time it runs a new row is created
	* Its the main proccess
	*/
	for (int row = 0; row <= sizeSqr - 1; row++)
	{
		/*
		* The index needed to be "pulled" from str is calculated
		* by the current  (ROW * (SIZE_SQR + 1)) - COUNT_SPACES
		* We add 1 to SIZE_SQR because the extra index is '/'
		* Then we subtract the amount of total spaces to sync it just right
		*/
		currentIndex = (row * (sizeSqr + 1)) - totalSpaces;
		//stores the last index (we dont subtract 1 to account for the extra '/' index)
		lastIndexInLine = currentIndex + sizeSqr;
		//On each new row we reset the line index to 0
		lineIndex = 0;
		didWeGetSlash = 0;
		//This loop goes throuh the current line (FROM INDEX TO INDEX + 9)
		for (int i = currentIndex; i <= lastIndexInLine; i++, lineIndex++)
		{
			//Checking if we need to go down by a row
			if (str[i] == '/' || i == strlen(str))
			{
				//We make this variable 1, so we know this line has no more then 9 characters
				didWeGetSlash = 1;
				//If we have less then 9 characters, we "fill the gaps" with spacebars
				for (int k = lineIndex; k < sizeSqr; k++, lineIndex++)
				{
					board[row][lineIndex] = ' ';
					/*
					* Increasing the amount of spaces so we can sync
					* between the board and the input string
					*/
					totalSpaces++;
				}
				break;
			}
			//Checking if the input is a character who represents spacebars
			if (str[i] >= 'a' && str[i] <= largestCharacter)
			{
				/*
				* If the user asked for more spacebars then we can store in that line
				* we print an error massage
				*/
				if (str[i] + lineIndex > largestCharacter)
				{
					dupBoard(board, saveBoard);
					printf("Error\n");
					return;
				}

				//CHARACTER_VALUE('a') = 1,  CHARACTER_VALUE('b') = 2 and so on....
				spaces = CHARACTER_VALUE(str[i]);
				for (int k = 0; k < spaces; k++, lineIndex++, totalSpaces++)
					board[row][lineIndex] = ' ';
				/*
				* Adgusting the totalSpaces and lineIndex by 1
				* because when the second main loop repeats it increases thier values by 1
				*/
				totalSpaces--;

				lineIndex--;

				continue;
			}
			//If the character isnt a,b,c... we assign it (It could either be a number or a variable)
			board[row][lineIndex] = str[i];
		}

		//If we checked 9 indexes and didnt encounter even 1 slash, it means the input is bad
		if (!didWeGetSlash)
		{
			dupBoard(board, saveBoard);
			printf("Error\n");
			return;
		}
	}
}

/******************
* Function Name: printBoard
* Input: A board that war previously initilized by "createBoard"
* Output: Prints the board, and spaces it out elegently
* Function Operation: We use 2 for loops and print every index of the board
* -Every new line, we go dows by 1 line
* -Every 3 (or 2..) lines, we go dows an extra line, so we can better see the subgrids
* -Every 3 (or 2..) characters in the current line, we print " | " for the same reason
******************/
void printBoard(char board[][SIZE * SIZE])
{
	const int lastIndex = (SIZE * SIZE) - 1;

	int currentPosition;

	for (int row = 0; row < SIZE * SIZE; row++)
	{
		for (int col = 0; col < SIZE * SIZE; col++)
		{
			printf("%c", board[row][col]);
			/*
			 * look where we print " | " - 01(2)" | "34(5)" | "678
			 * We print " | " every 3 lines, and in c we start counting from 0
			 * So we check if the (index+1) is devisable by 3 
			*/
			if (((col + 1) % SIZE == 0) && col != lastIndex)
				printf(" | ");
		}
		//^^^ same goes here ^^^
		if (((row + 1) % SIZE == 0) && row != lastIndex)
			printf("\n");
		//We go down 1 line to make room for the next row
		printf("\n");
	}
	printf("\n");
}

/******************
* Function Name: checkArrayUniuqe
* Input: A fixed array (only 1-9 or spaces) that represents a row/collumn/sub-square
* Output: If a digit has repeated itself, we return 0, if not - return 1
* Function Operation: We initilize an array with 0
* -The N'th index of the array will tell us how many times the 'N+1' digit has appeared
* If at least 1 digit repeated more that once - return 0
* If EVERY digit has appeared once or not al all - return 1
******************/
int checkArrayUniuqe(char str[SIZE * SIZE])
{
	int numSet[9] = { 0 };
	//value will hold the ascii value of the character
	int value;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		if (str[i] == ' ')
			continue;

		//storing the digit in value
		value = CHAR_DIGIT_TO_INT_VALUE(str[i]);
		//in c we count from 0, and soduku starts from 1, so we adjust it
		if (numSet[value - 1] != 0)
		{
			//we return 0 which means a number has appeared twice and str isnt unique
			return 0;
		}
		//every time a number appears we assign it here
		numSet[value - 1] = 1;
	}
	//we return 1 which means str is unique
	return 1;
}

/******************
* Function Name: testBoard
* Input: A board that was initilized by "createBoard"
* Output: returns 0 if the board is invalid by the rules of the soduku game
* returns 1 if the board is valid
* Function Operation: The board has to pass 3 tests before it can be declared as a 'valid board'
* TEST 1 - We look for invalid characters everything besides 1-9 and spaces
* is counted as an invalid character
* TEST 2 - checking if all rows and columns does not have repeating values
* using the "checkArrayUniuqe" function
* TEST 3 - checking if all sub-squares for repeatations
* If the board has failed any of these tests, we return 0, otherwize, return 1
******************/
int testBoard(char board[][SIZE * SIZE])
{
	const int sizeSqr = SIZE * SIZE;
	int positionInSubSqr;
	char subSquare[SIZE * SIZE], row[SIZE * SIZE], col[SIZE * SIZE];

	//TEST 1# : checking if we have anything else besides 1-9 or spacebar
	for (int i = 0; i < sizeSqr; i++)
		for (int j = 0; j < sizeSqr; j++)
			/*
			* BASICLY :
			* IF (The character is not spacebar AND its not a number between '1' to '9' (size^2))
			*/
			if (board[i][j] != ' ' && (board[i][j] <= '0' || board[i][j] > DIGIT_TO_CHAR(SIZE * SIZE)))
				//We return 0 which means the board is invalid (we have an illegal character
				return 0;

	//TEST 2# : checking all rows and columns for repeatations
	for (int i = 0; i < sizeSqr; i++)
	{
		for (int k = 0; k < sizeSqr; k++)
		{
			row[k] = board[i][k];
			col[k] = board[k][i];
		}

		//if a row/collumn contain the same value twice, the board is illegal
		if (checkArrayUniuqe(row) == 0 || checkArrayUniuqe(col) == 0)
			return 0;
	}

	//TEST 3# : checking all possible subSqueres
	//here we go through all possible subsquares
	for (int startRow = 0; startRow < sizeSqr; startRow += SIZE)
		for (int startColumn = 0; startColumn < sizeSqr; startColumn += SIZE)
		{
			for (int r = startRow; r < startRow + SIZE; r++)
				for (int c = startColumn; c < startColumn + SIZE; c++)
				{
					/*
					* This will return the sub-square of the element we're checking, based on the "cordinates"
					* Since we have the subsquare where it is located
					* we can easily know where the top-left element is - (0,3)(0,6)(0,9)(3,3)...etc
					*/
					positionInSubSqr = (SIZE * (r - startRow)) + (c - startColumn);
					subSquare[positionInSubSqr] = board[r][c];
				}
			//If the sub-square contain repeating values, the board is invalid
			if (checkArrayUniuqe(subSquare) == 0)
				return 0;
		}
	//If we passed all 3 tests, we return 1 which means the board is valid
	return 1;
}

/******************
* Function Name: makeMove
* Input: A board that was initilized by "createBoard", and a string that represents a move
* Output: Changes the board according to the user instructions
* Function Operation: In this one we must check if the array actually represents an actual move
* FIRST - We use "strtok" to identify the type of the move (if the type is invalid, we print an error massage)
* SECONDLY - We coninue using 'strtok' to recive the arguments, and make sure that they are valid
* THE MOVE WILL BE EXECUTED ONLY AFTER WE MADE SURE THAT THE MOVE AND THE ARGUMENTS ARE OK!
******************/
void makeMove(char board[][SIZE * SIZE], char move[])
{
	//We will refer to all characters, row, columns indexes as "ARGUMENTS" (args for short)
	int argsCount = 0, maxArguments, lastIndex = SIZE * SIZE - 1;
	char* token;
	//The same constant as "largestCharacter" from "createBoard"
	const char LastcharacterToCheck = 'a' + lastIndex;
	//Having the last character a "," is an illegal move
	if (move[strlen(move) - 1] == ',')
	{
		//We print an error massage and cancel the move operation
		printf("Error\n");
		return;
	}
	//Now the token points at move (before the ',')
	token = strtok(move, ",");
	//We have 4 possible move types, so we check for each one of them
	if (token != NULL)
	{
		//i dont like doing : !strcmp(token, "replaceAll") because it logicly messes with my mind sometimes
		if (strcmp(token, "replaceAll") == 0)
		{
			/*
			* This variable will check if the first argument appears in the board
			* We'll get back to it at the end
			*/
			int isFirstArgUseful = 0;
			//Will contain both arguments
			char args[2];
			// args[0], args[1] - we count from 0
			maxArguments = 1;
			token = strtok(NULL, ",");
			while (token != NULL)
			{
				/*
				* If len =/= 1 it means we either have NULL or more then 1 character, in both cases
				* the move is illegal so we print an error massage
				* also argument such as ' ' or '/' are also illegal
				*/
				if (strlen(token) != 1 || argsCount > maxArguments || *token == '/' || *token == ' ')
				{
					printf("Error\n");
					return;
				}
				args[argsCount] = *token;
				token = strtok(NULL, ",");
				argsCount++;
			}

			/*
			* now we need to make sure that the arguments are valid (not 'a','b' etc)
			* Looking for illegal characters
			*/
			if (args[2] >= 'a' && args[2] <= LastcharacterToCheck)
			{
				printf("Error\n");
				return;
			}
			//After making sure the move is valid, we can execute it
			for (int row = 0; row <= lastIndex; row++)
			{
				for (int col = 0; col <= lastIndex; col++)
				{
					//Replace every args[0] with args[1]
					if (board[row][col] == args[0])
					{
						/*
						* Changing "isFirstArgUseful" to 1, the variable now indicates
						* that the first argument appeared at least once in the board
						*/
						isFirstArgUseful = 1;
						board[row][col] = args[1];
					}
				}
			}
			/*
			* If this variable did not change to 1, it means the first argument 
			* does not appear in the board, so we print an error massage
			*/
			if (isFirstArgUseful == 0)
			{
				printf("Error\n");
				return;
			}
			return;
		}
		if (strcmp(token, "change") == 0)
		{
			// args[0], args[1], args[2] - we count from 0
			maxArguments = 2;
			char args[3];
			token = strtok(NULL, ",");
			while (token != NULL)
			{
				/*
				* If len =/= 1 it means we either have NULL or more then 1 character, in both cases
				* the move is illegal so we print an error massage
				* Also argument such as ' ' or '/' are also illegal
				* The last condition checks that
				* the first 2 arguments have values between '0' to '8'(lastIndex)
				*/
				if (strlen(token) != 1 || argsCount > maxArguments || *token == ' ' || *token == '/' ||
					(argsCount < 2 && (*token < '0' || *token > DIGIT_TO_CHAR(lastIndex))))
				{
					printf("Error\n");
					return;
				}
				args[argsCount] = *token;
				token = strtok(NULL, ",");
				argsCount++;
			}
			/*
			* now we need to make sure that the last argument is valid (not 'a','b' etc)
			* Looking for illegal characters
			*/
			if (args[2] >= 'a' && args[2] <= LastcharacterToCheck)
			{
				printf("Error\n");
				return;
			}
			board[CHAR_DIGIT_TO_INT_VALUE(args[0])][CHAR_DIGIT_TO_INT_VALUE(args[1])] = args[2];
			return;
		}
		if (strcmp(token, "add") == 0)//locationRow, locationCol, char
		{
			// args[0], args[1], args[2] - we count from 0
			maxArguments = 2;
			char args[3];
			token = strtok(NULL, ",");
			while (token != NULL)
			{
				/*
				* If len =/= 1 it means we either have NULL or more then 1 character, in both cases
				* the move is illegal so we print an error massage
				* Also argument such as ' ' or '/' are also illegal
				* The last condition checks that
				* the first 2 arguments have values between '0' to '8'(lastIndex)
				*/
				if (strlen(token) != 1 || argsCount > maxArguments || *token == ' ' || *token == '/' ||
					(argsCount < 2 && (*token < '0' || *token > DIGIT_TO_CHAR(lastIndex))))
				{
					printf("Error\n");
					return;
				}
				args[argsCount] = *token;
				token = strtok(NULL, ",");
				argsCount++;
			}
			/*
			* now we need to make sure that the last argument is valid (not 'a','b' etc)
			* Looking for illegal characters
			*/
			if (args[2] >= 'a' && args[2] <= LastcharacterToCheck)
			{
				printf("Error\n");
				return;
			}
			if (board[CHAR_DIGIT_TO_INT_VALUE(args[0])][CHAR_DIGIT_TO_INT_VALUE(args[1])] != ' ')
			{
				printf("Error\n");
				return;
			}
			board[CHAR_DIGIT_TO_INT_VALUE(args[0])][CHAR_DIGIT_TO_INT_VALUE(args[1])] = args[2];
			return;
		}
		if (strcmp(token, "delete") == 0)
		{
			int args[2];
			// args[0], args[1] - we count from 0
			maxArguments = 1;
			token = strtok(NULL, ",");
			while (token != NULL)
			{
				/*
				* If len =/= 1
				* it means we either have NULL or more then 1 character, in both cases
				* the move is illegal so we print an error massage
				* The last 2 conditions check that the first 2 arguments
				* contain values between '0' to '8'(lastIndex)
				*/
				if (strlen(token) != 1 || argsCount > maxArguments || *token < '0' ||
					*token > DIGIT_TO_CHAR(lastIndex))
				{
					printf("Error\n");
					return;
				}
				args[argsCount] = CHAR_DIGIT_TO_INT_VALUE(*token);
				token = strtok(NULL, ",");
				argsCount++;
			}
			board[args[0]][args[1]] = ' ';
			return;
		}
		printf("Error\n");
		return;
	}
	printf("Error\n");
}

/******************
* Function Name: isSameBoard
* Input: 2, 2D arrays that represents boards
* Output: returns 1 if the boards are the same
* Otherwize, we print the first inequality and return 0
* Function Operation: This algorithm is simple
* We go through all indexes and check for differences using 2 nested for loops
* THIS PROCCES IS POSSIBLE WITH 1 LOOP HOWEVER ITS HARDER TO EXPLAIN, UNDERSTAND AND MAKE CHANGES TO
******************/
int isSameBoard(char board1[][SIZE * SIZE], char board2[][SIZE * SIZE])
{
	int lastIndex = SIZE * SIZE - 1;
	//This algorithm is simple, we go through all indexes and check for differences
	for (int row = 0; row <= lastIndex; row++)
		for (int col = 0; col <= lastIndex; col++)
			if (board1[row][col] != board2[row][col])
			{
				//If we found a different index, we'll print the row and collumn indexes
				printf("Found inequality on row %d col %d.\n", row, col);
				//We return 0 which means the boards are not same
				return 0;

			}
	//If we didnt find any differences, we return 1 which means the boards are the same
	return 1;
}

/******************
* Function Name: fill
* Input: A fixed array (only 1-9 or spaces) that represents a row/collumn/sub-square
* Output: Fills the line in the missing index, if possible 
* Function Operation: In this process, we go through the line, and look for 2 things
* -How many missing characters there are (int count)
* -If there is only 1 number missing, we fill it
* -The actual process is explaines beautifly in the code below
* The point of this function is to complete the board
******************/
void fill(char line[SIZE * SIZE])
{
	//every time we get a digit, we save it in the set
	int numSet[9] = { 0 };
	//count counts the amount of missing characters, and missingIndex will save the index
	int count = 0, missingIndex;
	//missing will hold the value of the missing character
	char missing;
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		if (line[i] == ' ')
		{
			missingIndex = i;
			count++;
			continue;
		}
		//writing 1 on the Nth place in the numSet
		numSet[CHAR_DIGIT_TO_INT_VALUE(line[i] - 1)] = 1;
	}
	//If (we only have 1 missing spot which we can fix)
	if (count == 1)
	{
		//this for loop will look for zeros in numSet, and will assign the index to the line
		for (int i = 0; i < SIZE * SIZE; i++)
		{
			if (numSet[i] == 0)
			{
				missing = DIGIT_TO_CHAR(i + 1);
				line[missingIndex] = missing;
				return;
			}
		}
	}
}

/******************
* Function Name: completeBoard
* Input: A board that was initilized by "createBoard"
* Output: completes the board according to the soduku rules, if possible
* Function Operation: The board goes 2 several processes and its presaved in case we encounter an error
* FIRST - We check if the board is valid, using the "testBoard" function
* SECONDLY - We save the board in case it turnes out to be not "Almost completes"
* THEN - We fill all 9 rows and columns, if possible
* AFTER THAT - We access all 9 sub-squares, and fill them too (again, if possible)
* After all of this process, if the board is not 100% complete, it means it wasnt "Almost completed"
* and in that case, we print "error" and revert all changes
******************/
void completeBoard(char board[][SIZE * SIZE])
{
	int positionInSubSqr;
	char saveBoard[SIZE * SIZE][SIZE * SIZE];
	char row[SIZE * SIZE], col[SIZE * SIZE], subSquare[SIZE * SIZE];
	//First we test the board to make sure the input isnt bad
	if (!testBoard(board))
	{
		printf("Error\n");
		return;
	}
	//The board is legal and may or may not have an instant solution
	dupBoard(saveBoard, board);
	//first we fill the rows and collumns
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		for (int k = 0; k < SIZE * SIZE; k++)
		{
			row[k] = board[i][k];
			col[k] = board[k][i];
		}
		fill(row);
		fill(col);
		//now we assign the new values from the arrays (char row[], col[]) to the board
		for (int k = 0; k < SIZE * SIZE; k++)
		{
			if (board[i][k] != row[k])
				board[i][k] = row[k];
			if (board[k][i] != col[k])
				board[k][i] = col[k];
		}
	}
	/*
	* Accessing all 9 3*3 sub-squares on a 9*9 arrays reqires 4 nested loops to be readable
	* each sub-square has its own "starting_row" and "sartting_col" combination
	*/
	for (int startRow = 0; startRow < SIZE * SIZE; startRow += SIZE)
	{
		for (int startColumn = 0; startColumn < SIZE * SIZE; startColumn += SIZE)
		{

			for (int r = startRow; r < startRow + SIZE; r++)
				for (int c = startColumn; c < startColumn + SIZE; c++)
				{
					/*
					* Each NEW row has 3 digits
					* so we multiply 3*(r-startRow) and add the digits in the current line
					*/
					positionInSubSqr = (SIZE * (r - startRow)) + (c - startColumn);
					subSquare[positionInSubSqr] = board[r][c];
				}
			//filling the sub-Square
			fill(subSquare);
			int rowForSquare, colForSquare, newRows, newCols;
			for (int i = 0; i < SIZE * SIZE; i++)
			{
				//each New row is "created" after 3 digits, so we add that "start_row"
				newRows = i / SIZE;
				//The amount of columns is "reseted" every 3 indexes
				newCols = i % 3;
				rowForSquare = startRow + newRows;
				colForSquare = startColumn + newCols;
				if (board[rowForSquare][colForSquare] != subSquare[i])
				{
					board[rowForSquare][colForSquare] = subSquare[i];
					break;
				}
			}
		}
	}
	//If the board is "Almost Done", it means it should be filled at this point
	for (int i = 0; i < SIZE * SIZE; i++)
	{
		for (int k = 0; k < SIZE * SIZE; k++)
		{
			if (board[i][k] == ' ')
			{
				/*
				* If the board is not completed at this point
				* it means the input was a non completed valid board
				*/
				dupBoard(board, saveBoard);
				printf("Error\n");
				return;
			}
		}
	}
}
//END OF CODE
