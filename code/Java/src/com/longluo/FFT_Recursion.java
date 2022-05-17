package com.longluo;

import java.util.Arrays;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * FFT Recursion Version
 */
public class FFT_Recursion {

    static class Complex {
        double x;
        double y;

        Complex(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public Complex plus(Complex other) {
            return new Complex(this.x + other.x, this.y + other.y);
        }

        public Complex minus(Complex other) {
            return new Complex(this.x - other.x, this.y - other.y);
        }

        public Complex times(Complex other) {
            double real = this.x * other.x - this.y * other.y;
            double imag = this.x * other.y + this.y * other.x;
            return new Complex(real, imag);
        }

        public Complex multiply(Complex other) {
            double real = this.x * other.x - this.y * other.y;
            double imag = this.x * other.y + this.y * other.x;
            return new Complex(real, imag);
        }

        public Complex scale(double alpha) {
            return new Complex(alpha * x, alpha * y);
        }

        public Complex conjugate() {
            return new Complex(x, -y);
        }

        public String toString() {
            if (y == 0) {
                return x + "";
            }

            if (x == 0) {
                return y + "i";
            }

            if (y < 0) {
                return x + " - " + (-y) + "i";
            }

            return x + " + " + y + "i";
        }
    }

    /**
     * Returns the FFT of the specified complex array.
     *
     * @param x the complex array
     * @return the FFT of the complex array {@code x}
     * @throws IllegalArgumentException if the length of {@code x} is not a power of 2
     */
    public static Complex[] FFT(Complex[] x) {
        int n = x.length;

        // base case
        if (n == 1) {
            return new Complex[]{x[0]};
        }

        if (n % 2 != 0) {
            throw new IllegalArgumentException("n is not a power of 2");
        }

        // fft of even terms
        Complex[] even = new Complex[n / 2];
        for (int k = 0; k < n / 2; k++) {
            even[k] = x[2 * k];
        }
        Complex[] q = FFT(even);

        // fft of odd terms
        Complex[] odd = even;  // reuse the array
        for (int k = 0; k < n / 2; k++) {
            odd[k] = x[2 * k + 1];
        }
        Complex[] r = FFT(odd);

        // combine
        Complex[] y = new Complex[n];
//        for (int k = 0; k < n / 2; k++) {
//            double kth = 2 * k * Math.PI / n;
//            Complex wk = new Complex(Math.cos(kth), Math.sin(kth));
//            y[k] = q[k].plus(wk.multiply(r[k]));
//            y[k + n / 2] = q[k].minus(wk.multiply(r[k]));
//        }

        for (int k = 0; k < n / 2; k++) {
            double kth = -2 * k * Math.PI / n;
            Complex wk = new Complex(Math.cos(kth), Math.sin(kth));
            y[k] = q[k].plus(wk.times(r[k]));
            y[k + n / 2] = q[k].minus(wk.times(r[k]));
        }

        return y;
    }

    /**
     * Returns the inverse FFT of the specified complex array.
     *
     * @param x the complex array
     * @return the inverse FFT of the complex array {@code x}
     * @throws IllegalArgumentException if the length of {@code x} is not a power of 2
     */
    public static Complex[] IFFT(Complex[] x) {
        int n = x.length;
        Complex[] y = new Complex[n];

        // take conjugate
        for (int i = 0; i < n; i++) {
            y[i] = x[i].conjugate();
        }

        // compute forward FFT
        y = FFT(y);

        // take conjugate again
        for (int i = 0; i < n; i++) {
            y[i] = y[i].conjugate();
        }

        // divide by n
        for (int i = 0; i < n; i++) {
            y[i] = y[i].scale(1.0 / n);
        }

        return y;
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
            A[len1 - 1 - i].x = num1.charAt(i) - '0';
        }

        for (int i = len2 - 1; i >= 0; i--) {
            B[len2 - 1 - i].x = num2.charAt(i) - '0';
        }

        System.out.println("num1 = ");
        display(A);
        System.out.println("num2 = ");
        display(B);

        Complex[] mid1 = FFT(A);
        Complex[] mid2 = FFT(B);

        System.out.println("After FFT: ");
        display(mid1);
        display(mid2);

        Complex[] mid = new Complex[n];
        for (int i = 0; i < n; i++) {
            mid[i] = mid1[i].multiply(mid2[i]);
        }

        System.out.println("After times:");
        display(mid);

        Complex[] res = IFFT(mid);

        System.out.println("Output: ");
        display(res);

        int[] sum = new int[n];
        int carry = 0;

        for (int i = 0; i < n; i++) {
            int op = (int) (Math.floor(res[i].x + 0.5)) + carry;
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

    public static void swap(int[] nums, int x, int y) {
        int temp = nums[x];
        nums[x] = nums[y];
        nums[y] = temp;
    }

    public static void display(Complex[] nums) {
        for (int i = 0; i < nums.length; i++) {
            System.out.print(" " + nums[i]);
        }

        System.out.println();
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
                String result = multiply(numbers[0], numbers[1]);
                System.out.println("Result: " + result + " = " + numbers[0] + " * " + numbers[1]);
            }
        } catch (IllegalStateException | NoSuchElementException e) {
            e.printStackTrace();
        }
    }
}
