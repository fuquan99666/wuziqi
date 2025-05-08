#include "Al.h"

void Al::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void Al::go()
{
	ChessPos pos = think();
	Sleep(1000);//假装思考
	chess->chessDown(&pos, CHESS_WHITE);
}

void Al::calculateScore()
{
	

	//评分数组清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap.size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			//对每个点计算
			

			if (chess->getChessData(row, col) != 0) {
				continue;
			}
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if (x == 0 and y == 0) {
						continue;
					}

					int personNum = 0;//棋手方（黑棋）有多少连续棋子
					int aiNum = 0;//白棋方有多少连续棋子
					int emptyNum = 0;//该方向两端空白位数量

					//对黑棋考虑
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow,curCol) == 1) {
							personNum++;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == -1) {

							break;

						}
					}
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 1) {
							personNum++;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == -1) {
							break;

						}
					}
					if (personNum == 1) {//连二
						scoreMap[row][col] = scoreMap[row][col] + 10;

					}
					if (personNum == 2 and emptyNum==1) {//死三
						scoreMap[row][col] += 30;

					}
					if (personNum == 2 and emptyNum == 2) {//活三
						scoreMap[row][col] += 40;
					}
					if (personNum == 3 and emptyNum == 1) {//死四
						scoreMap[row][col] += 60;
					}
					if (personNum == 3 and emptyNum == 2) {//活四
						scoreMap[row][col] += 2000;
					}
					if (personNum == 4 ) {//黑五
						scoreMap[row][col] += 10000;
					}

					//对白棋考虑
					emptyNum = 0;
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == -1) {
							aiNum++;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 1) {
							break;
						}
					}
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == -1) {
							aiNum++;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;

						}
						if (curRow >= 0 and curRow < size and curCol >= 0 and curCol < size and chess->getChessData(curRow, curCol) == 1) {
							break;

						}
					}
					if (aiNum == 0 and emptyNum == 1) {
						scoreMap[row][col] += 2;
					}
					if (aiNum == 0 and emptyNum == 2) {
						scoreMap[row][col] += 5;
					}
					if (aiNum == 1 and emptyNum==2) {//连二
						scoreMap[row][col] = scoreMap[row][col] + 10;
					}
					if (aiNum == 1 and emptyNum == 1) {
						scoreMap[row][col] += 7;
					}
					if (aiNum == 2 and emptyNum == 1) {//死三
						scoreMap[row][col] += 40;

					}
					if (aiNum == 2 and emptyNum == 2) {//活三
						scoreMap[row][col] += 50;
					}
					if (aiNum == 3 and emptyNum == 1) {//死四
						scoreMap[row][col] += 62;
					}
					if (aiNum == 3 and emptyNum == 2) {//活四
						scoreMap[row][col] += 3000;
					}
					if (aiNum == 4) {//白五
						scoreMap[row][col] += 20000;
					}
				}
			}
		}
	}
}

ChessPos Al::think()
{
	calculateScore();


	vector<ChessPos>maxPoints;
	int maxscore = 0;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (chess->getChessData(i, j) == 0) {
				if (scoreMap[i][j] > maxscore) {
					maxscore = scoreMap[i][j];
					maxPoints.clear();
				}
				if (scoreMap[i][j] == maxscore) {
					
					maxPoints.push_back(ChessPos(i,j));
				}
			}
		}
	}

	int index = rand() % maxPoints.size();
	return maxPoints[index];
}
