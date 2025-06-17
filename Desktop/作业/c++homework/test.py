import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 创建网格
x = np.linspace(0, 3, 100)
y = np.linspace(0, 3, 100)
X, Y = np.meshgrid(x, y)

# 定义凹区域和函数
def f(x, y):
    return np.where((x > 1) & (x < 2) & (y > 1), np.nan,  # 挖掉中间部分
                  np.where(x < 1.5, Y, Y + 1))            # 左右不同定义

Z = f(X, Y)

# 3D绘图
fig = plt.figure(figsize=(12, 6))
ax = fig.add_subplot(111, projection='3d')

# 绘制表面
surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8, 
                      linewidth=0, antialiased=True)

# 标记区域
ax.text(0.5, 1.5, 1.5, "f(x,y)=y", color='red', fontsize=10)
ax.text(2.5, 1.5, 2.5, "f(x,y)=y+1", color='red', fontsize=10)

# 设置观察角度
ax.view_init(elev=30, azim=-45)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x,y)')
ax.set_title("二元函数在凹区域上的三维表现", fontsize=14)

plt.tight_layout()
plt.show()
