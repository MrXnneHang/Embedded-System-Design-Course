import serial
import time

"""
写UI的时候方便调试建立了虚拟串口对，进行一个信息发送和读取。
串口调试助手开到COM2->COM1,即可接收到。
"""
# 配置串口参数
ser1 = serial.Serial('COM1', 115200, timeout=1)


# 发送数据到COM2
ser1.write(b'HelloHello  WORLD LLM[Send complete]\n')

# 关闭串口
ser1.close()
