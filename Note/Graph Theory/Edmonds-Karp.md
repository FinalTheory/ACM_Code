# Edmonds-Karp算法核心思想 #

- 为了简便起见，使用二维数组以邻接矩阵形式存储图；
- 该算法的思想是尝试不断寻找增广路，方式是BFS；
- 使用一个数组记录从源点达到所有点的最小残量，也就是允许的残量；
- 初始时刻，显然自己到自己的残量为无限大，其余置零。
- 将起始点加入队列，然后按照BFS的思想，每次出队一个点，遍历所有未处理的点，如果出队的点到这个点的容量大于流量，就更新残量数组，并记录路径，也就是父节点；
- 当上述循环结束后，如果到汇点的残量大于零，证明存在增广路，此时沿路径回溯，更新流量矩阵，正向增加流量，反向减少流量。
- 最后，将这个残量增加到最大流量上面。