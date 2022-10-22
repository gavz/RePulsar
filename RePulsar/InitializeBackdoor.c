#include <ntddk.h>
#include "common.h"
NTSTATUS GetModuleByName(_In_ LPCSTR driverName, _Out_ PVOID* ImageBase);
NTSTATUS GetRoutineByName(_In_ PVOID DriverImageBase, _In_ LPCSTR FunctionName, _Out_ PVOID* RoutineAddress);
SRVNETSTOPCLIENT SrvNetStopClient;
SRVNETDEREGISTERCLIENT SrvNetDeregisterClient;
HANDLE SrvNetHandle = 0;
NTSTATUS RegisterSrvNetEndpoint(){
	SRVNETREGISTERCLIENT SrvNetRegisterClient;
	SRVNETSTARTCLIENT SrvNetStartClient;
	NTSTATUS status;
	if (NT_SUCCESS(status = GetModuleByName("srvnet.sys", &DriverImageBase))) {
		if (NT_SUCCESS(status = GetRoutineByName(DriverImageBase, "SrvNetRegisterClient", (PVOID*)&SrvNetRegisterClient))) {
			if (NT_SUCCESS(status = GetRoutineByName(DriverImageBase, "SrvNetStartClient", (PVOID*)&SrvNetStartClient))) {
				if (NT_SUCCESS(status = GetRoutineByName(DriverImageBase, "SrvNetStopClient", (PVOID*)&SrvNetStopClient))) {
					if (NT_SUCCESS(status = GetRoutineByName(DriverImageBase, "SrvNetDeregisterClient", (PVOID*)&SrvNetDeregisterClient))) {
						if (NT_SUCCESS(status = SrvNetRegisterClient(CallbackTable, &SrvNetHandle))) {
							if (!NT_SUCCESS(status = SrvNetStartClient(SrvNetHandle))) {
								DbgPrint("[-] Failed to start client!\n");
							}
						}
					}
				}
			}
		}
	}
	return STATUS_SUCCESS;
}
NTSTATUS DeregisterSrvNetEndpoint(){
	NTSTATUS status;
	if (SrvNetHandle){
		if (NT_SUCCESS(status = SrvNetStopClient(SrvNetHandle))) {
			if (NT_SUCCESS(status = SrvNetDeregisterClient(SrvNetHandle))) {
				SrvNetHandle = NULL;
			}
		}
	}
}
