//#include <LPC21xx.H>
#include "string.h"
#include "decoding.h"
#include <stdio.h>
								
int main(){


	char aString1[] = "load 0x20 immediately";
	char aString2[] = "store 0xF1 secure";
	char aString3[] = "store 0x0A confirm";
	char aString4[] = "reset 0xAF immediately";
	char aString5[] = "store 0xCD desired_state";
	
	printf("eCompareString\n\n ");
	
	DecodeMsg(aString1);
	DecodeMsg(aString2);
	DecodeMsg(aString3);
	DecodeMsg(aString4);
	DecodeMsg(aString5);
	


}
