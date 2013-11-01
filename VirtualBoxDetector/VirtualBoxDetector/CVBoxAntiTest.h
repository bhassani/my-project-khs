#ifndef _H_KHS_CVBOXANTITEST
#define _H_KHS_CVBOXANTITEST


#include <Windows.h>

#define VIRTUAL_DRIVER_NAME	"VBOX"
#define IDT_ADDRESS_LIMIT	0x0d000000


#define SIZE_DRIVER_NAME	128

class CVboxAnti	
{
private:

public:
	char m_pszModel[SIZE_DRIVER_NAME];
public:
	CVboxAnti() {}
		
	/********** Start = Utils Func **********/
	void AllToUpper(unsigned char* str,unsigned long len);
	unsigned char* ScanDataForString(unsigned char* data,unsigned long data_length,unsigned char* string2);
	/********** End = Utils func **********/

	/********** Start = VirtualCheck Func **********/
	PSTR GetFirstPhysicalDriveModelNames();
	unsigned int GetIDT();
	bool CheckLDT(unsigned int *a_pLdtBase);
	unsigned long CheckRDTSC();
	bool CheckTss(unsigned int *pAddrTss);
	bool QueryRegedit();
	bool CheckNICMacInfo();
	bool CheckRegSMBios();
	bool CheckBiosWMI();
	bool CheckDXDiagSysInfo();
	bool CheckWindowSetupLog();
	/********** End = VirtualCheck Func **********/


	/********** Start = Virtual TestCase Func **********/
	bool TestCase1();	// # ����� ����̹� ���ڿ� Ž��
	bool TestCase2();	// # IDT �ּҰ� ��ġ�� ���� ��
	bool TestCase3();	// # LDT �ּҰ� ��ġ�� ���� ��
	bool TestCase4();	// # RDTSC �ð����̸� �� Ž��
	bool TestCase5();	// # Tss�� ���� ���̸� �� Ž��
	bool TestCase6();	// # ��ϵ� ���������� VBOX ���ڿ� �� Ž��
	bool TestCase7();	// # NIC�� Mac Address ������ �� Ž��
	bool TestCase8();	// # Reg�� ��ϵ� SMBios�� Type�� �� Ž�� 
	bool TestCase9();	// # Bios Brand Version �� Ž�� (WMI)
	bool TestCase10();	// # DirectX SysInfo�� ���ڿ� �� Ž��
	bool TestCase11();	// # c:\\windows\\setuplog.txt �� VBOX ���ڿ� �� Ž��

	/********** End = Virtual TestCase Func **********/
};

#endif 