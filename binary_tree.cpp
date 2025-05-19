#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNode(int data) {
	NODE* curr = new NODE();
	curr->key = data;
	curr->p_left = NULL;
	curr->p_right = NULL;
	return curr;
}
vector<int> NLR(NODE* pRoot) {
    vector<int> data;
    if (pRoot == NULL) return data;

    data.push_back(pRoot->key);
    vector<int> left = NLR(pRoot->p_left);
    data.insert(data.end(), left.begin(), left.end());
    vector<int> right = NLR(pRoot->p_right);
    data.insert(data.end(), right.begin(), right.end());
    return data;
}
vector<int> LNR(NODE* pRoot) {
    vector<int>data;
    if (pRoot == NULL) return {};

    vector<int>left = NLR(pRoot->p_left);
    data.insert(data.end(), left.begin(), left.end());
    data.push_back(pRoot->key);
    vector<int>right = NLR(pRoot->p_right);
    data.insert(data.end(), right.begin(), right.end());
    return data;
}
vector<int> LRN(NODE* pRoot) {
    vector<int>data;
    if (pRoot == NULL) return {};

    vector<int>left = NLR(pRoot->p_left);
    data.insert(data.end(), left.begin(), left.end());
    vector<int>right = NLR(pRoot->p_right);
    data.insert(data.end(), right.begin(), right.end());
    data.push_back(pRoot->key);
    return data;
}
vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>>res;
    if (!pRoot) return {{}};
        
    queue<NODE*>q;
    q.push(pRoot);
    while (!q.empty()) {
        vector<int>preres;
        for (int i = 0; i < q.size(); i++) {
            NODE* curr = q.front();
            q.pop();
            preres.push_back(curr->key);
            if (curr->p_left) q.push(curr->p_left);
            if (curr->p_right) q.push(curr->p_right);
        }
        res.push_back(preres);
    }
    return res;
}
int countNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
int sumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
int height(NODE* pRoot) {
    if (!pRoot) return -1;
    int leftHeight = height(pRoot->p_left);
    int rightHeight = height(pRoot->p_right);
    return 1 + max(leftHeight, rightHeight);
}
NODE* findNodebyValue(NODE* pRoot,int value) {
    if (!pRoot) return nullptr;
    if (pRoot->key == value) return pRoot;
    NODE* left = findNodebyValue(pRoot->p_left, value);
    if (left) return left;
    return findNodebyValue(pRoot->p_right, value);
}
int heightNode(NODE* pRoot, int value) {
    if (pRoot) return -1;
    NODE* curr = findNodebyValue(pRoot, value);
    int heightofNode = height(curr);
    if (!curr) return -1;
    return heightofNode;
}
int findNodebyNode(NODE* pRoot, NODE* tmp, int level) {
    if (!pRoot) return -1;
    if (pRoot == tmp) return level;

    int left = findNodebyNode(pRoot->p_left, tmp, level + 1);
    if (left != -1) return left;
    return findNodebyNode(pRoot->p_right, tmp, level + 1);
}
int Level(NODE* pRoot, NODE* p) {
    return findNodebyNode(pRoot, p, 0);
}
int countLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

