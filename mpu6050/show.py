
# 导入通信的模块
import serial

# 创建串口通信
ser = serial.Serial('com4', 9600, timeout=0.5)


# 不断搜索是否有信息传入
while 1:
    # 读取串口的信息
    val = ser.readline().decode('utf-8')
    #print(val)
    if(len(val)==0):
        continue
    # 以逗号来分割传入的数据
    parsed = val.split(',')
    # 去除末尾的数据
    parsed = [ x.rstrip() for x in parsed]
    # 把数据转化为数字类型
    parsed = [ eval(x) for x in parsed]
    print(parsed)
