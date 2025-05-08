#pragma once
#include"chess.h"

class Al
{
public:
	//�ṩ��ʼ����
	void init(Chess* chess);

	//Al����
	void go();

private:
	Chess* chess;
	vector<vector<int>>scoreMap;

private:
	void calculateScore();
	ChessPos think();

};

