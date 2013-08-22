/*  
     �����Ϸ� : Microsoft Visual Studio 6.0
     ���� : �⺻ ������â �ϳ��� ����.
*/

#include <fstream>
#include <windows.h>
#include <string>
#include <map>
typedef std::map<int,std::string> mMap;

#define HIDE_HOTKEY	'E'
#define NUM_START	'0'
#define NUM_END	'9' + 1
#define MAX_NUM		10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
mMap g_Map;
HWND g_hNext;
LPCTSTR lpszClass = TEXT("ClipBoardSL_A(1.0.0Ver)");  //������ �̸� �� Ÿ��Ʋ�ٿ� ����� ���ڿ�

std::string g_sDirPath = "";

void HotKeyShowHIde(HWND hWnd);
void DrawClipBoardList(HWND hWnd,HDC hdc);
void HotKeyLoadKey(HWND hWnd,ULONG uVirtKey);
bool IsExisting(std::string &s);
void WriteClipBoardData();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
 HWND hWnd;
 MSG Message;
 WNDCLASS WndClass;
 g_sDirPath = lpszCmdParam;
 g_hInst = hInstance;

 if(g_sDirPath != "")		CreateDirectoryA(g_sDirPath.c_str(),NULL);

 //------------ �Ʒ� �κ��� ������ Ŭ������ �������ִ� ���̴�. --------------------

 WndClass.cbClsExtra = 0;
 WndClass.cbWndExtra = 0;
 WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
 WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
 WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
 WndClass.hInstance = hInstance;
 WndClass.lpfnWndProc = WndProc;
 WndClass.lpszClassName = lpszClass;
 WndClass.lpszMenuName = NULL;
 WndClass.style = CS_HREDRAW | CS_VREDRAW;

 //------------ �� �κ��� ������ Ŭ������ �������ִ� ���̴�. --------------------

 RegisterClass(&WndClass);   //  <-- ���⼭�� ������ ������ Ŭ������ ����Ѵ�.

 hWnd = CreateWindowEx(WS_EX_TOPMOST,lpszClass,lpszClass,WS_POPUPWINDOW,0,220,800,
      220,NULL,(HMENU)NULL,hInstance,NULL);   // �����ϰ� ����� �����츦 �����Ѵ�.

// ShowWindow(hWnd,nCmdShow);   //������ �����츦 ���..(�� �Լ��� ȣ������������ �����찡 ������ �ʴ´�.)
 ShowWindow(hWnd,SW_HIDE);   //������ �����츦 ���..(�� �Լ��� ȣ������������ �����찡 ������ �ʴ´�.)

 while(GetMessage(&Message,NULL,0,0))   //����ڰ� �����ϱ� ������ �ݺ��ؼ� �޼��� ó���� ȣ���Ѵ�.
 {
  TranslateMessage(&Message);
  DispatchMessage(&Message);
 }

  return (int)Message.wParam;
}

