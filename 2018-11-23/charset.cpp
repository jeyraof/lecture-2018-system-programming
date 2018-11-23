#include <Windows.h>
#include <stdio.h>
#include <locale.h>

int main() {
	WCHAR *b = L"This is a test";
	wchar_t a = L'a';
	wchar_t *str = L"안녕하세요";

	setlocale(LC_ALL, "");
	wprintf(L"%s\n", str);

	return 0;
}