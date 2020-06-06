# File: proj2.py
# Author: Dylan McQuaid
# Date: 10/31/17
# Section: 27
# Email: mcdyl1@umbc.edu
# Description: Program gets input from the user for setting up a board and
#              number of iterations to run a game of "Conway's Game of Life"


MIN_LENGTH = 1 #for making board
MIN_DIM = 0 #minimum dimension for getting alive cells
MIN_ITER = 0 #minimum number of iterations
QUIT = "q" #for user to exit program
ALIVE = "A" #alive cell
DEAD = "." #dead cell
NO_MAX = "none" #if input being checked has no max value

##################################################################
# nextIteration(): applies rules of the game to board
# Input: board; 2D list of original board
#        rowLength; integer for width
#        colLength; integer for length
#
# Output: changingBoard; 2D list of new changed board
def nextIteration(board, rowLength, colLength):
    changingBoard = drawBoard(rowLength, colLength)
    colSize = colLength - 1
    rowSize = rowLength - 1
    for i in range(len(board)):

        for j in range(len(board[i])):
            aliveCount = 0
            deadCount = 0

            if board[i][j] == ALIVE:

            #middle board
                if i != 0 and i != rowSize and j != 0 and j != colSize:
                    if board[i - 1][j] == ALIVE: #checks up above
                        aliveCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        aliveCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        aliveCount += 1
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        aliveCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        aliveCount += 1

            # top left corner
                if i == 0 and j == 0:
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        aliveCount += 1

            #top right corner
                elif i == 0 and j == colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        aliveCount += 1

            #top middle 
                elif i == 0 and j != colSize and j != 0:
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        aliveCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1

            #middle left
                elif i != 0 and i != rowSize and j == 0:
                    if board[i - 1][j] == ALIVE: #checks below
                        aliveCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        aliveCount += 1

            #bottom left corner
                elif i == rowSize and j == 0:
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1

            #bottom middle
                elif i == rowSize and j != colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        aliveCount += 1
                    if board[i - 1][j] == ALIVE: #checks up
                        aliveCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        aliveCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        aliveCount += 1

            #bottom right corner
                elif i == rowSize and j == colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        aliveCount += 1
                    if board[i - 1][j] == ALIVE: #checks up
                        aliveCount += 1

            #right middle
                elif i != 0 and i != rowSize and j == colSize:
                    if board[i - 1][j] == ALIVE: #checks up
                        aliveCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        aliveCount += 1
                    if board[i][j - 1] == ALIVE: #checks left
                        aliveCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        aliveCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        aliveCount += 1

##################################################################
            
            elif board[i][j] == DEAD:
            #top left
                if i == 0 and j == 0:
                    if board[i + 1][j] == ALIVE: #checks below 
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        deadCount += 1

            #top right corner
                elif i == 0 and j == colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        deadCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        deadCount += 1

            #top middle
                elif i == 0 and j != colSize and j != 0:
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        deadCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        deadCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        deadCount += 1

            #middle left
                elif i != 0 and i != rowSize and j == 0:
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        deadCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        deadCount += 1

            #bottom left corner
                elif i == rowSize and j == 0:
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1

            #bottom middle
                elif i == rowSize and j != 0 and j != colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        deadCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        deadCount += 1

            #bottom right corner
                elif i == rowSize and j == colSize:
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        deadCount += 1
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1

            #right middle
                elif i != 0 and i != rowSize and j == colSize:
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        deadCount += 1
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        deadCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        deadCount += 1

            #middle board
                elif i != 0 and i != rowSize and j != 0 and j != colSize:
                    if board[i - 1][j] == ALIVE: #checks above
                        deadCount += 1
                    if board[i - 1][j - 1] == ALIVE: #checks up, left diagonal
                        deadCount += 1
                    if board[i - 1][j + 1] == ALIVE: #checks up, right diagonal
                        deadCount += 1
                    if board[i][j - 1] == ALIVE: #checks left
                        deadCount += 1
                    if board[i][j + 1] == ALIVE: #checks right
                        deadCount += 1
                    if board[i + 1][j] == ALIVE: #checks below
                        deadCount += 1
                    if board[i + 1][j - 1] == ALIVE: #checks down, left diagonal
                        deadCount += 1
                    if board[i + 1][j + 1] == ALIVE: #checks down, right diagonal
                        deadCount += 1

            #rules of game
            if aliveCount < 2:
                changingBoard[i][j] = DEAD
            if aliveCount == 2 or aliveCount == 3:
                changingBoard[i][j] = ALIVE
            elif aliveCount > 3:
                changingBoard[i][j] = DEAD
            if deadCount == 3:
                changingBoard[i][j] = ALIVE
    
    return changingBoard
            
