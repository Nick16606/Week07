#include<iostream>
#include<algorithm>
#include<array>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* Search(NODE* pRoot, int x) {
	if (!pRoot) return nullptr;

	if (pRoot->key == x) return pRoot;
	else if (pRoot->key > x) return Search(pRoot->p_left, x);
	else if (pRoot->key < x) return Search(pRoot->p_right, x);

	return nullptr;
}
void Insert(NODE*& pRoot, int x) {
	if (!pRoot) return;

	if (pRoot->key == x) return;
	else if (pRoot->key > x) Insert(pRoot->p_left, x);
	else Insert(pRoot->p_right, x);

	pRoot = new NODE();
	pRoot->key = x;
	pRoot->p_left = NULL, pRoot->p_right = NULL;
	return;
}
void searchStandFor(NODE* pRoot, NODE* q) {
	if (pRoot->p_left) {
		searchStandFor(pRoot, q->p_left);
	}
	else {
		pRoot->key = q->key;
		pRoot = q;
		q = q->p_right;
	}
}
void Remove(NODE*& pRoot, int x) {
	if (!pRoot) return;
	if (pRoot->key > x) Remove(pRoot->p_left, x);
	else if (pRoot->key < x) Remove(pRoot->p_right, x);
	else {
		NODE* tmp = pRoot;
		if (!pRoot->p_left) pRoot = pRoot->p_right;
		else if (!pRoot->p_right) pRoot = pRoot->p_left;
		else if (pRoot->p_left && pRoot->p_right) {
			NODE* q = pRoot->p_right;
			searchStandFor(tmp, q);
		}
	}
}
NODE* createTree(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		swap(a[i], a[min]);
	}
	NODE* pRoot = new NODE();
	pRoot->key = a[n / 2];
	pRoot->p_left = NULL, pRoot->p_right = NULL;
	for (int i = 0; i < n; i++) {
		if (i != n / 2) {
			Insert(pRoot, a[i]);
		}
	}
	return pRoot;
}
void removeTree(NODE*& pRoot) {
	if (!pRoot) return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	return;
}
int height(NODE* pRoot) {
	if (!pRoot) return -1;
	int leftHeight = height(pRoot->p_left);  
	int rightHeight = height(pRoot->p_right); 
	return 1 + max(leftHeight, rightHeight); 
}
int countLess(NODE* pRoot, int x) {
	if (!pRoot) return 0;

	if (pRoot->key >= x) {
		return countLess(pRoot->p_left, x);
	}
	else {
		return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
	}
}
int countGreater(NODE* pRoot, int x) {
	if (!pRoot) return 0;

	if (pRoot->key <= x) {
		return countGreater(pRoot->p_right, x);
	}
	else {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
}
bool CheckBST(NODE* node, int min, int max) {
	if (node == nullptr) return true;

	if (node->key <= min || node->key >= max)
		return false;

	return CheckBST(node->p_left, min, node->key) &&
		CheckBST(node->p_right, node->key, max);
}

bool isBST(NODE* pRoot) {
	return CheckBST(pRoot, 0, 100);
}
bool isFullBinaryTree(NODE* node) {
	if (node == nullptr)
		return true;
	if (!node->p_left && !node->p_right)
		return true;
	if (node->p_left && node->p_right)
		return isFullBinaryTree(node->p_left) && isFullBinaryTree(node->p_right);
	return false;
}
bool isFullBST(NODE* root) {
	return CheckBST(root,0, 100) && isFullBinaryTree(root);
}


