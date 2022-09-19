proc add(a,b:string) = echo a&b
add "hello", "world"

proc printThings(things: varargs[string]) =
  for thing in things:
    echo thing

printThings "words", "to", "print"

proc print[T](s:varargs[T, `$`]) = (for l in s: echo l)

print 2,3,4
print "words", @[1,2,3], 2