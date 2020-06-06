#include "Imperial.h"

bool Imperial::attack(Ship* enemy){
  if(getAttack() > enemy->getDefense()){
    return 1;
  }
  else{
    return 0;
  }
}

ostream& Imperial::toString(ostream& os){
  os << " Imperial ";
  return os;
}
