//
// Created by longluo on 2022/5/17.
//

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    const double PI = acos(-1.0);  // PI = arccos(-1)

    void display(vector<complex<double>> num) {
        for (auto &cd : num) {
            cout << cd;
        }

        cout << endl;
    }

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
            a[i] = complex<double>(num1[len1 - 1 - i] - '0', 0);
        }

        for (int i = len2 - 1; i >= 0; i--) {
            b[i] = complex<double>(num2[len2 - 1 - i] - '0', 0);
        }

        cout << "Before FFT" << endl;
        display(a);
        display(b);

        vector<complex<double>> midA, midB;

        midA = FFT(a, false);
        midB = FFT(b, false);

        cout << "After FFT" << endl;
        display(midA);
        display(midB);

        vector<complex<double>> mid(n);
        for (int i = 0; i < n; i++) {
            mid[i] = midA[i] * midB[i];
        }

        cout << "Times:" << endl;
        display(mid);

        vector<complex<double>> result;
        result = FFT(mid, true);

        cout << "Result:" << endl;
        display(result);

        string ans;
        int carry = 0;
        for (int i = 0; i < result.size(); i++) {
            int sum = round(round(result[i].real()) / result.size()) + carry;
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
        cout << "Output: " << ans << endl;
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
    cout << num1 << " x " << num2 << "=" << result << endl;
}
