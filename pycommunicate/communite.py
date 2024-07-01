import win32gui
import win32con
import win32api
import ctypes


def print_window_info(hwnd):
    # 获取窗口类名
    class_name = win32gui.GetClassName(hwnd)

    # 获取窗口标题
    window_text = win32gui.GetWindowText(hwnd)

    # 获取窗口样式
    style = win32api.GetWindowLong(hwnd, win32con.GWL_STYLE)

    # 打印信息
    print(f"窗口句柄: {hwnd}")
    print(f"类名: {class_name}")
    print(f"标题: {window_text}")
    print(f"样式: {hex(style)}")
    print("--------------------------")


def find_window_by_title(title):
    hwnd = win32gui.FindWindow(None, title)
    if hwnd == 0:
        print("未找到窗口")
        return None
    print_window_info(hwnd)
    return hwnd


def enum_child_windows(hwnd):
    child_windows = []

    def callback(hwnd, lParam):
        child_windows.append(hwnd)
        return True

    win32gui.EnumChildWindows(hwnd, callback, None)
    return child_windows


def get_window_text(hwnd):
    length = win32gui.SendMessage(hwnd, win32con.WM_GETTEXTLENGTH) + 1
    buffer = ctypes.create_unicode_buffer(length)
    win32gui.SendMessage(hwnd, win32con.WM_GETTEXT, length, buffer)
    return buffer.value


def print_all_child_windows_info(hwnd):
    child_windows = enum_child_windows(hwnd)
    for child_hwnd in child_windows:
        print_window_info(child_hwnd)


if __name__ == "__main__":
    title = "正点原子串口调试助手 V2.8"
    hwndParent = find_window_by_title(title)

    if hwndParent:
        print("父窗口相关信息：")
        print_window_info(hwndParent)

        print("子窗口相关信息：")
        child_windows = enum_child_windows(hwndParent)

        for child_hwnd in child_windows:
            print_window_info(child_hwnd)
            # 获取子窗口内容
            text = get_window_text(child_hwnd)
            print(f"窗口内容: {text}")
