#include "stdafx.h"
#include "Decks.h"


Decks::Decks()
{
}


Decks::~Decks()
{
}

Card* Decks::PopCard()
{
	if (m_CardList.empty())
	{
		return nullptr;
	}
	auto ret = m_CardList.front();
	m_CardList.pop_front();
	return ret; 
}
