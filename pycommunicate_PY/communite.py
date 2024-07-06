import dash
from dash import dcc, html, Input, Output, State
import dash_bootstrap_components as dbc
import subprocess
"""
main file,包含UI,和对接收到的信息的处理。
"""
# 忽略的字符串列表
ignore = ["--------------------------", "发送", ""]
latest_message_index = 0
# 初始化 Dash 应用
app = dash.Dash(__name__, external_stylesheets=[dbc.themes.BOOTSTRAP])

# 定义应用的布局
app.layout = html.Div([
    dbc.Container([
        dbc.Row([
            dbc.Col([
                html.Div(id='output-box',
                         style={'whiteSpace': 'pre-line', 'border': '1px solid black', 'padding': '10px', 'height': '420px',
                                'overflowY': 'scroll', 'margin-top': '12px', 'backgroundColor': 'rgba(255, 255, 255, 0.5)'})
            ], width=12)
        ]),
        dbc.Row([
            dbc.Col([
                dbc.Input(id='input-box', type='text', placeholder='请输入数据...', style={'margin-top': '8px'}),
            ], width=10),  # 调整宽度为10
            dbc.Col([
                dbc.Button('发送', id='send-button', n_clicks=0, className='mt-2',
                           style={'width': '100%', 'margin-top': '2px'})
            ], width=2)  # 调整宽度为2
        ]),
        dcc.Interval(
            id='interval-component',
            interval=2 * 1000,  # 每2秒更新一次
            n_intervals=0
        )
    ])
], style={
    'backgroundImage': 'url("https://image.baidu.com/search/down?url=https://img3.doubanio.com/view/photo/l/public/p1933116042.webp")',
    'backgroundSize': 'cover',
    'backgroundPosition': 'center',
    'backgroundRepeat': 'no-repeat',
    'backgroundAttachment': 'fixed',
    'height': '100vh',
    'width': '100vw',
    'opacity': '0.5'
})

def check_output_from_Cpp(send_data, open_chuankou=1, close_chuankou=0):
    result = subprocess.run(
        [r'D:\program\stm32\cpp_hwnd\x64\Debug\stmCpp.exe', send_data, str(open_chuankou), str(close_chuankou)],
        capture_output=True,
        text=True,
        encoding='utf-8'
    )
    return result.stdout


# 全局变量，用于存储所有对话内容
conversation = []
last_output = ""  # 上次的输出


# 定义回调函数更新输出框
@app.callback(
    Output('output-box', 'children'),
    Input('send-button', 'n_clicks'),
    Input('interval-component', 'n_intervals'),
    State('input-box', 'value')
)
def update_output(n_clicks, n_intervals, value):
    global conversation, last_output,latest_message_index
    context = dash.callback_context

    if not context.triggered:
        return [html.Div(entry['text'], style={'textAlign': 'right', 'color': 'blue'}) if entry[
                                                                                              'type'] == 'send' else html.Div(
            entry['text'], style={'textAlign': 'left', 'color': 'black'}) for entry in conversation]

    trigger = context.triggered[0]['prop_id'].split('.')[0]

    if trigger == 'send-button' and value:
        # 记录发送的数据
        conversation.append({'type': 'send', 'text': value})
        # 调用 C++ 程序并获取输出
        output = check_output_from_Cpp(value)
        # 过滤输出
        filtered_output = [line for line in output.split('\n') if line and line not in ignore]
        filtered_output = filtered_output[1:]
        last_output = '\n'.join(filtered_output)  # 更新上次的输出
        conversation.extend([{'type': 'receive', 'text': line} for line in filtered_output[latest_message_index:]])
        latest_message_index = len(filtered_output)

    elif trigger == 'interval-component':
        output = check_output_from_Cpp("")
        filtered_output = [line for line in output.split('\n') if line and line not in ignore]
        filtered_output = filtered_output[1:]
        if '\n'.join(filtered_output) != last_output:
            conversation.extend([{'type': 'receive', 'text': line} for line in filtered_output[latest_message_index:]])
            latest_message_index = len(filtered_output)
            last_output = '\n'.join(filtered_output)  # 更新上次的输出

    # 格式化对话内容
    formatted_conversation = []
    for entry in conversation:
        if entry['type'] == 'send':
            formatted_conversation.append(html.Div(entry['text'], style={'textAlign': 'right', 'color': 'blue'}))
        else:
            formatted_conversation.append(html.Div(entry['text'], style={'textAlign': 'left', 'color': 'black'}))

    return formatted_conversation


# 运行应用
if __name__ == '__main__':
    check_output_from_Cpp("",1,0)
    print("打开串口")
    app.run_server(debug=True)
