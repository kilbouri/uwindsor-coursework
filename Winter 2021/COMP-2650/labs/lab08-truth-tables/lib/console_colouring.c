#include "console_colouring.h"

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>

static HANDLE stdoutHandle;
static DWORD outModeInit;

/**
 * Prepares the terminal for ANSI colour codes
 */
void ready_terminal() {
	DWORD outMode = 0;
	stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (stdoutHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
	}

	if (!GetConsoleMode(stdoutHandle, &outMode)) {
		exit(GetLastError());
	}

	outModeInit = outMode;

	// Enable ANSI escape codes
	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(stdoutHandle, outMode)) {
		exit(GetLastError());
	}
}
/**
 * Resets the terminal to default colours and
 * un-readies the terminal for ANSI colour codes.
 */
void reset_terminal() {
	// Reset colors
	printf(RESET);

	// Reset console mode
	if (!SetConsoleMode(stdoutHandle, outModeInit)) {
		exit(GetLastError());
	}
}
#else
/**
 * Prepares the terminal for ANSI colour codes
 */
void ready_terminal() {}
/**
 * Resets the terminal to default colours and
 * un-readies the terminal for ANSI colour codes.
 */
void reset_terminal() {}
#endif // _WIN32