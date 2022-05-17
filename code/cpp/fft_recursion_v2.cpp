//
// Created by longluo on 2022/5/17.
//

#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);    // PI = arccos(-1)

// Complex Number
struct Complex {
    double x, y;

    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
    }

    Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
    }

    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }

    Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

/**
 * FFT Recursion 实现
 *
 * @param a
 * @param invert true means IFFT, else FFT
 * @return y
 */
vector<complex<double>> FFT(vector<complex<double>> &a, bool invert) {
    //第一个参数为一个多项式的系数, 以次数从小到大的顺序, 向量中每一项的实部为该项系数
    int n = a.size();

    // 如果当前多项式仅有常数项时直接返回多项式的值
    if (n == 1) {
        return a;
    }

    vector<complex<double>> Pe(n / 2), Po(n / 2); // 文中的Pe与Po的系数表示法

    for (int i = 0; 2 * i < n; i++) {
        Pe[i] = a[2 * i];
        Po[i] = a[2 * i + 1];
    }

    // Divide 分治
    // 递归求 ye = Pe(xi), yo = Po(xi)
    vector<complex<double>> ye = FFT(Pe, invert);
    vector<complex<double>> yo = FFT(Po, invert);

    // Combine
    vector<complex<double>> y(n);

    // Root of Units
    double ang = 2 * PI / n * (invert ? -1 : 1);
    complex<double> wn(cos(ang), sin(ang)); // wn为第1个n次复根,
    complex<double> w(1, 0);   // w为第零0个n次复根, 即为 1

    for (int i = 0; i < n / 2; i++) {
        y[i] = ye[i] + w * yo[i];  // 求出P(xi)
        y[i + n / 2] = ye[i] - w * yo[i]; // 由单位复根的性质可知第k个根与第k + n/2个根互为相反数
        w *= wn;  // w * wn 得到下一个复根
    }

    // IFFT最终结果需要除以 n ，其中 n 为不小于原多项式阶+1的最小2的整数次幂
//    if (invert) {
//        for (auto &cd : y) {
//            cd /= n;
//        }
//    }

    return y;  // 返回最终的系数
}

//获取系数, 注意需要从右向左获取(从0次幂的系数开始)
vector<complex<double>> read() {
    string num;
    cin >> num;
    vector<complex<double>> result;
    for (int i = num.size() - 1; i >= 0; i--) {
        complex<double> tmp(num[i] - '0', 0);
        result.push_back(tmp);
    }

    return result;
}

// 多项式系数表达式的修饰
void solve(vector<complex<double>> &a, vector<complex<double>> &b) {
    complex<double> tmp(0, 0);
    int sum = a.size() + b.size();

    while (a.size() < sum) {
        a.push_back(tmp);
    }

    while (b.size() < sum) {
        b.push_back(tmp);
    }

    //如果两式的阶不同, 先补齐
    int temp = 1;
    while (temp < a.size()) {
        temp <<= 1;
    }

    //获取不小于n的最小2的整数次幂
    while (a.size() < temp) {
        a.push_back(tmp);
        b.push_back(tmp);
    }

    //补齐
}

void display(vector<complex<double>> num) {
    for (auto &cd : num) {
        cout << cd;
    }

    cout << endl;
}

int main() {
    vector<complex<double>> num1, num2;

    num1 = read();
    num2 = read();

    vector<complex<double>> tmp1, tmp2, mid, ans;
    solve(num1, num2);

    cout << "Input: " << endl;
    cout << "num1 = ";
    display(num1);
    cout << "num2 = ";
    display(num2);

    tmp1 = FFT(num1, false);
    tmp2 = FFT(num2, false);

    num1.clear();
    num2.clear();

    for (int i = 0; i < tmp1.size(); i++) {
        mid.push_back(tmp1[i] * tmp2[i]);
    }

    cout << "mid = ";
    display(mid);

    tmp1.clear();
    tmp2.clear();

    ans = FFT(mid, true);
    bool Ans = false;
    int add = 0;
    string final;

    cout << "Output: ";
    display(ans);

    //进位处理
    for (int i = 0; i < ans.size(); i++) {
        int op = round(round(ans[i].real()) / ans.size()) + add;
        add = 0;
        if (op >= 10) {
            add = op / 10;
        }

        final += op % 10 + '0';
    }

    if (add > 0) {
        final += add % 10 + '0';
    }

    cout << "Result is: " << endl;

    for (int i = final.size() - 1; i >= 0; i--) {
        if (final[i] != '0') {
            Ans = true;
        } else if (!Ans) {
            continue;
        }

        cout << final[i];
    }

    cout << '\n';
}
