#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int  key;
    char value[20];
    int  height;       
    struct node *left, *right;
} node;

typedef struct bst {
	node *root;
}bst;

node *newNode(const int key, char *value){
    node *n = (node*)malloc(sizeof(node));
    n->key = key;
    strcpy(n->value, value);
    n->left  = n->right = NULL;
    n->height = 1;  

    return n;
}

static inline int maxInt(int a, int b){ return a > b ? a : b; }

int nodeHeight(node *n){ return n ? n->height : 0; }

//tinggi nya di update
void updateHeight(node *n){
    if(n) n->height = 1 + maxInt(nodeHeight(n->left), nodeHeight(n->right));
}

//nge cek balance
int balanceFactor(node *n){
    return n ? nodeHeight(n->left) - nodeHeight(n->right) : 0;
}

bst *newBST() {
	bst *b = (bst*)malloc(sizeof(bst));
	b->root = NULL;
	
	return b;
}

node *rotateRight(node *pivot){
    node *newRoot  = pivot->left;
    node *tempSub  = newRoot->right;

    newRoot->right = pivot;
    pivot->left    = tempSub;

    updateHeight(pivot);
    updateHeight(newRoot);
    return newRoot;
}

node *rotateLeft(node *pivot){
    node *newRoot = pivot->right;
    node *tempSub = newRoot->left;

    newRoot->left  = pivot;
    pivot->right   = tempSub;

    updateHeight(pivot);
    updateHeight(newRoot);
    return newRoot;
}

node *rebalance(node *root){
    updateHeight(root);
    int bf = balanceFactor(root);

    /* Left heavy */
    if(bf > 1){
        if(balanceFactor(root->left) < 0)        // LR case
            root->left = rotateLeft(root->left);
        return rotateRight(root);                // LL case
    }

    /* Right heavy */
    if(bf < -1){
        if(balanceFactor(root->right) > 0)       // RL case
            root->right = rotateRight(root->right);
        return rotateLeft(root);                 // RR case
    }

    return root;  // sudah seimbang
}

node *insertNode(node *root, const int key, char *value) {
    if(root == NULL) return newNode(key, value);

    if(key < root->key)
        root->left  = insertNode(root->left,  key, value);
    else if(key > root->key)
        root->right = insertNode(root->right, key, value);
    else
        strcpy(root->value, value);   

    return rebalance(root);
}

void push(bst *tree, const int key, char *value) {
	if(tree != NULL) {
		tree->root = insertNode(tree->root, key, value);
	}
}

node *successor(node *root) {
	node *curr = root->right;
	while(curr->left != NULL) {
		curr = curr->left;
	}	
	return curr;
}

node *predecessor(node *root) {
	node *curr = root->left;
	while(curr->right != NULL) {
		curr = curr->right;
	}	
	return curr;
}

node *deleteNode(node *root, const int key) {
	if(root == NULL) {
		return NULL;
	}
	
	if(key < root->key) {
		root->left = deleteNode(root->left, key);
	} else if(key > root->key) {
		root->right = deleteNode(root->right, key);
	} else {
		if(root->right == NULL && root->left == NULL) {
			free(root);
			root = NULL;
		} else if (root->right == NULL || root->left == NULL) {
			node *temp;
			if(root->left == NULL) {
				temp = root->right;
			} else {
				temp = root->left;
			}
			*root = *temp;
			free(temp);
		} else {
			node *pred = predecessor(root);
			root->key = pred->key;
			strcpy(root->value, pred->value);
			root->left = deleteNode(root->left, pred->key);
		}
	}
    if(root)root = rebalance(root); // klo masih ada node perbaruin trus tinggiin
	
	return root;
}

void pop(bst *tree, const int key) {
	if(tree != NULL) {
		tree->root = deleteNode(tree->root, key);
	}
}

void prefix(node *root) {
	if(root != NULL) {
		printf("%d\n", root->key);
		prefix(root->left);
		prefix(root->right);
	}
}

void infix(node *root) {
	if(root != NULL) {
		infix(root->left);
		printf("%d\n", root->key);
		infix(root->right);
	}
}

void postfix(node *root) {
	if(root != NULL) {
		postfix(root->left);
		postfix(root->right);
		printf("%d\n", root->key);
	}
}

int main() {
	bst *tree = newBST();
	push(tree, 21, "alpha_giga");
	push(tree, 8, "beta_giga");
	push(tree, 34, "delta_giga");
	push(tree, 13, "omega_giga");
	push(tree, 55, "nova_giga");
	push(tree, 3, "luna_giga");
	push(tree, 89, "terra_giga");
	push(tree, 2, "cyber_giga");
	push(tree, 17, "kappa_giga");
	push(tree, 29, "magma_giga");
	push(tree, 44, "astro_giga");
	push(tree, 76, "phantom_giga");
	push(tree, 97, "blitz_giga");
	push(tree, 38, "draco_giga");
	push(tree, 12, "electro_giga");
	push(tree, 60, "plasma_giga");
	push(tree, 5, "quake_giga");
	push(tree, 16, "storm_giga");
	push(tree, 70, "fusion_giga");
	push(tree, 25, "zero_giga");
	pop(tree, 25);
	prefix(tree->root);
	free(tree);
}