#define ID_HOTKEY_A		0x0001
#define ID_HOTKEY_AS	0x0002


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) //���⼭ ������ �޽����� ó���Ѵ�.
{
	ULONG nHit;
	HDC hdc;
	PAINTSTRUCT ps;
	static int KEY_ID = 0;

 switch(iMessage)
 { 
 case WM_CREATE:
	 //g_hNext
	g_hNext = SetClipboardViewer(hWnd);
	{
	RegisterHotKey(hWnd,KEY_ID++,MOD_ALT,HIDE_HOTKEY);

	for(int i=NUM_START; i < NUM_END; i++)
		RegisterHotKey(hWnd,KEY_ID++,MOD_ALT | MOD_SHIFT,i);	
	
	}
	 return 0;

 case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		DrawClipBoardList(hWnd,hdc);
		EndPaint(hWnd,&ps);
	 return 0;

 case WM_DRAWCLIPBOARD:{
		static int Index = 0;
		if(g_hNext)
			SendMessage(g_hNext,WM_DRAWCLIPBOARD,wParam,lParam);
		
		if(!IsClipboardFormatAvailable(CF_TEXT))	return 0;

		HANDLE hmem;
		char *p = NULL;
		OpenClipboard(hWnd);
		hmem = GetClipboardData(CF_TEXT);
		p = (char*)GlobalLock(hmem);

		if(Index >= MAX_NUM){
			Index = 0;
			if(g_sDirPath != "")	WriteClipBoardData();
		}

		std::string s = std::string(p);

		if(!IsExisting(s))
			g_Map[Index++] = s;

		GlobalUnlock(hmem);
		CloseClipboard();

		InvalidateRect(hWnd,NULL,TRUE);
	}
	 return 0;

 case WM_HOTKEY:
	 {
		UINT fuModifiers = (UINT) LOWORD(lParam);  // MOD_...�� ����
		UINT uVirtKey = (UINT) HIWORD(lParam);     // ���߾� Ű �ڵ�

		switch(fuModifiers){
			case MOD_ALT:
				if(uVirtKey == HIDE_HOTKEY)	
					HotKeyShowHIde(hWnd);
				break;

			case (MOD_ALT | MOD_SHIFT):
					HotKeyLoadKey(hWnd,uVirtKey);
				break;

		}
		
	 }
	 

	 case WM_NCHITTEST:
		nHit = DefWindowProc(hWnd,iMessage,wParam,lParam);
		if(nHit == HTCLIENT)
			nHit = HTCAPTION;


		return nHit;

	 return 0;

 case WM_DESTROY:
	 WriteClipBoardData();
	 ChangeClipboardChain(hWnd,g_hNext);
	 {	
		 for(int i=0; i<KEY_ID; i++)
			 UnregisterHotKey(hWnd,i);
	 }
  PostQuitMessage(0);
  return 0;
 }

 return DefWindowProc(hWnd,iMessage,wParam,lParam);  //���α׷��Ӱ� ó������ ���� ������ ������ �⺻ó���� �ѱ��.
}


void HotKeyShowHIde(HWND hWnd){

	static bool bShow = false;

	if(bShow)		ShowWindow(hWnd,SW_HIDE);
	else			ShowWindow(hWnd,SW_SHOW);

	bShow = !bShow;

}

void DrawClipBoardList(HWND hWnd,HDC hdc)
{
		
	mMap::iterator it;
	using namespace std;	
	char buf[512] = {0};
	

	string s;

	int Index = 0;
	int yPos = 20;

	strcpy(buf,"[Auto ClipBoard Save] Hide_Show(Alt + E) , Load : [ Alt + Shift + ���� ]");

	TextOutA(hdc,0,0,buf,strlen(buf));				

	for(it = g_Map.begin(); it != g_Map.end(); it++){
		Index = (*it).first;	
		wsprintfA(buf,"%d : ",Index);
		TextOutA(hdc,0,yPos,buf,strlen(buf));
		TextOutA(hdc,20,yPos,g_Map[Index].c_str(),strlen(g_Map[Index].c_str()));				
		yPos+=20;
	}
	
}

void HotKeyLoadKey(HWND hWnd,ULONG uVirtKey){

	int index = uVirtKey - NUM_START;
	char *p = NULL;
	int len = strlen( g_Map[index].c_str() ) + 1;

	HGLOBAL hmem = GlobalAlloc(GHND,len);
	p = (char*)GlobalLock(hmem);
	memcpy(p,g_Map[index].c_str(),len);
	GlobalUnlock(hmem);

	if(OpenClipboard(hWnd)){
		EmptyClipboard();
		SetClipboardData(CF_TEXT,hmem);
		CloseClipboard();
	}else{
		GlobalFree(hmem);
	}
}

bool IsExisting(std::string &s){
	

	mMap::iterator it;

	for(it=g_Map.begin(); it!=g_Map.end(); it++){

		if((*it).second == s)	return true;
	}

	return false;

}

void WriteClipBoardData(){

	using namespace std;
	SYSTEMTIME st;
	GetLocalTime(&st);

	char FileName[64] = {0};
	wsprintfA(FileName,"%d_%d_%d.txt",st.wYear,st.wMonth,st.wDay);
	string s = string(g_sDirPath) + "\\" + FileName;

	mMap::iterator it;
	ofstream outFile;
	outFile.open(s.c_str(),ios_base::app);

	if(!outFile.is_open())	return;

	for(it = g_Map.begin(); it != g_Map.end(); it++){
		outFile << "**************************************************************" << endl;
		outFile << (*it).second.c_str() << endl;
	}
	outFile.close();
}
