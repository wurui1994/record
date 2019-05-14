//clang main.cpp -lole32 -loleaut32 -luuid
#include <stdio.h>
#include <windows.h>

void main(void)
{
	IDispatch *pDisp;	  // Main IDispatch pointer.
	unsigned short *ucPtr; // Temporary variable to hold names.
	DISPID dispID;		   // Temporary variable to hold DISPIDs.
	CLSID clsid;		   // Holds CLSID of server after CLSIDFromProgID.
	HRESULT hr;			   // General error/result holder.
	char buf[8192];		   // Generic buffer for output.

	// IDispatch::Invoke() parameters...
	DISPPARAMS dispParams = {NULL, NULL, 0, 0};
	VARIANT parm1;
	DISPID dispidNamed = DISPID_PROPERTYPUT;

	// Initialize OLE Libraries.
	OleInitialize(NULL);
	{
		// Get CLSID for Excel.Application from registry.
		hr = CLSIDFromProgID(L"Excel.Application", &clsid);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Excel not registered.", "Error",
					   MB_SETFOREGROUND);
			return;
		}
		// Start Excel97, Excel 2000, or Excel 2002 and get its IDispatch pointer.
		hr = CoCreateInstance(&clsid, NULL, CLSCTX_LOCAL_SERVER,
							  &IID_IDispatch, (void **)&pDisp);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Couldn't start Excel.", "Error",
					   MB_SETFOREGROUND);
			return;
		}

		// Get the 'visible' property's DISPID.
		ucPtr = L"Visible";
		pDisp->lpVtbl->GetIDsOfNames(pDisp, &IID_NULL, &ucPtr, 1,
									 LOCALE_USER_DEFAULT, &dispID);

		sprintf(buf, "DISPID for 'Visible' property = 0x%08lx",
				dispID);
		MessageBox(NULL, buf, "Debug Notice", MB_SETFOREGROUND);

		// Initiate parameters to set visible property to true.
		VariantInit(&parm1);
		parm1.vt = VT_I4;
		parm1.lVal = 1; // true

		// One argument.
		dispParams.cArgs = 1;
		dispParams.rgvarg = &parm1;

		// Handle special-case for property-puts!
		dispParams.cNamedArgs = 1;
		dispParams.rgdispidNamedArgs = &dispidNamed;

		// Set 'visible' property to true.
		hr = pDisp->lpVtbl->Invoke(pDisp,
								   dispID, &IID_NULL, LOCALE_SYSTEM_DEFAULT,
								   DISPATCH_PROPERTYPUT | DISPATCH_METHOD,
								   &dispParams, NULL, NULL, NULL);
		if (FAILED(hr))
		{
			sprintf(buf, "IDispatch::Invoke() failed with %08lx", hr);
			MessageBox(NULL, buf, "Debug Notice", MB_SETFOREGROUND);
		}

		// All done.
		MessageBox(NULL, "done.", "Notice", MB_SETFOREGROUND);
	}
	// Uninitialize OLE Libraries.
	//OleUninitialize();
}