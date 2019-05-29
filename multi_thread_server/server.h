#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define  _CRT_SECURE_NO_WARNINGS
#ifndef __SERVER_H
#define __SERVER_H
#include <thread>
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <stdlib.h>
#pragma  comment(lib,"ws2_32.lib")
using namespace std;
static struct MyStruct
{
	SOCKET sock;
	int empt;
}soc[4];
class Server
{
public:
	Server();
	~Server();
	static void Work(int id);
private:
	SOCKET s;
};
#endif