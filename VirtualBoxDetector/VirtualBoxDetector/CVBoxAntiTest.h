#ifndef _H_KHS_CVBOXANTITEST
#define _H_KHS_CVBOXANTITEST


#include <Windows.h>

#define VIRTUAL_DRIVER_NAME	"VBOX"
//#define VIRTUAL_DRIVER_NAME "APPLE SSD SM0128F"
#define IDT_ADDRESS_LIMIT	0x0d000000


#define SIZE_DRIVER_NAME	128

class CVboxAnti	
{
private:

public:
	char m_pszModel[SIZE_DRIVER_NAME];
public:
	CVboxAnti() {}
	PSTR GetFirstPhysicalDriveModelNames();
	unsigned int GetIDT();
	bool CheckLDT();
	unsigned long CheckRDTSC();
	bool CheckTss();
	bool QueryRegedit();
	bool CheckNICMacInfo();


	bool TestCase1();	// # ����� ����̹� ���ڿ� Ž��
	bool TestCase2();	// # IDT �ּҰ� ��ġ�� ���� ��
	bool TestCase3();	// # LDT �ּҰ� ��ġ�� ���� ��
	bool TestCase4();	// # RDTSC �ð����̸� �� Ž��
	bool TestCase5();	// # Tss�� ���� ���̸� �� Ž��
	bool TestCase6();	// # ��ϵ� ���������� VBOX ���ڿ� �� Ž��
	bool TestCase7();	// # NIC�� Mac Address ������ �� Ž��
};

#endif 