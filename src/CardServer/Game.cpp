#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

/*
들어올 패킷
1. 플레이어
2. 카드 종류 : 비전 아니면 유닛
3. 내 핸드에 어떤걸 말하는건지
4. 추가행동
4.1 내가 이 유닛을 어디에 놓을건지
4.2 내가 이 마법을 누구에게 쓸건지
4.2.1 내가 마법을 몇명에게 쓸건지
4.2.2 내가 마법을 각각 누구에게 쓸건지

<확인작업>
유닛인 경우
1. 내가 그 자리에 놓을 수 있는지 확인
2. 마나가 충분히 있는지 확인
3. 효과를 사용할 수 있는지 확인

비전인 경우
1. 마나가 충분히 있는지 확인
2. 효과를 사용할 수 있는지 확인
*/ 

bool Game::OnCard(protocol::Card inPacket)
{
	auto playerType = GetPlayerType(inPacket.playerid());
	auto cardType = (Hands::CardType)(inPacket.cardtype());
	auto handsIndex = (Hands::CardIndex)(inPacket.handsindex());

	// 1. Available Card?
	if (inPacket.cardtype() == Hands::CardType::UNIT)
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


	Card* card = GetPlayer(playerType)->GetHands()->GetCard(cardType, handsIndex);
	if (card == nullptr)
		return false;

	if (card->AvailableAction(inPacket, this) == false)
		return false;
	switch (cardType)
	{
	case Hands::CardType::UNIT:
		card->DoAction(inPacket, this);
		break;
		
	case Hands::CardType::ARCANE:
		PushArcaneCardInStack(card, inPacket);
		break;
	}

	// Mana Costing
	GetPlayer(playerType)->CostMana(card->GetCostMana());

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

Game::PlayerType Game::GetPlayerType(Player* player)
{
	//assert(player == &m_Player1 || player == &m_Player2);
	return player == &m_Player1 ? PlayerType::PLAYER_1 : PlayerType::PLAYER_2;
}

Game::PlayerType Game::GetPlayerType(PlayerID playerID)
{
	//assert(playerID == m_Player1ID || playerID == m_Player2ID);
	return playerID == m_Player1ID ? PlayerType::PLAYER_1 : PlayerType::PLAYER_2;
}

void Game::PushArcaneCardInStack(Card* card, protocol::Card& inPacket)
{
	ArcaneStackNode node;
	node.inPacket.CopyFrom(inPacket);
	node.arcaneCard = card;
	m_ArcaneStack.push_back(node);
}

void Game::OnTurn()
{
	// send packet

	while (!m_ArcaneStack.empty())
	{
		auto arcaneNode = m_ArcaneStack.back();
		m_ArcaneStack.pop_back();

		arcaneNode.arcaneCard->DoAction(arcaneNode.inPacket, this);
	}

	for (int i = 0; i < 2; i++) // Front or End
	{
		for (int l = 0; l < 3; l++) // field index
		{
			Field::FrontOrBack fob = (Field::FrontOrBack)i;
			Field::CardIndex index = (Field::CardIndex)l;

			auto card = GetPlayer(m_TurnPlayerType)->GetField()->GetCard(fob, index);
			if (nullptr == card)
				continue;

			// TODO : if (attack able on index)

			card->DoAttack(this);
		}
	}

	for (int i = 0; i < 2; i++) // Front or End
	{
		for (int l = 0; l < 3; l++) // field index
		{
			Field::FrontOrBack fob = (Field::FrontOrBack)i;
			Field::CardIndex index = (Field::CardIndex)l;

			auto player = GetPlayer(m_TurnPlayerType);
			auto field = player->GetField();
			auto card = field->GetCard(fob, index);
			if (nullptr == card)
				continue;

			if (card->IsDead())
			{
				field->SetCard(fob, index, nullptr);
				auto deck = player->GetDecks();
				deck->PushCard(card);
			}
		}
	}

	if (IsGameOver())
	{
		OnGameOver();
	}
	else
	{
		m_TurnPlayerType = GetPlayerType(GetEnemyPlayer(GetPlayer(m_TurnPlayerType)));
		m_Phase = Phase::UNIT_PHASE;
	}



}

Player* Game::GetEnemyPlayer(Player* player)
{
	//assert(player == m_Player1 || player == m_Player2);
	return player == &m_Player1 ? &m_Player2 : &m_Player1;
}

bool Game::IsGameOver()
{
	bool isPlayer1Die = m_Player1.GetHP() <= 0;
	bool isPlayer2Die = m_Player2.GetHP() <= 0;

	return isPlayer1Die || isPlayer2Die;
}

void Game::OnGameOver()
{
	// send packet

	// remove all.
}
