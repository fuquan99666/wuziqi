


#define le "A"
#define lele "AA"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>//�������
#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<WinSock2.h>//������

#pragma comment(lib,"ws2_32.lib")//�����





int main(void) {


	
		
	





	//��ʼ�������
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	// �׽��֣���ͷ���ӵ�����)
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	//���׽��� �趨��ַ�Ͷ˿ڣ���ͬ�ķ���
	SOCKADDR_IN serAddr;
	serAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//�ֽ���ת�� �����ֽ���-�������ֽ���,��ַ�ǳ����ͣ�long
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(80);//�˿��Ƕ�����short

	//�������൱��һ����Ů���ͻ��˾��൱����С���꣬��Ůס���Ǹ���ַ�أ��Ǹ����ƺ���

	bind(server, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));//����ַ��ӿڰ�
	
	//���׽�������Ϊ����ģʽ,���ǿ��Կ�ʼ������
	listen(server, 5);//��������






	//��ѭ��
	while (1) {//�������Ƕ�ʮ��Сʱ���������

		SOCKADDR_IN addrClient1;
		int len1 = sizeof(addrClient1);
		SOCKADDR_IN addrClient2;
		int len2 = sizeof(addrClient2);
		
			SOCKET client1 = accept(server, (sockaddr*)&addrClient1, &len1);//һ���������
			printf("���һ�Ѿ�����\n");
			SOCKET client2 = accept(server, (sockaddr*)&addrClient2, &len2);//�����������
			printf("��Ҷ��Ѿ�����\n");
			printf("׼������\n");
			srand(time(NULL));//���������
			int index = rand() % 2;
	
			if (index == 0) {
				send(client1, le, strlen(le), 0);
				send(client2, lele, strlen(lele), 0);
			}
			else {
				send(client2, le, strlen(le), 0);
				send(client1, lele, strlen(lele), 0);
			}

			
			//����������Ϣ
			
			char buf[9];
			
	

			

			if (index == 0) {
				while (1) {
					int chang = recv(client1, buf, sizeof(buf), 0);//�ڷ���������
					
						
					
						
						send(client2, buf, chang, 0);//�����׷�
						chang = recv(client2, buf, sizeof(buf), 0);//���巢������
					
						send(client1, buf, chang, 0);//�����ڷ�
					

				}
			}
			else {
				while (1) {
					int du = recv(client2, buf, sizeof(buf), 0);//�ڷ���������
					buf[du] = '\0';
					
					
						send(client1, buf,du , 0);//�����׷�
						du = recv(client1,buf,sizeof(buf), 0);//���巢������
						buf[du] = '\0';
						send(client2, buf, du, 0);//�����ڷ�
					

				}
			}
			
			

		
	}
	return 0;

}