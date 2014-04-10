int main(void)
{
    int var1 = -3;
    int *var2 = &var1;

    var1 += +3;

    --var1;
    ++var1;

    var1 = *var2;

    var1 = ~var1;
    var1 = !var1;

    var1++;
    var1--;

    return var1;
}
