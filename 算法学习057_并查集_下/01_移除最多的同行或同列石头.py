from typing import List

"""
======================================================================================
📝 题目: 947. 移除最多的同行或同列石头 (Most Stones Removed with Same Row or Column)
🔗 链接: https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
📈 难度: 中等 (Medium)
======================================================================================
【题目描述】
n 块石头放置在二维平面中的一些整数坐标点上.每个坐标点上最多只能有一块石头.

如果一块石头的 "同行或者同列" 上有其他石头存在,那么就可以移除这块石头.

给你一个长度为 n 的数组 stones ,其中 stones[i] = [xi, yi] 表示第 i 块石头的位置,
返回 "可以移除的石子" 的最大数量.

--------------------------------------------------------------------------------------
🌟 【示例 1】
输入: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
输出: 5
解释: 一种移除 5 块石头的方法如下所示:
1. 移除石头 [2,2] , 因为它和 [2,1] 同行.
2. 移除石头 [2,1] , 因为它和 [0,1] 同列.
3. 移除石头 [1,2] , 因为它和 [1,0] 同列.
4. 移除石头 [1,0] , 因为它和 [0,0] 同列.
5. 移除石头 [0,1] , 因为它和 [0,0] 同行.
石头 [0,0] 不能移除，因为它没有与另一块石头同行/列.

🌟 【示例 2】
输入: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
输出: 3
解释: 一种移除 3 块石头的方法如下所示:
1. 移除石头 [2,2] , 因为它和 [2,0] 同行.
2. 移除石头 [2,0] , 因为它和 [0,0] 同列.
3. 移除石头 [0,2] , 因为它和 [0,0] 同行.
石头 [0,0] 和 [1,1] 不能移除,因为它们没有与另一块石头同行/列.

🌟 【示例 3】
输入: stones = [[0,0]]
输出: 0
解释: [0,0] 是平面上唯一一块石头,所以不可以移除它.

--------------------------------------------------------------------------------------
📏 【提示】
• 1 <= stones.length <= 1000
• 0 <= xi, yi <= 10^4
• 不会有两块石头放在同一个坐标点上
======================================================================================
"""

# 时间复杂度: O(n)
class Solution:
    # key:是某一行, value是第一次遇到的石头的编号
    rowFirst: dict[int, int] = dict()  # 🗺️ 记录某行第一次出现的石头下标

    # key:是某一列, value是第一次遇到的石头的编号
    colFirst: dict[int, int] = dict()  # 🗺️ 记录某列第一次出现的石头下标

    MAX: int = 1001
    father: list[int] = [0] * MAX      # 🌲 并查集数组
    sets: int = 0                      # 🧩 连通分量(集合)的总数

    def build(self, n: int) -> None:
        self.rowFirst.clear()          # 🧹 清空行记录
        self.colFirst.clear()          # 🧹 清空列记录
        for i in range(n):
            self.father[i] = i         # 🏳️ 初始化:父节点指向自己
        self.sets = n                  # 🔢 初始:每个石头都是一个独立集合

    def find(self, i: int) -> int:
        if i != self.father[i]:        # 🔍 如果不是根节点
            self.father[i] = self.find(self.father[i]) # 🛤️ 路径压缩:直接连到根
        return self.father[i]

    # 把第x块石头和第y块是否合并
    def union(self, x: int, y: int) -> None:
        fx: int = self.find(x)         # 🔍 找 x 的根
        fy: int = self.find(y)         # 🔍 找 y 的根
        if fx != fy:                   # ⚡ 如果根不同,说明还没连通
            self.father[fx] = fy       # 🔗 合并:让 x 的根指向 y 的根
            self.sets -= 1             # 📉 成功合并,集合数量减 1

    def removeStones(self, stones: List[List[int]]) -> int:
        n: int = len(stones)           # 🔢 石头总数
        self.build(n)                  # 🏗️ 初始化并查集
        for i in range(n):
            row: int = stones[i][0]    # ↔️ 当前行坐标
            col: int = stones[i][1]    # ↕️ 当前列坐标
            
            # row in self.rowFirst 判断第row行是否存放过石头
            if not row in self.rowFirst:   # 🆕 如果这行是第一次遇到
                self.rowFirst[row] = i     # 📍 记录当前石头为这行的"代表"
            else:                          # ♻️ 如果这行之前出现过
                self.union(self.rowFirst[row], i) # 🔗 与这行的"代表"合并
            
            # col in self.colFirst 判断第col列是否存放过石头
            if not col in self.colFirst:   # 🆕 如果这列是第一次遇到
                self.colFirst[col] = i     # 📍 记录当前石头为这列的"代表"
            else:                          # ♻️ 如果这列之前出现过
                self.union(self.colFirst[col], i) # 🔗 与这列的"代表"合并
                
        return n - self.sets           # 🏁 结果 = 总石头数 - 连通分量数
    
