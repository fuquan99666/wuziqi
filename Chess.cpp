#include "Chess.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<math.h>
#include<conio.h>




void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}

Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y=margin_y;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::init()
{
	

	//��ʾ���ǵ�����ͼƬ
	loadimage(0, "res/棋盘4.jpg");
	

	//��ʼ��ʾ��
	mciSendString("play res/start.wav", 0, 0, 0);

	//���غ���Ͱ����ͼƬ
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);

	//��������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}

	playerFlag = true;
}

void Chess::wunai()
{

	//��ʾ���ǵ�����ͼƬ
	loadimage(0, "res/棋盘4.jpg");


	//��ʼ��ʾ��
	mciSendString("play res/bg.mp3", 0, 0, 0);

	//���غ���Ͱ����ͼƬ
	loadimage(&chessBlackImg, "res/black.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "res/white.png", chessSize, chessSize, true);

	//��������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}

	playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	int row = (y - margin_y) / chessSize;
	int col = (x - margin_x) / chessSize;
	int leftTopPosX = margin_x + col * chessSize;
	int leftTopPosY = margin_y + row * chessSize;
	int offset = chessSize * 0.4;

	int len;
	bool ret = false;

	do {
		//���ϽǾ�����ж�
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));

		
		if (len <= offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[row][col] == 0) {
				ret = true;
			}
			break;
		}
		
		//���Ͻǵ��ж�
		int x2 = leftTopPosX + chessSize;
		int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len <= offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[row][col + 1] == 0) {
				ret = true;
			}
			break;
		}

		//���½ǵ��ж�
		int x3 = leftTopPosX;
		int y3 = leftTopPosY + chessSize;
		len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
		if (len <= offset) {
			pos->row = row + 1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

		//���½ǵ��ж�
		int x4 = leftTopPosX + chessSize;
		int y4 = leftTopPosY + chessSize;
		len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
		if (len <= offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}

	} while (0);
	return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play res/down7.WAV",0,0,0);
	int x = margin_x + pos->col * chessSize-0.5*chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize+2;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);

	}
	if (kind == CHESS_BLACK) {
		putimagePNG(x, y, &chessBlackImg);
	}

	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
	
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkover()
{
	
	//checkwin()
	if (checkWin()) {
		Sleep(1500);
		if (playerFlag == false) {
			//�ղ�������Ǻڷ�
			mciSendString("play res/胜利.mp3", 0, 0, 0);
			loadimage(0, "res/胜利.jpg",900,902,true);
		}
		else {
			mciSendString("play res/失败.mp3", 0, 0, 0);
			loadimage(0, "res/失败.jpg",900,902,true);
		}

		_getch();//��ͣ
		return true;
	}
	return false;
}

void Chess::updateGameMap(ChessPos* pos)
{
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;
	lastPos = *pos;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;//������ӵ�λ��

	//ˮƽ����
	for (int i = 0; i < 5; i++) {
		//���ڵ�i�ε��������ʼλ��
		if (col - i >= 0 and col - i + 4 < gradeSize and chessMap[row][col - i] == chessMap[row][col - i + 1] and chessMap[row][col - i + 1] == chessMap[row][col - i + 2] and chessMap[row][col - i + 2] == chessMap[row][col - i + 3] and chessMap[row][col - i + 3] == chessMap[row][col - i + 4]) {
			return true;
		}
	}
	//��ֱ����
	for (int i = 0; i < 5; i++) {
		if ( row - i >= 0 and row - i + 4 < gradeSize and chessMap[row - i][col] == chessMap[row - i + 1][col] and chessMap[row - i + 1][col] == chessMap[row - i + 2][col] and chessMap[row - i + 2][col] == chessMap[row - i + 3][col] and chessMap[row - i + 3][col] == chessMap[row - i + 4][col] ) {
			return true;
		}
	}

	//��\������
	for (int i = 0; i < 5; i++) {
		if ( row - i >= 0 and row - i + 4 < gradeSize and col - i >= 0 and col - i + 4 < gradeSize and chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] and chessMap[row - i + 1][col - i + 1] == chessMap[row - i + 2][col - i + 2] and chessMap[row - i + 2][col - i + 2] == chessMap[row - i + 3][col - i + 3] and chessMap[row - i + 3][col - i + 3] == chessMap[row - i + 4][col - i + 4]  ) {
			return true;
		}
	}
	//"/"����
	for (int i = 0; i < 5; i++) {
		if ( row - i >= 0 and row - i + 4 < gradeSize and col + i < gradeSize and col + i - 4 >= 0 and chessMap[row - i][col + i] == chessMap[row - i + 1][col + i - 1] and chessMap[row - i + 1][col + i - 1] == chessMap[row - i + 2][col + i - 2] and chessMap[row - i + 2][col + i - 2] == chessMap[row - i + 3][col + i - 3] and chessMap[row - i + 3][col + i - 3] == chessMap[row - i + 4][col + i - 4]  ) {
			return true;
		}
	}


	return false;
}

