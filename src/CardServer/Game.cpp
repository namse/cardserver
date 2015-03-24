#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

/*
���� ��Ŷ
1. �÷��̾�
2. ī�� ���� : ���� �ƴϸ� ����
3. �� �ڵ忡 ��� ���ϴ°���
4. �߰��ൿ
4.1 ���� �� ������ ��� ��������
4.2 ���� �� ������ �������� ������
4.2.1 ���� ������ ����� ������
4.2.2 ���� ������ ���� �������� ������

<Ȯ���۾�>
������ ���
1. ���� �� �ڸ��� ���� �� �ִ��� Ȯ��
2. ������ ����� �ִ��� Ȯ��
3. ȿ���� ����� �� �ִ��� Ȯ��

������ ���
1. ������ ����� �ִ��� Ȯ��
2. ȿ���� ����� �� �ִ��� Ȯ��
*/ 

bool Game::OnCard(PlayerType playerType, Hands::CardType cardType, 
	Hands::CardIndex handsIndex, Field::FrontOrBack fieldFrontOrBack,
	Field::CardIndex fieldIndex)
{
	// 1. Available Card?
	if (cardType == Hands::CardType::UNIT)
	{
		if (playerType == m_TurnPlayerType)
		{
			if (nullptr == GetPlayer(playerType)->GetHands()->GetCard(cardType, handsIndex))
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
			if (m_ArcaneTurnPlayerType != playerType)
				return false;
		}
	}
	

	// 3. Unit or Arcane?
	if (cardType == Hands::CardType::UNIT)
	{
		if (nullptr == GetPlayer(playerType)->GetField()->GetCard(fieldFrontOrBack, fieldIndex))
		{

		}
	}
	else // ARCANE
	{

	}

	// 3.0 Reduce Mana

	// 3.1 Unit : Place.
	// 3.1.1 Unit:OnPlace.


	// 3.2 Arcane : Wait for ends.


	// 4. Send Card Packet
}

PlayerID Game::GetPlayerID(Player* player)	
{
	//assert(player == &m_Player1 || player == &m_Player2);
	return player == &m_Player1 ? m_Player1ID : m_Player2ID;
}

PlayerID Game::GetPlayerID(PlayerType playerType)
{
	return playerType == PLAYER_1 ? m_Player1ID : m_Player2ID;
}

Player* Game::GetPlayer(PlayerID playerID)
{
	//assert(playerID == m_Player1ID || playerID == m_Player2ID);
	return playerID == m_Player1ID ? &m_Player1 : &m_Player2;
}

Player* Game::GetPlayer(PlayerType playerType)
{
	return playerType == PLAYER_1 ? &m_Player1 : &m_Player2;
}
