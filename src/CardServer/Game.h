#pragma once
typedef unsigned int PlayerID;
typedef unsigned int GameID;

class Game
{
public:
	Game();
	~Game();

	void OnStart();
	void OnTurn();
	void OnCard();
	void OnGameOver();


private:
	GameID m_GameID;
	PlayerID m_Player1ID;
	PlayerID m_Player2ID;


};

