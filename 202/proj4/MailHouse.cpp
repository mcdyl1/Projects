#include "MailHouse.h"
#include <cstdlib>

MailHouse::MailHouse(){

}

int MailHouse::loadMail(char* file){
  int ups_Capacity = 0;
  int fedex_Capacity = 0;
  float ups_speed = 0;
  float fedex_speed = 0;
  float ltrCost = 0;
  float pkgCost = 0;
  ifstream infile;

  //read in first line of file
  infile.open(file);
  if(infile){
    infile >> ups_Capacity;
    infile >> fedex_Capacity;
    infile >> ups_speed;
    infile >> fedex_speed;
    infile >> ltrCost;
    infile >> pkgCost;
  }

  //creating & adding carriers
  Carrier* carrier_ups = new Ups();
  Carrier* carrier_fedEx = new FedEx();
  m_carriers.push_back(carrier_ups);
  m_carriers.push_back(carrier_fedEx);
  m_carriers.at(UPS)->setRate(ups_speed);
  m_carriers.at(UPS)->setMaxCapacity(ups_Capacity);
  m_carriers.at(FEDEX)->setRate(fedex_speed);
  m_carriers.at(FEDEX)->setMaxCapacity(fedex_Capacity);
  
  string carrier;
  string type_mail;
  string sender;
  string receiver;
  string size;
  while(!infile.eof()){
    getline(infile, carrier, ',');
    getline(infile, type_mail, ',');
    getline(infile, sender, ',');
    getline(infile, receiver, ',');
    getline(infile, size);
    if(infile.peek() == '\n')
      infile.ignore();
    
    //conversions for parameters
    int carrierInt = atoi(carrier.c_str());
    int mailTypeInt = atoi(type_mail.c_str());
    float sizeflt = atof(size.c_str());

    //creating & adding mail
    if(mailTypeInt == LETTER && (carrierInt == UPS || carrierInt == FEDEX)){
      Mail* ltr = new Letter(carrierInt, sender, receiver, sizeflt, ltrCost);
      m_mail.push_back(ltr);
    }

    else if(mailTypeInt == PACKAGE && (carrierInt == UPS || carrierInt == FEDEX)){
      Mail* pkg = new Package(carrierInt, sender, receiver, sizeflt, pkgCost);
      m_mail.push_back(pkg);
    }

    else{
      cout << "*****************************************" << endl;
      cout << "A PIECE OF THE MAIL DID NOT HAVE A PROPER CARRIER" << endl;
      cout << "*****************************************" << endl;
      cout << endl;
      return 0;
    }
  }

  return 1;
}

int MailHouse::fillCarriers(){
  
  //Add to storage vectors for respective carriers 
  cout << *m_carriers.at(UPS);
  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == UPS){
      if(m_carriers.at(UPS)->insert(m_mail.at(i)) == 0)
	return 0;
    }
  }

  cout << *m_carriers.at(FEDEX);
  for(unsigned int i = 0; i < m_mail.size(); i++){
    if(m_mail.at(i)->getCarrier() == FEDEX){
      if(m_carriers.at(FEDEX)->insert(m_mail.at(i)) == 0)
	return 0;
    }
  }

  return 1;
}

int MailHouse::deliverMail(){
  cout << *m_carriers.at(UPS);
  m_carriers.at(UPS)->deliver();
  cout << *m_carriers.at(FEDEX);
  m_carriers.at(FEDEX)->deliver();

  return 1;
}

int MailHouse::cleanUp(){
  //loop over both vectors and delete allocated memory
  for(unsigned int i = 0; i < m_mail.size(); i++){
    delete m_mail.at(i);
    m_mail.at(i) = NULL;
  }

  for(unsigned int i = 0; i < m_carriers.size(); i++){
    delete m_carriers.at(i);
    m_carriers.at(i) = NULL;
  }

  return 1;
}
