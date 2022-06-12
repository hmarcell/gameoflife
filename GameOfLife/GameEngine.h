#pragma once
#include "Cell.h"
#include <random>
#include <iostream>

class GameEngine {
public:
	GameEngine(uint8_t side, float density = 0.1f);
	GameEngine(uint8_t height, uint8_t width, float density = 0.1f);
	GameEngine(uint8_t height, uint8_t width, uint8_t top, uint8_t left, const std::vector<std::vector<Cell>>& matrix);	
	void Start();
	std::vector<std::vector<Cell>> GetBoard() const;
private:
	void InsertPattern(uint8_t top, uint8_t left, const std::vector<std::vector<Cell>>& matrix);
	bool CheckSurvivors();
	friend std::ostream& operator<<(std::ostream& os, const GameEngine& engine);
	void CountNeighbours();
	void PopulateMatrix(float density);
	void NextTurn();
	std::vector<std::vector<Cell>> mBoard;		
	uint8_t mHeight;
	uint8_t mWidth;
	const uint8_t mFINISH = 100;
};