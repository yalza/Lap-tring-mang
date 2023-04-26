#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


#define BUFLEN 512

using namespace std;

int main(int argc, char **argv) 
{
    WSADATA wsaData;
	cout << "Khoi tao Winsock" << endl;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "Failed with error : " << WSAGetLastError() << endl;
        return 1;
    }
	cout<<"WSAStartup OK"<<endl;

	sockaddr_in server;
	int client_socket;
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        printf("Socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
	cout<<"ConnectSocket = socket OK"<<endl;

	int port = 81;
	const char *IP="127.0.0.1";
	memset((char*)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(IP);
	while(true){

        //----------------------AAAAAA------------------------------
        string infor;
        string msv;
        int a;

        cout<<"\n<=====Sua thong tin sinh vien=====>\n";
        while(true){
            cout<<"<===============Menu===============>\n";
            cout<<"Chon 0 de xem danh sach sinh vien\n";
            cout<<"Chon 1 de sua ten cua sinh vien\n";
            cout<<"Chon 2 de sua tuoi cua sinh vien\n";
            cout<<"Chon 3 de sua ngay sinh cua sinh vien\n";
            cout<<"Chon 4 de thoat chuong trinh\n";
            cout<<"<==================================>\n\n";
            cout<<"Nhap lua chon cua ban: ";
            cin>>a;
            if(a==0){
                cout<<"Ban da chon Xem danh sach sinh vien!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
                infor = "0";
                break;
            }
            else if(a==1){
                cout<<"Ban da chon sua ten!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout<<"Nhap ma sinh vien can sua thong tin : ";
                cin>>msv;
                cin.ignore();
                cout<<"Nhap ten moi: ";
                string newName; getline(cin,newName);
                infor = "1;" + msv + ";" + newName;
                break;
            }
            else if(a==2){
                cout<<"Ban da chon sua tuoi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout<<"Nhap ma sinh vien can sua thong tin : ";
                cin>>msv;
                cout<<"Nhap tuoi moi: ";
                string newAge; cin>>newAge;
                infor = "2;" + msv + ";" + newAge;
                break;
            }
            else if(a==3){
                cout<<"Ban da chon sua ngay sinh!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout<<"Nhap ma sinh vien can sua thong tin : ";
                cin>>msv;
                cout<<"Nhap ngay sinh moi moi: ";
                string newDateOfBirth; cin>>newDateOfBirth;
                infor = "3;" + msv + ";" + newDateOfBirth;
                break;
            }
            else if(a==4){
                cout<<"Thoat chuong trinh thanh cong!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                return 0;
            }
            else{
                cout<<"Nhap sai!. Hay nhap lai!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
            }
        }

        // ------------------------------------------------------

        // send the message
        if (sendto(client_socket, infor.c_str(), infor.size(), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code: %d", WSAGetLastError());
            return 3;
        }

        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char answer[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if (answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        // --------------------------------AAAAAAA----------------------------------

        string s(answer);

        if(a==0){
            stringstream ss(s);
            string token;
            int stt = 0;
            cout<<"<============================================Danh sach sinh vien===========================================>\n\n";
            cout<<string(109,'-')<<endl;
            while(getline(ss,token,'\n')){
                stringstream xx(token);
                string l;
                int index = 0;
                string M[4];
                while(getline(xx,l,';')){
                    M[index++] = l;
                }
                stt++;
                
                cout<<"| STT: " + string(1,stt + '0') + " | " + "Ho va ten: " + M[1] + string(20-M[1].length(),' ') + " | " + "Ma sinh vien: " + M[0] + string(9-M[0].length(),' ') + " | " + "Tuoi: " + M[2] + string(4-M[2].length(),' ') + " | " + "Ngay sinh: " + M[3] + string(12-M[3].length(),' ') + " | \n";
                cout<<string(109,'-')<<endl;
            }
        }
        else{
            cout<<s<<string(100,'!')<<endl;
        }
        cout<<"\n<===========================================================================================================>\n";

        //--------------------------------------------------------------------

	}

    closesocket(client_socket);
    WSACleanup();
	getchar();
    return 0;
}

