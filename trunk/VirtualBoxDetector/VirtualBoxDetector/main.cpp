#include <windows.h>
#include <stdio.h>
#include "CVBoxAntiTest.h"
#include <conio.h>

 

int main()
{
	CVboxAnti cAntiVm;
	
	cAntiVm.TestCase1();		// # 서명된 드라이버 문자열 탐지
	cAntiVm.TestCase2();		// # IDT 주소가 위치한 곳을 비교
	cAntiVm.TestCase3();		// # LDT 주소가 위치한 곳을 비교
	cAntiVm.TestCase4();		// # RDTSC 시간차이를 비교
	cAntiVm.TestCase5();		// # Tss의 값의 차이를 비교
	cAntiVm.TestCase6();		// # 등록된 레지스터의 VBOX 문자열 비교 
	cAntiVm.TestCase7();		// # NIC의 Mac Address 범위를 비교 탐지
	
	printf("종료하려면 아무키나...anti vm evasion 우리 조 화이팅!!\n");
	getch();

    return 0;
}