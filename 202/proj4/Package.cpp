#include "Package.h"

Package::Package(){

}

Package::Package(int carrier, string sender, string receiver, float size, float baseCost){
  m_carrier = carrier;
  m_sender = sender;
  m_recipient = receiver;
  m_size = size;
  m_baseCost = baseCost;
}

Package::~Package(){

}

string Package::toString(){
  return "PACKAGE";
}
