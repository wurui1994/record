echo "Hello World"

proc getAlphabet(): string =
  var accm = ""
  for letter in 'a'..'z':  # see iterators
    accm.add(letter)
  return accm

# Computed at compilation time
const alphabet = getAlphabet()

# Mutable variables
var
  a = "foo"
  b = 0
  # Works fine, initialized to 0
  c: int

# Immutable variables
let
  d = "foo"
  e = 5
  # Compile-time error, must be initialized at creation
  # f: float

# Works fine, `a` is mutable
a.add("bar")
b += 1
c = 3

# Compile-time error, const cannot be modified at run-time
# alphabet = "abc"

# Compile-time error, `d` and `e` are immutable
# d.add("bar")
# e += 1

echo alphabet

var x = int(1.0 / 3) # type conversion

var y: seq[int] = @[] # empty seq needs type specification

var z = "Foobar"
proc ffi(foo: ptr array[6, char]) = echo repr(foo)
ffi(cast[ptr array[6, char]](addr z[0]))

import strutils, random

randomize()
let answer = random(10) + 1
# while true:
echo "I have a number from 1 to 10, what is it? "
let guess = parseInt("12")

if guess < answer:
  echo "Too low, try again"
elif guess > answer:
  echo "Too high, try again"
else:
  echo "Correct!"
  # break
