function i32 fact(i32 n)
{
    l1:
        t2 = stackalloc i32
        store i32 n, i32* t2
        t3 = load i32* t2
        t4 = cmp le i32 t3, 1
        cjump i1 t4, l5, l6
    l5:
        ret 1
    l6:
        t7 = load i32* t2
        t8 = load i32* t2
        t9 = sub i32 t8, 1
        t10 = call fact i32 (i32 t9)
        t11 = mul i32 t7, i32 t10
        ret i32 t11
    l12:
        ret
}
function i32 main()
{
    l0:
        t1 = call fact i32 (4)
        ret i32 t1
}
