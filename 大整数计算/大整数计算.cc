#include <iostream>
#include <cstring>
#include <string>
class BigInt {
public:
    BigInt(std::string n_) {
        n = n_;
    }
    BigInt() {
        n = "0";
    }
    int getLength() {
        return n.length();
    }
    void display() {
        std::cout << n << std::endl;
    }
    BigInt operator+(BigInt b) {
        BigInt a = *this;
        if(a.getLength() < b.getLength()) {
            std::string tmp = a.n;
            a.n = b.n;
            b.n = tmp;
        }
        int * c = new int[a.getLength() + 1];
        int * c = new int[a.getLength() + 1];
        std::memset(c, 0, sizeof(c));
        int i, j;
        for(i = 0; i < a.getLength() - b.getLength(); i++) {
            c[i + 1] = a.n[i] -'0';
        }
        for(j = 0; j < b.getLength(); i++, j++) {  //注意循环范围
            c[i + 1] = a.n[i] - '0' + b.n[j] - '0';
        }
        for(i = a.getLength(); i > 0; i--) {
            if(c[i] >= 10) {
                c[i] -= 10;
                c[i - 1] += 1;
            }
        }
        std::string d;
        if(c[0] != 0) {
            d.push_back(c[0] + '0');
        }
        for(i = 1; i < a.getLength() + 1; i++) {
            d.push_back(c[i] + '0');
        }
        return BigInt(d);
    }
    BigInt operator-(BigInt b) {
        BigInt a = *this;
        int sign = 1;
        if(a.getLength() < b.getLength()) {
            std::string tmp = a.n;
            a.n = b.n;
            b.n = tmp;
            sign = -1;
        }
        int * c = new int[a.getLength() + 1];
        std::memset(c, 0, sizeof(c));
        
        int i, j;
        for(i = 0; i < a.getLength() - b.getLength(); i++) {
            c[i + 1] = a.n[i] -'0';
        }
        for(j = 0; j < b.getLength(); i++, j++) {
            c[i + 1] = (a.n[i] - '0') - (b.n[j] - '0');  //注意加括号
        }
        for(i = a.getLength(); i > 0; i--) {
            if(c[i] < 0) {
                c[i] += 10;
                c[i - 1] -= 1;
            }
        }
        std::string d;
        if(sign == -1 || (sign == 1 && c[0] == -1)) {
            d.push_back('-');
        }
        for(i = 1; c[i] == 0; i++) {
            ;
        }
        for(; i < a.getLength() + 1; i++) {
            d.push_back(c[i] + '0');
        }
        return BigInt(d);
    }
    BigInt operator*(BigInt b) {
        BigInt a = *this;
        BigInt d("0");
        for(int i = 0; i < b.getLength(); i++) {
            BigInt tmp;
            tmp = sMul(a, b.n[i] - '0');  //别忘了减0
            for(int j = 0; j < b.getLength() - i - 1; j++) {
                tmp.n.push_back('0');
            }
            d = d + tmp;
        }
        return d;
    }
    BigInt operator/(BigInt b) {
        BigInt a = *this;
        BigInt one("1");
        BigInt result("0");
        while(a.n[0] != '-') {
            a = a - b;
            result = result + one;
        }
        result = result - one;
        return result;
    }
    BigInt operator%(BigInt b) {
        BigInt a = *this;
        BigInt one("1");
        BigInt result("0");
        while(a.n[0] != '-'){
            result = a;
            a = a - b;
        }
        return result;
    }
private:
    std::string n;
    BigInt sMul(BigInt a, int b) {
        int * c = new int[a.getLength() + 1];
        std::memset(c, 0, sizeof(c));
        for(int i = 0; i < a.getLength(); i++) {
            c[i + 1] = (a.n[i] - '0') * b;
        }
        for(int i = a.getLength(); i > 0; i--) {
            if(c[i] > 9) {
                c[i-1] += c[i] / 10;  //注意两个运算的顺序
                c[i] %= 10;
            }
        }
        std::string d;
        if(c[0] != 0) {
            d.push_back(c[0] + '0');
        }
        for(int i = 1; i < a.getLength() + 1; i++) {
            d.push_back(c[i] + '0');
        }
        return BigInt(d);
    }
};
int main(void)
{
    BigInt a("123");
    BigInt b("11");
    (a + b).display();
    (a - b).display();
    (a * b).display();
    (a / b).display();
    (a % b).display();
    return 0;
}
