#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr){
        return nullptr;
    }
    invertTree(root->left);
    invertTree(root->right);
    TreeNode* p = root->left;
    root->left = root->right;
    root->right = p;
    return root;
}

/*---------------------------- 测试 ----------------------------*/
void printTree(TreeNode* root){          // 先序打印，null 用 _ 表示
    if(root == nullptr){
        cout << "_ ";
        return;
    }
    cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

int main(){
    // [4,2,7,1,3,6,9]  →  反转后 [4,7,2,9,6,3,1]
    TreeNode* r = new TreeNode(4,
        new TreeNode(2, new TreeNode(1), new TreeNode(3)),
        new TreeNode(7, new TreeNode(6), new TreeNode(9)));

    cout << "反转前: "; printTree(r); cout << endl;
    invertTree(r);
    cout << "反转后: "; printTree(r); cout << endl;

    cout << "空树  : "; printTree(invertTree(nullptr)); cout << endl;

    cout << "单结点: "; printTree(invertTree(new TreeNode(5))); cout << endl;

    return 0;
}
