#include "Letter.h"

Letter::Letter(){

}

Letter::Letter(int carrier, string sender, string receiver, float size, float baseCost){
  m_carrier = carrier;
  m_sender = sender;
  m_recipient = receiver;
  m_size = size;
  m_baseCost = baseCost;
}

Letter::~Letter(){

}

string Letter::toString(){
  return "LETTER";
}

