import serial
import time

# 配置串口参数
ser1 = serial.Serial('COM1', 115200, timeout=1)


# 发送数据到COM2
ser1.write(b'Hello from COM1!\n')
time.sleep(1)  # 等待数据发送

# 关闭串口
ser1.close()
