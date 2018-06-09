#include <LPC21xx.H>
#include "string.h"

#define NULL										0
#define MAX_TOKEN_NR 						3
#define MAX_KEYWORD_STRING_LTH	10
#define MAX_KEYWORD_NR 			    3

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

typedef struct {
	KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

Keyword asKeywordList[MAX_KEYWORD_NR]= {
{ST, "store"},
{LD, "load"},
{RST, "reset"}
};


Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;
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
						asToken[ucTokenNr].uValue.pcString = pcString + uiStringIndexCtr;
						ucTokenNr++;
					}
		break;
		}
	}
}

Result eStringToKeyword(char pcStr[], KeywordCode *peKeywordCode){
	
		unsigned int ucKeywordCtr;
		
		for (ucKeywordCtr = 0; ucKeywordCtr < MAX_KEYWORD_NR; ucKeywordCtr++){
			if(eCompareString(pcStr, asKeywordList[ucKeywordCtr].cString) == EQUAL){
			*peKeywordCode = asKeywordList[ucKeywordCtr].eCode;
			return OK;
			}
		}
		return ERROR;
}

void DecodeTokens(){
	
		unsigned char ucTokenCtr;
	
	for(ucTokenCtr=0; ucTokenCtr < ucTokenNr; ucTokenCtr++){
		KeywordCode eKeywordCode;
		unsigned int uiNumberValue;
		Token sToken = asToken[ucTokenCtr];
		
		if(eStringToKeyword(sToken.uValue.pcString, &eKeywordCode)== OK){
			sToken.eType = KEYWORD;
			sToken.uValue.eKeyword = eKeywordCode;
		}
		else if(eHexStringToUInt(sToken.uValue.pcString, &uiNumberValue) == OK){
			sToken.eType = NUMBER;
			sToken.uValue.uiNumber = uiNumberValue;
		}
		else{
			sToken.eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){
	
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ', NULL);
	DecodeTokens();
	}


int main(){

	
	char aString1[] = "load 0x20 immediately";
	char aString2[] = "store 0xF1 secure";
	char aString3[] = "store 0x0A confirm";
	char aString4[] = "reset 0xAF immediately";
	char aString5[] = "store 0xCD desired_state";
	
	DecodeMsg(aString1);
	DecodeMsg(aString2);
	DecodeMsg(aString3);
	DecodeMsg(aString4);
	DecodeMsg(aString5);
	


}
