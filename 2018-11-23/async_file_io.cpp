// 미완성
#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <locale.h>

#define READ_SIZE 512

void CheckOsVersion();

int main() {
	BOOL rc;
	HANDLE hFile;
	DWORD numread;
	OVERLAPPED overlap;
	wchar_t buf[READ_SIZE];
	wchar_t szPath[MAX_PATH];

	CheckOsVersion();

	GetWindowsDirectory(szPath, sizeof(szPath));
	wchar_t endpoint[] = L"\\WINHLP32.EXE";
	wcscat_s(szPath, wcslen(szPath)+wcslen(endpoint)+1, L"\\WINHLP32.EXE");
	hFile = CreateFile(
		szPath,
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("Could not open %s\n", szPath);
		return -1;
	}

	return 0;
}