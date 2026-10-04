#include <vector>
#include <iostream>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void dfs(TreeNode* node, vector<int>& res);

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    dfs(root, res);
    return res;
}

void dfs(TreeNode* node, vector<int>& res){
    if(node == nullptr){
        return ;
    }
    dfs(node->left, res);
    res.push_back(node->val);
    dfs(node->right, res);
}

/*---------------------------- 测试 ----------------------------*/
// 只读，所以用 const 引用 —— 这样既能接变量，也能接临时值（如 inorderTraversal(root) 的返回值）
void printVec(const vector<int>& v){
    for(int x : v) cout << x << " ";
    cout << endl;
}

int main(){
    // 构造树：1 的左孩子是 2（2 的左孩子 4、右孩子 5），1 的右孩子是 3
    // 中序遍历应为 4 2 5 1 3
    TreeNode* n4 = new TreeNode(4);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n2 = new TreeNode(2, n4, n5);
    TreeNode* n3 = new TreeNode(3);
    TreeNode* root = new TreeNode(1, n2, n3);

    cout << "中序    : "; printVec(inorderTraversal(root));          // 期望 4 2 5 1 3
    cout << "空树    : "; printVec(inorderTraversal(nullptr));       // 期望 空
    cout << "单结点  : "; printVec(inorderTraversal(new TreeNode(7)));// 期望 7

    return 0;
}
