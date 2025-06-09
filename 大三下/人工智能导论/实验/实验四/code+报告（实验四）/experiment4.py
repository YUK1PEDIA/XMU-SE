import numpy as np
import matplotlib.pyplot as plt

# 目标函数
def f(x):
    return 11 * np.sin(6 * x) + 7 * np.cos(5 * x)

# 模拟退火算法
def simulated_annealing(func, bounds, max_iter=1000, T0=100, K=0.95, T_end=1e-8):
    low, high = bounds
    x_current = np.random.uniform(low, high)  # 初始解
    x_best = x_current
    f_current = func(x_current)
    f_best = f_current
    
    best_history = []  # 记录最优解历史
    temp_history = []  # 记录温度历史
    
    for iter in range(max_iter):
        if T0 < T_end:
            break
        temp_history.append(T0)
        
        for _ in range(100):  # 每个温度下的迭代次数
            # 生成新解（随机扰动）
            step = 0.1 * T0  # 步长随温度衰减
            x_new = x_current + np.random.uniform(-step, step)
            x_new = np.clip(x_new, low, high)  # 确保在区间内
            
            f_new = func(x_new)
            delta_f = f_new - f_current
            
            # Metropolis准则
            if delta_f < 0 or np.random.rand() < np.exp(-delta_f / T0):
                x_current = x_new
                f_current = f_new
                
                # 更新最优解
                if f_current < f_best:
                    x_best = x_current
                    f_best = f_current
        
        best_history.append(f_best)
        T0 *= K  # 温度衰减
    
    return x_best, f_best, best_history, temp_history

# 运行算法
bounds = (0, 2 * np.pi)
x_opt, f_opt, best_history, temp_history = simulated_annealing(f, bounds)

# 结果可视化
x = np.linspace(bounds[0], bounds[1], 1000)
plt.figure(figsize=(10, 6))

# 绘制函数曲线
plt.subplot(2, 1, 1)
plt.plot(x, f(x), label='目标函数')
plt.scatter(x_opt, f_opt, color='red', s=100, label=f'最优解：x={x_opt:.4f}, f(x)={f_opt:.4f}')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('目标函数曲线与最优解')
plt.legend()

# 绘制收敛过程
plt.subplot(2, 1, 2)
plt.plot(temp_history, best_history, label='温度-最优解收敛曲线')
plt.xlabel('温度 T')
plt.ylabel('最优解 f(x)')
plt.title('模拟退火收敛过程')
plt.legend()

plt.tight_layout()
plt.show()

print(f"最优解位置：x = {x_opt:.4f}")
print(f"最小值：f(x) = {f_opt:.4f}")