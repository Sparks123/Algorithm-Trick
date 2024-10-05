// 多项式字符串哈希（方便计算子串哈希值）
// 哈希函数 hash(s) = s[0] * base^(n-1) + s[1] * base^(n-2) + ... + s[n-2] * base + s[n-1]
const int MOD = 1'070'777'777;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int BASE = uniform_int_distribution<>(8e8, 9e8)(rng); // 随机 base，防止 hack
vector<int> pow_base(n + 1); // pow_base[i] = base^i
vector<int> pre_hash(n + 1); // 前缀哈希值 pre_hash[i] = hash(s[:i])
pow_base[0] = 1;
for (int i = 0; i < n; i++) {
    pow_base[i + 1] = (long long) pow_base[i] * BASE % MOD;
    pre_hash[i + 1] = ((long long) pre_hash[i] * BASE + target[i]) % MOD; // 秦九韶算法计算多项式哈希
}
// 计算 target[l] 到 target[r-1] 的哈希值
int sub_hash (int l, int r) {
    return ((pre_hash[r] - (long long) pre_hash[l] * pow_base[r - l]) % MOD + MOD) % MOD;
};

