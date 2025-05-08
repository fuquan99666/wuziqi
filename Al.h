#pragma once
#include"chess.h"

class Al
{
public:
	//提供初始条件
	void init(Chess* chess);

	//Al下棋
	void go();

private:
	Chess* chess;
	vector<vector<int>>scoreMap;

private:
	void calculateScore();
	ChessPos think();

};

