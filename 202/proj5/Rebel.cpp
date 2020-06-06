#include "Rebel.h"

bool Rebel::attack(Ship* enemy){
  if(getAttack() > enemy->getDefense()){
    return 1;
  }
  else{
    return 0;
  }

}

ostream& Rebel::toString(ostream& os){
  os << " Rebel ";
  return os;
}
