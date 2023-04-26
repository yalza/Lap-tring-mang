#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#define DEFAULT_BUFLEN 512

using namespace std;

class Student{
	private:
		string name,msv,age;
		
	public:
		Student(string msv, string name, string age){
			this->name = name;
			this->age = age;
			this->msv = msv;
		}
		
		string toString(){
			return this->msv + "," + this->name + "," + this->age;
		}
};

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
        // Xu ly ----------------------------------------------------------------------------------------------
        
        
        int first = s.find_first_of(",");
        int second = s.find_last_of(",");
        
        Student A = Student(s.substr(0,first),s.substr(first+1,second- first - 1),s.substr(second+1));
        
        vector<string> Students;
        
        
        ifstream infile("sinhvien.txt");
        string token;
        while(getline(infile,token)){
        	Students.push_back(token);
        	cout<<token<<endl;
        }
        infile.close();
        
        Students.push_back(A.toString());
              
        ofstream outfile("sinhvien.txt");
        for(string a: Students){
        	if(a=="")continue;
        	outfile << a;
        	res += a + ";";
        	outfile << "\n";
        }
        
        outfile.close();
        
        
        
        //---------------------------------------------------------------------------------------

        if (sendto(server_socket, res.c_str(), res.length(), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
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


