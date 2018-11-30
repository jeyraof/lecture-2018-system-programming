#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define READ_SIZE 512

void CheckOsVersion();

int main() {
	BOOL rc;
	HANDLE hFile;
	DWORD numread;
	OVERLAPPED overlap;
	char buf[READ_SIZE];
	wchar_t szPath[MAX_PATH]; // Windows API 매개변수를 위한 유니코드 문자 설정

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

	// Initialize the OVERLAPPED structure
    memset(&overlap, 0, sizeof(overlap));
    overlap.Offset = 1500;

    // Request the data
    rc = ReadFile(
                hFile,
                buf,
                READ_SIZE,
                &numread,
                &overlap
            );
    printf("Issued read request\n");

    // Was the operation queued?
    if (rc)
    {
        // The data was read successfully
        printf("Request was returned immediately\n");
    }
    else
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            // We could do something else for awhile here...

            printf("Request queued, waiting...\n");
            WaitForSingleObject(hFile, INFINITE);
            printf("Request completed.\n");

            rc = GetOverlappedResult(
                                    hFile,
                                    &overlap,
                                    &numread,
                                    FALSE
                                );
            printf("Result was %d\n", rc);
        }
        else
        {
			// We should check for memory and quota
			// errors here and retry. See the samples
			// IoByEvnt and IoByAPC.

            // Something went wrong
            printf("Error reading file\n");
        }
    }

    CloseHandle(hFile);

	return EXIT_SUCCESS;
}

void CheckOsVersion()
{
    OSVERSIONINFO   ver;
    BOOL            bResult;

    ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    bResult = GetVersionEx((LPOSVERSIONINFO) &ver);

    if ( (!bResult) ||
         (ver.dwPlatformId != VER_PLATFORM_WIN32_NT) )
    {
        fprintf(stderr, "IoByFile must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
    }

}
