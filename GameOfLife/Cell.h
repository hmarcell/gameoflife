#pragma once
#include <vector>

class Cell {
public:
	const bool GetIsAlive() const;
	void SetIsAlive(bool IsAlive);
	void NextTurn();
	void DetermineNextState();
	Cell();
	void SetAliveNeighbours(uint8_t aliveNeighbours);
private:
	bool mIsAlive;
	bool mSurvives;
	uint8_t mAliveNeighbours;
};