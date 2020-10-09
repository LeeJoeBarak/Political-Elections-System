#include "DandL.h"
//Param Constructor
DandL::DandL(string firstName, string lastName, int ID, int strength):Politician(firstName, lastName, ID, strength) {};


void DandL::printPolitician() {
	//implemented in Politician: 
	//-->cout << "Person:" << m_sFirstName << " " << m_sLastName << ", Id:" << m_iID << ", Power:"<<m_iPower;

		//-->Democratic Person:Juan Vargas, Id:4116, Power:17, Type:L, Chairman: None/string
	cout << "Democratic ";
	Politician::printPolitician();
	cout << ", Type:L, Chairman: " << this->getChairmanFirstName();

}//printPolitician

bool DandL::RegisterToParty(Party *ptr_party)  {
    if( ptr_party->registerDemocraticPolitician(this))
    {
        /** sets NULL ptr to */
        this->setMyParty(ptr_party); //this setter already sets the chairman + charimanName as well
        return true;
    }
    else{
        return false;
    }
}
//Destructor:
DandL::~DandL() { }//destructor


