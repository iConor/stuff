#include "Windows.h"
#include "stdio.h"


static void nlog(char *str, ...)
{
	HWND notepad, edit;
	va_list ap;
	char buf[256];

	va_start(ap, str);
	vsprintf(buf, str, ap);
	va_end(ap);

//	strcat(buf, "\r\n");

	notepad = FindWindowA(NULL, "Untitled - Notepad");
	edit = FindWindowExA(notepad, NULL, "EDIT", NULL);
	SendMessage(edit, EM_REPLACESEL, TRUE, (LPARAM)buf);
}


int main(int argc, char *argv[])
{
	for(int i = 1; i < argc; i++)
		nlog("%s ", argv[i]);

	nlog("%s", "\r\n");	

	return 0;
}
