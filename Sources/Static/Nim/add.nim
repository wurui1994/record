proc add(a: int, b: int): int = a + b

proc add2(a: int, b: int): int = 
    return a + b

proc `+`(a,b:string):string = a & b

proc add_generic[T](a: T, b: T): T = a + b

echo add(2,3), add2(3,4), add_generic("Hello,", "World!")
echo 2.add(4), "Hello".add_generic("World!")