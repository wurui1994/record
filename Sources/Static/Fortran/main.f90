subroutine tohex(num)
	integer::num,a,b
	a=num/16
	b=mod(num,16)
	if(a>9)then
		print '(A,$)',char(a-10+ichar('A'))
	else 
		print '(I1,$)',a
	endif
	if(b>9)then
		print '(A,$)',char(b-10+ichar('A'))
	else 
		print '(I1,$)',b
	endif
	print '(A,$)',' '
end


!二进制Stream读写
CHARACTER,allocatable::str(:)
integer file_size
INQUIRE(FILE='test.bmp', SIZE=file_size)
allocate(str(file_size))
OPEN(10,file='test.bmp', ACCESS='STREAM', FORM='UNFORMATTED')
read (10) str
!输出数据
!print *,ichar(str)
do I=1,file_size
call tohex(ichar(str(I)))
enddo
CLOSE(10)
end

