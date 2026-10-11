#include<iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void dfs(TreeNode* root, vector<int>& res){
    if(root == nullptr){
        return ;
    }
    res.push_back(root->val);
    dfs(root->left, res);
    dfs(root->right, res);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    dfs(root, res);
    return res;
}

/*---------------------------- 测试 ----------------------------*/
void printVec(const vector<int>& v){
    for(int x : v) cout << x << " ";
    cout << endl;
}

int main(){
    // 测试树：1 的左孩子 2（2 的左4 右5）、1 的右孩子 3
    TreeNode* root = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), new TreeNode(5)),
        new TreeNode(3));

    cout << "前序  : "; printVec(preorderTraversal(root));            // 期望 1 2 4 5 3
    cout << "空树  : "; printVec(preorderTraversal(nullptr));         // 期望 空
    cout << "单结点: "; printVec(preorderTraversal(new TreeNode(7))); // 期望 7

    return 0;
}
