function i32 main()
{
    l0:
        a = stackalloc i32
        b = stackalloc i32
        store 0, i32* a
        store 0, i32* b
        t1 = load i32* a
        t2 = alsh i32 t1, 1
        store i32 t2, i32* a
        t3 = load i32* a
        t4 = arsh i32 t3, 2
        store i32 t4, i32* a
        t5 = load i32* a
        t6 = or i32 t5, 3
        store i32 t6, i32* a
        t7 = load i32* a
        t8 = and i32 t7, 4
        store i32 t8, i32* a
        t9 = cast 1 to i32
        t10 = load i32* b
        t11 = rsh i32 t10, i32 t9
        store i32 t11, i32* b
        t12 = cast 2 to i32
        t13 = load i32* b
        t14 = lsh i32 t13, i32 t12
        store i32 t14, i32* b
        t15 = load i32* a
        ret i32 t15
}
