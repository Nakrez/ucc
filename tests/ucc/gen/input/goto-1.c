int main(void)
{
    int i = 1;

    while (i)
    {
        if (i)
            goto end;
        else
            ++i;
    }

end:

    return 0;
}
