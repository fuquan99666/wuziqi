#pragma once
#include"Man.h"
#include"Al.h"
#include"Chess.h"

using namespace std;

class Man;
class ChessGame
{
public:
	//��ʼ��
	ChessGame(Man* man, Al* ai, Chess* chess);
	//��ʼ�Ծ�
	void play();

	//��������
	void lianji();

	void continueplay(string filename);

	void xiaochou(string filename);
	
	void zaiwan();

	int flag = 0;
//������ݳ�Ա
private:
	Man* man;
	Al* ai;
	Chess* chess;
	
};

