#include "Car.h"

Car::Car(){
  m_next = NULL;
}

Car::Car(CARGO_TYPE cargo){
  m_cargo = cargo;
  m_next = NULL;
}

Car::~Car(){
  //delete m_next;
  //m_next = NULL;
}

CARGO_TYPE Car::getCargo() const{
  return m_cargo;
}

void Car::setCargo(CARGO_TYPE cargo){
  m_cargo = cargo;
}

Car *const Car::getNext() const{
  return m_next;
}

void Car::setNext(Car* next){
  m_next = next;
}

int Car::getLength() const{
  Car *tempCar;
  int length = 0;
  while(m_next != NULL){
    tempCar->setNext(m_next);
    length++;
  }
}
