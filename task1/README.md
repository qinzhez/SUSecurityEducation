# Task A: SGX memory-protection Profiling

## Task Overview

The purpose of the task is to help you understand the basic structure of code for Intel SGX technology.

The first step, please learn some basic content about Intel SGX technology.


* [Intel SGX for Dummies](https://software.intel.com/en-us/blogs/2013/09/26/protecting-application-secrets-with-intel-sgx)

* [Intel SGX](https://software.intel.com/en-us/sgx)

To complete this task, you need to read code files in **/sample/App** and **/sample/Enclave**. After you organized the structure of the trusted and untrusted program in mind, you can complete the **sum.h** in **/sample/App/** to see differential performance for trusted and untrusted program.

## Task

We will try to use a function to compute the sum of an array of integers. Through the time differences you observed, you should be able to explain the result you found.

### Step 1
Read the program structure and calling hierarchy.

### Step 2
Open **/sample/App/sum.h**, you can find `bar()` and `call_sum()`.

You need to complete the existed `call_sum()` function to compute the sum of the list. Then, you simply invoke the `bar` to output your result to standard output. Save your code.

### Step 3
Add the header file **sum.h** to necessary source files.

### Step 4
Under the folder level of **task1**, use command `make` to compile and link files. Try to fixed the problems you have.

### Step 5
Once the program compiled, run `app`. You will see a menu. Follow instructions to enter your input. Record the result by using `script` or screenshot.

## Question

1. Why do you need to call `bar_print` instead of using `printf` or other common printing method?

1. Where does the program define the interface of trusted function? Please provide the fileName:#line.

1. Why does the program use trusted and untrusted interfaces to separate functions?

1. What difference did you observed about running time? Please explain the reason about the difference.

