#pragma once

#ifndef PARTY_H_
#define PARTY_H_

#include <iostream>
#include <string>
#include <vector>
#include "Politician.h"

class Politician;

using namespace std;

class Party
{
		string m_sPartyName;
		Politician* m_ptrChairman;
		string m_sChairman_FirstName;
		//Politician* dummy_poli;
protected:
		vector<Politician*> m_vecMyPoliticians;

public:
		//default constructor
		Party();

		//param constructor
		Party(string);
		
		/* copy constructor - we only use pointers so maybe copy constructor is unecessary? */
		//Party(const Party& party);

		virtual ~Party();//destructor

		void notifyPolitician(Politician* new_chairman);//NotifyPolitician
		void primaries();
		virtual bool registerDemocraticPolitician(Politician* democratic_politician) = 0;//Input: Observer
		virtual bool registerRepublicanPolitician(Politician* republican_politician) = 0;//Input: Observer
		virtual void unregister(Politician* politician);/*After calling unregister() you must free your object[no dynamic
		                                                 * memory allocs occured in this class */
        virtual void printAllParty();
        int getPartyPower();

		Party& operator=(const Party& other);
		bool operator<(const Party& partyObj)const { return this->getSize() < partyObj.getSize(); }
		bool operator>(const Party& partyObj)const { return this->getSize() > partyObj.getSize(); }

		string getName();
		Politician* getChairman() { return this->m_ptrChairman; } //ret ptr might be NULL - alwats check pointers before accessing !
		int getSize()const;
		vector<Politician*> getPoliticians() { return this->m_vecMyPoliticians;}
        void setPartyChairman(Politician* new_chairman);
		string getChairmanFirstName(); //TODO ! move this to politician! having this here defeats the purpose of Observer Pattern... I think?


};

#endif /* PARTY_H_ */






