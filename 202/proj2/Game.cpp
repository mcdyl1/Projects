#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

Game::Game(){
  cout << "Welcome to Dragon Wars" << endl;
  cout << "What is your name: " << endl;
  getline(cin, m_name);
  LoadDragons();

}

void Game::LoadDragons(){
  string dragonName;
  string dragonType;
  string dragonMaxSizeStr;
  string dragonRarityStr;
  

  //reading and loading data from file
  ifstream infile(PROJ2_DRAGONS.c_str());
  if(infile.is_open()){

    while(infile){
      getline(infile, dragonName, ',');
      getline(infile, dragonType, ',');
      getline(infile, dragonMaxSizeStr, ',');
      int dragonMaxSize = atoi(dragonMaxSizeStr.c_str()) - 1;
      getline(infile, dragonRarityStr, '\n');
      int dragonRarity = atoi(dragonRarityStr.c_str());

      //creating and adding dragon objects to vector
      Dragon tempDragon(dragonName, dragonType, false, tiny, 
			dragonSize(dragonMaxSize), dragonRarity);

      m_dragons.push_back(tempDragon);
    }
    //DisplayAllDragons();
  }
}

void Game::DisplayAllDragons(){
  for(unsigned int i = 0; i < m_dragons.size(); i++){
    cout << i << ". ";
    cout << m_dragons[i].GetName() << endl;
    cout << m_dragons[i].GetType() << endl;
    cout << m_dragons[i].GetIsHatched() << endl;
    cout << m_dragons[i].GetCurSize() << endl;
    cout << m_dragons[i].GetMaxSize() << endl;
    cout << m_dragons[i].GetRarity() << endl;
  }
}

void Game::StartGame(){
  int userInput = 0;
  
  //call functions based on userInput
  while(userInput != 5){
    userInput = MainMenu();
    switch(userInput){
    case 1:
      SearchEgg();
      break;
    case 2:
      HatchEgg();
      break;
    case 3:
      DisplayMyDragons();
      break;
    case 4:
      Attack();
      break;
    }
  }
}

int Game::MainMenu(){
  int input;

  while (input < 1 || input > 5){ 
    cout << "What would you like to do?" << endl;
    cout << "1. Search for an egg" << endl
	 << "2. Try to hatch egg" << endl
	 << "3. Display all dragons and eggs" << endl
	 << "4. Attack!" << endl
	 << "5. Quit" << endl;
    cin >> input;
  }
  
  return input;
}

