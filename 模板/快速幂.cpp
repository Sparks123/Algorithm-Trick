//求(x^n)%mod
int pow(long long x, long long n, long long mod) {
        long long res = 1 % mod;
        for (; n; n /= 2) {
            if (n % 2) {
                res = res * x % mod;
            }
            x = x * x % mod;
        }
        return res;
    }
