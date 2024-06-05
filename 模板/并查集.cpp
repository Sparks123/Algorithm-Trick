//fa[i]表示i节点的根节点, size[k](k为某个根节点)表示以k为根节点的集合的大小

void init()
{
    for(int i=0;i<n;i++){
        fa[i]=i;
        size[i]=1;
    }
}

//找x的根节点
int find(int x) { 
    return fa[x] == x ? x : fa[x] = find(fa[x]); 
}

//按节点数合并的实现：
void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (size[x] < size[y])
        swap(x, y);
    fa[y] = x;
    size[x] += size[y];
}

//普通合并
void unite(int x, int y) { 
    fa[find(x)] = find(y); 
}

//删除
void erase(int x) {
    --size[find(x)];
    fa[x] = x;
}


//移动
void move(int x, int y) {
  auto fx = find(x), fy = find(y);
  if (fx == fy) return;
  fa[x] = fy;
  --size[fx], ++size[fy];
}