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
	pDriverObject->DriverUnload = DriverUnload;
	/********************************************************************************************************
	* Strings																								*
	* In kernel driver, you can't use char, consta char* or std::string										*
	* You can use: UNICODE_STRING or WCHAR (I recomend UNICODE_STRING because is more easy and fast to use) * 
	********************************************************************************************************/

	// Let's see some example using UNICODE_STRING
	UNICODE_STRING string = RTL_CONSTANT_STRING(L"Hello, i am a string =)\r\n");
	// Note: We use the macro "RTL_CONSTANT_STRING" to iniatilize our string
	
	// How to print string value?
	// It's very similar to c in usermode
	// You can use the KdPrint too, just use %wZ to represent that's a string
	// After you put the string value
	
	// Example: 
	KdPrint(("The string value is %wZ", &string));

	// Now, let's make a simple exercise that's compare two strings

	UNICODE_STRING password = RTL_CONSTANT_STRING(L"12345");
	UNICODE_STRING correct_password = RTL_CONSTANT_STRING(L"6789");

	// Now, you need to compare the two streings to see if the password is correct
	// For this, you can use RtlEqualUnicodeString
	// RtlEqualUnicodeString is a functon that's expect three parameters
	// String 1, String 2 and a boolean that's determinate if the functions check if strings are eqauls or different

	// Because the function retur is a boolean, you can use if statement to check teh return
	if (RtlEqualUnicodeString(&password, &correct_password, TRUE))
	{
		KdPrint(("The Password is correct\r\n"));
	}
	else
	{
		KdPrint(("The password is incorrect!\r\n"));
	}

	// Note: in this case the password is not equals to correct_password, so we print "The password is incorrect"


	// Say for compiler that's parameter is not used 
	UNREFERENCED_PARAMETER(pRegistryPath);
	// Print some message, like printf()
	KdPrint(("Hello, World!\r\n")); 
	// Return some status for your function, like return 0
	return STATUS_SUCCESS;
}