#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
void getNext(char *p, int *next , int patternLength);
int KMP_match(char *targetStr, char * patternStr , int patternLength);

/**
Get the Next array;
*/
void getNext(char *p, int *next , int patternLength)
{
    int k = -1;
    int j = 0;
    next[0] = -1;
    for (j = 0; j < patternLength; j++) {
        while (k >= 0 && p[k] != p[j]) {
            k = next[k];
        }
        next[j + 1] = ++k;
    }
}

int KMP_match(char *targetStr, char * patternStr, int patternLength) {
    int *next = new int[patternLength+1];
    getNext(patternStr, next , patternLength);
    int k = 0, p = 0; //k for targetStr, p for patternStr
    int count = 0;
    for(k = 0 ; k < (int)strlen(targetStr); k++) {
        while(targetStr[k]!=patternStr[p] && p>0){
            p = next[p];
        }
        if (targetStr[k] == patternStr[p]) {
            if (p < patternLength-1)
            {
                p++;
            }
            else {
                //cout << "found" << endl << endl;
                count++;
                p = next[p+1];
            }
        }
    }

    return count;
}


int main(int argv, char argc)
{
    int TestRound = 0;
    cin >> TestRound;
    char **targetStr = new char*[TestRound];
    char **patternStr = new char*[TestRound];
    for (int i = 0; i < TestRound; i++) {
        patternStr[i] = new char[10001];
        targetStr[i] = new char[1000001];
    }
    for (int i = 0; i < TestRound; i++)
    {
        cin >> patternStr[i];
        cin >> targetStr[i];
    }
    for (int i = 0; i < TestRound; i++)
    {
        cout << KMP_match(targetStr[i], patternStr[i], strlen(patternStr[i])) << endl;
    }
    return 0;
}