##################################################################
# printBoard(): formats board to print neatly
# Input: gameBoard; 2D list
#
# Output: None
def printBoard(gameBoard):
    #prints 2D list in box shape
    row = 0
    while row < len(gameBoard):
        col = 0
        while col < len(gameBoard[row]):
            print(gameBoard[row][col], end="")
            col += 1
        print()
        row += 1

##################################################################
# getValidInput(): makes sure input is correct
# Input: prompt; string to get userInput
#        errorPrompt; string if userInput not correct
#        minimum; integer
#        maximum; integer
#
# Output: userInput; int or string
def getValidInput(prompt, errorPrompt, minimum, maximum):
    #inputs with no maximum value
    if maximum == NO_MAX:
        userInput = int(input(prompt))
        while userInput < minimum:
            print(errorPrompt)
            userInput = int(input(prompt))

    else:
        userInput = input(prompt)
        if userInput == QUIT:
            return userInput
        while int(userInput) < minimum or int(userInput) > maximum:
            print(errorPrompt)
            userInput = input(prompt)
            if userInput == QUIT:
                return userInput
    return int(userInput)

##################################################################
# drawBoard(): creates the board to proper length
# Input: rowLength; integer for dimension
#        colLength; integer for dimension
#
# Output: gameBoard; 2D list with proper dimensions
def drawBoard(rowLength, colLength):
    gameBoard = []
    row = []
    #creates a 2D list
    for i in range(colLength):
        row.append(DEAD)

    for i in range(rowLength):
        gameBoard.append( row[:])#deep copy

    return gameBoard

##################################################################
# aliveBoard(): makes spots on board alive that user
#               wants
# Input: rowNum; integer for y coordinate
#        colNum; integer for x coordinate
#        gameBoard; 2D list with all dead cells
#
# Output: gameBoard; 2D list with now some alive cells
def aliveBoard(rowNum, colNum, gameBoard):
    gameBoard[rowNum][colNum] = ALIVE

    return gameBoard

##################################################################
def main():

    #dimensions for creating the board
    numRowsPrompt = ("Enter number of rows: ")
    numRowsError = ("\tNot valid; Enter a number greater than or equal to 1")
    numRows = getValidInput(numRowsPrompt, numRowsError, MIN_LENGTH, NO_MAX)
    
    numColsPrompt = ("Enter number of columns: ")
    numColsError = ("\tNot valid; Enter a number greater than or equal to 1")
    numCols = getValidInput(numColsPrompt, numColsError, MIN_LENGTH, NO_MAX)
    
    gameBoard = drawBoard(numRows, numCols)
    
    #index always 1 less than length
    rowSize = numRows - 1
    colSize = numCols - 1
    
    #coordinates(row, col) that user wants to start alive
    rowCellPrompt = ("Enter the row of a cell to turn on(or q to exit): ")
    rowCellError = ("Not valid; Must be between", MIN_DIM, "and", \
                        rowSize, "inclusive")
    colCellPrompt = ("Enter a column for that cell: ")
    colCellError = ("Not valid: Must be between", MIN_DIM, "and", \
                        colSize, "inclusive")
    
    rowCell = ""
    while rowCell != QUIT:
        rowCell = getValidInput(rowCellPrompt, rowCellError, MIN_DIM, rowSize)
        #branches off to rest of the game
        if rowCell == QUIT:
            numIterPrompt = ("How many iterations should I run? ")
            numIterError = ("Not valid; Enter number greater than or equal to 1")
            numIter = getValidInput(numIterPrompt, numIterError, MIN_ITER, \
                                        NO_MAX)

            print("Starting Board: ")
            printBoard(gameBoard)
            count = 1
            
            #runs the game proper amount of times
            while (count - 1) != numIter:
                print("Iteration", count, ":")
                gameBoard = nextIteration(gameBoard, numRows, numCols)
                printBoard(gameBoard)
                print()
                count += 1 

        #gets col number and updates the board
        else:
            colCell = getValidInput(colCellPrompt, colCellError, MIN_DIM, \
                                        colSize)
            gameBoard = aliveBoard(rowCell, colCell, gameBoard)
        
    
main()
