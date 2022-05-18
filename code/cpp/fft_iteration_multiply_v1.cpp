#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    const double PI = acos(-1.0);    // PI = arccos(-1)

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
