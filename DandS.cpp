
#include "DandS.h"

//Param Constructor
DandS::DandS(string firstName, string lastName, int ID, int strength) :Politician(firstName, lastName, ID, strength) {};


void DandS::printPolitician() {
//implemented in Politician: 
//-->cout << "Person:" << m_sFirstName << " " << m_sLastName << ", Id:" << m_iID << ", Power:"<<m_iPower;

	//-->Democratic *Person:Jim Costa, Id:4111, Power:18*, Type:S, Chairman: None/string
	cout << "Democratic ";
	Politician::printPolitician();
	cout << ", Type:S, Chairman: " << this->getChairmanFirstName();

}//printPolitician

bool DandS::RegisterToParty(Party *ptr_party){
    //TODO ADD NULL CHECK
    if(ptr_party->registerDemocraticPolitician(this))
    {
        this->setMyParty(ptr_party);//this setter already sets the chairman + charimanName as well
        return true;
    }
    else{
        return false;
    }
}


//Destructor:
DandS::~DandS() { }//destructor

