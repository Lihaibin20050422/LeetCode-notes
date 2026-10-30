#include <iostream>
#include <vector>
#include <string>
using namespace std;

int findLeft(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (target <= nums[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int findRight(vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (target >= nums[mid]) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return r;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int left = findLeft(nums, target);
    int right = findRight(nums, target);
    if (left >= nums.size() || nums[left] != target) {
        return {-1, -1};
    }
    return {left, right};
}

void show(vector<int>& nums, int target, const string& expect) {
    vector<int> r = searchRange(nums, target);
    cout << "target=" << target << "  -> [" << r[0] << "," << r[1] << "]"
         << "   期望 " << expect << endl;
}

int main()
{
    vector<int> a = {5,7,7,8,8,10};
    cout << "nums = [5,7,7,8,8,10]" << endl;
    show(a, 8,  "[3,4]");
    show(a, 6,  "[-1,-1]  不存在");
    show(a, 5,  "[0,0]");
    show(a, 10, "[5,5]");
    show(a, 11, "[-1,-1]  比所有都大");
    show(a, 1,  "[-1,-1]  比所有都小");

    vector<int> b = {};
    cout << "\nnums = []" << endl;
    show(b, 8, "[-1,-1]  空数组");

    vector<int> c = {8};
    cout << "\nnums = [8]" << endl;
    show(c, 8, "[0,0]");

    vector<int> d = {8,8,8};
    cout << "\nnums = [8,8,8]" << endl;
    show(d, 8, "[0,2]");

    return 0;
}
