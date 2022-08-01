#include <iostream>

#include "com_example_HelloWorldJNI.h"

JNIEXPORT void JNICALL Java_com_example_HelloWorldJNI_sayHello(JNIEnv* env, jobject thisObject) {
    std::cout << "Hello from C++11" << std::endl;
}

