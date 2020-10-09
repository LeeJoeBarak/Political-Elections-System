#include "RandL.h"
//Param Constructor
RandL::RandL(string firstName, string lastName, int ID, int strength) :Politician(firstName, lastName, ID, strength) {};


void RandL::printPolitician() {
	//implemented in Politician: 
	//-->cout << "Person:" << m_sFirstName << " " << m_sLastName << ", Id:" << m_iID << ", Power:"<<m_iPower;

	//-->Republican Person:Gary Palmer, Id:1117, Power:21, Type:L, Chairman: Dunald/None
	cout << "Republican ";
	Politician::printPolitician();
	cout << ", Type:L, Chairman: " << this->getChairmanFirstName();

}//printPolitician

bool RandL::RegisterToParty(Party *ptr_party)  {
    if(ptr_party->registerRepublicanPolitician(this)){

        this->setMyParty(ptr_party); //this setter already sets the chairman + charimanName as well
        return true;
    }
    else{
        return false;
    }
}

//Destructor:
RandL::~RandL() { }//destructor

