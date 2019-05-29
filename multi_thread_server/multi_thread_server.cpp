// multi_thread_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Server.h"
Server::Server()
{
	WSADATA wsadata;
	WORD v = MAKEWORD(2, 2);
	if (::WSAStartup(v, &wsadata) < 0) { cout << "Failed to start server!" << endl; system("pause"); exit(0); }
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(13574);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (::bind(s, (LPSOCKADDR)& sin, sizeof(sin)) == SOCKET_ERROR) return;
	if (::listen(s, 5) == SOCKET_ERROR) return; cout << "The server has been started!" << endl;
	while (true)
	{
		int i;
		for (i = 0; i < 100; i++)
			if (soc[i].empt == 0) { soc[i].empt = 1; break; }
		sockaddr_in re; int n = sizeof(re);
		soc[i].sock = ::accept(s, (SOCKADDR*)& re, &n);
		if (soc[i].sock == INVALID_SOCKET) return;
		cout << "New client => " << soc[i].sock << endl;
		std::thread t(Work, i); t.detach();
	}
	closesocket(s);
}
Server::~Server() { ::WSACleanup(); }
void Server::Work(int id)
{
	char Msg[] = "Server => Welcome! Press [Esc] to edit your message, then press [Enter] to send!";
	::send(soc[id].sock, Msg, strlen(Msg), 0);
	while (true)
	{
		char buff[1024];
		int nR = ::recv(soc[id].sock, buff, 1025, 0);
		if (nR > 0)
		{
			buff[nR] = '\0';
			cout << "Received :" << buff << " (id:" << soc[id].sock << ")" << endl;
			for (int i = 0; i < 100; i++)
				if (soc[i].empt) ::send(soc[i].sock, buff, strlen(buff), 0);
		}
		else
		{
			cout << "Client => " << soc[id].sock << " logout!" << endl;
			closesocket(soc[id].sock);
			soc[id].empt = 0; return;
		}
	}
}
int main() { Server server; return 0; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
