# 编译与使用

使用Qt 6.9.2 MinGW 64-bit套件打开Calculator.pro。在Qt Creator中选择正确套件后构建并运行；calculator.ui可在设计模式或独立Qt Designer中编辑。

命令行构建（先将Qt bin和MinGW bin加入当前终端PATH）：

```powershell
mkdir build
cd build
qmake ../Calculator.pro
mingw32-make -j4
./release/Calculator.exe
```

计算逻辑测试使用tests/engine_tests.pro；界面测试使用tests/ui_tests.pro。在不同构建目录中分别执行qmake和mingw32-make，然后运行对应release下的测试程序。

键盘支持0～9、.、+、-、*、/、=、Enter、Backspace。Esc、Delete和C清除。运算采用即时连续求值，2+3*4=20；没有一元负号输入，负数可以由减法得到；科学计数法结果不支持逐字符退格；单个输入最多16个字符。上述行为不影响实验要求的四则运算功能。

Windows独立运行包中的Calculator.exe需要与同目录Qt DLL和platforms子目录一起保留，不能只复制exe。

测试视频来自tests/demo.cpp驱动的真实窗口连续录屏，鼠标事件通过QtTest::mouseClick发送，键盘通过QtTest::keyClicks发送，已在画面中标注自动化演示。视频无语音，有中文操作说明。
