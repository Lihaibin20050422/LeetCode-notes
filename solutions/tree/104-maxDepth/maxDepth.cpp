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

int maxDepth(TreeNode* root) {
    if(root == nullptr){
        return 0;
    }
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return lh > rh ? lh + 1 : rh + 1;
}

/*---------------------------- 测试 ----------------------------*/
int main(){
    // 1 的左孩子 2（2 的左孩子 4）、右孩子 3  →  深度 3
    TreeNode* t1 = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), nullptr),
        new TreeNode(3));

    cout << "深度(3层树)  : " << maxDepth(t1)                    << "  (期望 3)" << endl;
    cout << "空树         : " << maxDepth(nullptr)               << "  (期望 0)" << endl;
    cout << "单结点       : " << maxDepth(new TreeNode(1))      << "  (期望 1)" << endl;

    // 单支树：1 只有右孩子 2，2 只有右孩子 3  →  深度 3
    TreeNode* chain = new TreeNode(1, nullptr,
                        new TreeNode(2, nullptr,
                          new TreeNode(3)));
    cout << "单支链       : " << maxDepth(chain) << "  (期望 3)" << endl;

    return 0;
}
