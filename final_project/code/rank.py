import math
import random
import math
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

sns.set_style('darkgrid')

# 假设有A，B，C，D，E五个网站
n = 5
transfer_matrix = np.array(
    [[0.2, 0.2, 0.2, 0.2, 0.2], [0.333, 0, 0.333, 0.333, 0], [0, 0.5, 0, 0.5, 0], [0, 0, 1, 0, 0], [0, 0, 1, 0, 0]], dtype='float32')
start_matrix = np.array([[1, 0, 0, 0, 0]], dtype='float32')  # 从A页面开始浏览

unmodified_transfer_matrix = transfer_matrix

# 设置阻尼系数并利用阻尼系数对转换矩阵进行修正
d = 0.85
for i in range(5):
    for j in range(5):
        transfer_matrix[i][j] *= d
        transfer_matrix[i][j] += (1 - d) * (1 / n)

unmodified_value1 = []
unmodified_value2 = []
unmodified_value3 = []
unmodified_value4 = []
unmodified_value5 = []


value1 = []
value2 = []
value3 = []
value4 = []
value5 = []

for i in range(30):
    start_matrix = np.dot(start_matrix, transfer_matrix)
    value1.append(start_matrix[0][0])
    value2.append(start_matrix[0][1])
    value3.append(start_matrix[0][2])
    value4.append(start_matrix[0][3])
    value5.append(start_matrix[0][4])
    unmodified_value1.append(start_matrix[0][0])
    unmodified_value2.append(start_matrix[0][1])
    unmodified_value3.append(start_matrix[0][2])
    unmodified_value4.append(start_matrix[0][3])
    unmodified_value5.append(start_matrix[0][4])

# 进行可视化
x = np.arange(30)

plt.plot(x, unmodified_value1, label='unmodified_Apage')
plt.plot(x, unmodified_value2, label='unmodified_Bpage')
plt.plot(x, unmodified_value3, label='unmodified_Cpage')
plt.plot(x, unmodified_value4, label='unmodified_Dpage')
plt.plot(x, unmodified_value5, label='unmodified_Epage')
plt.legend()
plt.show()

plt.plot(x, value1, label='Apage')
plt.plot(x, value2, label='Bpage')
plt.plot(x, value3, label='Cpage')
plt.plot(x, value4, label='Dpage')
plt.plot(x, value5, label='Epage')
plt.legend()
plt.show()
