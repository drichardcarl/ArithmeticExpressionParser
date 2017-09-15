#include <stdio.h>
#include "node.h"

void preorder(struct NODE* _tr){
    if (_tr == NULL)
        return;

    int c=0, d=0; // for tracking
    // pretty straightforward
    if (!strcmp(_tr->info, "+")) printf("Sum ");
    else if (!strcmp(_tr->info, "-")) printf("Dif ");
    else if (!strcmp(_tr->info, "*")) printf("Mul ");
    else if (!strcmp(_tr->info, "/")) printf("Div ");
    else printf("(Num %s)", _tr->info);

    // if left subtree's depth is greater than 1
    // this means that the expression is compound
    // thus, it must be grouped inside a parenthesis
    if (getDepth(_tr->left) > 1){
        printf("(");
        ++c;
        d=1; // don't print space since space is provided
             // after the closing parenthesis
    }
    // display the content of left subtree
    if (_tr->left != NULL)
        preorder(_tr->left);
    // print a closing parenthesis if an open parenthesis
    // has been printed
    if (c){
        printf(") ");
        --c;
    }
    // if the node is the last node (leaf) of the left
    // subtree and d=0 then print a space
    if (_tr->left == NULL && _tr->parent->left == _tr && !d)
        printf(" ");
    // if right subtree's depth is greater than 1
    // this means that the expression is compound
    // thus, it must be grouped inside a parenthesis
    if (getDepth(_tr->right) > 1){
        printf("(");
        ++c;
    }
    // display the content of right subtree
    if (_tr->right != NULL)
        preorder(_tr->right);
    // print a closing parenthesis if an open parenthesis
    // has been printed
    if (c){
        printf(")");
        --c;
    }
}

void postorder(struct NODE* _tr){
    if (_tr == NULL)
        return;

    postorder(_tr->left);

    postorder(_tr->right);

    printf("%s ", _tr->info);
}

void inorder(struct NODE* _tr){
    if (_tr == NULL)
        return;
    inorder(_tr->left);

    printf("%s ", _tr->info);

    inorder(_tr->right);
}

struct NODE* createNode(struct NODE* _parent){
    struct NODE* _t = (struct NODE*)malloc(sizeof(struct NODE));
    _t->info = (char*)malloc(AEXPRSZ * sizeof(char));
    _t->info = "";
    _t->parent = _parent;
    _t->left = NULL;
    _t->right = NULL;

    return _t;
}

int getDepth(struct NODE* _t){
    int ldepth = 0, rdepth = 0;

    if (_t == NULL)
        return 0;
    // base case
    // if node is last node (leaf)
    if (_t->left == NULL && _t->right == NULL)
        return 1;

    ldepth = getDepth(_t->left);
    rdepth = getDepth(_t->right);

    // return max(left, right)+1
    return ((ldepth > rdepth) ? ldepth : rdepth) + 1;
}