void Game::SearchEgg(){
  srand(time(NULL));//seeds random 
  int randNum = rand() % 100 + 1; //num for likeliness to find rarity 
  int randIndex = rand() % m_dragons.size() + 0;//num to be used to get random dragon
  int userRarity = 0;

  while(userRarity < 1 || userRarity > 10){
    cout << "What rarity egg would you like to search for?" << endl;
    cout << "Enter a rarity (1 = very common and 10 = very rare): " << endl;
    cin >> userRarity;
  }

  //what to do based on rarity being search for 
  if(userRarity == 1){

    //91% chance of finding
    if(randNum <= 91){
      int i = randIndex;

      //finds proper dragon
      while(m_dragons[i].GetRarity() != userRarity){
	i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);
    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 2){

    //82% chance of finding
    if(randNum <= 82){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);
    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 3){

    //73% chance of finding
    if(randNum <= 73){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 4){

    //64% chance of finding 
    if(randNum <= 64){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 5){
    
    //55% chance of finding
    if(randNum <= 55){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 6){

    //46% chance of finding
    if(randNum <= 46){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 7){

    //37% chance of finding
    if(randNum <= 37){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 8){

    //28% chance of finding
    if(randNum <= 28){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 9){

    //19% chance of finding
    if(randNum <= 19){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }

  if(userRarity == 10){

    //10% chance of finding
    if(randNum <= 10){
      int i = randIndex;

      while(m_dragons[i].GetRarity() != userRarity){
        i = rand() % m_dragons.size() + 0;
      }

      cout << "You found a " << m_dragons[i].GetName() << endl;
      m_myDragons.push_back(m_dragons[i]);

    }

    else{
      cout << "Sorry, you did not find a dragon of that rarity" << endl;
    }
  }
}

void Game::HatchEgg(){
  if(m_myDragons.size() == 0){
    cout << "You have no dragons" << endl;
  }
  else{
    DisplayMyDragons();
    int randNum = rand() % 100 + 1;//for percentage chance
    unsigned int userChoice = 0;
    
    do{
      cout << "Which dragon would you like to try and hatch?" << endl;
      cin >> userChoice;
    }while(userChoice < 1 || userChoice > m_myDragons.size());
    
    //checks 50% chance and that dragon isn't already hatched
    if(randNum >= 50 && m_myDragons[userChoice - 1].GetIsHatched() == false
       && m_myDragons.size() > 0){
      m_myDragons[userChoice - 1].HatchDragon();
      
      cout << "Your " << m_myDragons[userChoice - 1].GetName() 
	   << " egg hatches into a dragon!" << endl;
      m_countHatchedDragons++;
    }
    
    else{
      cout << "The dragon did not hatch or is alreay hatched" << endl;
    }
  }
}

void Game::DisplayMyDragons(){
  cout.fill(' ');
  int i = 1;

  //formats table display dragon information
  cout << "************************" << endl;
  cout << m_name << "'s Dragons" << endl;
  cout << setw(27) << "Name" << setw(13) << "Type" 
       << setw(12) << "Egg/Dragon" << setw(14) << "Current Size"
       << setw(11) << "Max Size" << endl;

  for(unsigned int j = 0; j < m_myDragons.size(); j++){
    cout << setw(3) << i << "." << setw(23);
    cout << m_myDragons[j].GetName() << setw(13); 
    cout << m_myDragons[j].GetType() << setw(11);

    if(m_myDragons[j].GetIsHatched() == 0){
      cout << "egg" << setw(11);
    }

    else{
      cout << "dragon" << setw(11);
    }
    
    cout << m_myDragons[j].GetCurSize() + 1 << setw(11);
    cout << m_myDragons[j].GetMaxSize() + 1 << endl;
    i++;
  }
}

void Game::Attack(){

  //gets number of hatched dragons in users list
  //for(unsigned int i = 0; i < m_myDragons.size(); i++){

    //if(m_myDragons[i].GetIsHatched() == 1){
      //hatchedDragons++;
      //}
  //}
  
  //makes sure user can fight
  if(m_myDragons.size() > 0 && m_countHatchedDragons > 0){
    string userInput = "";
    unsigned int dragonChoice;
    int breathAttack = rand() % 100 + 1;//5% chance for breathattack
    int randSize = rand() % 4 + 0;//random size for randomly chosen dragon to fight
    int randNum = rand() % m_dragons.size() + 0; // random index for getting dragon
    Dragon randDragon = m_dragons[randNum];
    randDragon.HatchDragon();//automatically hatches random dragon

    while(randSize > randDragon.GetMaxSize()){
      randSize = rand() % 4 + 0;
    }

    randDragon.SetCurSize(dragonSize(randSize));
    cout << "Attack!" << endl;
    cout << "You found a " << randDragon.GetName() << " to fight!" << endl;

    do{
      cout << "Do you want to fight it? (y/n)" << endl;
      cin >> userInput;
    }while(userInput != "n" && userInput != "y");

    if(userInput == "n"){
      cout << "You fled the fight" << endl;
    }
    //end attack dragons if user chooses not to fight

    //matched with if(userInput == "n")
    else{
      cout << "You chose to fight" << endl;
      DisplayMyDragons();

      //makes sure user chooses valid hatched dragon
      do{
	cout << "Which dragon would you like to fight with?" << endl;
	cin >> dragonChoice;
      }while(dragonChoice < 1 || dragonChoice > m_myDragons.size()
	     || m_myDragons[dragonChoice - 1].GetIsHatched() == 0); 

      //user dragon automatically wins
      if(breathAttack <= 5){
	cout << m_myDragons[dragonChoice - 1].BreathAttack() << endl;
	cout << "Your " << m_myDragons[dragonChoice - 1].GetName()
	     <<" defeats the enemy " << randDragon.GetName() << endl;

	bool growth = m_myDragons[dragonChoice - 1].AttemptGrow();
	
	//dragons grows larger if it can
	if(growth == true){
          cout << "Your dragon grows a bit larger" << endl;
        }

        else{
          cout << "Your dragon cannot grow any larger" << endl;
        }
      }

      //dragon wins without special attack or is defeated
      else if (m_myDragons[dragonChoice - 1].AttackDragon(randDragon) == true && breathAttack > 5){
	bool growth = m_myDragons[dragonChoice - 1].AttemptGrow();

	if(growth == true){
	  cout << "Your dragon grows a bit larger" << endl;
	}

	else{
	  cout << "Your dragon cannot grow any larger" << endl;
	}
      }

      //remove user dragon if loses
      //matched with if(breathAttack <= 5)
      else{
	m_myDragons.erase(m_myDragons.begin() + (dragonChoice - 1));
      }
    }
  }

  //matched with if(m_myDragons.size() > 0 && hatchedDragons > 0)
  else{
    cout << "You have no hatched dragons" << endl;
  }
}
