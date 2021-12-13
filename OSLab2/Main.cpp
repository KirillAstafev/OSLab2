#include <Windows.h>
#include <stdio.h>

#define PROCESS_COUNT 4
#define FILE_COUNT 4

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2) {
		printf_s("ньхайю! мебепмне йнк-бн юпцслемрнб!\n");
		return 1;
	}

	char* name = argv[1];

	HANDLE hFiles[FILE_COUNT];
	SECURITY_ATTRIBUTES attr = { sizeof(attr), NULL, TRUE };

	hFiles[0] = CreateFileA("f1_in.txt", GENERIC_READ, FILE_SHARE_READ,
		&attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[1] = CreateFileA("f1_out.txt", GENERIC_WRITE, FILE_SHARE_WRITE,
		&attr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[2] = CreateFileA("f2_in.txt", GENERIC_READ, FILE_SHARE_READ,
		&attr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	hFiles[3] = CreateFileA("f3_out.txt", GENERIC_WRITE, FILE_SHARE_WRITE,
		&attr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hProc[PROCESS_COUNT];
	STARTUPINFOA startUpInfo[PROCESS_COUNT];
	PROCESS_INFORMATION procInfo[PROCESS_COUNT];

	for (int i = 0; i < PROCESS_COUNT; i++) {
		ZeroMemory(&(startUpInfo[i]), sizeof(STARTUPINFO));
		ZeroMemory(&(procInfo[i]), sizeof(PROCESS_INFORMATION));
		ZeroMemory(&(hProc[i]), sizeof(HANDLE));
	}

	startUpInfo[0].hStdInput = hFiles[0];
	startUpInfo[0].hStdOutput = hFiles[1];
	startUpInfo[0].cb = sizeof(STARTUPINFO);
	startUpInfo[0].dwFlags = STARTF_USESTDHANDLES;

	if (!CreateProcessA(NULL, argv[1], &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[0]), &(procInfo[0]))) {
		
		printf_s("ньхайю опх янгдюмхх опнжеяяю ╧%d: йнд ньхайх: %d\n", 1, GetLastError());
		return 1;
	}

	hProc[0] = procInfo[0].hProcess;
	WaitForSingleObject(hProc[0], INFINITE);

	startUpInfo[1].hStdInput = hFiles[2];
	startUpInfo[1].hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startUpInfo[1].cb = sizeof(STARTUPINFO);
	startUpInfo[1].dwFlags = STARTF_USESTDHANDLES;

	if (!CreateProcessA(NULL, argv[1], &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[1]), &(procInfo[1]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю ╧%d: йнд ньхайх: %d\n", 2, GetLastError());
		return 1;
	}

	hProc[1] = procInfo[1].hProcess;
	WaitForSingleObject(hProc[1], INFINITE);

	startUpInfo[2].hStdOutput = hFiles[3];
	startUpInfo[2].hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startUpInfo[2].cb = sizeof(STARTUPINFO);
	startUpInfo[2].dwFlags = STARTF_USESTDHANDLES;

	if (!CreateProcessA(NULL, argv[1], &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[2]), &(procInfo[2]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю ╧%d: йнд ньхайх: %d\n", 3, GetLastError());
		return 1;
	}

	hProc[2] = procInfo[2].hProcess;

	startUpInfo[3].cb = sizeof(STARTUPINFO);

	if (!CreateProcessA(NULL, argv[1], &attr, NULL, TRUE,
		NULL, NULL, NULL, &(startUpInfo[3]), &(procInfo[3]))) {

		printf_s("ньхайю опх янгдюмхх опнжеяяю ╧%d: йнд ньхайх: %d\n", 4, GetLastError());
		return 1;
	}

	hProc[3] = procInfo[3].hProcess;

	WaitForMultipleObjects(2, hProc + 2, TRUE, INFINITE);
	
	system("pause");
	return 0;
}