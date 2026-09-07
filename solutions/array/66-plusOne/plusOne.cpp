/*
给定一个表示大整数的整数数组 digits，其中digits[i]是整数的第 i 位数字。这些数字按从左到右，从最高位到最低位排列。这个大整数不包含任何前导0。
将大整数加 1，并返回结果的数字数组。
*/
#include<iostream>
#include<vector>
using namespace std;

vector<int> plusOne(vector<int>& digits) {
    for(int i = digits.size()-1;i>=0;i--){
        if( digits[i]!=9){
            digits[i]+=1;
            return digits;
        }else{
            digits[i]=0;
        }
    }
    digits.push_back(0);
    for(int i=digits.size()-1;i>=1;i--){
        digits[i] = digits[i-1];
    }
    digits[0]=1;
    return digits;
}

int main(){
    int n;
    cin >> n;
    vector<int> digits(n);
    for(int i=0;i<n;i++){
        cin >> digits[i];
    }
    vector<int> res = plusOne(digits);
    for(int i=0;i<res.size();i++){
        cout << res[i];
    }
    return 0;
}