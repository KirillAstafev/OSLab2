#include <Windows.h>
#include <stdio.h>

#define PROCESS_COUNT 3

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2) {
		printf_s("ньхайю! мебепмне йнк-бн юпцслемрнб!\n");
		return 1;
	}

	char* name = argv[1];

	HANDLE hFiles[PROCESS_COUNT + 1];
	SECURITY_ATTRIBUTES attr = { sizeof(attr), NULL, TRUE };

	hFiles[0] = CreateFileA("f1.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 
		&attr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[1] = CreateFileA("f2_input.txt", GENERIC_READ, FILE_SHARE_READ,
		&attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[2] = CreateFileA("f2_output.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 
		&attr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[3] = CreateFileA("f3.txt", GENERIC_READ, FILE_SHARE_READ,
		&attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hProc[PROCESS_COUNT];
	STARTUPINFOA startUpInfo[PROCESS_COUNT];
	PROCESS_INFORMATION procInfo[PROCESS_COUNT];

	for (int i = 0; i < PROCESS_COUNT; i++) {
		ZeroMemory(&(startUpInfo[i]), sizeof(STARTUPINFO));
		ZeroMemory(&(procInfo[i]), sizeof(PROCESS_INFORMATION));
		ZeroMemory(&(hProc[i]), sizeof(HANDLE));
	}

	HANDLE stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE stdInput = GetStdHandle(STD_INPUT_HANDLE);

	BOOL res1 = SetStdHandle(STD_OUTPUT_HANDLE, hFiles[0]);

	if (!CreateProcessA(NULL, argv[1], &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[0]), &(procInfo[0]))) {
		
		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 1);
		return 1;
	}

	hProc[0] = procInfo[0].hProcess;

	BOOL res2 = SetStdHandle(STD_INPUT_HANDLE, hFiles[1]);
	BOOL res3 = SetStdHandle(STD_OUTPUT_HANDLE, hFiles[2]);

	if (!CreateProcessA(argv[1], NULL, &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[1]), &(procInfo[1]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 2);
		
		WaitForSingleObject(hProc[0], INFINITE);
		CloseHandle(hProc[0]);

		return 1;
	}

	hProc[1] = procInfo[1].hProcess;

	WaitForMultipleObjects(2, hProc, FALSE, INFINITE);

	BOOL res4 = SetStdHandle(STD_OUTPUT_HANDLE, stdOutput);
	BOOL res5 = SetStdHandle(STD_INPUT_HANDLE, hFiles[3]);

	if (!CreateProcessA(argv[1], NULL, &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[2]), &(procInfo[2]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 3);

		WaitForMultipleObjects(2, hProc, TRUE, INFINITE);
		CloseHandle(hProc[0]);
		CloseHandle(hProc[1]);

		return 1;
	}

	WaitForMultipleObjects(3, hProc, TRUE, INFINITE);
	BOOL res6 = SetStdHandle(STD_INPUT_HANDLE, stdInput);

	for (int i = 0; i < PROCESS_COUNT; i++) {
		if(hProc[i] != INVALID_HANDLE_VALUE)
			CloseHandle(hProc[i]);
	}

	for (int i = 0; i < PROCESS_COUNT + 1; i++)
		CloseHandle(hFiles[i]);

	return 0;
}