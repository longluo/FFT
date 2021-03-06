//
// Created by longluo on 2022/5/18.
//

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const double PI = acos(-1.0);

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

    string toString() {
        return "(" + to_string(x) + "," + to_string(y) + "i)";
    }
};

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 *len 必须为 2 的幂
 */
void change(Complex y[], int len) {
    int i, j, k;
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}

/*
 * 做 FFT
 *len 必须是 2^k 形式
 *on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
    change(y, len);

    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }

    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i].x /= len;
        }
    }
}

void display(Complex *arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << " " << arr[i].toString();
    }

    cout << endl;
}

const int MAXN = 10005;
Complex x1[MAXN], x2[MAXN];
char str1[MAXN / 2], str2[MAXN / 2];
int sum[MAXN];

int main() {
    while (scanf("%s%s", str1, str2) == 2) {
        int len1 = strlen(str1);
        int len2 = strlen(str2);

        int len = 1;
        while (len < len1 * 2 || len < len2 * 2) {
            len *= 2;
        }

        for (int i = 0; i < len1; i++) {
            x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
        }
        for (int i = len1; i < len; i++) {
            x1[i] = Complex(0, 0);
        }

        for (int i = 0; i < len2; i++) {
            x2[i] = Complex(str2[len2 - 1 - i] - '0', 0);
        }
        for (int i = len2; i < len; i++) {
            x2[i] = Complex(0, 0);
        }

        cout << "Before FFT" << endl;
        display(x1, len);
        display(x2, len);

        fft(x1, len, 1);
        fft(x2, len, 1);

        cout << "After FFT" << endl;
        display(x1, len);
        display(x2, len);

        for (int i = 0; i < len; i++) {
            x1[i] = x1[i] * x2[i];
        }

        cout << "Times: " << endl;
        display(x1, len);

        // IFFT
        fft(x1, len, -1);

        cout << endl << "Result: " << endl;
        display(x1, len);

        cout << "Sum: " << endl;
        for (int i = 0; i < len; i++) {
            sum[i] = int(x1[i].x + 0.5);
            cout << sum[i] << " ";
        }

        for (int i = 0; i < len; i++) {
            sum[i + 1] += sum[i] / 10;
            sum[i] %= 10;
        }

        len = len1 + len2 - 1;
        while (sum[len] == 0 && len > 0) {
            len--;
        }

        cout << endl;
        cout << "Result is:" << endl;
        for (int i = len; i >= 0; i--) {
            printf("%c", sum[i] + '0');
        }

        cout << endl;
    }

    return 0;
}
