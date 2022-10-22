//Source https://github.com/loneicewolf/smbdoor/blob/master/smbdoor/smbdoor/modules.c
#include <ntddk.h>
#include <ntimage.h>
#include "common.h"

NTSTATUS GetRoutineByName(
	_In_ PVOID DriverImageBase,
	_In_ LPCSTR FunctionName,
	_Out_ PVOID *RoutineAddress
)
{
	ULONG dirSize;
	PIMAGE_EXPORT_DIRECTORY pExportDir;
	PULONG names;
	PUSHORT ordinals;
	PULONG functions;
	UNICODE_STRING RtlImageString;

	*RoutineAddress = NULL;

	RtlInitUnicodeString(&RtlImageString, L"RtlImageDirectoryEntryToData");
	RTLIMAGEDIRECTORYENTRYTODATA FnRtlImageDirectoryEntryToData = MmGetSystemRoutineAddress(&RtlImageString);

	pExportDir = (PIMAGE_EXPORT_DIRECTORY)FnRtlImageDirectoryEntryToData(DriverImageBase, TRUE, IMAGE_DIRECTORY_ENTRY_EXPORT, &dirSize);
	names = (PULONG)RVA(DriverImageBase, pExportDir->AddressOfNames);
	ordinals = (PUSHORT)RVA(DriverImageBase, pExportDir->AddressOfNameOrdinals);
	functions = (PULONG)RVA(DriverImageBase, pExportDir->AddressOfFunctions);

	for (ULONG i = 0; i < pExportDir->NumberOfNames; ++i)
	{
		LPCSTR name = (LPCSTR)RVA(DriverImageBase, names[i]);
		if (0 == strcmp(FunctionName, name))
		{
			*RoutineAddress = RVA(DriverImageBase, functions[ordinals[i]]);
			return STATUS_SUCCESS;
		}
	}

	return STATUS_NOT_FOUND;
}
inline BOOLEAN xstricmp(LPCSTR s1, LPCSTR s2)
{
	for (ULONG i = 0; 0 == ((s1[i] ^ s2[i]) & 0xDF); ++i)
	{
		if (0 == s1[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

NTSTATUS GetModuleByName(
	_In_ LPCSTR driverName,
	_Out_ PVOID *ImageBase
)
{
	NTSTATUS status;
	ULONG size = 0;
	UNICODE_STRING RtlQueryString = { 0 };

	PAGED_CODE();

	*ImageBase = NULL;

	RtlInitUnicodeString(&RtlQueryString, L"RtlQueryModuleInformation");
	RTLQUERYMODULEINFORMATION FnRtlQueryModuleInformation = MmGetSystemRoutineAddress(&RtlQueryString);

	if (NULL == FnRtlQueryModuleInformation)
	{
		return STATUS_NOT_IMPLEMENTED;
	}

	status = FnRtlQueryModuleInformation(&size, sizeof(RTL_MODULE_EXTENDED_INFO), NULL);

	if (NT_SUCCESS(status))
	{
		PRTL_MODULE_EXTENDED_INFO pDrivers = (PRTL_MODULE_EXTENDED_INFO)ExAllocatePoolWithTag(PagedPool, size, "MuDa");

		if (NULL == pDrivers)
		{
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		status = FnRtlQueryModuleInformation(&size, sizeof(RTL_MODULE_EXTENDED_INFO), pDrivers);

		if (NT_SUCCESS(status))
		{
			ULONG i;
			status = STATUS_NOT_FOUND;

			for (i = 0; i < size / sizeof(RTL_MODULE_EXTENDED_INFO); ++i)
			{
				if (xstricmp(driverName, &pDrivers[i].FullPathName[pDrivers[i].FileNameOffset]))
				{
					*ImageBase = pDrivers[i].BasicInfo;
					status = STATUS_SUCCESS;
					break;
				}
			}

		}

		ExFreePoolWithTag(pDrivers, "MuDa");
	}

	return status;
}