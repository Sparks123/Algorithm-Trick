/*线段树的精髓在于分治，在搞懂线段树的原理后再用模板，才能灵活掌握。 

除非是模板题，不然很难直接一字不差地套用线段树模板

线段树上每个节点维护的信息要根据题目的要求去定义（这往往是题目的难点）。模板中维护的是区间和
*/
//注意：这个模板只适用单点修改，并不适用区间修改，因为区间修改如果遍历区间一个个去修改，时间复杂度无法承受。这时候可以引入懒惰标记，有机会在后面的模板中介绍
//对数组a[n]建线段树，维护区间。树中每个节点存储的信息为d[p](p为节点编号，d[p]为该节点对应的区间和)

void maintain(int p) {
    d[p] = d[p * 2] + d[(p * 2) + 1];//根据题目要求改，这里是求区间和
}

void build(int s, int t, int p) {
  // 对 [s,t] 区间建立线段树,当前根的编号为 p，p>=1
  if (s == t) {
    d[p] = a[s];//根据题目要求改
    return;
  }
  int m = s + ((t - s) >> 1);
  // 移位运算符的优先级小于加减法，所以加上括号
  // 如果写成 (s + t) >> 1 可能会超出 int 范围
  build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
  // 递归对左右区间建树
  maintain(p);
}

//单点更新
void update(int p, int s, int t, int i, int val) {
    //把 a[i] 改成 val,p表示当前节点，s和t分别表示该节点对应的区间
    if (s == t) {
        d[p] = val;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (i <= m) {
        update(p * 2, s, m, i, val); //如果i在左儿子代表的区间
    } else {
        update(p * 2 + 1, m + 1, t, i, val);//如果i在右儿子代表的区间
    }
    maintain(p);
}

//区间查询
int getsum(int l, int r, int s, int t, int p) {
  // [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
  if (l <= s && t <= r)
    return d[p];  // 当前区间为询问区间的子集时直接返回当前区间的和
  int m = s + ((t - s) >> 1), sum = 0;
  if (l <= m) sum += getsum(l, r, s, m, p * 2);
  // 如果左儿子代表的区间 [s, m] 与询问区间有交集, 则递归查询左儿子
  if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  // 如果右儿子代表的区间 [m + 1, t] 与询问区间有交集, 则递归查询右儿子
  return sum;
}



