#include "Cell.h"


Cell::Cell()
	: mIsAlive(0)
	, mSurvives(0)			
	, mAliveNeighbours(0)
{
	
}

const bool Cell::GetIsAlive() const {
	return mIsAlive;
}

void Cell::SetIsAlive(bool IsAlive) {
	mIsAlive = IsAlive;
}

void Cell::SetAliveNeighbours(uint8_t aliveNeighbours) {
	mAliveNeighbours = aliveNeighbours;
}

void Cell::DetermineNextState() {
	mSurvives = mIsAlive ? mAliveNeighbours == 2 || mAliveNeighbours == 3 : mAliveNeighbours == 3;	
}

void Cell::NextTurn() {
	mIsAlive = mSurvives;
}