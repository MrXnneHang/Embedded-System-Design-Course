import subprocess

# 调用C++可执行文件，并传递参数
result = subprocess.run([r'D:\program\stm32\cpp_hwnd\x64\Debug\stmCpp.exe', '156'], capture_output=True, text=True, encoding='utf-8')

# 获取输出
print(result.stdout)  # 正确处理并显示UTF-8编码的输出
