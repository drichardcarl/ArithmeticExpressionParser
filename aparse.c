#include <stdio.h>

#include "node.h"
#include "tokens.h"
#include "aparse.h"

int isKeywordValid(char* input){
    char iKeyword[30];
    getKeyword(input, iKeyword);

    int i, hasMatch = 0;
    for (i=0; i<NK; ++i){
        if (!strcmp(KEYWORD[i], iKeyword)){
            hasMatch = 1;
            break;
        }
    }

    return hasMatch;
}

void getKeyword(char* _src, char* _dest){
    int i;
    for (i=0; _src[i]!='\0' && _src[i]!=' ' && _src!='\n'; ++i){
        _dest[i] = _src[i];
    }
    _dest[i] = '\0';
}

int getAExp(char* _src, char* _dest){
    int i,j, start=0, error=-1;
    // extracts the contents inside of the open and close
    // quotation marks
    for (i=0,j=0; i<BUFFER; ++i){
        if (start){
            if (_src[i] == '"'){error=0; break;}
            _dest[j++] = _src[i];
        }
        else
            if (_src[i] == '"'){start=1; continue;}
    }
    _dest[j] = '\0';
    cleanStr(_dest); // strip spaces from an arithmetic expression

    // check if closing quotation mark is encountered
    // but still has empty destination
    if (!error)
        if (!strlen(_dest)) error=-1;
    // error = 0  : no error
    // error = -1 : error encountered
    return error;
}

void cleanStr(char* _str){
    int i, j;
    // copy all characters except the whitespaces
    for (i=0, j=0; i<strlen(_str); ++i){
        if (_str[i] != ' ')
            _str[j++] = _str[i];
    }
    _str[j] = '\0';
}

void zeroFill(char* _src, int _sz){
    // set every character element of the array to NULL
    int i;
    for (i=0; i<_sz; ++i)
        _src[i] = '\0';
}

int isIExpAExp(char* _iExp){
    if (strlen(_iExp) == 0) return 0;
    int i, j, error = 0;
    int _t;

    // test if the expression has the right symbols only
    for (i=0; i<strlen(_iExp); ++i){
        _t=0;
        for (j=0; j<NS; ++j){
            if (_iExp[i] == SYMBOL[j]) {_t=1; break;}
        }
        if (!_t) {error=-1; break;}
    }

    // test if the expression has the correct # of open and close
    // parenthesis
    if (ccount(_iExp, '(') != ccount(_iExp, ')'))
        error = -1;

    // test if the expression has at least 1 operator
    // other than parenthesis
    if (!ccount(_iExp, '*') &&
        !ccount(_iExp, '/') &&
        !ccount(_iExp, '+') &&
        !ccount(_iExp, '-'))
        error = -1;

    return ((!error) ? 1 : 0);
}

int ccount(char* _src, char _c){
    int i, _num = 0;
    // increment _num if each time the character _c occurs
    for (i=0; i<strlen(_src); ++i)
        if (_src[i] == _c) ++_num;
    return _num;
}

void gin(char* _ibuff, char* _keyword, char* _expr){
    int i, j, next=0;
    // * everything before the first whitespace
    //   is considered a KEYWORD
    // * everything after the first whitespace
    //   is considered an EXPRESSION
    for (i=0, j=0; i<strlen(_ibuff); ++i){
        if (_ibuff[i] == ' ' && !next){next=1; continue;}
        if (!next) _keyword[i] = _ibuff[i];
        else _expr[j++] = _ibuff[i];
    }
}

int inparse(char* _keyword, char* _expr){
    // check validity of keyword
    // code -1 is for invalid keyword
    if (!isKeywordValid(_keyword)) return -1;
    // check validity of expression base on keyword
    switch(getKwdIdx(_keyword)){
    case 0: // exit
        return 1; // code 1 is exit
        break;
    case 1:; // aparse
        char aExpr[BUFFER];
        zeroFill(aExpr, BUFFER);
        // if invalid arithmetic expression -> error
        // code -2 is for invalid arithmetic expression
        if (getAExp(_expr, aExpr) || !isIExpAExp(aExpr))
            return -2;
        printf("[*] ");
        aparse(aExpr);
        return 0;
        break;
    }
}

int getKwdIdx(char* _kwd){
    // assumtion : keyword is already checked
    //           : which means, keyword is valid
    int i;
    for (i=0; i<NK; ++i)
        if (!strcmp(_kwd, KEYWORD[i]))
            return i;
}

void aparse(char* _aexpr){
    struct NODE* _t = bAExpr3(_aexpr);
    preorder(_t);
}

struct NODE* bAExpr3(char* _aExpr){
    struct NODE* _t;
    _t = _bAExpr3(_aExpr, NULL);
    return _t;
}

struct NODE* _bAExpr3(char* _aExpr, struct NODE* _parent){
    // assumption : _aExpr contains the right arithmetic expression
    struct NODE* _t = createNode(_parent);

    unparenthesize(_aExpr);
    char _opt = getOpt(_aExpr);

    if (_opt != '\0'){
        _t->info = char2str(_opt);
        char* _L = (char*)malloc(AEXPRSZ * sizeof(char));
        char* _R = (char*)malloc(AEXPRSZ * sizeof(char));
        getLRExpr(_aExpr, _L, _R, _opt);
        _t->left = _bAExpr3(_L, _t);
        _t->right = _bAExpr3(_R, _t);
    }

    // base case
    // when _aExpr is just a number
    else{
        _t->info = _aExpr;
        _t->left = NULL;
        _t->right = NULL;
    }

    return _t;
}

char getOpt(char* _aExpr){
    // assumption : input arithmetic expression is not enclosed by
    //              parentheses i.e., fist character is not '(' and
    //              last character is not ')'
    int i, skip=0;
    char _opt = '\0';

    for (i=0; i<strlen(_aExpr); ++i){
        // skip parenthesized expression
        // check for operator with lowest precedence
        // after the parenthesized expression
        if (_aExpr[i] == '(') ++skip;
        if (_aExpr[i] == ')') --skip;
        if (skip) continue;

        if (_aExpr[i] == '+' || _aExpr[i] == '-'){
            if (_opt == '*' || _opt == '/' || _opt == '\0')
                _opt = _aExpr[i];
        }
        else if (_aExpr[i] == '*' || _aExpr[i] == '/'){
            if (_opt == '\0')
                _opt = _aExpr[i];
        }
    }
    return _opt;
}

void getLRExpr(char* _src, char* _left, char* _right, char _opt){
    int i, j, startr=0, skip=0;
    // split the source string into two using the operator
    //  - left subexpression is stored to _left
    //  - right subexpression is stored to _right
    for (i=0, j=0; i<strlen(_src); ++i){
        if (!startr){
            if (_src[i] == '(' && !i) ++skip;
            if (_src[i] == ')') --skip;
            if (skip > 0){
                _left[i] = _src[i];
                continue;
            }

            if (_src[i] == _opt){
                startr=1;
                _left[i] = '\0';
                continue;
            }

            _left[i] = _src[i];
        }
        else
            _right[j++] = _src[i];
    }
    _right[j] = '\0';
}

char* char2str(char _c){
    char* _t = malloc(2*sizeof(char));
    _t[0] = _c;
    _t[1] = '\0';
    return _t;
}

void unparenthesize(char* _src){
    // assumption : first and the last characters before null character
    //            : are '(' and ')' respectively
    if (_src[0] != '(' || _src[strlen(_src)-1] != ')')
        return;

    int i=1;
    for (; i<strlen(_src)-2; ++i){
        _src[i-1] = _src[i];
    }
    _src[i] = '\0';
}
