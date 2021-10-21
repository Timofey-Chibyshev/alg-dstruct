#pragma warning(disable:4996)

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


void MemoryLeaks(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    const char *name1 = "Mass.txt";
    const char *name2 = "Mass1.txt";
    const char *summary = "Sum.txt";
    AllOperations(name1, name2, summary);
    MemoryLeaks();
    return 0;
}
