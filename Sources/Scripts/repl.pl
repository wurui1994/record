# Method 1
# You can use the perl debugger on a trivial program, like so:
perl -de1

# Method 2
perl -e 'print ">";while(<>){print eval,"\n>"}'