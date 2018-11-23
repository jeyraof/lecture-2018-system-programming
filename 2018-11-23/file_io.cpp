//**************************************************************
// 제목: File I/O 예제 
// 기능: 
// 파일이름: file_io.cpp
// 수정날짜: 2018년11월23일
// 작성자: 이재영
//**************************************************************

#include <stdlib.h>
#include <stdio.h>

int main() {
	FILE *fp;
	char buff[] = "I'm just a poor boy. Nobody loves me.";
	char rBuff[100];

	fopen_s(&fp, "test.txt", "r");
	if (fp == NULL) {
		printf("Error opening the file\n");
		return 0;
	}
	
	// Write string to fp
	//fprintf(fp, "Queen'Bohemian Rapsody : %s\n", buff);

	// Read one word separated by white-space
	fscanf_s(fp, "%s", rBuff, 100);
	printf("%s\n", rBuff);
	
	// Read one-line from fp
	fgets(rBuff, 100, fp);
	printf("%s\n", rBuff);

	fgets(rBuff, 100, fp);
	printf("%s\n", rBuff);

	//fscanf_s(fp, "%s\n", buff);
	//printf("1: %s\n", buff);

	//fgets(buff, 255, (FILE*)fp);
	//printf("2: %s\n", buff);

	//fgets(buff, 255, (FILE*)fp);
	//printf("3: %s\n", buff);
	
	fclose(fp);

	return 0;
}