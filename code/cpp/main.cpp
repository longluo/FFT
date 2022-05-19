#include <bits/stdc++.h>

#define sync ios::sync_with_stdio(false)

using namespace std;

const double PI = acos(-1.0);    // PI = arccos(-1)

/**
 * FFT 实现
 *
 * @param a
 * @param flag  1->FFT, flag == -1->IFFT
 * @return
 */
vector<complex<double>> FFT(vector<complex<double>> &a, int flag) {
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
    vector<complex<double>> ye = FFT(Pe, flag);
    vector<complex<double>> yo = FFT(Po, flag);

    // Combine
    vector<complex<double>> y(n);

    // Root of Units
    double ang = 2 * PI / n;
    complex<double> omega(cos(ang), sin(flag * ang)); // omega为第一个n次复根,
    complex<double> curRoot(1, 0);   // curr为第零0个n次复根, 即为 1

    for (int i = 0; i < n / 2; i++) {
        y[i] = ye[i] + curRoot * yo[i];  // 求出P(xi)
        y[i + n / 2] = ye[i] - curRoot * yo[i]; // 由单位复根的性质可知第k个根与第k + n/2个根互为相反数
        curRoot *= omega;   // cur * omega得到下一个复根
    }

    return y;  // 返回最终的系数
}

vector<complex<double>> read() {    //获取系数, 注意需要从右向左获取(从0次幂的系数开始)
    string num;
    cin >> num;
    vector<complex<double> > result;
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

int main() {
    sync;
    vector<complex<double>> num1 = read(), num2 = read(), tmp1, tmp2, mid, ans;
    solve(num1, num2);
    tmp1 = FFT(num1, 1), tmp2 = FFT(num2, 1);
    num1.clear();
    num2.clear();
    for (int i = 0; i < tmp1.size(); i++) {
        mid.push_back(tmp1[i] * tmp2[i]);
    }

    tmp1.clear();
    tmp2.clear();

    ans = FFT(mid, -1);
    bool Ans = false;
    int add = 0;
    string final;

    //进位处理
    for (int i = 0; i < ans.size(); i++) {
        int op = round(round(ans[i].real()) / ans.size()) + add;
        add = 0;
        if (op >= 10)
            add = op / 10;
        final += op % 10 + '0';
    }

    if (add > 0) {
        final += add % 10 + '0';
    }

    for (int i = final.size() - 1; i >= 0; i--) {
        if (final[i] != '0') {
            Ans = true;
        } else if (!Ans)
            continue;

        cout << final[i];
    }

    cout << '\n';
}
