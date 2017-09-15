#ifndef __NODE_H__
#define __NODE_H__

#define AEXPRSZ 64

struct NODE {
    char* info;
    struct NODE* parent;
    struct NODE* left;
    struct NODE* right;
};

// preorder tree traversal (root, left, right)
// - used to solve any arithmetic expression
//   from its Abstract Syntax Tree (AST)
void preorder(struct NODE*);
// postorder tree traversal (left, right, root)
void postorder(struct NODE*);
// inorder tree traversal (left, root, right)
void inorder(struct NODE*);

// returns a pointer to a created NODE
struct NODE* createNode(struct NODE*);
// return the max depth of a given tree
int getDepth(struct NODE*);

#endif // __NODE_H__