bool Chess::dianji(int x, int y, int shang, int xia, int zuo, int you)
{
	if (x > zuo and x<you and y>shang and y < xia) {
		return true;
	}
	return false;
}

void Chess::gengxin(ChessPos* Pos, int zhi)
{
	chessMap[Pos->row][Pos->col] = zhi;
}

void Chess::luozi(ChessPos* pos, int zhi)
{
	int x = margin_x + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize+2;

	if (zhi == -1) {
		putimagePNG(x, y, &chessWhiteImg);

	}
	if (zhi ==1) {
		putimagePNG(x, y, &chessBlackImg);
	}
}



void Chess::baocun(string filename)
{
	ofstream file(filename);
	if (file.is_open()) {
		for (int i = 0; i < gradeSize; i++) {
			for (int j = 0; j < gradeSize; j++) {
				file << chessMap[i][j] << " ";
			}
			file << '\n';
		}
	}
	file.close();
}

void Chess::chessnazou(ChessPos* pos)///С�������֮�٣���Ȼû���ˣ������Ǽ���һ��
{

	mciSendString("play res/无效点击.mp3", 0, 0, 0);
	float x = margin_x + pos->col * chessSize - 0.5 * chessSize+0.9;//�������
	float y = margin_y + pos->row * chessSize - 0.5 * chessSize+4.5;
	loadimage(&xiaoqipan, "res/����6.jpg",chessSize,chessSize,true);
	putimage(x, y, &xiaoqipan);
	
}

