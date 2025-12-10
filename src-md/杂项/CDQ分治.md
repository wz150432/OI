# CDQ分治

陈丹琦分治，是一个早年 IOI 选手整理的处理 [三维偏序](https://www.luogu.com.cn/problem/P3810) 问题的分治算法。三维偏序问题就是有 $n$ 个元素，第 $i$ 个元素有 $ a_i,b_i,c_i $ 三个属性，求出满足 $ a_j \leq a_i $ 且 $ b_j \leq b_i $ 且 $ c_j \leq c_i $ 且 $ j \ne i $ 的 $j$ 的数量。



在写 CDQ 分治前，我们先想想二维偏序怎么处理。很显然，经过简单思考就可以按照双关键字排序，然后用树状数组求解。

相似的，对于三维偏序的问题，我们按照一排序，二归并，三树状的方法处理。这是什么意思呢，我们对按照三关键字排序后的数列再次使用归并排序对于属性 $b$ 进行排序。当我们合并左右两边的时候，当满足 $b_i \le b_j$ 的时候我们把 $c_i$ 加入到树状数组；当 $b_j > b_i$ 的时候我们后面已经没有更多满足第二维限制的元素了，所以直接对于之前满足第二维的元素查询插入了多少满足第三维限制的 $c_i$，但是记得插入完树状数组记得清空，数组不清空，亲人两行泪。



```cpp
void cdq(int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1, cnt = 0;
    cdq(l, mid), cdq(mid + 1, r);
    while (i <= mid && j <= r) {
        if (a[i].b <= a[j].b) {
            add(a[i].c, a[i].s);
            tmp[ ++ cnt] = a[i ++ ];
        } else {
            a[j].res += query(a[j].c);
            tmp[ ++ cnt] = a[j ++ ];
        }
    }
    while (i <= mid) {
        add(a[i].c, a[i].s);
        tmp[ ++ cnt] = a[i ++ ];
    }
    
    while (j <= r) {
        a[j].res += query(a[j].c);
        tmp[ ++ cnt] = a[j ++ ];
    }
    for (int i = l; i <= mid; ++ i) add(a[i].c, -a[i].s);
    for (int i = 0; i < cnt; ++ i) a[i + l] = tmp[i + 1];
}
```
