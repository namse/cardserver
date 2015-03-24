#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}


bool Game::OnCard(PlayerType playerType, CardType type, DeckIndex index)
{
	// 1. Available Card?
	if (type == UNIT)
	{
		if (playerType == m_TurnPlayerType)
		{
			if (index >= m_Player->m_PlayerHandsUnit.size())
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else // ARCANE
	{
		if (m_Phase == UNIT_PHASE)
		{
			if (m_TurnPlayerType != playerType)
				return false;
		}
		else
		{
			if (m_ArcanePlayerTurn != playerType)
				return false;
		}
	}
	


	// 2. Send Card Packet

	// 3. Unit or Arcane?

	// 3.0 Reduce Mana

	// 3.1 Unit : Place.
	// 3.1.1 Unit:OnPlace.


	// 3.2 Arcane : Wait for ends.
}
