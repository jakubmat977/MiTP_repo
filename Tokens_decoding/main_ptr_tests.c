
#include <LPC21xx.H> 
//#include <stdio.h>
//#include <string.h>
#define MAX_TOKEN_NR 3

//Token asToken[MAX_TOKEN_NR];
#define NULL 					           0
#define MAX_TOKEN_NR 			       3
#define MAX_KEYWORD_STRING_LTH 	 10 // max dl komendy
#define MAX_KEYWORD_NR 			     3
#define MAX_ILOSC_ZNAKOW	       6

void UIntToHexStr(unsigned int uiValue, char pcStr[]);
typedef enum { OK, ERROR } Result;
unsigned char ucFindTokensInString(char *pcString);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
enum CompResult {NOTEQUAL, EQUAL};
unsigned char ucTokenNr;

enum state {DELIMITER,TOKEN};
typedef enum { LD, ST, RST} KeywordCode;
typedef enum { KEYWORD, NUMBER, STRING} TokenType;

typedef union {
    KeywordCode eKeyword;
    unsigned int uiNumber;
    char *pcString;
}TokenValue;


typedef struct {                       
    TokenType eType;									 
    TokenValue uValue;								 
}Token;																

Token asToken[MAX_TOKEN_NR];

typedef struct
{
	KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

//example keywords
Keyword asKeywordList[MAX_KEYWORD_NR]= 
{
	{ST, "store"},
  {LD, "load"},
  {RST, "reset"}
};


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

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0;pcString[ucCharacterCounter]!=NULL;ucCharacterCounter ++){
        if(pcString[ucCharacterCounter]==cOldChar){
            pcString[ucCharacterCounter]=cNewChar;
        }
    }   
}      

unsigned int uiStringIndexCtr;
unsigned char ucFindTokensInString(char *pcString){
	
	enum state eState = DELIMITER;
	ucTokenNr = 0;
	
	for(uiStringIndexCtr=0; ;uiStringIndexCtr++){
	unsigned char ucCurrentChar = pcString[uiStringIndexCtr];
		switch(eState){
				case TOKEN:
					if(ucCurrentChar == NULL){
						return ucTokenNr;
					}
					else if(ucTokenNr == MAX_TOKEN_NR){
						return ucTokenNr;
					}
					else if(ucCurrentChar == ' '){
						eState = DELIMITER;
					}
					else{
						eState = TOKEN;
					}
		break;
				case DELIMITER:
					if(ucCurrentChar == NULL){
						return ucTokenNr;
					}
					else if(ucCurrentChar == ' '){
						eState = DELIMITER;
					}
					else{
						eState = TOKEN;
						asToken[ucTokenNr++].uValue.pcString = pcString + uiStringIndexCtr;
					}
		break;
		}
	}
}

Result eStringToKeyword(char pcStr[], KeywordCode *peKeywordCode){
	
		unsigned int ucKeywordCtr;
		
		for (ucKeywordCtr = 0; ucKeywordCtr < MAX_KEYWORD_NR; ucKeywordCtr ++){
			if(eCompareString(pcStr, asKeywordList[ucKeywordCtr].cString) == EQUAL){
			*peKeywordCode = asKeywordList[ucKeywordCtr].eCode;
			return OK;
			}
		}
		return ERROR;
}

void DecodeTokens(){
	
		unsigned char ucTokenCtr;
	
	for(ucTokenCtr=0; ucTokenCtr < ucTokenNr;ucTokenCtr++){
		KeywordCode eKeywordCode;
		unsigned int uiNumberValue;
		Token *pasToken;
		
		pasToken = &asToken[ucTokenCtr];
		
		if(eStringToKeyword(pasToken->uValue.pcString, &eKeywordCode)==OK){
			pasToken->eType = KEYWORD;
			pasToken->uValue.eKeyword = eKeywordCode;
		}
		else if(eHexStringToUInt(pasToken->uValue.pcString, &uiNumberValue) == OK){
			pasToken->eType = NUMBER;
			pasToken->uValue.uiNumber = uiNumberValue;
		}
		else{
			pasToken->eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){
	
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ', NULL);
	DecodeTokens();
	}


void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
 
    unsigned char ucCharacterCounter;
 
    for (ucCharacterCounter=0; pcDestinationStr[ucCharacterCounter]!=NULL; ucCharacterCounter++){}
    UIntToHexStr(uiValue, pcDestinationStr + ucCharacterCounter);
}


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



int main(){

	volatile KeywordCode eType1;
	volatile KeywordCode eType2;
	volatile KeywordCode eType3;
	volatile KeywordCode eType4;
	volatile KeywordCode eType5;
	volatile unsigned int ucValue1;
	volatile unsigned int ucValue2;
	volatile unsigned int ucValue3;
	volatile unsigned int ucValue4;
	volatile unsigned int ucValue5;
	char *pcMessage1;
	char *pcMessage2;
	char *pcMessage3;
	char *pcMessage4;
	char *pcMessage5;
	
	char aString1[] = "load 0x20 immediately";
	char aString2[] = "store 0xF1 secure";
	char aString3[] = "store 0x0A confirm";
	char aString4[] = "reset 0xAF immediately";
	char aString5[] = "store 0xCD desired_state";

	
	DecodeMsg(aString1);
  eType1 = asToken[0].uValue.eKeyword;
	ucValue1 = asToken[1].uValue.uiNumber;
	pcMessage1 = asToken[2].uValue.pcString; 
	
	DecodeMsg(aString2);
  eType2 = asToken[0].uValue.eKeyword;
	ucValue2 = asToken[1].uValue.uiNumber;
	pcMessage2 = asToken[2].uValue.pcString;
	
	DecodeMsg(aString3);
  eType3 = asToken[0].uValue.eKeyword;
	ucValue3 = asToken[1].uValue.uiNumber;
	pcMessage3 = asToken[2].uValue.pcString;
	
	DecodeMsg(aString4);
  eType4 = asToken[0].uValue.eKeyword;
	ucValue4 = asToken[1].uValue.uiNumber;
	pcMessage4 = asToken[2].uValue.pcString;
	
	DecodeMsg(aString5);
  eType5 = asToken[0].uValue.eKeyword;
	ucValue5 = asToken[1].uValue.uiNumber;
	pcMessage5 = asToken[2].uValue.pcString;
	
	DecodeMsg(pcMessage1);
	DecodeMsg(pcMessage2);
	DecodeMsg(pcMessage3);
	DecodeMsg(pcMessage4);
	DecodeMsg(pcMessage5);

}







