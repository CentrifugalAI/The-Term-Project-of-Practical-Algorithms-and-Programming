import math
import random
import math
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

sns.set_style('darkgrid')
#plt.rcParams['figure , figsize'] = (12, 8)

transfer_matrix = np.array(
    [[0.4, 0.6], [0.5, 0.5]], dtype='float32')
start_matrix = np.array([[1, 0]], dtype='float32')

value1 = []
value2 = []

for i in range(30):
    start_matrix = np.dot(start_matrix, transfer_matrix)
    value1.append(start_matrix[0][0])
    value2.append(start_matrix[0][1])
# print(start_matrix)

# 进行可视化
x = np.arange(30)
plt.plot(x, value1, label='chooseA')
plt.plot(x, value2, label='chooseB')
plt.legend()
plt.show()
