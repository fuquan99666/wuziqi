#pragma once
#include<string>

#include<fstream>

//easyx��ͷ�ļ�������easyx����װ��
#include<graphics.h>

#include<vector>
using namespace std;

//��ʾ����λ��
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) :row(r), col(c){}
};

typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1  //����
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);

	//���̳�ʼ��
	void init();

	void wunai();

	//������Ƿ��γ�����
	bool clickBoard(int x, int y, ChessPos* pos);

	//���ӹ���
	void chessDown(ChessPos* pos, chess_kind_t kind);

	//��ȡ���̵Ĵ�С��13��15��17��19��
	int getGradeSize();

	//��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);

	int getChessData(int row, int col);

	//����Ƿ���ֽ���
	bool checkover();

	bool dianji(int x, int y, int shang, int xia, int zuo, int you);

	//���������
	int board[15][15];

	//��������
	void gengxin(ChessPos* Pos,int zhi);

	//��������
	void luozi(ChessPos* pos, int zhi);

	//���溯��
	void baocun(string filename);

	void chessnazou(ChessPos*pos);

	
	IMAGE xiaoqipan;//С����

	bool checkjinshou(ChessPos*pos);

	bool changlianjinshou();


	//������˭��
	bool playerFlag;//true:������  false:������

	bool getcheckWin();

	ChessPos* Pos = &lastPos;

private:
	IMAGE chessBlackImg;//��������
	IMAGE chessWhiteImg;//��������
	

	int gradeSize;//���̴�С��13��15��17��19��
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;//���Ӵ�С


	//��ǰ������ӷֲ���0�ޣ�1�ڣ�-1�� 
	vector<vector<int>> chessMap;




	void updateGameMap(ChessPos* pos);

	bool checkWin();//���ʤ���ѷ֣�����true,���򷵻�false

	ChessPos lastPos;

	

	


};

      