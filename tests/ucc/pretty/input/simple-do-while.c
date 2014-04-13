int main(void)
{
    int var = 0;

    do
    {
        ++var;
    } while (var < 10);

    do
        ++var;
    while (var < 20);

    return var;
}
