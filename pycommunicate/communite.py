import subprocess
import time

def check_output(send_data):
    # 调用C++可执行文件，并传递参数
    result = subprocess.run([r'D:\program\stm32\cpp_hwnd\x64\Debug\stmCpp.exe', send_data], capture_output=True, text=True, encoding='utf-8')

    return result.stdout

def wait_for_update(old_message,show_waitting=False):
    while(True):
        if show_waitting:
            print("waiting for response...")
        new_message = generate_new_messgae()
        if new_message[-1] != old_message[-1]:
            return new_message
        else:
            time.sleep(0.5)




def response2messgae(response):
    messages = response.split("--------------------------")[:-1]
    new_message = []
    for i in messages:
        i = i.replace("\n","")
        if i not in ["发送","清除接收"]:
            new_message.append(i)
    return  new_message

def generate_new_messgae():
    messages = check_output("").split("--------------------------")[:-1]
    new_message = []
    for i in messages:
        i = i.replace("\n","")
        if i not in ["发送","清除接收"]:
            new_message.append(i)
    return  new_message

def find_diff_part(a, b):
    # 找到a和b中共同部分的长度
    common_length = 0
    min_length = min(len(a), len(b))

    for i in range(min_length):
        if a[i] != b[i]:
            break
        common_length += 1

    # 提取b中不同的部分
    diff_part = b[common_length:]
    return diff_part



def 待机模式(old_message,waitting=False):
        time.sleep(0.5)
        new_message = generate_new_messgae()
        if new_message[-1] != old_message[-1]:
            print(new_message[-1][len(old_message[-1]):])

        return new_message

def 对话模式(old_message,send_data,waitting=True):
    response = check_output(send_data)
    message = wait_for_update(old_message=old_message,show_waitting=waitting)
    return message

if __name__ == "__main__":
    old_message = ["", ""]
    message = []
    while True:
        变化 = 1
        保持不变的次数 = 5
        while 保持不变的次数:
            message = 待机模式(old_message)
            if message[-1] != old_message[-1] and 变化==1:
                变化-=1
                old_message = message
            else:

                保持不变的次数-=1
                time.sleep(0.3)
        old_message = message
        print(old_message)
        send_data = input("A:")
        对话模式(old_message, send_data)