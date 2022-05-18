package com.longluo;

import java.util.Arrays;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * FFT Iteration
 */
public class FFT_Iteration_v1 {

    static class Solution {
        static class Complex {
            double re;
            double im;

            Complex(double re, double im) {
                this.re = re;
                this.im = im;
            }

            public Complex plus(Complex other) {
                return new Complex(this.re + other.re, this.im + other.im);
            }

            public Complex minus(Complex other) {
                return new Complex(this.re - other.re, this.im - other.im);
            }

            public Complex times(Complex other) {
                double real = this.re * other.re - this.im * other.im;
                double imag = this.re * other.im + this.im * other.re;
                return new Complex(real, imag);
            }

            public Complex scale(double alpha) {
                return new Complex(alpha * re, alpha * im);
            }

            public Complex conjugate() {
                return new Complex(re, -im);
            }

            public String toString() {
                return "(" + re + "," + im + ")";
            }
        }

        public static void swap(Complex[] arr, int i, int j) {
            Complex temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        public static void bitReverse(Complex[] arr, int[] rev) {
            int len = arr.length;

            rev[0] = 0;
            for (int i = 1; i < len; i++) {
                rev[i] = rev[i >> 1] >> 1;
                if ((i & 0x01) == 1) {
                    rev[i] |= len >> 1;
                }
            }

            for (int i = 0; i < len; ++i) {
                if (i < rev[i]) {
                    swap(arr, i, rev[i]);
                }
            }
        }

        public static void FFT(Complex[] x, boolean invert) {
            int n = x.length;

            if (n == 1) {
                return;
            }

            if (n % 2 != 0) {
                throw new IllegalArgumentException("n is not a power of 2");
            }

            int[] rev = new int[n];
            bitReverse(x, rev);

            for (int len = 2; len <= n; len <<= 1) {
                double ang = 2 * Math.PI / len * (invert ? -1 : 1);
                Complex wlen = new Complex(Math.cos(ang), Math.sin(ang));

                for (int i = 0; i < n; i += len) {
                    Complex w = new Complex(1, 0);
                    for (int j = 0; j < len / 2; j++) {
                        Complex u = x[i + j];
                        Complex v = w.times(x[i + j + len / 2]);
                        x[i + j] = u.plus(v);
                        x[i + j + len / 2] = u.minus(v);
                        w = w.times(wlen);
                    }
                }
            }

            if (invert) {
                for (int i = 0; i < n; i++) {
                    x[i].re /= n;
                }
            }
        }

        public static String multiply(String num1, String num2) {
            if ((num1.length() == 1 && Integer.parseInt(num1) == 0)
                    || (num2.length() == 1 && Integer.parseInt(num2) == 0)) {
                return "0";
            }

            int len1 = num1.length();
            int len2 = num2.length();

            int n = 1;
            while (n < len1 + len2) {
                n = n << 1;
            }

            Complex[] A = new Complex[n];
            Complex[] B = new Complex[n];

            Arrays.setAll(A, e -> new Complex(0, 0));
            Arrays.setAll(B, e -> new Complex(0, 0));

            for (int i = len1 - 1; i >= 0; i--) {
                A[len1 - 1 - i].re = num1.charAt(i) - '0';
            }
            for (int i = len2 - 1; i >= 0; i--) {
                B[len2 - 1 - i].re = num2.charAt(i) - '0';
            }

            FFT(A, false);
            FFT(B, false);

            for (int i = 0; i < n; i++) {
                A[i] = A[i].times(B[i]);
            }

            FFT(A, true);

            int[] sum = new int[n];
            int carry = 0;
            for (int i = 0; i < n; i++) {
                int op = (int) (A[i].re + 0.5) + carry;
                carry = op / 10;
                sum[i] = op % 10;
            }

            int idx = n - 1;
            while (sum[idx] == 0 && idx > 0) {
                idx--;
            }

            StringBuilder ans = new StringBuilder();
            for (int i = idx; i >= 0; i--) {
                ans.append(sum[i]);
            }

            return ans.toString();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            while (true) {
                System.out.println("Please Input 2 numbers: ");
                String[] numbers = sc.nextLine().split("\\s+");
                if (numbers.length > 2) {
                    System.out.println("Error Input!");
                    continue;
                }

                Solution s = new Solution();
                String result = s.multiply(numbers[0], numbers[1]);
                System.out.println("Result: " + result + " = " + numbers[0] + " * " + numbers[1]);
            }
        } catch (IllegalStateException | NoSuchElementException e) {
            e.printStackTrace();
        }
    }
}
