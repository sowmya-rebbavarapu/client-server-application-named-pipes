#include <windows.h>
#include <stdio.h>

#define PIPE_NAME L"\\\\.\\pipe\\my_pipe"

int main() {
    HANDLE hPipe;
    DWORD dwBytesRead;
    wchar_t data[100];

    // Create the named pipe
    hPipe = CreateNamedPipeW(
        PIPE_NAME,                   // Pipe name
        PIPE_ACCESS_INBOUND,         // Read access
        PIPE_TYPE_BYTE |             // Byte-type pipe
        PIPE_READMODE_BYTE |         // Byte-read mode
        PIPE_WAIT,                   // Blocking mode
        1,                           // Number of instances
        0,                           // Out buffer size
        0,                           // In buffer size
        0,                           // Default time-out
        NULL);                       // Default security attributes

    if (hPipe == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to create named pipe. Error code: %d\n", GetLastError());
        return 1;
    }

    // Wait for the client to connect
    printf("Waiting for client to connect...\n");
    if (!ConnectNamedPipe(hPipe, NULL)) {
        fprintf(stderr, "Failed to connect to named pipe. Error code: %d\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected. Ready to receive data.\n");

    // Read data from the pipe
    while (1) {
        ZeroMemory(data, sizeof(data));  // Clear the buffer before reading
        if (ReadFile(hPipe, data, sizeof(data) - sizeof(wchar_t), &dwBytesRead, NULL)) {
            if (dwBytesRead > 0) {
                data[dwBytesRead / sizeof(wchar_t)] = '\0'; // Null-terminate the received string
                wprintf(L"Received data from client: %s\n", data);
            }
        } else {
            fprintf(stderr, "Failed to read from named pipe. Error code: %d\n", GetLastError());
            break;
        }
    }

    // Close the named pipe handle
    CloseHandle(hPipe);

    return 0;
}
