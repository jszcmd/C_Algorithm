from typing import List

class Solution:
    MAXN = 401
    queue = [''] * MAXN             # 使用数组模拟队列，提前开辟空间
    l = r = 0                       # l: 队头指针, r: 队尾指针
    adjList = [[] for _ in range(26)] # 邻接表，下标0->'a', 1->'b'... 存放包含对应字母的贴纸
    visited = set()                 # 记录访问过的 target 状态，防止重复计算

    def minStickers(self, stickers: List[str], target: str) -> int:
        
        # --- 初始化阶段 ---
        self.adjList = [[] for _ in range(26)] # 每次调用需清空邻接表，防止数据残留
        self.visited.clear()                   # 清空访问记录

        # --- 预处理贴纸 ---
        for str_ in stickers:
            s = "".join(sorted(str_))          # 关键：对贴纸排序，配合后续双指针减法
            for i in range(len(s)):
                # 优化：同一贴纸含重复字符时(如"aa")，仅在首个字符处挂载，避免重复搜索
                if i == 0 or s[i] != s[i-1]:
                    self.adjList[ord(s[i]) - ord('a')].append(s)
        
        # --- 预处理 Target ---
        target = "".join(sorted(target))       # Target 也必须排序,这是逻辑前提
        
        # --- BFS 准备 ---
        self.visited.add(target)
        self.l = self.r = 0                    # 队列指针复位
        self.queue[self.r] = target            # 初始状态入队
        self.r += 1
        
        level = 1                              # 记录层数(当前使用的贴纸数量)
        
        # --- 开始 BFS 循环 ---
        while self.l < self.r:                 # 当队列不为空时
            size = self.r - self.l             # 获取当前层节点数量
            
            for _ in range(size):              # 遍历当前层所有节点
                cur = self.queue[self.l]       # 弹出队头字符串
                self.l += 1
                
                if not cur: return 0           # 防御性编程：空串直接返回
                
                # 贪心剪枝：cur[0]是必消的首字符，只尝试能消除它的贴纸，极大减少分支
                first_char_idx = ord(cur[0]) - ord('a')
                
                for s in self.adjList[first_char_idx]:
                    next_str = self.next_state(cur, s) # 计算使用贴纸后的剩余字符串
                    
                    if next_str == "":         # 拼完了！直接返回当前层数
                        return level
                    elif next_str not in self.visited: # 去重：新状态才入队
                        self.visited.add(next_str)
                        self.queue[self.r] = next_str
                        self.r += 1
            level += 1                         # 当前层处理完，步数+1

        return -1                              # 队列空了仍未拼出，无解
    
    def next_state(self, t: str, s: str) -> str:
        """
        计算 target (t) 减去 sticker (s) 后的剩余字符串.
        输入必须已排序。使用双指针算法模拟集合减法。
        """
        builder = []
        i, j = 0, 0
        len_t, len_s = len(t), len(s)

        while i < len_t:
            # 情况1: 贴纸耗尽，或 t[i] < s[j] (贴纸字符太大)，保留 t[i]
            if j == len_s or t[i] < s[j]:
                builder.append(t[i])
                i += 1
            # 情况2: t[i] > s[j] (贴纸字符太小)，贴纸指针后移寻找匹配
            elif t[i] > s[j]:
                j += 1
            # 情况3: 相等，字符被抵消，双指针后移
            else:
                i += 1
                j += 1
        
        return "".join(builder)