#include "Dragon.h"

Dragon::Dragon(string name, string type, bool isHatched, dragonSize curSize,
	       dragonSize maxSize, int rarity){
  SetName(name);
  SetType(type);
  m_isHatched = 0;//all dragons start off unhatched
  SetCurSize(curSize);
  SetMaxSize(maxSize);
  SetRarity(rarity);
}

string Dragon::GetName(){
  return m_name;
}

void Dragon::SetName(string name){
  m_name = name;
}

string Dragon::GetType(){
  return m_type;
}

void Dragon::SetType(string type){
  m_type = type;
}

bool Dragon::GetIsHatched(){
  return m_isHatched;
}

void Dragon::HatchDragon(){
  if(m_isHatched == 0){
    m_isHatched = 1;
  }
}

dragonSize Dragon::GetCurSize(){
  return m_curSize;
}

void Dragon::SetCurSize(dragonSize curSize){
  m_curSize = curSize;
}

dragonSize Dragon::GetMaxSize(){
  return m_maxSize;
}

void Dragon::SetMaxSize(dragonSize maxSize){
  m_maxSize = maxSize;
}

int Dragon::GetRarity(){
  return m_rarity;
}

void Dragon::SetRarity(int rarity){
  m_rarity = rarity;
}

bool Dragon::AttemptGrow(){
  //cant grow
  if (m_curSize == m_maxSize){
    return (false);
  }

  //grows
  else{
    switch(m_curSize){
    case 0:
      m_curSize = small;
	break;
    case 1:
      m_curSize = medium;
      break;
    case 2:
      m_curSize = large;
      break;
    case 3:
      m_curSize = huge;
      break;
    }
    return (true);
  }
}

bool Dragon::AttackDragon(Dragon& randDragon){
  if(randDragon.GetCurSize() > m_curSize){
    cout << "The enemy " << randDragon.GetName()
	 << " defeated your " << m_name << endl;

    return (false);
  }

  else{ 
    if(randDragon.GetCurSize() == m_curSize){
      cout << "The battle results in a draw" << endl;
    }

    else{
      cout << "Your " << m_name << " defeats the enemy "
	   << randDragon.GetName() << endl;
    }
    return(true);
  }
}

string Dragon::BreathAttack(){
  if (m_type == "acid")
    return ("Your dragon used a special acid attack");

  if (m_type == "water")
    return ("Your dragon used a special water attack");

  if (m_type == "ice")
    return ("Your dragon used a special ice attack");

  if (m_type == "fire")
    return ("Your dragon used a special fire attack");

  if (m_type == "wind")
    return ("Your dragon used a special wind attack");
} 
