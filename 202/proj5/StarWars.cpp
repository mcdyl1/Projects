#include "StarWars.h"

StarWars::StarWars(){
}

StarWars::~StarWars(){
  //loops through vectors and deletes all allocated memory
  for(unsigned int i = 0; i < m_imperialShips.size(); i++){
    delete m_imperialShips.at(i);
    m_imperialShips.at(i) = NULL;
  }
  for(unsigned int i = 0; i < m_rebelShips.size(); i++){
    delete m_rebelShips.at(i);
    m_rebelShips.at(i) = NULL;
  }

}

bool StarWars::loadShips(char* files[]){
  ifstream impInfile;
  string impName;
  string impType;
  string impAttackStr;
  string impDefenseStr;

  //opens and reads info from imperial file
  impInfile.open(files[0]);
  if(impInfile.is_open()){
    while(!impInfile.eof()){
      getline(impInfile, impName, ',');
      getline(impInfile, impType, ',');
      getline(impInfile, impAttackStr, ',');
      int impAttack = atoi(impAttackStr.c_str());
      getline(impInfile, impDefenseStr);
      int impDefense = atoi(impDefenseStr.c_str());
      if(impInfile.peek() == '\n')
	impInfile.ignore();
      
      //creates imperial ship object and adds to vector
      Ship* imperialShip = new Imperial(impName, impType, impAttack, impDefense);
      m_imperialShips.push_back(imperialShip);
    }
  }
  
  else{
    cout << "Imperial file could not open" << endl;
    return 0;
  }
 
  ifstream rebInfile;
  string rebName;
  string rebType;
  string rebAttackStr;
  string rebDefenseStr;
  
  //opens and reads info from rebel file
  rebInfile.open(files[1]);
  if(rebInfile.is_open()){
    while(!rebInfile.eof()){
      getline(rebInfile, rebName, ',');
      getline(rebInfile, rebType, ',');
      getline(rebInfile, rebAttackStr, ',');
      int rebAttack = atoi(rebAttackStr.c_str());
      getline(rebInfile, rebDefenseStr);
      int rebDefense = atoi(rebDefenseStr.c_str());
      if(rebInfile.peek() == '\n')
	rebInfile.ignore();
      
      //creates rebel ship object and adds to vector
      Ship* rebelShip = new Rebel(rebName, rebType, rebAttack, rebDefense);
      m_rebelShips.push_back(rebelShip);
    }  
  }
  
  else{
    cout << "Rebel file could not open" << endl;
    return 0;
  }

  if(m_rebelShips.size() == 0 || m_imperialShips.size() == 0){
    cout << "One of the vectors is empty" << endl;
    return 0;
  }
  else{
    cout << "Success in loading ships" << endl;
  }

  impInfile.close();
  rebInfile.close();
  return 1;
} 

void StarWars::Start(char* files[]){
  int numShips;
  cout << "Welcome to Star Wars" << endl;
  loadShips(files);

  //gets number of ships player wants on each team
  do{
  cout << "How many ships would you like on a team?" << endl;
  cin >> numShips;
  }while(numShips <= 0);

  createTeams(numShips);
  battle();
}

void StarWars::createTeams(int numShips){
  srand(time(NULL));
  int counter = 0;
  //selects random ships from vectors and adds them to respective Tqueue
  while(counter < numShips){
    int impRanIndex = rand() % (m_imperialShips.size() - 1) + 0;
    int rebRanIndex = rand() % (m_rebelShips.size() - 1) + 0;
    
    m_myShips.enqueue(m_rebelShips.at(rebRanIndex));
    m_enemyShips.enqueue(m_imperialShips.at(impRanIndex));
    counter++;
  }
}

void StarWars::battle(){
  cout << "The battle begins..." << endl;
  int whoStarts = rand() % 100 + 0;
  while(!m_myShips.isEmpty() && !m_enemyShips.isEmpty()){
    
    //imperial attacks
    if(whoStarts < 50){
      bool result = m_enemyShips.queueFront()->attack(m_myShips.queueFront());
      cout << "The " << *m_enemyShips.queueFront() << m_enemyShips.queueFront()->getName() 
	   << " attacks the " << *m_myShips.queueFront() 
	   << m_myShips.queueFront()->getName() << endl;

      //rebel ship being attacked is destroyed
      if(result == 1){
	cout << "The " << *m_myShips.queueFront() 
	     << m_myShips.queueFront()->getName() << " was destroyed" << endl;
	cout << "---------------------------------" << endl;

	m_myShips.dequeue();
	//gets new random number to see who goes next
	whoStarts = rand() % 100 + 0;
      }

      //rebel ship being attaked gets damaged
      else{
	cout << "The " << *m_myShips.queueFront() 
	     << m_myShips.queueFront()->getName() << " was damaged" << endl;
	cout << "---------------------------------" << endl;

	//how much damage the rebel ship takes
	int attack = m_enemyShips.queueFront()->getAttack();
	int defense = m_myShips.queueFront()->getDefense();
	int newDefense = 0;
	newDefense = defense - attack;
	m_myShips.queueFront()->setDefense(newDefense);
	whoStarts = 51;//rebel ship retaliates
      }
    }

    //rebel attacks
    else{
      bool result = m_myShips.queueFront()->attack(m_enemyShips.queueFront());
      cout << "The " << *m_myShips.queueFront() << m_myShips.queueFront()->getName() 
	   << " attacks the " <<  *m_enemyShips.queueFront() 
	   << m_enemyShips.queueFront()->getName() << endl;
      if(result == 1){
	cout << "The " << *m_enemyShips.queueFront()
	     << m_enemyShips.queueFront()->getName() << " was destroyed" << endl;
	cout << "---------------------------------" << endl;


	m_enemyShips.dequeue();
	whoStarts = rand() % 100 + 0;
      }
      else{
	cout << "The " << *m_enemyShips.queueFront()
             << m_enemyShips.queueFront()->getName() << " was damaged" << endl;
	cout << "---------------------------------" << endl;


	int attack = m_myShips.queueFront()->getAttack();
	int defense = m_enemyShips.queueFront()->getDefense();
	int newDefense = 0;
	newDefense = defense - attack;
	m_enemyShips.queueFront()->setDefense(newDefense);
	whoStarts = 49;
      }
    }
  }
  if(m_myShips.isEmpty()){
    cout << "You lost!" << endl;
  }
  else{
    cout << "You Won!" << endl;
  }

}

