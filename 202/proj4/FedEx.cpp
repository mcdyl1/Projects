#include "FedEx.h"

FedEx::FedEx(){

}

FedEx::~FedEx(){
}

int FedEx::deliver(){
  float total = 0;//keep track of price
  float priceMail = 0;//cost for piece of mail

  if(m_storage.size() != 0){
    for(unsigned int i = 0; i < m_storage.size(); i++){
      //calculate cost
      priceMail = m_storage.at(i)->getBaseCost() * m_storage.at(i)->getSize() * m_delivery_rate;

      //printing all information for that piece of mail
      cout << "Delivered" << endl;
      cout << "--------------------------" << endl;
      cout << *m_storage.at(i);
      cout << "--------------------------" << endl;
      total += priceMail;
    }
    //format total money made
    cout << fixed;
    cout << setprecision(2);
    cout << endl;
    cout << "Deliveries completed. Total made: " << total << endl;
    cout << endl;
  }

  else{
    cout << "FedEx had no mail to deliver" << endl;
    cout << "*****************************" << endl;
    cout << endl;
  }
  return 1;
}

ostream& FedEx::print(ostream& os) const{
  os << "FedEx Truck Contents:" << endl
     << "---------------------" << endl;
  return os;
}
