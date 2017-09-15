#ifndef __APARSE_H___
#define __APARSE_H___

#define BUFFER 256

// checks if given keyword is valid
int isKeywordValid(char*);
// checks if an Input Expression is also an Arithmetic Expression
int isIExpAExp(char*);
// get keyword from the buffer
void getKeyword(char*,char*);
// returns the Arithmetic Expression from an Input Expression
int getAExp(char*,char*);
// removes any extra spaces
void cleanStr(char*);
// initializes the parameter's contents to  NULL
void zeroFill(char*, int);
// returns the number of occurences of a character from a stream
// of characters
int ccount(char*,char);

// analyzes the input and designates the keyword and expression
void gin(char*, char*, char*);
// performs the task specified by the keyword and the
// input expression
int inparse(char*, char*);
// returns the index of a given keyword from the materlist
int getKwdIdx(char*);
// performs the aparse command
void aparse(char*);
// builds Arithmetic Expression Tree from a Arithmetic Expression
struct NODE* bAExpr3(char*);
struct NODE* _bAExpr3(char*, struct NODE*);
// returns the operator of highest precedence
char getOpt(char*);
// get Left and Right sub-expression
void getLRExpr(char*, char*, char*, char);
// converts one char to string
char* char2str(char);

#endif // __APARSE_H___

