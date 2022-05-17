#include <bits/stdc++.h>

using namespace std;

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

const double PI = acos(-1.0);    // PI = arccos(-1)

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

    if (invert) {
        for (auto &x : a) {
            x /= n;
        }
    }
}

string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    int len1 = num1.size();
    int len2 = num2.size();

    int n = 1;
    while (n < len1 + len2) {
        n = n << 1;
    }

    vector<complex<double>> a(n);
    vector<complex<double>> b(n);

    for (int i = len1 - 1; i >= 0; i--) {
        a[i].real((num1[len1 - 1 - i] - '0'));
    }

    for (int i = len2 - 1; i >= 0; i--) {
        b[i].real((num2[len2 - 1 - i] - '0'));
    }

    FFT(a, false);
    FFT(b, false);

    for (int i = 0; i < n; i++) {
        a[i] = a[i] * b[i];
    }

    FFT(a, true);

    vector<int> res(n);
    int carry = 0;
    for (int i = 0; i < n; i++) {
        int sum = floor(a[i].real() + 0.5) + carry;
        carry = sum / 10;
        res[i] = sum % 10;
    }

    int idx = n - 1;
    while (res[idx] == 0 && idx > 0) {
        idx--;
    }

    string ans = "";
    for (int i = idx; i >= 0; i--) {
        ans += res[i] + '0';
    }

    return ans;
}

int main() {
    string num1, num2;
    cin >> num1 >> num2;

    cout << num1 << " x " << num2 << "=" << multiply(num1, num2) << endl;
}
