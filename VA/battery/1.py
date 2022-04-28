from cmath import exp
from sqlite3 import DatabaseError
import matplotlib.pyplot as plt
import numpy as np
        
#电荷量
quantityOfElectricity=[]
quantityOfElectricity_2=[]
quantityOfElectricity_percent=[]
quantityOfElectricity_s=0
#能量
Energy=[]
Energy_2=[]
Energy_percent=[]
Energy_s=0
#电流
current=[]
#电压
voltage=[]
#实验时间
expTime=[]
Time=0



resistance=15.0

#读取数据
f=open('d:\\\\data.txt', 'r')
for line in f:
    currentline = line.split(",")
    for j in currentline:
        if j=="\n" :
            continue
        if(int(j)>4000):
            continue
        if(int(j)<500):
            continue
        voltage.append(int(j)/1000.0)
        Time=Time+1
        expTime.append(Time)

# print(expTime)


for data_i in voltage:
    current.append(data_i/resistance)
    quantityOfElectricity_s=quantityOfElectricity_s+(data_i/resistance)*60
    Energy_s=Energy_s+(data_i*data_i)/resistance*60
    quantityOfElectricity.append(quantityOfElectricity_s)
    Energy.append(Energy_s)

for data_i in quantityOfElectricity:
    quantityOfElectricity_2.append(quantityOfElectricity_s-data_i)
    quantityOfElectricity_percent.append((quantityOfElectricity_s-data_i)/quantityOfElectricity_s*100)

for data_i in Energy:
    Energy_2.append(Energy_s-data_i)
    Energy_percent.append((Energy_s-data_i)/Energy_s*100)




plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False   #用来正常显示负号


#U-t
plt.scatter(expTime,voltage,1)
plt.title("南孚电池放电曲线U-t图") #显示图表名称
plt.xlabel("x轴-时间(min)")    #x轴名称
plt.ylabel("y轴-电压(V)")    #y轴名称

plt.savefig(r'D:\\result\\Ut.jpg',dpi=400,bbox_inches = 'tight')
plt.show()

plt.cla()


#q-t
plt.scatter(expTime,quantityOfElectricity_2,1)
plt.title("南孚电池放电曲线q-t图") #显示图表名称
plt.xlabel("x轴-时间(min)")    #x轴名称
plt.ylabel("y轴-电量(C)")    #y轴名称
plt.savefig(r'D:\\result\\qt.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()



#q-U
plt.scatter(voltage,quantityOfElectricity_2,1)
plt.title("南孚电池放电曲线U-q图") #显示图表名称
plt.xlabel("x轴-电压(V)")    #x轴名称
plt.ylabel("y轴-电量(C)")    #y轴名称
plt.savefig(r'D:\\result\\qU.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()




#Qp-U
plt.scatter(voltage,quantityOfElectricity_percent,1)
plt.title("南孚电池放电曲线U-q图") #显示图表名称
plt.xlabel("x轴-电压(V)")    #x轴名称
plt.ylabel("y轴-百分比(%))")    #y轴名称
plt.savefig(r'D:\\result\\QpU.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()


#e-t
plt.scatter(expTime,Energy,1)
plt.title("南孚电池放电曲线E-t图") #显示图表名称
plt.xlabel("x轴-时间(min)")    #x轴名称
plt.ylabel("y轴-能量(J)")    #y轴名称
plt.savefig(r'D:\\result\\Et.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()

#E-U
plt.scatter(voltage,Energy_2,1)
plt.title("南孚电池放电曲线E-U图") #显示图表名称
plt.xlabel("x轴-电压(V)")    #x轴名称
plt.ylabel("y轴-能量(J)")    #y轴名称
plt.savefig(r'D:\\result\\EU.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()

#Ep-U
plt.scatter(voltage,Energy_percent,1)
plt.title("南孚电池放电曲线E-U图") #显示图表名称
plt.xlabel("x轴-电压(V)")    #x轴名称
plt.ylabel("y轴-能量百分比(%)")    #y轴名称
plt.savefig(r'D:\\result\\Ep-U.jpg',dpi=400,bbox_inches = 'tight')
plt.cla()

f.close()