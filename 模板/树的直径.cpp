/*
树上任意两节点之间最长的简单路径即为树的「直径」
有如下性质：
1. 任意节点 x 开始进行第一次 DFS，到达距离其最远的节点，记为 z，可以证明z必定为直径的一端
利用这个性质做两次dfs就可以得到直径
2. 若树上所有边边权均为正，则树的所有直径中点重合


改模板采用另一个方法：树形dp
思想：当每个节点为其子树的根，往下所能延伸的最长路径d1,与次长路径d2(与d1无公共边)，
那么直径就是对于每一个点，该点 d1 + d2 能取到的值中的最大值。
*/
const int N = 10000 + 10;

int n, d = 0;
int d1[N], d2[N];
vector<int> E[N];

void dfs(int u, int fa) {
  d1[u] = d2[u] = 0;
  for (int v : E[u]) {
    if (v == fa) continue;
    dfs(v, u);
    int t = d1[v] + 1;
    if (t > d1[u])
      d2[u] = d1[u], d1[u] = t;
    else if (t > d2[u])
      d2[u] = t;
  }
  d = max(d, d1[u] + d2[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    E[u].push_back(v), E[v].push_back(u);
  }
  dfs(1, 0);//1为根节点 0为虚拟节点
  printf("%d\n", d);
  return 0;
}
