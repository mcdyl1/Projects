# File:    proj1.py
# Author:  Dylan McQuaid
# Date:    10/18/17
# Section: 27
# E-mail:  mcdyl1@umbc.edu
# Description: gives the user options to create a playlist from or search a
#              database of songs created into a 2D list. The program then 
#              creates its own 2D list of the songs matching the criteria
#              given by the user

# main menu options
USER_QUIT    = -1
MENU_SEARCH  = 0
MENU_CREATE  = 1

MIN_SONG_NUM = 0
MAX_SONG_NUM = 10  # maximum number of songs in a playlist, row

# these constants are used to give names to the columns of the 2D list
YEAR     = 0
ARTIST   = 1
TITLE    = 2
GENRE    = 3
DURATION = 4
TEMPO    = 5

DETAIL_MIN = YEAR   # minimum value; used for getValidInput()
DETAIL_MAX = TEMPO  # maximum value;

PLAYLIST_MIN = 1 #min value for choosing type of playlist
PLAYLIST_MAX = 3 #max value for choosing type of playlist

############################################################################
# make2DList() constructs a 2D list from a file that contains information
#              about songs in a music library, such as year and artist
# Input:       filename;   a string of the music library's file name
# Output:      resultList; a 2D list of that file in the format below
#  __________________________________________________
# |   0  |    1   |   2   |   3   |     4    |   5   |
# |------|--------|-------|-------|----------|-------|
# | year | artist | title | genre | duration | tempo | 
# |--------------------------------------------------|
# | year | artist | title | genre | duration | tempo | 
# |--------------------------------------------------|
# | year | artist | title | genre | duration | tempo | 
# |--------------------------------------------------|
# | year | artist | title | genre | duration | tempo | 
#  --------------------------------------------------
def make2DList(filename):
    fileObj = open(filename)
    lines = fileObj.readlines()
    fileObj.close()

    resultList = []
    index = 0

    while index < len(lines):
        line = lines[index].strip().split(",")
        line[YEAR]     = int(line[YEAR]) 
        line[DURATION] = float(line[DURATION])
        line[TEMPO]    = float(line[TEMPO])
        resultList.append(line)
        index += 1

    return resultList

############################################################################
# displayMainMenu() prints out the main menu of the program
# Input: None
# Output: None
def displayMainMenu():
    print("What would you like to do next?")
    print("\t0) Perform a search.")
    print("\t1) Create a playlist.")
    print()

############################################################################
# displayOptions() prints out a list of six different attributes shown for
#                  each song
# Input: None
# Output: None
def displayOptions():
    print("0 - Year")
    print("1 - Artist")
    print("2 - Title")
    print("3 - Genre")
    print("4 - Duration")
    print("5 - Tempo")

############################################################################
# displayPLOptions() prints out the three different options for creating a
#                    playlist
# Input: None
# Output: None
def displayPLOptions():
    print("1 - Year")
    print("2 - Artist")
    print("3 - Genre")

############################################################################
# printSongs() Prints the details of every song in the given 2D list
# Input: songs; 2D list with each song being a separate interior list
# Output: None
def printSongs(songs):
    index = 0
    #loops and prints all the songs in final list
    while index < len(songs):
        print(songs[index])
        index += 1
    

############################################################################
# getValidInput() gets a valid integer from the user that falls within the 
#                 appropriate range; uses a prompt provided at function call
# Input: prompt; a string to use when asking for input
#        minimum; a minimum integer
#        maximum; a maximum integer
# Output: userInput; an integer within the range
def getValidInput(prompt, minimum, maximum):
    userInput = int(input(prompt))
    #prompts user until input is valid
    while userInput < minimum or userInput > maximum:
        print("You entered invalid input.")
        userInput = int(input(prompt))

    return userInput
    
############################################################################
# colToString() Converts a number to the corresponding column heading
# Input: searchChoice; index of a column
# Output: string; contains the column heading
def colToString(searchColumn):
    if searchColumn == YEAR:
        return "Year"
    elif searchColumn == ARTIST:
        return "Artist"
    elif searchColumn == TITLE:
        return "Title"
    elif searchColumn == GENRE:
        return "Genre"
    elif searchColumn == DURATION:
        return "Duration"
    elif searchColumn == TEMPO:
        return "Tempo"

############################################################################
# songToString() Converts a song's info into a string of its details
# Input: 1D list; contains the details of a single song
# Output: final string; the string with all details
def songToString(song):
    index = 0
    while index <= len(song):
        #concatenates all songs info into a single string
        songDescription = str(song[YEAR]) + " - " + song[GENRE] + " - " + song[ARTIST] + " - " + song[TITLE]
        index += 1
    return songDescription

