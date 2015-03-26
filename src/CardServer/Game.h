#pragma once
#include "Player.h"
#include "protocol.pb.h"
#include <vector>
typedef unsigned int PlayerID;
typedef unsigned int GameID;

struct ArcaneStackNode
{
	Card* arcaneCard;
	protocol::Card inPacket;
};
class Game
{
public:
	enum PlayerType
	{
		PLAYER_1,
		PLAYER_2,
	};

	enum Phase
	{
		UNIT_PHASE,
		VISION_PHASE,
	};

	Game();
	~Game();

	void OnPacket();

	void OnStart();
	void OnTurn();
	bool OnCard(protocol::Card inPacket);
	void OnGameOver();


	PlayerID GetPlayerID(Player* player);
	PlayerID GetPlayerID(PlayerType playerType);
	Player* GetPlayer(PlayerID playerID);
	Player* GetPlayer(PlayerType playerType);
	PlayerType GetPlayerType(Player* player);
	PlayerType GetPlayerType(PlayerID playerID);

	Player* GetEnemyPlayer(Player* player);

	void PushArcaneCardInStack(Card* card,
		protocol::Card& inPacket);
private:
	GameID m_GameID;
	PlayerID m_Player1ID;
	PlayerID m_Player2ID;

	Player m_Player1;
	Player m_Player2;


	PlayerType m_TurnPlayerType;
	PlayerType m_ArcaneTurnPlayerType;
	Phase m_Phase;

	std::vector<ArcaneStackNode> m_ArcaneStack;
};

