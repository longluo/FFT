//
// Created by longluo on 2022/5/18.
//

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

void display(vector<long long> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

class Solution {

public:
    const long long G = 3;
    const long long G_INV = 332748118;
    const long long MOD = 998244353;

    vector<int> rev;

    void display(vector<long long> arr) {
        for (int i = 0; i < arr.size(); i++) {
            cout << arr[i] << " ";
        }

        cout << endl;
    }

    long long quickPower(long long a, long long b) {
        long long res = 1;

        while (b > 0) {
            if (b & 1) {
                res = (res * a) % MOD;
            }

            a = (a * a) % MOD;
            b >>= 1;
        }

        return res % MOD;
    }

    void ntt(vector<long long> &a, bool invert) {
        int n = a.size();

        if (n == 1) {
            return;
        }

        vector<long long> Pe(n / 2), Po(n / 2);

        for (int i = 0; 2 * i < n; i++) {
            Pe[i] = a[2 * i];
            Po[i] = a[2 * i + 1];
        }

        ntt(Pe, invert);
        ntt(Po, invert);

        long long wn = quickPower(invert ? G_INV : G, (MOD - 1) / n);
        long long w = 1;

        for (int i = 0; i < n / 2; i++) {
            a[i] = Pe[i] + w * Po[i] % MOD;
            a[i] = (a[i] % MOD + MOD) % MOD;
            a[i + n / 2] = Pe[i] - w * Po[i] % MOD;
            a[i + n / 2] = (a[i + n / 2] % MOD + MOD) % MOD;
            w = w * wn % MOD;
        }
    }

    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        int len1 = num1.size();
        int len2 = num2.size();

        int n = 1;

        while (n < (len1 + len2)) {
            n = n << 1;
        }

        vector<long long> a(n, 0), b(n, 0);

        for (int i = 0; i < len1; ++i) {
            a[i] = num1[len1 - 1 - i] - '0';
        }

        for (int i = 0; i < len2; ++i) {
            b[i] = num2[len2 - 1 - i] - '0';
        }

        cout << "Before FFT" << endl;
        display(a);
        display(b);

        ntt(a, false);
        ntt(b, false);

        cout << "After FFT" << endl;
        display(a);
        display(b);

        for (int i = 0; i < n; i++) {
            a[i] = (a[i] * b[i]) % MOD;
        }

        cout << "After Times:" << endl;
        display(a);

        ntt(a, true);

        cout << "After IFFT" << endl;
        display(a);

        string res;
        long long carry = 0;
        long long inver = quickPower(n, MOD - 2);

        for (int i = 0; i < n; i++) {
            a[i] = a[i] * inver % MOD;
        }

        cout << "Result:" << endl;
        display(a);

        for (int i = 0; i < n; i++) {
            long long sum = a[i] + carry;
            res += sum % 10 + '0';
            carry = sum / 10;
        }

        while (carry) {
            res += carry % 10 + '0';
            carry /= 10;
        }

        int idx = n - 1;
        while (idx >= 0 && res[idx] == '0') {
            idx--;
        }

        res = res.substr(0, idx + 1);
        reverse(res.begin(), res.end());
        return res;
    }
};

/*
123 456
Before FFT
3 2 1 0 0 0 0 0
6 5 4 0 0 0 0 0
After FFT
6 658473933 825076919 65787358 2 166602990 173167438 107380084
15 518064901 565325765 793466147 5 785754073 432918592 897447962
After Times:
90 11925151 784316648 497879635 10 130608434 213927693 357831189
After IFFT
144 216 224 104 32 0 0 0
Result:
18 27 28 13 4 0 0 0
Result:56088
 */
int main() {
    cout << "Please Input 2 numbers: " << endl;

    string num1, num2;
    cin >> num1 >> num2;

    Solution s;
    string result = s.multiply(num1, num2);

    cout << "Result:" << result << endl;
}


