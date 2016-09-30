#include <vector>
#include <fstream>
#include <string>
#include "Windows.h"
#include "Parser.h"

#ifdef max
#undef max //remove crap
#endif

unsigned long long GetFileSize(const char * fileName)
{
    ::HANDLE hFile = CreateFileA(fileName,
                                 GENERIC_READ,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return std::numeric_limits<unsigned long long>::max(); // error condition, could call GetLastError to find out more
    }

    ::LARGE_INTEGER size;
    if (!GetFileSizeEx(hFile, &size))
    {
        CloseHandle(hFile);
        return std::numeric_limits<unsigned long long>::max(); // error condition, could call GetLastError to find out more
    }

    CloseHandle(hFile);
    return size.QuadPart;
}

int main(int argc, char* argv[])
{
    std::vector<char> atmFile;
    auto const aFileSize = GetFileSize(argv[1]);
    atmFile.reserve(static_cast<unsigned int>(aFileSize));
    std::ifstream atm_file(argv[1]);

    atmFile.assign(std::istreambuf_iterator<char>(atm_file), std::istreambuf_iterator<char>());

    RText::Parser aParser(atmFile);
}
