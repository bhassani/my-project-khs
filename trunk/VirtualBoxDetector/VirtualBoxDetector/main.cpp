#include <windows.h>
#include <stdio.h>
#include "CVBoxAntiTest.h"
#include <conio.h>

 

int main()
{
	CVboxAnti cAntiVm;
	
	cAntiVm.TestCase1();		// # ������ ����̹� ���ڿ� Ž��
	cAntiVm.TestCase2();		// # IDT �ּҰ� ��ġ�� ���� ��
	cAntiVm.TestCase3();		// # LDT �ּҰ� ��ġ�� ���� ��
	cAntiVm.TestCase4();		// # RDTSC �ð����̸� ��
	cAntiVm.TestCase5();		// # Tss�� ���� ���̸� ��
	cAntiVm.TestCase6();		// # ��ϵ� ���������� VBOX ���ڿ� �� 
	cAntiVm.TestCase7();		// # NIC�� Mac Address ������ �� Ž��
	cAntiVm.TestCase8();		// # Reg�� ��ϵ� SMBios�� Type�� �� Ž�� 
	
	printf("�����Ϸ��� �ƹ�Ű��...anti vm evasion �츮 �� ȭ����!!\n");
	getch();

    return 0;
}