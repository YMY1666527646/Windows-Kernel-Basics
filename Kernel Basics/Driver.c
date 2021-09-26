// Default header for kernel drivers, like iostream in usermode apps
#include <ntddk.h>

// Unload Routine
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("Unload Called!\r\n"));
}

// Driver Entry Point, like int main()
NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	// Define Unload point for our driver
	pDriverObject->DriverUnload = DriverUnload;
	// Say for compiler that's parameter is not used 
	UNREFERENCED_PARAMETER(pRegistryPath);
	// Print some message, like printf()
	KdPrint(("Hello, World!\r\n")); 
	// Return some status for your function. like retur 0
	return STATUS_SUCCESS;
}