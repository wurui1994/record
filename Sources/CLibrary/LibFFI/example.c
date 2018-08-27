#include <stdio.h>
#include <ffi.h>
#include <Windows.h>

#pragma comment(lib,"ffi")

int main()
{
	ffi_cif cif;
	HINSTANCE dllHandle = LoadLibrary("user32.dll");
	int n = 4;
	ffi_type *ffi_argTypes[4];
	void *values[4];
	UINT64 a=0;
	UINT32 b=0;
	TCHAR* s1= "hello";
	TCHAR* s2= "hello2";
	values[0] = &a;
	values[1] = &s1;
	values[2] = &s2;
	values[3] = &b;
	ffi_argTypes[0] = &ffi_type_uint64;
	ffi_argTypes[1] = &ffi_type_pointer;
	ffi_argTypes[2] = &ffi_type_pointer;
	ffi_argTypes[3] = &ffi_type_uint;
	ffi_type *c_retType = &ffi_type_sint;
	ffi_type rc; // return value
	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 4, &ffi_type_sint, ffi_argTypes) == FFI_OK)    {
		ffi_call(&cif, FFI_FN(GetProcAddress(dllHandle,"MessageBoxA")), &rc, values);
	}
	return 0;
}