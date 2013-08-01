## Tarjan算法求强连通分量 ##

### 核心思想 ###
- 遍历一个点,指定一个唯一时间戳DFN[u];
- 指定该点向前追溯可追溯到的最老时间戳LOW[u].
- 枚举当前点的所有邻接点v,若DFN[v]=0表明未被搜索过,递归搜索之.搜索之后,v可能产生更早的时间戳，此时更新它.
- 若DFN[v]不为0,则v被搜索过,这时判断v是否在栈中,且v的时间戳DFN[v]小于当前时间戳DFN[u],可判定成环.将LOW[u]设定为DFN[v]
- 若这个点LOW[u]和DFN[u]相等,说明这个节点是所有强连通分量的元素中在栈中最早的节点.
- 弹栈,将这个强连通分量全部弹出,缩成点.

### 伪代码 ###
    tarjan(u)
    {
        DFN[u]=Low[u]=++Index                      // 为节点u设定次序编号和Low初值
        Stack.push(u)                              // 将节点u压入栈中
        for each (u, v) in E                       // 枚举每一条边
            if (v is not visted)               // 如果节点v未被访问过
                tarjan(v)                  // 继续向下找
                Low[u] = min(Low[u], Low[v])
            else if (v in S)                   // 如果节点v还在栈内
                Low[u] = min(Low[u], DFN[v])
        if (DFN[u] == Low[u])                      // 如果节点u是强连通分量的根
            repeat
                v = S.pop                  // 将v退栈，为该强连通分量中一个顶点
                print v
            until (u== v)
    }