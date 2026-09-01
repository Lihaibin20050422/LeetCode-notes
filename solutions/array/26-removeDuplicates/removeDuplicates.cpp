/*
给你一个非严格递增排列的数组 ，请你原地删除重复出现的元素，使每个元素只出现一次 ，返回删除后数组的新长度。
*/

#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if(nums.empty()){
        return 0;
    }
    int k = 1;
    for(int i=1;i<nums.size();i++){
        if(nums[i]!=nums[i-1]){
            nums[k++] = nums[i];
        }
    }
    return k;
}

int main(){
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin >> nums[i];
    }
    cout << removeDuplicates(nums) << endl;
    return 0;
}