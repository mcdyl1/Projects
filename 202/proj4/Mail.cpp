#include "Mail.h"

Mail::Mail(){
  //m_carrier = 0;
  //m_sender = "";
  //m_recipient = "";
  //m_size = 0;
  //m_baseCost = 0;
}

Mail::Mail(int carrier, string sender, string receiver, float size, float baseCost){
  m_carrier = carrier;
  m_sender = sender;
  m_recipient = receiver;
  m_size = size;
  m_baseCost = baseCost;
}

int Mail::getCarrier(){
  return m_carrier;
}

string Mail::getSender(){
  return m_sender;
}

string Mail::getRecipient(){
  return m_recipient;
}

float Mail::getSize(){
  return m_size;
}

float Mail::getBaseCost(){
  return m_baseCost;
}

ostream& operator<<(ostream& os, Mail& mail){
  os << mail.toString() << endl
     << "To: " << mail.getRecipient() << endl
     << "From: " << mail.getSender() << endl;

  if(mail.toString() == "LETTER"){
    os << "Size: " << mail.getSize() << " square inches" << endl;
  }

  else if(mail.toString() == "PACKAGE"){
    os << "Weight: " << mail.getSize() << " lbs" << endl;
  }

  return os;
}
