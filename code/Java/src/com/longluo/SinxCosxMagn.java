package com.longluo;

public class SinxCosxMagn {

    public static void main(String[] args) {
        for (int i = 1; i <= 20; i++) {
            double a = i;
            double b = Math.sqrt(250 - a * a);
            System.out.println("a = " + a + ", b = " + b);
        }
    }
}
