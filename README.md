# Kernel Basics

- This repository have a objective, show some kernel features in windows. This repository is maded for me while i'm learning about this tecnology.
- Note: In all sources of this repository have a lot of comments in the code that's teach you how each function does.   

# Entry point and Unload routine
## Driver Entry Point
- In the windows kernel the "main" function(Entry point) is called DriverEntry, that's expect two parameters</br>
1. The driver object, declared using "PDRIVER_OBJECT";
2. A Strig that's point to a RegistryPath;
- The function like this: 
```c
extern "C" NTSTATUS NTAPI DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
```

## The unload routine
- For now our unload routine not return any value, so you can made you return type VOID
- The unload function can have any name and expect a one parameter
1 - The driver object, declared using "PDRIVER_OBJECT";</br>
- The function like this:
```c
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObject) 
```
### Note: In the DriverEntry you need to declare your unload fucntion, you can use:
```c
pDriverObject->DriverUnload = /* Your unload function name, in my case: */DriverUnload;
```
# Print messages
- To print messages you have two principal methods </br>
1. KdPrint 
2. DbgPrint

- Example:
```c
KdPrint(("Hello World!\r\n"));
DbgPrint("Hello World!\r\n");
```

# Example 1 - Simple Driver
- In this section you make a simple driver using the concepts that's you see in last sections
```c
// Default header for kernel drivers, like iostream in usermode apps
#include <ntddk.h>

// Unload Routine
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("Unload Called!\r\n"));
} 

// Driver Entry Point, like int main()
extern "C" NTSTATUS NTAPI DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
  // Point a Unload Function
	pDriverObject->DriverUnload = DriverUnload;

  // Say for compiler that's parameter is not used 
	UNREFERENCED_PARAMETER(pRegistryPath);
  
  // Print some message, like printf()
	KdPrint(("Hello, i am a main function!\r\n")); 
  
  // Return some status for your function, like return 0
	return STATUS_SUCCESS;
}
```
# Strings
- In kernel driver, you can't use char, consta char* or std::string
- You can use: UNICODE_STRING or WCHAR (I recomend UNICODE_STRING because is more easy and fast to use)

- Let's see some example using UNICODE_STRING:
```c
UNICODE_STRING string = RTL_CONSTANT_STRING(L"Hello, i am a string =)\r\n");
```
### Note: We use the macro "RTL_CONSTANT_STRING" to iniatilize our string </hr>

### How to print string value?
- It's very similar to c in usermode, you can use the KdPrint too, just use %wZ to represent that's a string
- Example:
```c
KdPrint(("The string value is %wZ", &string));
```

# Example 2 - Comparing two strings
- Let's make a simple exercise that's compare two strings
```c
// Default header for kernel drivers, like iostream in usermode apps
#include <ntddk.h>

// Unload Routine
VOID NTAPI DriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("Unload Called!\r\n"));
} 

// Driver Entry Point, like int main()
extern "C" NTSTATUS NTAPI DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
  // Point a Unload Function
	pDriverObject->DriverUnload = DriverUnload;

  // Say for compiler that's parameter is not used 
	UNREFERENCED_PARAMETER(pRegistryPath);
  
 	UNICODE_STRING password = RTL_CONSTANT_STRING(L"12345");
	UNICODE_STRING correct_password = RTL_CONSTANT_STRING(L"6789");
	
	// Now, you need to compare the two strings to see if the password is correct
	// For this, you can use RtlEqualUnicodeString
	// RtlEqualUnicodeString is a functon that's expect three parameters
	// String 1, String 2 and a boolean that's determinate if the functions check the case sensitive
	// Because the function retur is a boolean, you can use if statement to check thh return
	if (RtlEqualUnicodeString(&password, &correct_password, TRUE))
	{
		KdPrint(("The Password is correct\r\n"));
	}
	else
	{
		KdPrint(("The password is incorrect!\r\n"));
	}
  
  // Return some status for your function, like return 0
	return STATUS_SUCCESS;
}
```
### Note: in this case the password is not equals to correct_password, so we print "The password is incorrect"