bool Chess::checkjinshou(ChessPos* pos)
{
	int row = pos->row;
	int col = pos->col;
	int san= 0;
	int si = 0;
	
	//��������
	//����
	if (((col-2>=0 and chessMap[row] [col-2]==0) or (col+4<gradeSize and chessMap[row][col+4]==0)) and col-1>=0 and col+3<gradeSize and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 1 and chessMap[row][col + 3] == 0 and chessMap[row][col - 1] == 0) {
		san++;//������ߣ�
	}
	if (((col - 3 >= 0 and chessMap[row][col - 3] == 0) or (col + 3 < gradeSize and chessMap[row][col + 3] == 0)) and col - 2 >= 0 and col + 2 < gradeSize and chessMap[row][col - 2] == 0 and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 0) {
		san++;//�м�
	}
	if (((col - 4 >= 0 and chessMap[row][col - 4] == 0) or (col + 2 < gradeSize and chessMap[row][col + 2] == 0)) and col - 3 >= 0 and col + 1 < gradeSize and chessMap[row][col - 3] == 0 and chessMap[row][col - 2] == 1 and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 0) {
		san++;//���ұ�
	}
	//����
	if (((col - 1 >= 0 and chessMap[row][col - 1] == 0) or (col + 4 < gradeSize and chessMap[row][col + 4] == 0)) and col + 3 < gradeSize and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 1 and chessMap[row][col + 3] == 1) {
		si++;//����
	}
	if (((col - 2 >= 0 and chessMap[row][col - 2] == 0) or (col + 3 < gradeSize and chessMap[row][col + 3] == 0)) and col - 1 >= 0 and col + 2 < gradeSize and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 1) {
		si++;//�ڶ���
	}
	if (((col - 3 >= 0 and chessMap[row][col - 3] == 0) or (col + 2 < gradeSize and chessMap[row][col + 2] == 0)) and col - 2 >= 0 and col + 1 < gradeSize and chessMap[row][col - 2] == 1 and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 1) {
		si++;//������
	}
	if (((col - 4 >= 0 and chessMap[row][col - 4] == 0) or (col + 1 < gradeSize and chessMap[row][col + 1] == 0)) and col - 3 >= 0 and chessMap[row][col - 3] == 1 and chessMap[row][col - 2] == 1 and chessMap[row][col - 1] == 1) {
		si++;//���ĸ�
	}
	//���ģ�3��1��
	//if (col-1>=0 and chessMap[row][col-1]==0 ????and col + 4 < gradeSize and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 1 and chessMap[row][col + 3] == 0 and chessMap[row][col + 4] == 1) {
		//si++;//��1
	//}
	//if (col - 2 >= 0 and chessMap[row][col-2]==0 and col + 3 < gradeSize and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 1 and chessMap[row][col + 2] == 0 and chessMap[row][col + 3] == 1) {
		//si++;//���
	//}
	//if (col - 2 >= 0 and col + 2 < gradeSize and chessMap[row][col - 2] == 1 and chessMap[row][col - 1] == 1 and chessMap[row][col + 1] == 0 and chessMap[row][col + 2] == 1) {
		//si++;//����
	//}
	//if (col - 4 >= 0 and chessMap[row][col - 4] == 1 and chessMap[row][col - 3] == 1 and chessMap[row][col - 2] == 1 and chessMap[row][col - 1] == 0) {
		//si++;//��һ
	//}
	//���ģ�1��3��
	//if(col)
	// �ϱ�����
	//����
	if (((row - 2 >= 0 and chessMap[row - 2][col] == 0) or (row + 4 < gradeSize and chessMap[row + 4][col] == 0)) and row - 1 >= 0 and row + 3 < gradeSize and chessMap[row + 1][col] == 1 and chessMap[row + 2][col] == 1 and chessMap[row + 3][col] == 0 and chessMap[row - 1][col] == 0) {
		san += 1; //�����ϱߣ�
		}
			
		if (((row - 3 >= 0 and chessMap[row - 3][col] == 0) or (row + 3 < gradeSize and chessMap[row + 3][col] == 0)) and row - 2 >= 0 and row + 2 < gradeSize and chessMap[row - 2][col] == 0 and chessMap[row - 1][col] == 1 and chessMap[row + 1][col] == 1 and chessMap[row + 2][col] == 0) {
			san += 1; // �м�
		}
			
		if (((row - 4 >= 0 and chessMap[row - 4][col] == 0) or (row + 2 < gradeSize and chessMap[row + 2][col] == 0)) and row - 3 >= 0 and row + 1 < gradeSize and chessMap[row - 3][col] == 0 and chessMap[row - 2][col] == 1 and chessMap[row - 1][col] == 1 and chessMap[row + 1][col] == 0) {
			san += 1;//���±�
		}
			

					// ����
		if (((row - 1 >= 0 and chessMap[row - 1][col] == 0) or (row + 4 < gradeSize and chessMap[row + 4][col] == 0)) and row + 3 < gradeSize and chessMap[row + 1][col] == 1 and chessMap[row + 2][col] == 1 and chessMap[row + 3][col] == 1) {
			si += 1; // ����
		}
						
		if (((row - 2 >= 0 and chessMap[row - 2][col] == 0) or (row + 3 < gradeSize and chessMap[row + 3][col] == 0)) and row - 1 >= 0 and row + 2 < gradeSize and chessMap[row - 1][col] == 1 and chessMap[row + 1][col] == 1 and chessMap[row + 2][col] == 1) {
			si += 1; //�ڶ���
		}
						
		if (((row - 3 >= 0 and chessMap[row - 3][col] == 0) or (row + 2 < gradeSize and chessMap[row + 2][col] == 0)) and row - 2 >= 0 and row + 1 < gradeSize and chessMap[row - 2][col] == 1 and chessMap[row - 1][col] == 1 and chessMap[row + 1][col] == 1) {
			si += 1; // ������
		}
							
		if (((row - 4 >= 0 and chessMap[row - 4][col] == 0) or (row + 1 < gradeSize and chessMap[row + 1][col] == 0)) and row - 3 >= 0 and chessMap[row - 3][col] == 1 and chessMap[row - 2][col] == 1 and chessMap[row - 1][col] == 1) {
			si += 1; //���ĸ�
		}
		// �������Ϸ���
		//����							

								
		if (((row - 2 >= 0 and col - 2 >= 0 and chessMap[row - 2][col - 2] == 0) or (row + 4 < gradeSize and col + 4 < gradeSize and chessMap[row + 4][col + 4] == 0)) and row - 1 >= 0 and col - 1 >= 0 and row + 3 < gradeSize and col + 3 < gradeSize and chessMap[row + 1][col + 1] == 1 and chessMap[row + 2][col + 2] == 1 and chessMap[row + 3][col + 3] == 0 and chessMap[row - 1][col - 1] == 0) {
			san += 1; // �������Ͻǣ�
		}
										
		if (((row - 3 >= 0 && col - 3 >= 0 && chessMap[row - 3][col - 3] == 0) ||
			(row + 3 < gradeSize && col + 3 < gradeSize && chessMap[row + 3][col + 3] == 0)) &&
			row - 2 >= 0 && col - 2 >= 0 && row + 2 < gradeSize && col + 2 < gradeSize &&
			chessMap[row - 2][col - 2] == 0 && chessMap[row - 1][col - 1] == 1 &&
			chessMap[row + 1][col + 1] == 1 && chessMap[row + 2][col + 2] == 0) {
			san++;
		}
		if (((row - 4 >= 0 && col - 4 >= 0 && chessMap[row - 4][col - 4] == 0) ||
			(row + 2 < gradeSize && col + 2 < gradeSize && chessMap[row + 2][col + 2] == 0)) &&
			row - 3 >= 0 && col - 3 >= 0 && row + 1 < gradeSize && col + 1 < gradeSize &&
			chessMap[row - 3][col - 3] == 0 && chessMap[row - 2][col - 2] == 1 &&
			chessMap[row - 1][col - 1] == 1 && chessMap[row + 1][col + 1] == 0) {
			san++;
		}
		// ����
		if (((row - 1 >= 0 && col - 1 >= 0 && chessMap[row - 1][col - 1] == 0) ||
			(row + 4 < gradeSize && col + 4 < gradeSize && chessMap[row + 4][col + 4] == 0)) &&
			row + 3 < gradeSize && col + 3 < gradeSize &&
			chessMap[row + 1][col + 1] == 1 && chessMap[row + 2][col + 2] == 1 &&
			chessMap[row + 3][col + 3] == 1) {
			si++;
		}
		if (((row - 2 >= 0 && col - 2 >= 0 && chessMap[row - 2][col - 2] == 0) ||
			(row + 3 < gradeSize && col + 3 < gradeSize && chessMap[row + 3][col + 3] == 0)) &&
			row - 1 >= 0 && col - 1 >= 0 && row + 2 < gradeSize && col + 2 < gradeSize &&
			chessMap[row - 1][col - 1] == 1 && chessMap[row + 1][col + 1] == 1 &&
			chessMap[row + 2][col + 2] == 1) {
			si++;
		}
		if (((row - 3 >= 0 && col - 3 >= 0 && chessMap[row - 3][col - 3] == 0) ||
			(row + 2 < gradeSize && col + 2 < gradeSize && chessMap[row + 2][col + 2] == 0)) &&
			row - 2 >= 0 && col - 2 >= 0 && row + 1 < gradeSize && col + 1 < gradeSize &&
			chessMap[row - 2][col - 2] == 1 && chessMap[row - 1][col - 1] == 1 &&
			chessMap[row + 1][col + 1] == 1) {
			si++;
		}
		if (((row - 4 >= 0 && col - 4 >= 0 && chessMap[row - 4][col - 4] == 0) ||
			(row + 1 < gradeSize && col + 1 < gradeSize && chessMap[row + 1][col + 1] == 0)) &&
			row - 3 >= 0 && col - 3 >= 0 &&
			chessMap[row - 3][col - 3] == 1 && chessMap[row - 2][col - 2] == 1 &&
			chessMap[row - 1][col - 1] == 1) {
			si++;
		}

																// �������Ϸ���
																// ����
																if (((row - 2 >= 0 && col + 2 < gradeSize && chessMap[row - 2][col + 2] == 0) ||
																	(row + 4 < gradeSize && col - 4 >= 0 && chessMap[row + 4][col - 4] == 0)) &&
																	row - 1 >= 0 && col + 1 < gradeSize && row + 3 < gradeSize && col - 3 >= 0 &&
																	chessMap[row + 1][col - 1] == 1 && chessMap[row + 2][col - 2] == 1 &&
																	chessMap[row + 3][col - 3] == 0 && chessMap[row - 1][col + 1] == 0) {
																	san++;
																}
										if (((row - 3 >= 0 && col + 3 < gradeSize && chessMap[row - 3][col + 3] == 0) ||
											(row + 3 < gradeSize && col - 3 >= 0 && chessMap[row + 3][col - 3] == 0)) &&
											row - 2 >= 0 && col + 2 < gradeSize && row + 2 < gradeSize && col - 2 >= 0 &&
											chessMap[row - 2][col + 2] == 0 && chessMap[row - 1][col + 1] == 1 &&
											chessMap[row + 1][col - 1] == 1 && chessMap[row + 2][col - 2] == 0) {
											san++;
										}
										if (((row - 4 >= 0 && col + 4 < gradeSize && chessMap[row - 4][col + 4] == 0) ||
											(row + 2 < gradeSize && col - 2 >= 0 && chessMap[row + 2][col - 2] == 0)) &&
											row - 3 >= 0 && col + 3 < gradeSize && row + 1 < gradeSize && col - 1 >= 0 &&
											chessMap[row - 3][col + 3] == 0 && chessMap[row - 2][col + 2] == 1 &&
											chessMap[row - 1][col + 1] == 1 && chessMap[row + 1][col - 1] == 0) {
											san++;
										}
										// ����
										if (((row - 1 >= 0 && col + 1 < gradeSize && chessMap[row - 1][col + 1] == 0) ||
											(row + 4 < gradeSize && col - 4 >= 0 && chessMap[row + 4][col - 4] == 0)) &&
											row + 3 < gradeSize && col - 3 >= 0 &&
											chessMap[row + 1][col - 1] == 1 && chessMap[row + 2][col - 2] == 1 &&
											chessMap[row + 3][col - 3] == 1) {
											si++;
										}
										if (((row - 2 >= 0 && col + 2 < gradeSize && chessMap[row - 2][col + 2] == 0) ||
											(row + 3 < gradeSize && col - 3 >= 0 && chessMap[row + 3][col - 3] == 0)) &&
											row - 1 >= 0 && col + 1 < gradeSize && row + 2 < gradeSize && col - 2 >= 0 &&
											chessMap[row - 1][col + 1] == 1 && chessMap[row + 1][col - 1] == 1 &&
											chessMap[row + 2][col - 2] == 1) {
											si++;
										}
										if (((row - 3 >= 0 && col + 3 < gradeSize && chessMap[row - 3][col + 3] == 0) ||
											(row + 2 < gradeSize && col - 2 >= 0 && chessMap[row + 2][col - 2] == 0)) &&
											row - 2 >= 0 && col + 2 < gradeSize && row + 1 < gradeSize && col - 1 >= 0 &&
											chessMap[row - 2][col + 2] == 1 && chessMap[row - 1][col + 1] == 1 &&
											chessMap[row + 1][col - 1] == 1) {
											si++;
										}
										if (((row - 4 >= 0 && col + 4 < gradeSize && chessMap[row - 4][col + 4] == 0) ||
											(row + 1 < gradeSize && col - 1 >= 0 && chessMap[row + 1][col - 1] == 0)) &&
											row - 3 >= 0 && col + 3 < gradeSize &&
											chessMap[row - 3][col + 3] == 1 && chessMap[row - 2][col + 2] == 1 &&
											chessMap[row - 1][col + 1] == 1) {
											si++;
										}
	if (san>=2 or  si >= 2) {
		return true;
	}
	return false;
}

