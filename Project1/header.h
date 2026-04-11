
#ifndef SERVER
#define SERVER
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#include <string.h>
#include <basetsd.h>
#include <stdlib.h>
#include <stdio.h>
#endif

extern void trim(char* s);

void trim(char* s)
{
    int i = 0, j;
    while ((s[i] == ' ') || (s[i] == '\t'))
    {
        i++;
    }
    if (i > 0)
    {
        for (j = 0; j < strlen(s); j++)
        {
            s[j] = s[j + i];
        }
        s[j] = '\0';
    }

    i = (int)strlen(s) - 1;
    while ((s[i] == ' ') || (s[i] == '\t'))
    {
        i--;
    }
    if (i < (strlen(s) - 1))
    {
        s[i + 1] = '\0';
    }
}