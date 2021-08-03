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

	HANDLE hProc[PROCESS_COUNT];
	STARTUPINFOA startUpInfo[PROCESS_COUNT];
	PROCESS_INFORMATION procInfo[PROCESS_COUNT];

	if (!CreateProcessA(argv[1], NULL, NULL, NULL, TRUE, 
		CREATE_NEW_CONSOLE, NULL, NULL, &(startUpInfo[0]), &(procInfo[0]))) {
		
		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 1);
		return 1;
	}

	hProc[0] = procInfo[0].hProcess;

	if (!CreateProcessA(argv[2], NULL, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &(startUpInfo[1]), &(procInfo[1]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 2);
		
		WaitForSingleObject(procInfo->hProcess, INFINITE);
		CloseHandle(hProc[0]);

		return 1;
	}

	hProc[1] = procInfo[1].hProcess;

	WaitForMultipleObjects(2, hProc, FALSE, INFINITE);

	if (!CreateProcessA(argv[3], NULL, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &(startUpInfo[2]), &(procInfo[2]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю %d.\n", 3);

		WaitForMultipleObjects(2, hProc, TRUE, INFINITE);
		CloseHandle(hProc[0]);
		CloseHandle(hProc[1]);

		return 1;
	}

	WaitForMultipleObjects(3, hProc, TRUE, INFINITE);

	for (int i = 0; i < PROCESS_COUNT; i++)
		CloseHandle(hProc[i]);

	return 0;
}