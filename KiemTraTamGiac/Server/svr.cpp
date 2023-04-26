#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BUFLEN 512

using namespace std;

class Triangle{
	private :
		int a, b, c;
		
	public :
		Triangle(int a, int b, int c){
			this->a = a;
			this->b = b;
			this->c = c;
		}
		bool isTriangle(){
			return (a + b > c && a + c > b && b + c > a);
		}
};

bool check(string s){
	stringstream ss(s);
	string tmp;
	vector <int> v;
	while(ss >> tmp){
		v.push_back(stoi(tmp));
	}
	Triangle x = Triangle(v[0], v[1], v[2]);
	return x.isTriangle();
}

int main(){
	int iResult = 0;
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		cout << "\nWINSOCK : Khoi tao that bai !" << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "\nWINSOCK : Khoi tao thanh cong" << endl;
	}
	SOCKET server_socket;
	server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(server_socket == INVALID_SOCKET){
		cout << "Error at socket() : " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	cout << "Socket created" << endl;
	u_short port = 81;
	const char *IP = "127.0.0.1"; // dia chi cua may receive
	sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(IP);
	
	iResult = bind(server_socket, (SOCKADDR*) &server, sizeof(server));
	if(iResult == SOCKET_ERROR){
		cout << "Bind failed with error : " << WSAGetLastError() << endl;
		return 0;
	}
	cout << "Bind done." << endl;
	
	while (true)
    {
        printf("Waiting for data...");
        char message[DEFAULT_BUFLEN] = {};
		
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, DEFAULT_BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("Receive failed with error code: %d", WSAGetLastError());
            exit(0);
        }
        string s(message);
        string res = "";
        if(check(s)){
        	res = "YES";
		}
		else{
			res = "NO";
		}

        if (sendto(server_socket, res.c_str(), sizeof(res), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("Send failed with error code: %d", WSAGetLastError());
            return 3;
        }
    }
	closesocket(server_socket);
	WSACleanup();
	getchar();
	return 0;
}