bool Chess::changlianjinshou()
{
	int row = lastPos.row;
	int col = lastPos.col;//������ӵ�λ��

	//ˮƽ����
	for (int i = 0; i < 6; i++) {
		//���ڵ�i�ε��������ʼλ��
		if (col - i >= 0 and col - i + 5 < gradeSize and chessMap[row][col - i] == chessMap[row][col - i + 1] and chessMap[row][col - i + 1] == chessMap[row][col - i + 2] and chessMap[row][col - i + 2] == chessMap[row][col - i + 3] and chessMap[row][col - i + 3] == chessMap[row][col - i + 4] and chessMap[row][col-i+4]==chessMap[row][col-i+5]) {
			return true;
		}
	}
	//��ֱ����
	for (int i = 0; i < 6; i++) {
		if (row - i >= 0 and row - i + 5 < gradeSize and chessMap[row - i][col] == chessMap[row - i + 1][col] and chessMap[row - i + 1][col] == chessMap[row - i + 2][col] and chessMap[row - i + 2][col] == chessMap[row - i + 3][col] and chessMap[row - i + 3][col] == chessMap[row - i + 4][col] and chessMap[row-i+4][col]==chessMap[row-i+5][col]) {
			return true;
		}
	}

	//��\������
	for (int i = 0; i < 6; i++) {
		if (row - i >= 0 and row - i + 5 < gradeSize and col - i >= 0 and col - i + 5 < gradeSize and chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] and chessMap[row - i + 1][col - i + 1] == chessMap[row - i + 2][col - i + 2] and chessMap[row - i + 2][col - i + 2] == chessMap[row - i + 3][col - i + 3] and chessMap[row - i + 3][col - i + 3] == chessMap[row - i + 4][col - i + 4] and chessMap[row-i+4][col-i+4]==chessMap[row-i+5][col-i+5]) {
			return true;
		}
	}
	//"/"����
	for (int i = 0; i < 6; i++) {
		if (row - i >= 0 and row - i + 5 < gradeSize and col + i < gradeSize and col + i - 5 >= 0 and chessMap[row - i][col + i] == chessMap[row - i + 1][col + i - 1] and chessMap[row - i + 1][col + i - 1] == chessMap[row - i + 2][col + i - 2] and chessMap[row - i + 2][col + i - 2] == chessMap[row - i + 3][col + i - 3] and chessMap[row - i + 3][col + i - 3] == chessMap[row - i + 4][col + i - 4] and chessMap[row-i+4][col+i-4]==chessMap[row-i+5][col+i-5]) {
			return true;
		}
	}

	return false;
}

bool Chess::getcheckWin()
{
	return checkWin();
}







