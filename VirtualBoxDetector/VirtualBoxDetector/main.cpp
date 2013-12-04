#include <windows.h>
#include <stdio.h>
#include "CVBoxAntiTest.h"
#include <conio.h>

#include "DXDIAG\\INCLUDE\\dxdiag.h"
 

int main()
{
	CVboxAnti cAntiVm;
	
	printf("======== Trust Result========\n");
	cAntiVm.TestCase1();		// # ����� ����̹� ���ڿ� Ž��
	cAntiVm.TestCase6();		// # ��ϵ� ���������� VBOX ���ڿ� �� 
	cAntiVm.TestCase7();		// # NIC�� Mac Address ������ �� Ž��
	cAntiVm.TestCase8();		// # Reg�� ��ϵ� SMBios�� Type�� �� Ž�� 
	cAntiVm.TestCase9();		// # Bios Brand Version �� Ž�� (WMI)
	cAntiVm.TestCase10();		// # DirectX SysInfo�� ���ڿ� �� Ž��
	cAntiVm.TestCase11();		// # c:\\windows\\setuplog.txt �� VBOX ���ڿ� �� Ž��

	printf("\n\n ======== Normal trust ========\n");
	cAntiVm.TestCase4();		// # RDTSC �ð����̸� ��


	printf("\n\n========Not trust result========\n");
	cAntiVm.TestCase2();		// # IDT �ּҰ� ��ġ�� ���� ��
	cAntiVm.TestCase3();		// # LDT �ּҰ� ��ġ�� ���� ��
	cAntiVm.TestCase5();		// # Tss�� ���� ���̸� ��
	cAntiVm.TestCase12();		// # CPUID eax=1 ecx[31bit] 1�� Ž��
	cAntiVm.TestCase13();		// # CPUID eax=1 edx[28bit] 1�� Ž��
	cAntiVm.TestCase14();		// # Single step Flags on cpuid tf bit


	printf("�����Ϸ��� �ƹ�Ű��...anti vm evasion �츮 �� ȭ����!!\n");
	getch();

    return 0;
}