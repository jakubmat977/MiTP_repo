#include <LPC21xx.H>
#define NULL 0

enum Result {OK, ERROR};

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
       
    unsigned char ucCurrentNibble;
    unsigned char ucNibbleCounter;
 
    pcStr[0] = '0';
    pcStr[1] = 'x';
    pcStr[6] = NULL;
 
    for(ucNibbleCounter = 0; ucNibbleCounter < 4; ucNibbleCounter++){
        ucCurrentNibble = (uiValue >> (ucNibbleCounter*4)) & 0xF;
        if(ucCurrentNibble < 10){
            pcStr[5 - ucNibbleCounter] = '0' + ucCurrentNibble;
        }
        else{
            pcStr[5 - ucNibbleCounter] = 'A' + (ucCurrentNibble - 10);
        }
    }
}
/////////////////HEX------>string////////////////////////////////////
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
    
    unsigned char ucCurrentCharacter;
    unsigned char ucCharacterCounter;
    *puiValue=0;
    
    if((pcStr[0] != '0')||(pcStr[1] != 'x')||(pcStr[2] == NULL)){
        return ERROR;
    }
    for(ucCharacterCounter=2; pcStr[ucCharacterCounter]!=NULL; ucCharacterCounter++){
        ucCurrentCharacter = pcStr[ucCharacterCounter];
        if (ucCharacterCounter>=6){
            return ERROR;
        }
        *puiValue = *puiValue<<4;
        if((ucCurrentCharacter>='0')&&(ucCurrentCharacter<='9')){
            *puiValue= *puiValue + (ucCurrentCharacter-'0');
        }else if((ucCurrentCharacter>='A')&&(ucCurrentCharacter<='F')){
            *puiValue= *puiValue + (ucCurrentCharacter-'A'+10);       
        }else{
            return ERROR;
        }
    }
    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
 
    unsigned char ucCharacterCounter;
 
    for (ucCharacterCounter=0; pcDestinationStr[ucCharacterCounter]!=NULL; ucCharacterCounter++){}
    UIntToHexStr(uiValue, pcDestinationStr + ucCharacterCounter);
}



//////// main for int to hex //////////
int main(){
	
	unsigned int uiValue = 1000;
	unsigned int uiValue2 = 2000;
	char cStr1[15];
	unsigned int uiRestoredValue = 0;
	
	UIntToHexStr(uiValue,cStr1);
	/* // test for str->int
	unsigned int uiRestoredValue = 0;
	char cStr1[] = "0xC5A8";
	char cStr2[] = "0XC511";
	char cStr3[] = "0xCG12";
	char cStr4[] = "0xB56AA";
	enum Result eResult1 = eHexStringToUInt(cStr1, &uiRestoredValue);
	enum Result eResult2 = eHexStringToUInt(cStr2, &uiRestoredValue);
	enum Result eResult3 = eHexStringToUInt(cStr3, &uiRestoredValue);
	enum Result eResult4 = eHexStringToUInt(cStr4, &uiRestoredValue);
	*/
	//eHexStringToUInt(cStr1, &uiRestoredValue);
	AppendUIntToString(uiValue2,cStr1);
	
	

}



