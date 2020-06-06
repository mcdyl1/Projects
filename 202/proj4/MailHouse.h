#ifndef MAIL_HOUSE_H
#define MAIL_HOUSE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Carrier.h"
#include "Letter.h"
#include "Package.h"
#include "FedEx.h"
#include "Ups.h"

using namespace std;

class MailHouse{
public:
  // Constructor
  // Preconditions: None
  // Postconditions: None
  MailHouse();
  
  // loadMail(char*) - loads the file and sets any data from the file
  // Preconditions: a valid filepath
  // Postconditions: Loads m_mail. Returns int for status (1 - success, 0 - fail)
  int loadMail(char*);
  
  // fillCarriers() - Loads the carrier vectors from the m_mail vectors
  // Preconditions: m_mail is populated. m_carriers is populated
  // Postconditions: m_carriers have mail in their respective vectors. 
  // Returns int for status (1 - success, 0 - fail)
  int fillCarriers();

  // deliverMail() - Send carriers out for delivery
  // Preconditions: m_carriers are populated
  // Postconditions: m_carriers have cleared their vectors. 
  // Returns int for status (1 - success, 0 - fail)
  int deliverMail();

  // cleanUp() - Any additional clean up is done here
  // Preconditions: Allocated memory
  // Postconditions: Deallocates any remaining allocations
  int cleanUp();
  
  enum carrierType {UPS, FEDEX, TOTAL_CARRIERS};
  enum mailType {LETTER, PACKAGE, TOTAL_MAIL};
private:
  // store all mail here
  vector<Mail*> m_mail;
  // store carriers here
  vector<Carrier*> m_carriers;
};

#endif
