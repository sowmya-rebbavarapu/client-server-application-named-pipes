#include <windows.h>
#include <stdio.h>

#define PIPE_NAME L"\\\\.\\pipe\\my_pipe"

int main() {
    HANDLE hPipe;
    DWORD dwBytesWritten;
    wchar_t data[100];

    // Connect to the named pipe
    hPipe = CreateFileW(
        PIPE_NAME,                   // Pipe name
        GENERIC_WRITE,               // Write access
        0,                           // No sharing
        NULL,                        // Default security attributes
        OPEN_EXISTING,               // Opens existing pipe
        0,                           // Default attributes
        NULL);                       // No template file

    if (hPipe == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to open named pipe. Error code: %d\n", GetLastError());
        return 1;
    }

    // Continuously prompt the user for data and send it to the server
    while (1) {
        printf("Enter data to write into the named pipe (type 'exit' to quit): ");
        fgetws(data, sizeof(data) / sizeof(wchar_t), stdin);

        // Remove newline character added by fgetws
        data[wcslen(data) - 1] = L'\0';

        if (wcscmp(data, L"exit") == 0) // Check if the user typed 'exit'
            break;

        // Write data to the named pipe
        if (!WriteFile(hPipe, data, wcslen(data) * sizeof(wchar_t), &dwBytesWritten, NULL)) {
            fprintf(stderr, "Failed to write to named pipe. Error code: %d\n", GetLastError());
            CloseHandle(hPipe);
            return 1;
        }

        printf("Data written to named pipe successfully.\n");
    }

    // Close the named pipe handle
    CloseHandle(hPipe);

    return 0;
}
