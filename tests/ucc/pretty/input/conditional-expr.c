int main(void)
{
    int var1;
    int var2;
    int cond1 = 0;
    int cond2 = 1;

    var1 = cond1 ? 0 : 1;
    var2 = cond2 ? 1 : 0;

    var1 = var2 ? 3 : 2;

    return var1;
}
