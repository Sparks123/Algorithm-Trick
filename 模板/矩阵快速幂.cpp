/*计算斐波那契数列的例子
base,ans均为矩阵(下标从0开始，即第一个元素的index为_00)，其中ans_00=1,ans_01=1
base_00=1,base_01=1,base_10=1,base_11=0
ans * base^(n-2)

*/
constexpr int mod = 1000000007;

struct Matrix {
  int a[2][2];

  Matrix() { memset(a, 0, sizeof a); }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)
          res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

void init() {
  base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
  ans.a[0][0] = ans.a[0][1] = 1;
}

void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}

int main() {
  int n = read();
  if (n <= 2) return puts("1"), 0;
  init();
  qpow(n - 2);
  println(ans.a[0][0] % mod);
}