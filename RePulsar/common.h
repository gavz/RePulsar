#define RVA(base, offset) ((PVOID)((PUCHAR)(base) + (ULONG)(offset)))
__int64 CallbackTable[13];
PVOID DriverImageBase;

typedef NTSTATUS(__stdcall *SRVNETSTOPCLIENT)(_In_ HANDLE Handle);
typedef NTSTATUS(__stdcall* SRVNETSTARTCLIENT)(_In_ HANDLE Handle);
typedef NTSTATUS(__stdcall *RTLQUERYMODULEINFORMATION)(ULONG *InformationLength, ULONG SizePerModule, PVOID InformationBuffer);
typedef NTSTATUS(__stdcall* SRVNETREGISTERCLIENT)(_In_ __int64 Table, _Out_ PHANDLE HandleToEntry);
typedef PVOID(__stdcall *RTLIMAGEDIRECTORYENTRYTODATA)(IN PVOID Base, IN BOOLEAN MappedAsImage, IN USHORT DirectoryEntry, OUT PULONG Size);
typedef NTSTATUS(__stdcall* SRVNETDEREGISTERCLIENT)(_In_ HANDLE Handle);

typedef struct _RTL_MODULE_EXTENDED_INFO
{
	PVOID BasicInfo;
	ULONG ImageSize;
	USHORT FileNameOffset;
	CHAR FullPathName[258];
} RTL_MODULE_EXTENDED_INFO, *PRTL_MODULE_EXTENDED_INFO;
