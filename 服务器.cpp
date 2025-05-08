


#define le "A"
#define lele "AA"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>//输入输出
#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<WinSock2.h>//网络编程

#pragma comment(lib,"ws2_32.lib")//网络库





int main(void) {


	
		
	





	//初始化网络库
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	// 套接字（插头连接到网络)
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	//绑定套接字 设定地址和端口（不同的服务）
	SOCKADDR_IN serAddr;
	serAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//字节序转化 本机字节序-》网络字节序,地址是长整型，long
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(80);//端口是短整型short

	//服务器相当于一个美女，客户端就相当于是小青年，美女住在那个地址呢，那个门牌号呢

	bind(server, (SOCKADDR*)&serAddr, sizeof(SOCKADDR));//将地址与接口绑定
	
	//将套接字设置为监听模式,就是可以开始收信了
	listen(server, 5);//三次握手






	//死循环
	while (1) {//服务器是二十四小时不间断运行

		SOCKADDR_IN addrClient1;
		int len1 = sizeof(addrClient1);
		SOCKADDR_IN addrClient2;
		int len2 = sizeof(addrClient2);
		
			SOCKET client1 = accept(server, (sockaddr*)&addrClient1, &len1);//一号玩家上线
			printf("玩家一已经上线\n");
			SOCKET client2 = accept(server, (sockaddr*)&addrClient2, &len2);//二号玩家上线
			printf("玩家二已经上线\n");
			printf("准备就绪\n");
			srand(time(NULL));//随机数种子
			int index = rand() % 2;
	
			if (index == 0) {
				send(client1, le, strlen(le), 0);
				send(client2, lele, strlen(lele), 0);
			}
			else {
				send(client2, le, strlen(le), 0);
				send(client1, lele, strlen(lele), 0);
			}

			
			//接受落子信息
			
			char buf[9];
			
	

			

			if (index == 0) {
				while (1) {
					int chang = recv(client1, buf, sizeof(buf), 0);//黑方发过来的
					
						
					
						
						send(client2, buf, chang, 0);//发给白方
						chang = recv(client2, buf, sizeof(buf), 0);//白棋发过来的
					
						send(client1, buf, chang, 0);//发给黑方
					

				}
			}
			else {
				while (1) {
					int du = recv(client2, buf, sizeof(buf), 0);//黑方发过来的
					buf[du] = '\0';
					
					
						send(client1, buf,du , 0);//发给白方
						du = recv(client1,buf,sizeof(buf), 0);//白棋发过来的
						buf[du] = '\0';
						send(client2, buf, du, 0);//发给黑方
					

				}
			}
			
			

		
	}
	return 0;

}