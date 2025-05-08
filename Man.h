#pragma once
#include"Chess.h"


class ChessGame;
class Man
{
public:
	//��ʼ����
	void init(Chess* chess);
	void lei(ChessGame* game);

	//������
	void go();

	void houshou();

	ChessPos pos;
	ChessPos* Pos = &pos;
	bool flag = false;

private:
	Chess* chess;
	ChessGame* game;
};

