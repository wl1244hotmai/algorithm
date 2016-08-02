#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>

using namespace std;


// A B C B D A
// 递归公式:
// if LPS[0] == LPS[n-1]
//        LPS(0,n-1) = 1 + LPS(1,n-2);
//   else
//        LPS(0,n-1) = max (LPS(1,n-1),LPS(0,n-2)))

// str[i] 到 str[j]的字符串的LPS
int dp[1001][1001] = {0};

int LPS(string str,int n, int m){
    for(int l = 1;l<=str.size();l++){
        for(int i = 0; i + l -1 < str.size();i++){
            int j = i + l - 1;
            if(i==j){
                dp[i][j] = 1;
            }
            else{
                if(str[i]==str[j]){
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
                else{
                    dp[i][j] = max(dp[i][j-1],dp[i+1][j]);
                }
            }
        }
    }
    return dp[n][m];
}

int main()
{
    vector<string> inputStrs;
    string str_temp;
    while(cin && cin >> str_temp && str_temp!="eof")
    {
        inputStrs.push_back(str_temp);
    }

    for_each(inputStrs.begin(),inputStrs.end(),[&](string str)
    {
        memset(dp,0,sizeof(dp));
        cout << str.size() - LPS(str,0,str.size()-1)<<endl;
    });
    return 0;
}
