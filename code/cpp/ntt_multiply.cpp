//
// Created by longluo on 2022/5/18.
//

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    static const long long MOD = 998244353;
    static const long long G = 3;
    static const int G_INV = 332748118;
    vector<int> rev;

public:
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

    void ntt(vector<long long> &a, bool invert = false) {
        int n = a.size();

        for (int i = 0; i < n; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            long long wlen = quickPower(invert ? G_INV : G, (MOD - 1) / len);

            for (int i = 0; i < n; i += len) {
                long long w = 1;
                for (int j = 0; j < len / 2; j++) {
                    long long u = a[i + j];
                    long long v = (w * a[i + j + len / 2]) % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len / 2] = (MOD + u - v) % MOD;
                    w = (w * wlen) % MOD;
                }
            }
        }

        if (invert) {
            long long inver = quickPower(n, MOD - 2);
            for (int i = 0; i < n; i++) {
                a[i] = (long long) a[i] * inver % MOD;
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
        int bit = 1;

        while ((n <<= 1) < (len1 + len2)) {
            ++bit;
        }

        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }

        vector<long long> a(n, 0), b(n, 0);

        for (int i = 0; i < len1; ++i) {
            a[i] = num1[len1 - 1 - i] - '0';
        }

        for (int i = 0; i < len2; ++i) {
            b[i] = num2[len2 - 1 - i] - '0';
        }

        ntt(a);
        ntt(b);

        for (int i = 0; i < n; i++) {
            a[i] = (a[i] * b[i]) % MOD;
        }

        ntt(a, true);

        string res;
        long long carry = 0;
        for (int i = 0; i < len1 + len2 - 1; ++i) {
            long long curr = a[i] + carry;
            res += curr % 10 + '0';
            carry = curr / 10;
        }

        while (carry) {
            res += carry % 10 + '0';
            carry /= 10;
        }

        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    cout << "Please Input 2 numbers: " << endl;

    string num1, num2;
    cin >> num1 >> num2;

    Solution s;
    string result = s.multiply(num1, num2);

    cout << "Result:" << result << endl;
}
