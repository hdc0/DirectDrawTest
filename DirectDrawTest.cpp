#include <cstdio>
#include <cstdlib>
#include <cwchar>

#include <ddraw.h>

int wmain(int argc, wchar_t **argv)
{
	bool useDirectDrawCreateEx = false;
	const wchar_t *funcDesc = L"DirectDrawCreate";
	GUID *guid = nullptr;
	const wchar_t *guidDesc = L"NULL";

	// Parse command line arguments
	for (int i = 1; i < argc; ++i)
	{
		if (wcsicmp(argv[i], L"/ex") == 0)
		{
			useDirectDrawCreateEx = true;
			funcDesc = L"DirectDrawCreateEx";
		}
		else if (wcsicmp(argv[i], L"/emulationonly") == 0)
		{
			guid = reinterpret_cast<GUID *>(DDCREATE_EMULATIONONLY);
			guidDesc = L"DDCREATE_EMULATIONONLY";
		}
		else if (wcsicmp(argv[i], L"/hardwareonly") == 0)
		{
			guid = reinterpret_cast<GUID *>(DDCREATE_HARDWAREONLY);
			guidDesc = L"DDCREATE_HARDWAREONLY";
		}
		else
		{
			std::fwprintf(stderr, L"Invalid command line argument: %s\n", argv[i]);
			return EXIT_FAILURE;
		}
	}

	// Call DirectDrawCreate or DirectDrawCreateEx with the specified GUID
	HRESULT resultDDC;
	if (!useDirectDrawCreateEx)
	{
		IDirectDraw *lpDD;
		resultDDC = DirectDrawCreate(guid, &lpDD, nullptr);
		if (resultDDC == DD_OK) lpDD->Release();
	}
	else
	{
		IDirectDraw7 *lpDD;
		resultDDC = DirectDrawCreateEx(guid,
			reinterpret_cast<LPVOID *>(&lpDD), IID_IDirectDraw7, nullptr);
		if (resultDDC == DD_OK) lpDD->Release();
	}
	std::wprintf(L"%s returned 0x%08X for GUID %s\n", funcDesc, resultDDC, guidDesc);

	return EXIT_SUCCESS;
}
