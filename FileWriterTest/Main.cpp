#include <stdio.h>
#include <Windows.h>
#include <conio.h>

int main() {
	char ch;
	DWORD numberOfBytes;
	while (ReadFile(GetStdHandle(STD_INPUT_HANDLE), &ch, 1, &numberOfBytes, NULL) > 0 && numberOfBytes > 0)
	{
		WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), &ch, 1, NULL, NULL);

		if (ch == -1)
			break;
	}

	return 0;
}