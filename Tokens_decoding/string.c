#include "string.h"
#define NULL 0

void CopyString(char pcSource[], char pcDestination[]){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0;pcSource[ucCharacterCounter]!=NULL;ucCharacterCounter++){
        pcDestination[ucCharacterCounter]=pcSource[ucCharacterCounter];
    }
    pcDestination[ucCharacterCounter]=pcSource[ucCharacterCounter];
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){

    unsigned char ucCharacterCounter;

    for(ucCharacterCounter=0;(pcStr1[ucCharacterCounter]!=NULL)&&(pcStr2[ucCharacterCounter]!=NULL);ucCharacterCounter++){
        if(pcStr1[ucCharacterCounter]!=pcStr2[ucCharacterCounter]){
            return NOTEQUAL;
        }
    }
    if(pcStr1[ucCharacterCounter]!=pcStr2[ucCharacterCounter]){
        return NOTEQUAL;
    }
    return EQUAL;
}

void AppendString(char pcSourceStr[], char pcDestinationStr[]){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0;pcDestinationStr[ucCharacterCounter]!=NULL;ucCharacterCounter++){}
    CopyString(pcSourceStr,pcDestinationStr+ucCharacterCounter);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0;pcString[ucCharacterCounter]!=NULL;ucCharacterCounter ++){
        if(pcString[ucCharacterCounter]==cOldChar){
            pcString[ucCharacterCounter]=cNewChar;
        }
    }   
}					           

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

Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
    
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






