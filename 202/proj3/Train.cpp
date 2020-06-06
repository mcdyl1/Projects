#include "Train.h"

Train::Train(){
  m_head = NULL;
}
Train::Train(int number){
  m_head = NULL;
  m_len = 0;
  m_number = number;
}
Train::~Train(){
  //delete m_head;
  //m_head = NULL;
}

void Train::display(ostream& output) const{
  output << "Train " << m_number << ": ";

  Car *temp = m_head;
  
  //format printing the linked list
  for(int i = 0; i < m_len; i++){
    CARGO_TYPE cargo = temp->getCargo();
    if(cargo == 0)
      cout << "BIO->";
    if(cargo == 1)
      cout << "POI->";
    if(cargo == 2)
      cout << "COM->";
    if(cargo == 3)
      cout << "OXI->";
    if(cargo == 4)
      cout << "RAD->";
    if(cargo == 5)
      cout << "ENGINE->";
    if(cargo == 6)
      cout << "CABOOSE " << endl;
    temp = temp->getNext();
  }
  cout << endl;
}


int Train::addCar(const CARGO_TYPE& cargo, int size){
  
  Car *carPtr = new Car();
  carPtr->setCargo(cargo);
  carPtr->setNext(NULL);

  //if list is empty
  if(m_head == NULL){
    m_head = carPtr;
  }

  //if list has at least one car
  else{
    Car *temp = m_head;
    while(temp->getNext() != NULL){
      temp = temp->getNext();
    }

    temp->setNext(carPtr);
  }
  
  m_len++;
  return 0;
}

int Train::getLength() const{
  return m_len;
}

int Train::getNumber() const{
  return m_number;
}

void Train::setNumber(int number){
  m_number = number;
}

std::ostream &operator<<(std::ostream& output, const Train& myTrain){
  myTrain.display(output);
  return output;
}

int Train::removeCar(CARGO_TYPE cargo){
  Car *temp;
  Car *temp2;
  temp = m_head;
  temp2 = temp->getNext();
  //loop through list until hit end
  while(temp2 != NULL){
    //nodes cargo is to be removed
    if(temp2->getCargo() == cargo){
      temp->setNext(temp2->getNext());
      delete temp2;
      temp2 = temp->getNext();
    }
    //dont remove, move on
    else{
      temp = temp2;
      temp2 = temp2->getNext();
    }
  }
  return 1;
}

int Train::removeCar(int pos){
  int counter = 0;
  int i = 0;

  if(m_head == NULL){
    cout << "List is empty" << endl;
    return 0;
  }

  Car *s, *ptr;
  s = m_head;
  if (pos == 1){
    m_head = s->getNext();
  }

  else{
    while(s != NULL){
      s = s->getNext();
      counter++;
    }

    if(pos > 0 && pos <= counter){
      s = m_head;

      for(i = 1; i < pos; i++){
	ptr = s;
	s = s->getNext();
      }

      ptr->setNext(s->getNext());
    }

    else{
      cout << "Position out of range" << endl;
    }
  }
  return 0;
}


bool Train::isValid() const{
  //counters
  //if statements for conditions
  return true;
}
 

