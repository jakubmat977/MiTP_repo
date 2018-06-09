#include "string.h"
#include "decoding.h"

#define NULL 0
#define MAX_TOKEN_NR 						3
#define MAX_KEYWORD_NR 			    3

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

Result eStringToKeyword(char *pcStr, KeywordCode *peKeywordCode){
	
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
		
		if(eStringToKeyword(asToken[ucTokenCtr].uValue.pcString, &eKeywordCode)== OK){
			asToken[ucTokenCtr].eType = KEYWORD;
			asToken[ucTokenCtr].uValue.eKeyword = eKeywordCode;
		}
		else if(eHexStringToUInt(asToken[ucTokenCtr].uValue.pcString, &uiNumberValue) == OK){
			asToken[ucTokenCtr].eType = NUMBER;
			asToken[ucTokenCtr].uValue.uiNumber = uiNumberValue;
		}
		else{
			asToken[ucTokenCtr].eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){
	
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,' ', NULL);
	DecodeTokens();
	}
