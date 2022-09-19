import std/[algorithm]
echo reversed([1, 2, 3, 4, 5]) # array
echo reversed(@[1, 2, 3]) # sequence
echo reversed("abc") # string

import std/[strutils]
echo reversed("abc").join("")