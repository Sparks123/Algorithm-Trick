/*
关于后缀数组的知识可以参考OI-Wiki,这里记录以O(nlogn)复杂度求sa[i]和rk[i].

一些约定：1.字符串下标从1开始。2.字符串s的长度为 n。3."后缀i" 代指以第i个字符开头的后缀，存储时用i代表字符串 s 的后缀 s[i...n]。

后缀数组的应用很灵活，这里以典型的字符串匹配为例子，复杂度O(|S|log|T|)。虽然KMP更快，但在多数时候O(|S|log|T|)复杂度是够用的。
思路：主串T，模式串S。我们可以先构造出T的后缀数组，然后查找子串S。因为我们已经将所有后缀排序了，我们可以通过在sa数组中二分S来实现。
比较子串S和当前后缀的时间复杂度为 O(|S|)，因此找子串的时间复杂度为 O(|S|log|T|)。
注意，如果该子串在T中出现了多次，则每次出现都是在sa数组中相邻的。因此出现次数可以通过再次二分找到，输出每次出现的位置也很轻松。
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1000010;

char s[N];
int n;
int m, p, rk[N * 2], oldrk[N], sa[N * 2], id[N], cnt[N];

void cal_sa() {
  //scanf("%s", s + 1);
  n = strlen(s + 1);
  m = 128;

  for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
  for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;

  for (int w = 1;; w <<= 1, m = p) {  // m = p 即为值域优化
    int cur = 0;
    for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
    for (int i = 1; i <= n; i++)
      if (sa[i] > w) id[++cur] = sa[i] - w;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) cnt[rk[i]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];

    p = 0;
    memcpy(oldrk, rk, sizeof(oldrk));
    for (int i = 1; i <= n; i++) {
      if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
          oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
        rk[sa[i]] = p;
      else
        rk[sa[i]] = ++p;
    }

    if (p == n) break;  // p = n 时无需再排序
  }

  //for (int i = 1; i <= n; i++) printf("%d ", sa[i]);

}

/*模式串s,主串t,主串T下标从1开始,dir=0表示找t中最左边的匹配，dir=1 表示找t中最右边的匹配。
假设存在多个匹配 left=match(string s,string t,  0), right=match(string s,string t, 1),那么匹配的位置为
for(int j=left;j<=right;j++){
    int pos=sa[j];//匹配位置为t[pos...pos+sz-1],(下标从1开始，sz为模式串的长度)
}
*/
int match(string s,char* t, int dir)
{
    int len=s.size();
    int l=1,r=n;//主串长度为n
    int mid;
    int flag=0;//判断是否匹配成功
    while(l<=r)
    {
        mid=(l+r)/2;
        int pos=sa[mid];
        for(int i=0;i<len;i++)
        {
            if(pos>n){
                l=mid+1;
                break;
            }
            if(s[i]==t[pos]) {
                pos++;
                if(i==len-1) {//匹配成功
                    if(dir==0) r=mid-1;
                    else l=mid+1;
                    flag=1;
                    break;
                }
            }
            else if(s[i]>t[pos]) {
                l=mid+1;
                break;
            }
            else if(s[i]<t[pos]) {
                r=mid-1;
                break;
            }
        }
    }
    if(flag==1) {
        if(dir==0) return l;
        else return r;
    }
    else return -1;
}

