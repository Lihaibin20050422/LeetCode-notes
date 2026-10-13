#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(root == nullptr){
        return res;
    }
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int levelSize = q.size();
        vector<int> level;
        for(int i = 0; i < levelSize; i++){
            TreeNode* cur = q.front();
            q.pop();
            level.push_back(cur->val);
            if(cur->left != nullptr){
                q.push(cur->left);
            }
            if(cur->right != nullptr){
                q.push(cur->right);
            }
        }
        res.push_back(level);
    }
    return res;
}

/*---------------------------- 测试 ----------------------------*/
void printVec2(const vector<vector<int>>& vv){
    cout << "[";
    for(int i = 0; i < (int)vv.size(); i++){
        cout << "[";
        for(int j = 0; j < (int)vv[i].size(); j++){
            cout << vv[i][j];
            if(j + 1 < (int)vv[i].size()) cout << ",";
        }
        cout << "]";
    }
    cout << "]" << endl;
}

int main(){
    // 示例1：root = [3,9,20,null,null,15,7]
    TreeNode* r1 = new TreeNode(3,
        new TreeNode(9),
        new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    cout << "层序  : "; printVec2(levelOrder(r1));              // 期望 [[3],[9,20],[15,7]]

    cout << "空树  : "; printVec2(levelOrder(nullptr));         // 期望 []

    cout << "单结点: "; printVec2(levelOrder(new TreeNode(7)));  // 期望 [[7]]

    // 只有左斜链：1 -> 2 -> 3
    TreeNode* r2 = new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);
    cout << "左斜链: "; printVec2(levelOrder(r2));              // 期望 [[1],[2],[3]]

    return 0;
}