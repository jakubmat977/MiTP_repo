typedef enum { OK, ERROR } Result;
enum CompResult {EQUAL, NOTEQUAL};

void CopyString(char [], char []);
enum CompResult eCompareString(char *, char *);
void AppendString(char [], char []);
void ReplaceCharactersInString(char [], char , char );
void UIntToHexStr(unsigned int uiValue, char pcStr[]);
Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);
