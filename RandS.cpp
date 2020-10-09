#include "RandS.h"
//Param Constructor
RandS::RandS(string firstName, string lastName, int ID, int strength) :Politician(firstName, lastName, ID, strength) {};


void RandS::printPolitician() {
	//implemented in Politician: 
	//-->cout << "Person:" << m_sFirstName << " " << m_sLastName << ", Id:" << m_iID << ", Power:"<<m_iPower;

	//-->Republican Person:Michael Conaway, Id:2111, Power:10, Type:S, Chairman: Dunald/None
	cout << "Republican ";
	Politician::printPolitician();
	cout << ", Type:S, Chairman: " << this->getChairmanFirstName();

}//printPolitician

bool RandS::RegisterToParty(Party *ptr_party) {
    if(ptr_party->registerRepublicanPolitician(this)){

        this->setMyParty(ptr_party);//this setter already sets the chairman + charimanName  as well
        return true;
    }
    else{
        return false;
    }
}

//Destructor:
RandS::~RandS() { }//destructor

