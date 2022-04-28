#导入模块
import serial 
import matplotlib.pyplot as plt
import numpy as np

x=[]
y=[]
plt.ion()  # 开启交互模式
plt.subplots()
#xy轴
plt.xlim(-1, 1000)
plt.ylim(-1, 1000)
ax = plt.scatter(x, y)

try:
  #端口，GNU / Linux上的/ dev / ttyUSB0 等 或 Windows上的 COM3 等
  portx="COM4"
  #波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
  bps=9600
  #超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
  timex=5
  # 打开串口，并得到串口对象
  ser=serial.Serial(portx,bps,timeout=timex)
  print("串口详情参数：", ser)



  print(ser.port)#获取到当前打开的串口名
  print(ser.baudrate)#获取波特率


  while True:
         if ser.in_waiting:
             str=ser.read(ser.in_waiting ).decode("gbk")
             if(str=="exit"):#退出标志
                 break
             else:
                print("收到数据：",str)
                plt.clf()     # 清空画布
                plt.xlim(0, 7000)      # 因为清空了画布，所以要重新设置坐标轴的范围
                plt.ylim(0, 40)
                strlist = str.split('|')	# 用逗号分割str字符串，并保存到列表
                #print("\n",strlist[0])
                x.append(float(strlist[0]))
                y.append(float(strlist[1]))
                plt.scatter(x, y)
                plt.pause(0.2)
               
  print("---------------")
  ser.close()#关闭串口


except Exception as e:
    print("---异常---：",e)
