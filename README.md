# Kernel Basics

- This repository have a objective, show some kernel features in windows. This repository is maded for me while i'm learning about this tecnology.
- Note: In all sources of this repository have a lot of comments in the code that's teach you how each function does.   

# Entry point and Unload routine
## Driver Entry Point
- In the windows kernel the "main" function(Entry point) is called DriverEntry, that's expect two parameters</br>
1 - The driver object, declared using "PDRIVER_OBJECT";</br>
2 - A Strig that's point to a RegistryPath;</br>
- The function like this: 
```c
NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
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
1 - KdPrint </br>
2 - DbgPrint </br>

- Example:
```c
KdPrint(("Hello World!\r\n"));
DbgPrint("Hello World!\r\n");
```
