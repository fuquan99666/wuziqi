#include "Man.h"
#include"ChessGame.h"
#include<conio.h>

void Man::init(Chess* chess)
{
	this->chess = chess;
	
}

void Man::lei(ChessGame* game)
{
	this->game = game;
}

void Man::go()
{
	
	MOUSEMSG msg;
	
	

	while (1) {
		//��ȡ�������Ϣ
		msg = GetMouseMsg();
		//ͨ��chess�������ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN and chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 0, 12, 0, 5)) {
			game->play();//���¿�ʼ
		}
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 0, 12, 893, 900)) {
			 chess->baocun("res/�浵.txt");//����
			exit(0);
		}
		
	}

	
	

	//����
	chess->chessDown(&pos, CHESS_BLACK);

	while (1) {
		msg = GetMouseMsg();
		//����
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 890, 902, 0, 5)) {
			
			chess->gengxin(&pos, 0);
			chess->playerFlag = !chess->playerFlag;
			chess->baocun("res/小丑存档.txt");//���ε�С��֮��
			game->xiaochou("res/小丑存档.txt");
			
		}
		if (msg.uMsg == WM_RBUTTONDOWN) {
			if ((chess->checkjinshou(&pos) and !chess->getcheckWin()) or chess->changlianjinshou() ) {
				
				mciSendString("play res/失败.mp3", 0, 0, 0);
				loadimage(0, "res/失败.jpg",900,902,true);//�Ҷ�������ĳ����������ĺ�����
				flag = !flag;
				
				_getch();
			}
			break;//������
		}
	}
}

void Man::houshou()
{
	MOUSEMSG msg;



	while (1) {
		//��ȡ�������Ϣ
		msg = GetMouseMsg();
		//ͨ��chess�������ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN and chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 0, 12, 0, 5)) {
			game->play();//���¿�ʼ
		}
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 0, 12, 893, 900)) {
			chess->baocun("res/存档.txt");//����
			exit(0);
		}

	}




	//����
	chess->chessDown(&pos, CHESS_WHITE);

	while (1) {
		msg = GetMouseMsg();
		//����
		if (msg.uMsg == WM_LBUTTONDOWN and chess->dianji(msg.x, msg.y, 890, 902, 0, 5)) {

			chess->gengxin(&pos, 0);
			chess->playerFlag = !chess->playerFlag;
			chess->baocun("res/小丑存档.txt");//���ε�С��֮��
			game->xiaochou("res/小丑存档.txt");

		}
		if (msg.uMsg == WM_RBUTTONDOWN) {
		
			break;//������
		}
	}
}




