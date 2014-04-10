typedef int type[];

int main(void)
{
    type test = { 1, 2, 3};
    int ret;

    ret = test[0] + test[1] + test[2];

    return ret;
}
