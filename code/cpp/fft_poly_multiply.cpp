//
// Created by longluo on 2022/5/17.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>

#define space putchar(' ')
#define enter putchar('\n')
using namespace std;
typedef long long ll;

template<class T>
void read(T &x) {
    char c;
    bool op = 0;
    while (c = getchar(), c < '0' || c > '9')
        if (c == '-') op = 1;
    x = c - '0';
    while (c = getchar(), c >= '0' && c <= '9')
        x = x * 10 + c - '0';
    if (op) x = -x;
}

template<class T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 1000005;
const double PI = acos(-1);
typedef complex<double> cp;

int len, ta[N], tb[N], res[N];
cp omg[N], inv[N];

void init(int n) {
    for (int i = 0; i < n; i++) {
        omg[i] = cp(cos(2 * PI * i / n), sin(2 * PI * i / n));
        inv[i] = conj(omg[i]);
    }
}

void fft(cp *a, int n, cp *omg) {
    int lim = 0;
    while ((1 << lim) < n) lim++;
    for (int i = 0; i < n; i++) {
        int t = 0;
        for (int j = 0; j < lim; j++)
            if (i >> j & 1) t |= 1 << (lim - j - 1);
        if (i < t) swap(a[i], a[t]);
    }
    for (int l = 2; l <= n; l *= 2) {
        int m = l / 2;
        for (cp *p = a; p != a + n; p += l)
            for (int i = 0; i < m; i++) {
                cp t = omg[n / l * i] * p[m + i];
                p[m + i] = p[i] - t;
                p[i] += t;
            }
    }
}

void multiply() {
    static cp a[N], b[N];
    for (int i = 0; i < len; i++)
        a[i].real(ta[i]), b[i].real(tb[i]);
    int n = 1;
    while (n < 2 * len) n *= 2;
    init(n);
    fft(a, n, omg);
    fft(b, n, omg);
    for (int i = 0; i < n; i++)a[i] *= b[i];
    fft(a, n, inv);
    for (int i = 0; i < n; i++)
        res[i] = floor(a[i].real() / n + 0.5);
}

int main() {

    read(len);
    for (int i = 0; i < len; i++)
        read(ta[i]), read(tb[i]);
    for (int i = 0, j = len - 1; i < j; i++, j--)
        swap(ta[i], ta[j]);
    multiply();
    for (int i = len - 1; i >= 0; i--)
        write(res[i]), enter;

    return 0;
}

