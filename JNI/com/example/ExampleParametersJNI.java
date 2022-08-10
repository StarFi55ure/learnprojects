package com.example;

class ExampleParametersJNI {

    static {
        System.loadLibrary("native");
    }

    public static void main (String[] args) {
        new HelloWorldJNI().sayHello();
    }

    private native void sayHello();
}
