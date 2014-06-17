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

    --i;
end:

    return 0;
}
