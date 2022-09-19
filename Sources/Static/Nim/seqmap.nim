import std/[sequtils, sugar]

let
  a = [1, 2, 3, 5, 7]
  b = a.map(x => 2*x)

echo b