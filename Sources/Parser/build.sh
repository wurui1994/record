# flex
lex simple.l
cc lex.yy.c -o example -ll
# ./example
cat >input <<EOF
1111
hello
stop
start
EOF
echo "test simple.l ..."
cat input | ./example
rm lex.yy.c example

# rpcalc
bison rpcalc.y
cc rpcalc*.c -o rpcalc
cat >input <<EOF
4 5 +
2 3 /
1 2 3 * +
EOF
echo "test rpcalc.y ..."
cat input | ./rpcalc
rm rpcalc rpcalc.tab.c

# calc
bison calc.y
cc calc*.c -o calc
# ./calc
cat >input <<EOF
2+3
3 + 4
3/4 + 5
EOF
echo "test calc.y ..."
cat input | ./calc
rm calc calc.tab.c

# mfcalc
bison mfcalc.y
cc mfcalc*.c -o mfcalc
# ./mfcalc
cat >input <<EOF
a=3
a
sin(a)
EOF
echo "test mfcalc.y ..."
cat input | ./mfcalc
rm mfcalc mfcalc.tab.c

rm input

# graphviz
bison --graph rpcalc.y
rm rpcalc.tab.c