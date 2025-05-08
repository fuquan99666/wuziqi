#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define heihei "shabi"
#include<stdio.h>//�������

#include<conio.h>
#include<WinSock2.h>//������

#pragma comment(lib,"ws2_32.lib")//�����


#include "ChessGame.h"
#include<mmsystem.h>






ChessGame::ChessGame(Man* man, Al* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

//�Ծ�
void ChessGame::play()
{
	chess->init();
	while (1) {
		//������������
		man->go();
		if (man->flag) {
			man->flag = !man->flag;
			chess->init();
			continue;
		}
		if (chess->checkover()) {
			chess->init();
			continue;
		}
	

		//����ai����
		ai->go();
		if (chess->checkover()) {
			chess->init();
			continue;
		}
	}

	
}

void ChessGame::lianji()
{
	//��ʼ�������
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	// �׽��֣���ͷ���ӵ�����)
	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);


	SOCKADDR_IN serAddr;				//tailscale
	serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.5.2");//�ֽ���ת�� �����ֽ���-�������ֽ���,��ַ�ǳ����ͣ�long
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(80);//�˿��Ƕ�����short
	//你好啊
	

	connect(client, (sockaddr*)&serAddr, sizeof(serAddr));

	chess->init();
	char buf[2025];
	int xuhao = recv(client, buf, strlen(buf), 0);
	printf("%d", xuhao);
	if (xuhao == 1) {
		printf("你是黑棋\n");
	}
	else {
		printf("你是白棋\n");
	}



	while (1) {
		//���Ǻ���
		if (xuhao == 1) {
			man->go();
			
		
			char a[20];
		
			int i = 0;
			char ha;
			if (man->pos.row <= 9) {
				ha = man->pos.row + '0';
				a[i] = ha;
				i++;
			}
			else {
				ha = man->pos.row - 10 + '0';
				a[i] = '1';
				i++;
				a[i] = ha;
				i++;
			}
			a[i] = ' ';
			i++;
			if (man->pos.col <= 9) {
				ha = man->pos.col + '0';
				a[i] = ha;
				i++;
			}
			else {
				ha = man->pos.col - 10 + '0';
				a[i] = '1';
				i++;
				a[i] = ha;
				i++;
			}
			a[i] = '\0';
		
			send(client, a, i, 0);

			if (man->flag) {
				man->flag = !man->flag;
				chess->init();
				continue;
			}
			if (chess->checkover()) {
				chess->init();
				continue;
			}

			char b[20];
			
			int n= recv(client, b, sizeof(b), 0);
			b[n] = '\0';
			if (n > 0) {
				ChessPos pos;
				int x, y;
				int wu;
				if (b[1] == ' ') {
					wu = b[0] - '0';
					x = wu;
					if (n==3) {
						wu = b[2] - '0';
						y = wu;
					}
					else {
						wu = b[3] - '0';
						y = 10 + wu;
					}
				}
				else {
					wu = b[1] - '0';
					x = 10 + wu;
					if (n==4) {
						wu = b[3] - '0';
						y = wu;
					}
					else {
						wu = b[4] - '0';
						y = 10 + wu;
					}
				}
				pos.row = x, pos.col = y;
				chess->chessDown(&pos, CHESS_WHITE);
				if (chess->checkover()) {
					chess->init();
					continue;
				}
			}
		}
		
		

		//���ǰ���
		if (xuhao == 2) {
			char b[20];

			int n = recv(client, b, sizeof(b), 0);
			b[n] = '\0';
			if (n > 0) {
				ChessPos pos;
				int x, y;
				int wu;
				if (b[1]==' ') {
					wu = b[0] - '0';
					x = wu;
					if (n==3) {
						wu = b[2] - '0';
						y = wu;
					}
					else {
						wu = b[3] - '0';
						y = 10 + wu;
					}
				}
				else {
					wu = b[1] - '0';
					x = 10 + wu;
					if (n==4) {
						wu = b[3] - '0';
						y = wu;
					}
					else {
						wu = b[4] - '0';
						y = 10 + wu;
					}
				}
				pos.row = x, pos.col = y;
				chess->chessDown(&pos, CHESS_BLACK);

				if ((chess->checkjinshou(chess->Pos) and !chess->getcheckWin()) or chess->changlianjinshou()) {

					mciSendString("play res/ʧ��.mp3", 0, 0, 0);
					loadimage(0, "res/ʧ��.jpg", 900, 902, true);//�Ҷ�������ĳ����������ĺ�����


					_getch();
				}
				if (chess->getcheckWin()) {
					chess->playerFlag = !chess->playerFlag;
					chess->checkover();
					chess->init();
					continue;
				}
			}
			//����2�ţ����֣�����
			man->houshou();
			
			
			char a[20];
			 int i = 0;
			 char ha;
			
			if (man->pos.row <= 9) {
				ha = man->pos.row + '0';
				a[i] = ha;
				i++;
			}
			else {
				ha = man->pos.row - 10 + '0';
				a[i] = '1';
				i++;
				a[i] = ha;
				i++;
			}
			a[i] = ' ';
			i++;
			if (man->pos.col <= 9) {
				ha = man->pos.col + '0';
				a[i] = ha;
				i++;
			}
			else {
				ha = man->pos.col - 10 + '0';
				a[i] = '1';
				i++;
				a[i] = ha;
				i++;
			}
			send(client, a, i, 0);
	

			if (chess->getcheckWin()) {
				chess->playerFlag = !chess->playerFlag;
				chess->checkover();
				chess->init();
				continue;
			}
		}
	}

}

void ChessGame::continueplay(string filename)
{
	chess->init();


	ChessPos Pos;
	
	ifstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < chess->getGradeSize(); i++) {
			for (int j = 0; j < chess->getGradeSize(); j++) {
				file >> chess->board[i][j];
				Pos.row = i;
				Pos.col = j;
				if (chess->board[i][j] == 1) {
					chess->gengxin(&Pos, 1);
					chess->luozi(&Pos, 1);
				}
				if (chess->board[i][j] == -1) {
					chess->gengxin(&Pos, -1);
					chess->luozi(&Pos, -1);
				}
			}
		}
	}
	file.close();
	zaiwan();
	
}

void ChessGame::xiaochou(string filename)
{
	chess->wunai();


	ChessPos Pos;

	ifstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < chess->getGradeSize(); i++) {
			for (int j = 0; j < chess->getGradeSize(); j++) {
				file >> chess->board[i][j];
				Pos.row = i;
				Pos.col = j;
				if (chess->board[i][j] == 1) {
					chess->gengxin(&Pos, 1);
					chess->luozi(&Pos, 1);
				}
				if (chess->board[i][j] == -1) {
					chess->gengxin(&Pos, -1);
					chess->luozi(&Pos, -1);
				}
			}
		}
	}
	file.close();
	zaiwan();
}

void ChessGame::zaiwan()
{
	while (1) {
		//������������
	
		man->go();
		if (man->flag) {
			man->flag = !man->flag;
			chess->init();
			continue;
		}
		if (chess->checkover()) {
			chess->init();
			continue;
		}

		//����ai����
		ai->go();
		if (chess->checkover()) {
			chess->init();
			continue;
		}
	}

}
