#include "GameEngine.h"

std::vector<std::vector<Cell>> GameEngine::GetBoard() const {
	return mBoard;
}

void GameEngine::CountNeighbours() {	
	uint16_t left, right, top, bottom;
	uint8_t alive;
	for (int x = 0; x < mWidth; ++x) {
		for (int y = 0; y < mHeight; ++y)
		{
			left = (x > 0) ? x - 1 : mWidth - 1;
			right = (x < mWidth - 1) ? x + 1 : 0;
			top = (y > 0) ? y - 1 : mHeight - 1;
			bottom = (y < mHeight - 1) ? y + 1 : 0;
			alive = 0;

			alive += mBoard[left][top].GetIsAlive();
			alive += mBoard[x][top].GetIsAlive();
			alive += mBoard[right][top].GetIsAlive();
			alive += mBoard[left][y].GetIsAlive();
			alive += mBoard[right][y].GetIsAlive();
			alive += mBoard[left][bottom].GetIsAlive();
			alive += mBoard[x][bottom].GetIsAlive();
			alive += mBoard[right][bottom].GetIsAlive();

			mBoard[x][y].SetAliveNeighbours(alive);
		}
	}
}

void GameEngine::PopulateMatrix(float density) {
	std::random_device device;
	std::default_random_engine engine(device());
	std::uniform_real_distribution<float> random(0.0f, 1.0f);

	for (auto& row : mBoard) {
		for (Cell& cell : row) {
			cell.SetIsAlive(random(engine) < density);
		}
	}
}

GameEngine::GameEngine(uint8_t side, float density)		
	: mBoard(std::vector<std::vector<Cell>>(side, std::vector<Cell>(side)))
	, mHeight(side)
	, mWidth(side)
{
	PopulateMatrix(density);
	CountNeighbours();
}

GameEngine::GameEngine(uint8_t height, uint8_t width, float density)
	: mBoard(std::vector<std::vector<Cell>>(width, std::vector<Cell>(height)))
	, mHeight(height)
	, mWidth(width)
{
	PopulateMatrix(density);
	CountNeighbours();
}

GameEngine::GameEngine(uint8_t height, uint8_t width, uint8_t top, uint8_t left, const std::vector<std::vector<Cell>>& matrix)
	: mBoard(std::vector<std::vector<Cell>>(width, std::vector<Cell>(height)))
	, mHeight(height)
	, mWidth(width)
{
	InsertPattern(top, left, matrix); 
	CountNeighbours();
}

void GameEngine::NextTurn() {
	for (auto& row : mBoard) {
		for (Cell& cell : row) {
			cell.DetermineNextState();
		}
	}
	
	for (auto& row : mBoard) {
		for (Cell& cell : row) {
			cell.NextTurn();
		}
	}
}

std::ostream& operator<<(std::ostream& os, const GameEngine& engine) {
	for (size_t i = 0; i < engine.mBoard[0].size() + 2; i++)
	{
		os << "O";
	}
	os << std::endl;
	for (const auto& row : engine.mBoard) {
		os << "O";
		for (const Cell& cell : row) {
			os << (cell.GetIsAlive() ? "#" : " ");
		}
		os << "O";
		os << std::endl;
	}
	for (size_t i = 0; i < engine.mBoard[0].size() + 2; i++)
	{
		os << "O";
	}
	os << std::endl;
	return os;
}

void clear() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	std::cout << "\x1B[2J\x1B[H";
}

void GameEngine::Start() {
	int round = 0;
	char inp;
	while (CheckSurvivors() && round++ < mFINISH)
	{
		clear();
		std::cout << *this;
		NextTurn();
		CountNeighbours();
		std::cin.get();
	}
	clear();
	std::cout << *this;
}

bool GameEngine::CheckSurvivors() {
	bool survivorsRemain = false;
	for (auto& row : mBoard) {
		for (Cell& cell : row) {
			if (cell.GetIsAlive())
			{
				survivorsRemain = true;
			}
		}
	}
	return survivorsRemain;
}

void GameEngine::InsertPattern(uint8_t top, uint8_t left, const std::vector<std::vector<Cell>>& matrix) {

	for (size_t i = 0 ; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[0].size(); ++j)
		{
			mBoard[top + i][left + j] = matrix[i][j];
		}
	}
}
