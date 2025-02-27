================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例是对高级定时器功能“六步PWM的产生”的演示，通过systick中断作为COM commutation
事件的触发源，实现（无刷电机的）换向
下表是换向步骤，比如第一步中的CH1和CH3N为1，即设置打开这两个通道的PWM输出。

Function descriptions:
This sample demonstrates advanced timer function 'six-step PWM generation',
systick interrupt as COM commutation event trigger source to achieve commutation
(brushless motor).
The following table shows the commutating steps. For example, CH1 and CH3N in 
the first step are set to 1, that mean the PWM output of these two channels is 
set to start
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
2. 刹车输入（PA06）接低电平；
3. 用示波器或逻辑分析仪接以上六个通道，可监测到上述描述波形；
4. 刹车输入（PA06）接高电平，触发刹车，可观测到上述波形没有了，并输出空闲电平（空
闲电平由寄存器配置决定）

Example execution steps:
1. compile and download the program to MCU and run it;
2. The brake input (PA06) is connected to a low level;
3. Connect the above six channels with an oscilloscope or logic analyzer,you can 
observed the above described waveform;
4. The brake input (PA06) is connected to a high level will trigger the brake, 
then above waveform can be observed to be absent, and the output pin output idle
level (Idle level is determined by register configuration)
================================================================================
注意事项：
PWM时序如下：
        第一步      第二步      第三步      第四步      第五步     第六步     
CH1      1           0           0           0           0          1          
CH1N     0           0           1           1           0          0          
CH2      0           0           0           1           1          0          
CH2N     1           1           0           0           0          0          
CH3      0           1           1           0           0          0          
CH3N     0           0           0           0           1          1          

CH1  (PA08)   |||||||_________________________________||||||||||||||_________________________________|||||||
CH1N (PA07)   _______________||||||||||||||||_______________________________||||||||||||||||________________
                                  
CH2  (PA09)   _______________________||||||||||||||||_______________________________||||||||||||||||________
CH2N (PB04)   |||||||||||||||________________________________|||||||||||||||________________________________
                                  
CH3  (PA10)   _______||||||||||||||||_______________________________||||||||||||||||________________________
CH3N (PB05)   ________________________________|||||||||||||||________________________________|||||||||||||||

Notes:
The PWM timing is as follows:
       Step 1      Step 2      Step 3      Step 4      Step 5     Step 6     
CH1      1           0           0           0           0          1          
CH1N     0           0           1           1           0          0          
CH2      0           0           0           1           1          0          
CH2N     1           1           0           0           0          0          
CH3      0           1           1           0           0          0          
CH3N     0           0           0           0           1          1          

CH1  (PA08)   |||||||_________________________________||||||||||||||_________________________________|||||||
CH1N (PA07)   _______________||||||||||||||||_______________________________||||||||||||||||________________
                                  
CH2  (PA09)   _______________________||||||||||||||||_______________________________||||||||||||||||________
CH2N (PB04)   |||||||||||||||________________________________|||||||||||||||________________________________
                                  
CH3  (PA10)   _______||||||||||||||||_______________________________||||||||||||||||________________________
CH3N (PB05)   ________________________________|||||||||||||||________________________________|||||||||||||||
================================================================================