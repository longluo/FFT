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

    static const int N = 256;

    Complex omega[N];
    Complex invert[N];

    int rev[N];

    void init(int n) {
        rev[0] = 0;

        for (int i = 0; i < n; i++) {
            double ang = 2 * PI * i / n;
            omega[i] = Complex(cos(ang), sin(ang));
            invert[i] = omega[i].conjugate();

            if (i > 0) {
                rev[i] = rev[i >> 1] >> 1;
                if (i & 1) {
                    rev[i] |= n >> 1;
                }
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
    void FFT(vector<Complex> &a, Complex *omega) {
        //第一个参数为一个多项式的系数, 以次数从小到大的顺序, 向量中每一项的实部为该项系数
        int n = a.size();

        // 如果当前多项式仅有常数项时直接返回多项式的值
        if (n == 1) {
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 2; len <= n; len *= 2) {
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < len / 2; j++) {
                    Complex u = a[i + j];
                    Complex v = omega[j * n / len] * a[i + j + len / 2];
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                }
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

        init(n);

        FFT(a, omega);
        FFT(b, omega);

        for (int i = 0; i < n; i++) {
            a[i] = a[i] * b[i];
        }

        FFT(a, invert);

        string ans;
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int sum = round(round(a[i].real()) / n) + carry;
            carry = sum / 10;
            ans += sum % 10 + '0';
        }

        if (carry > 0) {
            ans += carry % 10 + '0';
        }

        int idx = n - 1;
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
