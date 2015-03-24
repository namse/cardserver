#pragma once
#include <list>
#include "Card.h"
class Decks
{
public:
	Decks();
	~Decks();

	Card* PopCard();
	void PushCard(Card* card) {
		m_CardList.push_back(card);
	}
private:
	std::list<Card*> m_CardList;
};

