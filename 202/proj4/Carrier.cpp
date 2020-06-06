#include "Carrier.h"

Carrier::Carrier(){

}

int Carrier::insert(Mail* mail){
  //adding piece of mail to storage
  if(unsigned(m_storage.size()) != unsigned(m_max_capacity)){
    cout << *mail;
    cout << "--------------------" << endl;
    cout << "--------------------" << endl;
    m_storage.push_back(mail);
    return 1;
  }

  //warn user that piece of mail couldn't be added
  else{
    cout << endl;
    cout << "********************" << endl;
    cout << *mail;
    cout << endl;
    cout << "PIECE OF MAIL ABOVE NOT ADDED. STORAGE IS FULL\n\n";
  }
  return 0;
}

void Carrier::setMaxCapacity(int max_capacity){
  m_max_capacity = max_capacity;
}

void Carrier::setRate(float delivery_rate){
  m_delivery_rate = delivery_rate;
}

ostream &operator<<(ostream& os, const Carrier& carrier){
  carrier.print(os);
  return os;
}
