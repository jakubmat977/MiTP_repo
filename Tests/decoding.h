#define MAX_KEYWORD_STRING_LTH	10

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


unsigned char ucFindTokensInString(char *pcString);
Result eStringToKeyword(char pcStr[], KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
