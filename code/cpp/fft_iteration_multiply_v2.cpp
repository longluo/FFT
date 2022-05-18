#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    const double PI = acos(-1.0);    // PI = arccos(-1)

    struct Complex {
        double re, im;

        Complex(double _re = 0.0, double _im = 0.0) {
            re = _re;
            im = _im;
        }

        inline void real(const double &re) {
            this->re = re;
        }

        inline double real() {
            return re;
        }

        inline void imag(const double &im) {
            this->im = im;
        }

        inline double imag() {
            return im;
        }

        inline Complex operator-(const Complex &other) const {
            return Complex(re - other.re, im - other.im);
        }

        inline Complex operator+(const Complex &other) const {
            return Complex(re + other.re, im + other.im);
        }

        inline Complex operator*(const Complex &other) const {
            return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
        }

        inline void operator/(const double &div) {
            re /= div;
            im /= div;
        }

        inline void operator+=(const Complex &other) {
            this->re += other.re;
            this->im += other.im;
        }

        inline void operator-=(const Complex &other) {
            this->re -= other.re;
            this->im -= other.im;
        }

        inline void operator*=(const Complex &other) {
            *this = Complex(re * other.re - im * other.im, re * other.im + im * other.re);
        }

        inline Complex conjugate() {
            return Complex(re, -im);
        }
    };

    // 同样需要保证 len 是 2 的幂
    // 记 rev[i] 为 i 翻转后的值
    // time: O(n)
    void bitReverse(vector<Complex> &arr) {
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
    void FFT(vector<Complex> &a, bool invert) {
        //第一个参数为一个多项式的系数, 以次数从小到大的顺序, 向量中每一项的实部为该项系数
        int n = a.size();

        // 如果当前多项式仅有常数项时直接返回多项式的值
        if (n == 1) {
            return;
        }

        bitReverse(a);

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            Complex wlen(cos(ang), sin(ang));

            for (int i = 0; i < n; i += len) {
                Complex w(1, 0);
                for (int j = 0; j < len / 2; j++) {
                    Complex u = a[i + j];
                    Complex v = w * a[i + j + len / 2];
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (auto &cp : a) {
                cp.re /= n;
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

        vector<Complex> a(n);
        vector<Complex> b(n);

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

        string ans;
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int sum = floor(a[i].real() + 0.5) + carry;
            carry = sum / 10;
            ans += sum % 10 + '0';
        }

        if (carry > 0) {
            ans += carry % 10 + '0';
        }

        int idx = ans.size() - 1;
        while (ans[idx] == '0' && idx > 0) {
            idx--;
        }

        ans = ans.substr(0, idx + 1);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    string num1, num2;
    cin >> num1 >> num2;

    Solution s;
    string result = s.multiply(num1, num2);

    cout << "Result: " << num1 << " x " << num2 << "=" << result << endl;
}
