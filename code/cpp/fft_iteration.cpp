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

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change(vector<complex<double>> &y, int len) {
    int k;
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) {
            swap(y[i], y[j]);
        }

        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }

        if (j < k) {
            j += k;
        }
    }
}

// 同样需要保证 len 是 2 的幂
// 记 rev[i] 为 i 翻转后的值
// time: O(n)
void bitReverse(vector<complex<double>> &arr) {
    int len = arr.size();

    vector<int> rev(len);
    rev[0] = 0;

    for (int i = 1; i < len; i++) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) {
            rev[i] |= len >> 1;
        }
    }

    for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {
            swap(arr[i], arr[rev[i]]);
        }
    }
}

/**
 * FFT Iteration 实现
 *
 * @param a
 * @param invert true means IFFT, else FFT
 * @return y
 */
void FFT(vector<complex<double>> &a, bool invert) {
    //第一个参数为一个多项式的系数, 以次数从小到大的顺序, 向量中每一项的实部为该项系数
    int n = a.size();

    // 如果当前多项式仅有常数项时直接返回多项式的值
    if (n == 1) {
        return;
    }

    bitReverse(a);

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));

        for (int i = 0; i < n; i += len) {
            complex<double> w(1, 0);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = w * a[i + j + len / 2];
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
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

    solve(num1, num2);

    cout << "Input:" << endl;
    cout << "num1 = ";
    display(num1);
    cout << "num2 = ";
    display(num2);

    FFT(num1, false);
    FFT(num2, false);

    for (int i = 0; i < num1.size(); i++) {
       num1[i] *= num2[i];
    }

    cout << "Muplty num1 = ";
    display(num1);

    FFT(num1, true);

    bool Ans = false;
    int add = 0;
    string final;

    cout << "Output: ";
    display(num1);

    for (int i = 0; i < num1.size(); i++) {
        cout << "   Before: " << round(num1[i].real()) << " After: " << round(round(num1[i].real()) / num1.size());
    }

    cout << endl;

    //进位处理
    for (int i = 0; i < num1.size(); i++) {
        int op = round(round(num1[i].real()) / num1.size()) + add;
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