############################################################################
# search() creates a 2D list of all the songs that match the value being
#          searched for in the selected column
# Input: searchInput; integer between 0 and 5(representing year, artist, title
#        genre, duration, or temp, respectively)
#        searchString; value being searched for
#        songs; 2D list of each song
# Output: 2D list; list of all songs that match the value in the selected
#         column
def search(col, value, songs):
    #row vertical
    #column horizontal
    matchedSongs = []
    index = 0
    while index < len(songs):
        #for comparing column containing duration or tempo detail
        if col == TEMPO or col == DURATION:
            #converts value to float to compare to songs specific tempo or duration
            if float(value) <= songs[index][col]:
                #adds to list if found a correct tempo or duration
                matchedSongs.append(songToString(songs[index]))
        if value == str(songs[index][col]):
            matchedSongs.append(songToString(songs[index]))
        index += 1
    return matchedSongs
    

############################################################################
# createPlaylist() creates 2D list of all songs within the type selected by
#                  the user; limits the list to a length of length
# Input: songs; 2D list of each song
#        playlistColumn; integer between 1 and 3(representing the playlist options
#                of year, artist, or genre, respectively)
#        playlistLength; positive integer between 0 and 10(max length of a 
#                        playlist is 10 songs)
# Output: 2D list; a 2D list of the first length songs that match the value
#                  for the selected choice
def createPlaylist(playlistColumn, length, songs):
    index = 0
    foundSongs = [] #for search
    playlist = [] #trimmed down search results
    #changes the playlistColumns to match the search values
    if playlistColumn == 1:
        playlistColumn = YEAR
    elif playlistColumn == 2:
        playlistColumn = ARTIST
    elif playlistColumn == 3:
        playlistColumn = GENRE
    #changes playlist col number to a string for following print statement
    playlistString = colToString(playlistColumn)
    print("Enter a", playlistString, "to make a playlist of: ", end="")
    playlistOf = input()
    print()
    #gets songs from search that match the playlist value to search for
    foundSongs = search(playlistColumn, playlistOf, songs)
    #trims down the list from search to the length selected by the user
    while index < length and index < len(foundSongs):
        playlist.append(foundSongs[index])
        index += 1
    #tells user if the program finds no matches
    if len(playlist) == 0:
        print("Sorry, the", playlistString, playlistOf, "doesn't exist in your library.")
        print()
    return playlist
############################################################################
    


def main():
    print("This is the Music Organizer 3000!")
    print()
    filename = input("Enter the filename of your song library: ")
    print()
    #makes the 2D list of all songs in library
    songs = make2DList(filename)
    #displays the main menu and gets the users choice for what to do
    displayMainMenu()
    menuChoice = ("Enter a menu choice(0-1) or -1 to exit: ")
    menuInput = getValidInput(menuChoice, USER_QUIT, MENU_CREATE)

    while menuInput != USER_QUIT:
        #if the user enters 0
        if menuInput == MENU_SEARCH:
            print("Search by...")
            displayOptions()
            searchChoice = ("Enter a column choice(0-5): ")
            #gets what detail to search for
            searchColumn =  getValidInput(searchChoice, DETAIL_MIN, DETAIL_MAX)
            #changes the input for detail to corresponding string
            searchString = colToString(searchColumn)
            print("Enter the", searchString, "you want to search for: ", end=" ")
            #gets the specific value for the detail selected
            searchFor = input()
            print()
            #runs the search function returning the new list
            searchResults = search(searchColumn, searchFor, songs)
            #tells the user if nothing was found or just prints what was found
            if len(searchResults) == 0:
                print("Your search returned no results")
            elif len(searchResults) != 0:
                print("Found the following: ")
                printSongs(searchResults)
        
        #if the user enters 1
        elif menuInput == MENU_CREATE:
            print("What playlist type do you want to create?")
            displayPLOptions()
            #gets what type of playlist to make
            playlistChoice = ("Choose a playlist to make: ")
            playlistColumn = getValidInput(playlistChoice, PLAYLIST_MIN, PLAYLIST_MAX)
            #gets how long the user wants the playlist to be
            lengthPrompt = ("Enter the length of your playlist (0-10): ")
            lengthOfPlaylist = getValidInput(lengthPrompt, MIN_SONG_NUM, MAX_SONG_NUM)
            #returns the new list created to the appropriate length
            playlistResults = createPlaylist(playlistColumn, lengthOfPlaylist, songs)
            #tells user if no results were found, or prints what was found
            if len(playlistResults) == 0:
                print("Unable to create a playlist based on that criteria.")
                print()
            else:
                print("Created this playlist: ")
                printSongs(playlistResults)
        
        #ask for menuInput again, restarting the program
        print()
        displayMainMenu()
        menuInput = getValidInput(menuChoice, USER_QUIT, MENU_CREATE)
    #prints if user enters -1
    print("Thanks for using the Music Organizer 3000, come again!")
            
            
    
main()

