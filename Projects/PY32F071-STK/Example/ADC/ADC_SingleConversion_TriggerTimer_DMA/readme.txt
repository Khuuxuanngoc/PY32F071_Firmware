================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的多通道DMA传输的功能。

Function descriptions:
This example demonstrates the functionality of multi-channel DMA transmission
in ADC.
================================================================================
测试环境：
测试用板：PY32F071_STK
MDK版本： 5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F071_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译并下载程序；
2. 串口每隔1s打印一次通道4/5/6/7的DR值；

Example execution steps:
1. Compile and download the program;
2. The serial port prints the DR values of channel 4/5/6/7 every 1 second.
================================================================================
注意事项：
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND

Notes:
Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:

STK board USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND -->GND
================================================================================