# File: proj3.py
# Author: Dylan McQuaid
# Date: 11/27/17
# Section: 27
# E-mail: mcdyl1@umbc.edu
# Description: This program uses a recursive search algorithm to solve a maze
# read in from file 

# 1, 0, 0, 1
#wall on right, open bottom, open left, wall on top

#constants for indexes representing the sides of the squares
RIGHT = 0
BOTTOM = 1
LEFT = 2
TOP = 3

###############################################################################
# readDimensions(): takes in the file and reads the first
# line to get the rows and cols of the maze
# Input: mazeFile; a txt file opened in main
# Output: dimensionLine; a list of the first line containing
# the dimensions
def readDimensions(mazeFile):

    dimensionLine = mazeFile.readline()
    dimensionLine = dimensionLine.split()

    return (dimensionLine)

###############################################################################
# readFinish(): takes in the file and reads in the second 
# line to get where the finish is located
# Input: mazeFile; a txt file opened in main
# Output: finishLine; a list of the second line containing
# the location of the finish
def readFinish(mazeFile):
    
    finishLine = mazeFile.readline()
    finishLine = finishLine.split()

    return (finishLine)

###############################################################################
# readMaze(): takes in the file and reads in the rest of the
# lines forming them into a 3D list
# Input: mazeFile; a txt file opened in main
#        numRows; int for length of list
#        numCols; int for length of list
# Output: maze; a 3D list representing the final maze
def readMaze(mazeFile, numRows, numCols):

    squareWalls = mazeFile.readlines()
    maze = []
    row = []
    squares = []
    
    #2D list containing squares
    for line in squareWalls:
        squares.append(line.split())
    
    #make 3D list 
    for i in range(len(squareWalls)):
        row.append(squares[i])
        #make rows correct length
        if len(row) == numCols:
            maze.append(row)
            row = []
    
    return maze

###############################################################################
# searchMaze(): recursively finds the path to take from the
# start to find the finish
# Input: maze; 3D list representing the final maze
#        row; int for current row spot
#        col; int for current column spot
#        path; list representing the path so far
#        finishRow; row of finish in 3D list
#        finishCol; col of finish in 3D list
# Output: path; final path of the way to solution or None
#         if no solution is found    
def searchMaze(maze, row, col, path, finishRow, finishCol):

    #Base cases: found solution and start with
    #no where to go
    if row == finishRow and col == finishCol:
        print("Solution Found")
        path.append((row, col))
        return path

    elif maze[row][col][RIGHT] == '1' and maze[row][col][LEFT] == '1' and \
            maze[row][col][TOP] == '1' and maze[row][col][BOTTOM] == '1':
        return None
        
    else:
        
        #Recursive cases for going in each direction
        if maze[row][col][RIGHT] == '0' and (row, col + 1) not in path:
            path.append((row, col))
            rightPath = searchMaze(maze, row, col + 1, path, finishRow, finishCol)
            #check if leads to deadend
            if rightPath != None:
                return path
            path.remove((row, col))

        if maze[row][col][LEFT] == '0' and (row, col - 1) not in path:
            path.append((row, col))
            leftPath = searchMaze(maze, row, col - 1, path, finishRow, finishCol)
            #check if leads to deadend
            if leftPath != None:
                return path
            path.remove((row, col))

        if maze[row][col][TOP] == '0' and (row - 1, col) not in path:
            path.append((row, col))
            topPath = searchMaze(maze, row - 1, col, path, finishRow, finishCol)
            #check if leads to deadend
            if topPath != None:
                return path
            path.remove((row, col))

        if maze[row][col][BOTTOM] == '0' and (row + 1, col) not in path:
            path.append((row, col))
            bottomPath = searchMaze(maze, row +1, col, path, finishRow, finishCol)
            #check if leads to deadend
            if bottomPath != None:
                return path
            path.remove((row, col))
            
        #if no solution is found
        return None

###############################################################################
# getValidInput(): prompt user until input is valid
# Input: prompt; string to give info to user
#        maximum; maximum value that can be entered
# Output: userInput; the correct input taken from the user
def getValidInput(prompt, maximum):

    userInput = int(input(prompt))
    while userInput < 0 or userInput > maximum:
        print("Error, number must be between 0 and", maximum, "(inclusive)")
        userInput = int(input(prompt))

    return userInput

###############################################################################
def main():

    print("Welcome to the Maze Solver!")
    
    filename = input("Enter the filename of the maze: ")
    
    mazeFile = open(filename)
    
    dimensions = readDimensions(mazeFile)

    numRows = int(dimensions[0])
    numCols = int(dimensions[1]) 

    finish = readFinish(mazeFile)

    finishRow = int(finish[0])
    finishCol = int(finish[1])

    maze = readMaze(mazeFile, numRows, numCols)

    startRowPrompt = "Please enter the starting row: "
    startRow = getValidInput(startRowPrompt, (numRows - 1))

    startColPrompt = "Please enter the starting column: "
    startCol = getValidInput(startColPrompt, (numCols - 1))

    path = []

    path = searchMaze(maze, startRow, startCol, path, finishRow, finishCol)
    
    #what to print out based on return of searchMaze
    if path != None:
        for i in range(len(path)):
            print(path[i])
    if path == None:
        print("No solution found")
main()


