//
// Created by longluo on 2022/5/17.
//

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    const double PI = acos(-1.0);  // PI = arccos(-1)

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

        inline void operator*=(const Complex &other) {
            *this = Complex(re * other.re - im * other.im, re * other.im + im * other.re);
        }

        inline void operator+=(const Complex &other) {
            this->re += other.re;
            this->im += other.im;
        }

        inline Complex conjugate() {
            return Complex(re, -im);
        }
    };

    /**
     * FFT Recursion 实现
     *
     * @param a
     * @param invert true means IFFT, else FFT
     * @return im
     */
    vector<Complex> FFT(vector<Complex> &a, bool invert) {
        //第一个参数为一个多项式的系数, 以次数从小到大的顺序, 向量中每一项的实部为该项系数
        int n = a.size();

        // 如果当前多项式仅有常数项时直接返回多项式的值
        if (n == 1) {
            return a;
        }

        vector<Complex> Pe(n / 2), Po(n / 2); // 文中的Pe与Po的系数表示法

        for (int i = 0; 2 * i < n; i++) {
            Pe[i] = a[2 * i];
            Po[i] = a[2 * i + 1];
        }

        // Divide 分治
        // 递归求 ye = Pe(xi), yo = Po(xi)
        vector<Complex> ye = FFT(Pe, invert);
        vector<Complex> yo = FFT(Po, invert);

        // Combine
        vector<Complex> y(n);

        // Root of Units
        double ang = 2 * PI / n * (invert ? -1 : 1);
        Complex wn(cos(ang), sin(ang)); // wn为第1个n次复根,
        Complex w(1, 0);   // w为第零0个n次复根, 即为 1

        for (int i = 0; i < n / 2; i++) {
            y[i] = ye[i] + w * yo[i];  // 求出P(xi)
            y[i + n / 2] = ye[i] - w * yo[i]; // 由单位复根的性质可知第k个根与第k + n/2个根互为相反数
            w = w * wn;  // w * wn 得到下一个复根
        }

        return y;  // 返回最终的系数
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
            a[i] = Complex(num1[len1 - 1 - i] - '0', 0);
        }

        for (int i = len2 - 1; i >= 0; i--) {
            b[i] = Complex(num2[len2 - 1 - i] - '0', 0);
        }

        a = FFT(a, false);
        b = FFT(b, false);

        for (int i = 0; i < n; i++) {
            a[i] = a[i] * b[i];
        }

        a = FFT(a, true);

        string ans;
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int sum = round(round(a[i].re) / n) + carry;
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
    cout << "Please Input 2 Numbers:" << endl;
    string num1, num2;
    cin >> num1 >> num2;

    Solution s;
    string result = s.multiply(num1, num2);

    cout << "Result is:" << endl;
    cout << num1 << " re " << num2 << "=" << result << endl;
}
