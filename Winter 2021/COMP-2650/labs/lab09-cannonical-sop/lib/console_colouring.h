#ifndef CONSOLE_COLOURING_H
#define CONSOLE_COLOURING_H

#ifdef _WIN32
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif // ENABLE_VIRTUAL_TERMINAL_PROCESSING
#endif // _WIN32

// standard colours
#define BLACK        "\e[0;30m"
#define RED          "\e[0;31m"
#define GREEN        "\e[0;32m"
#define YELLOW       "\e[0;33m"
#define BLUE         "\e[0;34m"
#define PURPLE       "\e[0;35m"
#define CYAN         "\e[0;36m"
#define WHITE        "\e[0;37m"

// bold colours
#define B_BLACK      "\e[1;30m"
#define B_RED        "\e[1;31m"
#define B_GREEN      "\e[1;32m"
#define B_YELLOW     "\e[1;33m"
#define B_BLUE       "\e[1;34m"
#define B_PURPLE     "\e[1;35m"
#define B_CYAN       "\e[1;36m"
#define B_WHITE      "\e[1;37m"

// underlined colours
#define U_BLACK      "\e[4;30m"
#define U_RED        "\e[4;31m"
#define U_GREEN      "\e[4;32m"
#define U_YELLOW     "\e[4;33m"
#define U_BLUE       "\e[4;34m"
#define U_PURPLE     "\e[4;35m"
#define U_CYAN       "\e[4;36m"
#define U_WHITE      "\e[4;37m"

// high intensity colours
#define HI_BLACK     "\e[90m"
#define HI_RED       "\e[91m"
#define HI_GREEN     "\e[92m"
#define HI_YELLOW    "\e[93m"
#define HI_BLUE      "\e[94m"
#define HI_PURPLE    "\e[95m"
#define HI_CYAN      "\e[96m"
#define HI_WHITE     "\e[97m"

// bold high intensity colours
#define B_HI_BLACK   "\e[1;90m"
#define B_HI_RED     "\e[1;91m"
#define B_HI_GREEN   "\e[1;92m"
#define B_HI_YELLOW  "\e[1;93m"
#define B_HI_BLUE    "\e[1;94m"
#define B_HI_PURPLE  "\e[1;95m"
#define B_HI_CYAN    "\e[1;96m"
#define B_HI_WHITE   "\e[1;97m"

// background colours
#define BG_BLACK     "\e[40m"
#define BG_RED       "\e[41m"
#define BG_GREEN     "\e[42m"
#define BG_YELLOW    "\e[43m"
#define BG_BLUE      "\e[44m"
#define BG_PURPLE    "\e[45m"
#define BG_CYAN      "\e[46m"
#define BG_WHITE     "\e[47m"

// background high-intensity colours
#define BG_HI_BLACK  "\e[100m"
#define BG_HI_RED    "\e[101m"
#define BG_HI_GREEN  "\e[102m"
#define BG_HI_YELLOW "\e[103m"
#define BG_HI_BLUE   "\e[104m"
#define BG_HI_PURPLE "\e[105m"
#define BG_HI_CYAN   "\e[106m"
#define BG_HI_WHITE  "\e[107m"

// reset colour
#define RESET        "\e[0m"

// terminal colour setting functions
void ready_terminal();
void reset_terminal();
#endif // !CONSOLE_COLOURING_H