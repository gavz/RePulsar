#include <ntddk.h>
#include "common.h"
#include <minwindef.h>

NTSTATUS DisconnectClient(){
	DbgPrint("[+] Triggered DisconnectClient\n");
	return 0x1;
}
NTSTATUS RegisterEndpoint(){
	DbgPrint("[+] Triggered RegisterEndpoint\n");
	return 0x1;
}
NTSTATUS DeregisterEndpoint(){
	DbgPrint("[+] Triggered DeregisterEndpoint\n");
	return 0x1;
}

NTSTATUS ReceiveCallback(){
	DbgPrint("[+] Triggered ReceiveCallback\n");
	return STATUS_SUCCESS;
}

NTSTATUS ConnectCallback(){
	DbgPrint("[+] Triggered ConnectCallback\n");
	return STATUS_SUCCESS;
}

NTSTATUS NegotiateCallback(PVOID Unk0, ULONG InputBufferSize, PULONG InputBuffer){
	DbgPrint("[+] Triggered NegotiateCallback\n");
	DbgPrint("<================================>");
	if (*(ULONG*)InputBuffer == 0x6144754D){
		DbgPrint("[+] Received packet with tag 0x%x", *(ULONG*)InputBuffer);
	}else {
		goto Exit;
	}
	DbgPrint("[+] Received command 0x%x\n", *(ULONG*)(InputBuffer + 0x3));
	switch (*(ULONG*)(InputBuffer + 0x3))
	{

	default:
		break;

	case 0x0C:
		DbgPrint("[+] Ping-pong...\n");
	}
	DbgPrint("<================================>");
	return 0x1;
Exit:
	return 0x0;
}
