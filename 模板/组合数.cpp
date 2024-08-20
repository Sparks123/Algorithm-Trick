//求组合数C(n,k)
int c[31][31];
for (int i = 0; i < 31; i++) 
{
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; j++) 
    {
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
}