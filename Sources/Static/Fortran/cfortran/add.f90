subroutine add(a,b,c)
implicit none
real::a,b,c
c=a+b
write(*,*) a,'+',b,'=',c
return
end subroutine add