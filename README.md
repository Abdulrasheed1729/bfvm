## bfvm 🧠

A simple Brainfuck virtual machine written in C++. This is inspired by [Thorsten Ball](https://thorstenball.com)'s article [here](https://thorstenball.com/blog/2017/01/04/a-virtual-brainfuck-machine-in-go/).

### Running 🚀 

To run and compile the program run the followig in your terminal:
If on Windows
```posh
clang++.exe main.cc -o bfvm.exe machine.cc compiler.cc -O3
```
Linux and Mac:
```posh
clang++ main.cc -o bfvm machine.cc compiler.cc -O3

# or
g++ main.cc -o bfvm machine.cc compiler.cc -O3
```

### Benchmacking 📈

Using the Mandelbrot program in the `mandelbrot` file I have the following result after running
```posh
Measure-Command -Expression {.\bfvm.exe .\mandelbrot}
```
on my Intel Core i3 (11th gen) with 16gb of RAM, running Windows 11 btw.

```posh
Days              : 0
Hours             : 0
Minutes           : 0
Seconds           : 7
Milliseconds      : 429
Ticks             : 74295321
TotalDays         : 8.59899548611111E-05
TotalHours        : 0.00206375891666667
TotalMinutes      : 0.123825535
TotalSeconds      : 7.4295321
TotalMilliseconds : 7429.5321
```

### Testing 🧪

The unit tests inside the `*_test.cc` file can be run with cmake using the following commands in order
```
# 1.
cmake -S . -B build -Wno-dev

# 2.

cmake --build build

# 3.

cd build && ctest
```
Well, if you are using Windows btw, just run the `run-test.ps1` script directly.
```
.\run-test.ps1
```

### Contribution 🫂

New contributions are welcome, and if possibly you can help improve the code.

### Rant 📢

Used to be a Linux user but now, I use Windows btw.