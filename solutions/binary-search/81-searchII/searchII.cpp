#include <iostream>
#include <vector>
using namespace std;

bool search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            return true;
        }
        if(nums[left]==nums[mid] && nums[mid]==nums[right]){
            left++;
            right--;
        }
        else if(nums[left] <= nums[mid]){
            if(target >= nums[left] && target < nums[mid]){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        else{
            if(target > nums[mid] && target <= nums[right]){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
    }
    return false;
}

// 测试main函数
void show(vector<int>& nums, int target, bool expect) {
    cout << "  target=" << target << " -> " << (search(nums, target) ? "true" : "false")
         << "   (期望 " << (expect ? "true" : "false") << ")" << endl;
}

int main()
{
    vector<int> a = {2,5,6,0,0,1,2};
    cout << "nums = [2,5,6,0,0,1,2]" << endl;
    show(a, 0, true);
    show(a, 3, false);

    vector<int> b = {1,0,1,1,1};          // 经典陷阱：nums[left]==nums[mid]，但左半并不是有序的
    cout << "\nnums = [1,0,1,1,1]" << endl;
    show(b, 0, true);
    show(b, 1, true);

    vector<int> c = {1,1,1,1,1};
    cout << "\nnums = [1,1,1,1,1]" << endl;
    show(c, 2, false);
    show(c, 1, true);

    vector<int> d = {1};
    cout << "\nnums = [1]" << endl;
    show(d, 1, true);
    show(d, 0, false);

    vector<int> e = {3,1};
    cout << "\nnums = [3,1]" << endl;
    show(e, 1, true);

    vector<int> f = {};
    cout << "\nnums = []" << endl;
    show(f, 5, false);

    return 0;
}
