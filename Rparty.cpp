#include "Rparty.h"

Rparty::Rparty(string name) :Party(name) {}


void Rparty::printAllParty() {
/*
	Party's Print function implementation: 

	cout << "Party: " << this->m_sPartyName << ", chairman:" << this->m_sChairman_FirstName
	<< ", Size:" << this->m_vecMyPoliticians.size() << endl;

	Plus, for all politicians in party: \t + PrintPolitician
*/

	//-->Republican Party: Republicans_party, chairman:Dunald, Size:7
	cout << "Republican ";
	this->Party::printAllParty();

}//printAllParty


//destructor
Rparty::~Rparty() {}//destructor
