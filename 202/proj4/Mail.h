#ifndef MAIL_H
#define MAIL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Mail{
 public:
  // Default Constructor
  // Preconditions: None
  // Postconditions: None
  Mail();
  
  // Overloaded Constructor
  // Preconditions: Valid inputs
  // Postconditions: None
  Mail(int, string, string, float, float);
  
  // Destructor - virtual (implement in child classes)
  // Preconditions: Mail object in memory
  // Postconditions: Deallocates mail object in memory
  virtual ~Mail(){};
  
  // getCarrier() - returns the type of the carrier
  // Preconditions: m_carrier is set
  // Postconditions: returns an int reffering to which carrier
  int getCarrier();
  
  // getSender() - returns the sender of the mail
  // Preconditions: m_sender is set
  // Postconditions: returns a string of the sender
  string getSender();
  
  // getRecipient() - returns the recipient of the mail
  // Preconditions: m_recipient is set
  // Postconditions: returns a string of the recipient
  string getRecipient();
  
  // getSize() - returns the size of the Mail
  // Preconditions: m_size is set
  // Postconditions: returns a float
  float getSize();
  
  // getBaseCost() - returns the base cost of the mail
  // Preconditions: m_baseCost is set
  // Postconditions: returns a float
  float getBaseCost();
  
  // operator<<(ostream&, Mail&) - overload the << operator to handle a Mail object
  // Preconditions: a valid ostream and Mail operator
  // Postconditions: returns an ostream object
  friend ostream& operator<<(ostream&, Mail&);
 
 protected:
  // toString() - returns a string representation of a Mail object
  // Preconditions: a valid Mail object
  // Postconditions: returns a string
  virtual string toString() = 0;
  
  string m_sender;
  string m_recipient;
  int m_carrier;
  float m_size;
  float m_baseCost;
  
};

#endif
