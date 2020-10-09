#include <iostream>
#include <string>
#include "Politician.h"
#include "Party.h"
using namespace std;



//default constructor
Politician::Politician() {
	m_iID = 0;
	this->m_sFirstName = "";
	this->m_sLastName = "";
	this->m_ptrMyParty = NULL; //TODO check if correct
	this->m_ptrMyParty_chairman = NULL;
	m_iPower = 0;

}//default constructor


Politician::Politician(string firstName, string lastName, int ID, int strength) {

	this->m_iID = ID;
	this->m_sFirstName = firstName;
	this->m_sLastName = lastName;
	this->m_iPower = strength;
	this->m_ptrMyParty = NULL;
    this->m_ptrMyParty_chairman = NULL;
}//param constructor


Politician::~Politician() { }//destructor


void Politician::Update(Politician* new_chairman)
{
    ///IMPORTANT: if new_chairman is NULL it's OK (and it doesn't mean that the party is NULL)
	this->m_ptrMyParty_chairman = new_chairman;
	/* Lets print on console just to test the working */
	//std::cout << "Politician m_sPartyName:"<< this->m_sFirstName + this->LastName
	//<< " Belongs to Party:"<< this->m_ptrMyParty << "The new Head of Party is:" << this->head_of_party << endl;
}//Update




Politician& Politician::operator=(const Politician& other) {
	if (this == &other){
		return *this;
	}
	this->m_sFirstName = other.m_sFirstName;
	this->m_sLastName = other.m_sLastName;
	this->m_ptrMyParty = other.m_ptrMyParty;
	this->m_iPower = other.m_iPower;
	return *this;
}//operator=



void Politician::printPolitician() {
	//-->Person:Jim Costa, Id:4111, Power:18, Type:S, Chairman: None
	cout << "Person:" << m_sFirstName << " " << m_sLastName << ", Id:" << m_iID << ", Power:"<< m_iPower;
	//cout << m_iPower << endl;

}//printPolitician



/* Why can't I pass Party const& myParty and do: Party* p = &myParty
 * Answer: because Party* is a pointer to Party, not to Party const !
 * Important: no need for const, because the private attributes of Party are inaccessible
 * (not through pointer and not through reference)
 */
void Politician::setMyParty(Party* myParty) {
    if(myParty != NULL) {
        this->m_ptrMyParty = myParty;
        this->m_ptrMyParty_chairman = myParty->getChairman();
    }
    else{
        this->m_ptrMyParty = NULL;
        this->m_ptrMyParty_chairman = NULL;
    }
}


/*   Using the "new_name" string as an id (will not be modified).
 * Passing it in by const reference is probably the best idea here: (std::string const&)
 */

int Politician::getId() {
	return this->m_iID;
}

string Politician::getChairmanFirstName() {
    if(m_ptrMyParty_chairman == NULL){
        return "None";
    }
    else{
        return m_ptrMyParty_chairman->getFirstName();
    }
}

string Politician::getFirstName() {
	return this->m_sFirstName;
}

Party* Politician::getmyParty() {
	return this->m_ptrMyParty;
}




