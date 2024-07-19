#ifdef _WIN32
#define OS_WIN 1
#endif
#ifdef __APPLE__
#ifdef TARGET_OS_MAC
#define OS_MAC 1
#endif
#endif
#ifdef __unix__
#define OS_UNIX 1
#ifdef __linux__
#define OS_LINUX 1
#endif
#endif
