#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv)
{
	// 아래 예 같이 문자(인자) 하나(‘0’ 또는 ‘1’)를 받음
	/*
	- 인자로 받은 값을 프린트 함: 아래 예에서는 “GPIO Set : 1”
	- GPIO 파일에 그 문자를 write
	(디바이스 드라이버에서는 이 값에 따라 LED를 제어(on/off) 하겠지요…잘 동작하는지 확인)
	- GPIO 파일에서 문자 하나(내가 좀 전에 쓴 문자(‘0’ 또는 ‘1’)를 read 하여 아래 예의	
	형식으로 프린트 함 (“Read Data: 1 from kernel”)
	(내가 쓴 값이 제대로 쓰여졌는지 확인하기 위하여 수행하는 작업임) */

	print("GPIO Set : %s\n", argv);
	print("Read Data : %d from kernel\n", argc);


}