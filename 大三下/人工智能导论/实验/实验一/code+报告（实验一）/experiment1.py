import heapq

# 目标状态（0代表空格）
GOAL = [
    [1, 2, 3],
    [8, 0, 4],
    [7, 6, 5]
]

class Node:
    def __init__(self, state, parent=None, g=0):
        self.state = state  # 当前状态（二维列表）
        self.parent = parent  # 父节点
        self.g = g  # 已走步数（g(n)）
        self.h = self.calculate_h()  # 启发式函数值（h(n)）
        self.f = self.g + self.h  # 估价函数值（f(n)）

    def calculate_h(self):
        """计算曼哈顿距离之和（h(n)）"""
        h = 0
        for i in range(3):
            for j in range(3):
                num = self.state[i][j]
                if num == 0:
                    continue
                # 目标位置
                goal_i, goal_j = divmod(num-1, 3)
                h += abs(i - goal_i) + abs(j - goal_j)
        return h

    def generate_children(self):
        """生成子节点（空格左、上、右、下移动）"""
        children = []
        # 找到空格位置
        for i in range(3):
            for j in range(3):
                if self.state[i][j] == 0:
                    si, sj = i, j
                    break
            else:
                continue
            break
        # 移动方向（左、上、右、下）
        directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
        for di, dj in directions:
            ni, nj = si + di, sj + dj
            if 0 <= ni < 3 and 0 <= nj < 3:
                # 复制状态并交换
                new_state = [row.copy() for row in self.state]
                new_state[si][sj], new_state[ni][nj] = new_state[ni][nj], new_state[si][sj]
                children.append(Node(new_state, self, self.g + 1))
        return children

    def get_path(self):
        """回溯路径"""
        path = []
        current = self
        while current:
            path.append(current.state)
            current = current.parent
        return reversed(path)

def a_star(initial_state):
    """A*算法主函数"""
    initial_node = Node(initial_state)
    open_heap = []
    heapq.heappush(open_heap, (initial_node.f, id(initial_node), initial_node))
    closed = set()

    while open_heap:
        current_f, _, current_node = heapq.heappop(open_heap)
        state_tuple = tuple(tuple(row) for row in current_node.state)
        if state_tuple in closed:
            continue
        closed.add(state_tuple)
        # 检查是否为目标状态
        if current_node.state == GOAL:
            return current_node.get_path()
        # 生成子节点
        for child in current_node.generate_children():
            child_state = tuple(tuple(row) for row in child.state)
            if child_state not in closed:
                heapq.heappush(open_heap, (child.f, id(child), child))
    return None  # 无解

# 初始状态（注意空格用0表示）
INITIAL = [
    [2, 8, 3],
    [1, 6, 4],
    [7, 0, 5]
]

if __name__ == "__main__":
    path = a_star(INITIAL)
    if path:
        print("找到路径，共{}步：".format(len(list(path))-1))
        for i, state in enumerate(path):
            print(f"步骤{i}:")
            for row in state:
                print(row)
            print()
    else:
        print("无解")