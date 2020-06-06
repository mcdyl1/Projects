#include "Ups.h"

Ups::Ups(){

}

Ups::~Ups(){

}

int Ups::deliver(){
  float total = 0;
  float priceMail = 0;
  if(m_storage.size() != 0){
    for(unsigned int i = 0; i < m_storage.size(); i++){
      priceMail = m_storage.at(i)->getBaseCost() * m_storage.at(i)->getSize() * m_delivery_rate; 
      cout << "Delivered" << endl;
      cout << "---------------------------" << endl;
      cout << *m_storage.at(i);
      cout << "---------------------------" << endl;
      cout << "---------------------------" << endl;
      total += priceMail;
    }
    cout << fixed;
    cout << setprecision(2);
    cout << endl;
    cout << "Deliveries completed. Total made: " << total << endl;
    cout << endl;
  }
  else{
    cout << "UPS had no mail to deliver\n" << endl;
  }

  return 1;
}

ostream& Ups::print(ostream& os) const{  
  os << "UPS Truck Contents:" << endl
     << "---------------------" << endl;
  return os;

}
