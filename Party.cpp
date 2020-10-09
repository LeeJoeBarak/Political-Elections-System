#include <iostream>
#include <vector>
#include <algorithm>
#include "Party.h"
#include "Politician.h"


Party::Party() {
	m_ptrChairman = NULL;
	m_sPartyName = "";
	m_sChairman_FirstName = "None";
	/* no need to "init" vector (though it is way more efficient to give it init SIZE...)  */
	
}//default constructor


Party::Party(string name) {

	m_ptrChairman = NULL;
	this->m_sPartyName = name;
	this->m_sChairman_FirstName = "None";//is Chairmen chosen only during Primaries?

}//param constructor


//copy constructor - debatable...


Party& Party::operator=(const Party& other) {
	if(&other == this){
		return *this;
	}
	this->m_sPartyName = other.m_sPartyName;
	this->m_sChairman_FirstName = other.m_sChairman_FirstName;
	this->m_vecMyPoliticians = other.m_vecMyPoliticians;
	return *this;
}



Party::~Party() {

    m_vecMyPoliticians.clear();
} // TODO Auto-generated destructor stub



void Party::notifyPolitician(Politician* new_chairman) //option2 for implementation: Notify() // can be null !
{
	vector<Politician*>::iterator itPoli = m_vecMyPoliticians.begin();
	for (;itPoli != m_vecMyPoliticians.end(); ++itPoli ) {
        (*itPoli)->Update(new_chairman);
	}
}//notifyPolitician



void Party::unregister(Politician* politician) {
	if(politician == NULL){
		terminate();
	}
    /** if this politician is chairman - set party's chairman_ptr to NULL and m_sChairman to None*/
    if(politician == this->m_ptrChairman){
            this->m_ptrChairman =NULL;
            this->m_sChairman_FirstName = "None";
            notifyPolitician(NULL);
    }

    // find the observer
    vector<Politician*>::iterator it = find(m_vecMyPoliticians.begin(), m_vecMyPoliticians.end(), politician);
    if ( it != this->m_vecMyPoliticians.end()) { // observer found
        m_vecMyPoliticians.erase(it);
    }
    ///Notice: DO NOT CALL delete or try to free -> these pointers were allocated externally
}


void Party::printAllParty() {
//-->Party: Farmers, chairman:Mark, Size:7
	cout << "Party: " << this->m_sPartyName << ", chairman:" << this->m_sChairman_FirstName
		 << ", Size:" << this->m_vecMyPoliticians.size();// << endl;

	int i;
//-->Person:Mac Thornberry, Id:2113, Power:9, Type:S, Chairman: Mark
	if(this->m_vecMyPoliticians.size() > 0){
		cout<<""<<endl;
		for (i = 0; i < (int)m_vecMyPoliticians.size() -1 ; ++i) {
			cout << "\t";
			m_vecMyPoliticians[i]->printPolitician() ;
			cout << endl;
		}
		cout << "\t";
		m_vecMyPoliticians[i]->printPolitician();
	}
}



void Party::primaries() {

	Politician* strongest_politician = NULL;
	Politician* curr_politician = NULL;	//can be either Social or Leader
	string getName;

	int i;
	for (i = 0; i < (int)m_vecMyPoliticians.size(); i++) {

		//check if current candidate is Leader
		if(m_vecMyPoliticians[i]->canBeLeader()){	//current candidate is Leader
			curr_politician = m_vecMyPoliticians[i];
		}
		else{//current candidate is Social
			continue;
		}

		if (strongest_politician == NULL) {
			strongest_politician = curr_politician;
		}
		//notice that Politician_list should be ordered by INSERTION ORDER to the list: First-to-Last 
		// (politician*)->getPower is overriden
		else if (curr_politician->getPoliticianPower() > strongest_politician->getPoliticianPower())
		{
			strongest_politician = curr_politician;
		}
	}//end for loop

	//if there are no Leaders --> No Chairman. 
	if (strongest_politician == NULL || strongest_politician->getPoliticianPower() < 0) {
		this->setPartyChairman(NULL); //this func also changes the chairman name to "None"
	}
	else {
	    this->setPartyChairman(strongest_politician); // this func also sets the name + ptr of chairman
	}

	// Notify all politicians in party
	notifyPolitician(this->m_ptrChairman);

	//-->Mark is the chairman of Farmers
	cout << this->m_sChairman_FirstName << " is the chairman of " << this->m_sPartyName << endl;

}

int Party::getPartyPower() {
	int sum = 0;
	for (int i = 0; i < (int)this->m_vecMyPoliticians.size(); i++) {
		sum += m_vecMyPoliticians[i]->getPoliticianPower();
	}
	return sum;
}//getPartyPower

int Party::getSize()const {
	return (int)this->m_vecMyPoliticians.size();
}

string Party::getName() {
	return this->m_sPartyName;
}

string Party::getChairmanFirstName() {
    return this->m_sChairman_FirstName;
}

void Party::setPartyChairman(Politician* new_chairman) { // can get null
    if (new_chairman == NULL) {
        this->m_ptrChairman = NULL;
        this->m_sChairman_FirstName = "None";
    } else {
        this->m_ptrChairman = new_chairman;
        this->m_sChairman_FirstName = new_chairman->getFirstName();

    }
}
