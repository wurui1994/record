* --------------------------------------------
* Sample FORTRAN 77 program to make PPM / BMP
*
*  1998-Apr-03 (long long ago)
*      :
*  2005-Jul-22 (added P3)
*      :
*  2006 Dec-22 (added BMP)
*
*  Image array rgb(3,*,*) is filled in subroutine mkbitmap()
*  and
*  saved in PPM or BMP format in subroutine pixout().
*
*                                   K. Hayashi
* --------------------------------------------
*
       program pixelout
       implicit none
       integer ihpixf, jvpixf
       parameter(ihpixf = 128, jvpixf = 128) ! pixel size
       character*1 rgb(3,ihpixf,jvpixf) ! RGB image array
       integer nframe, nf2

       do nframe = 1, 50
         nf2 = nframe
         call mkbitmap(rgb,nf2)
         call pixout(rgb,nf2)
       enddo

       stop
       end program pixelout


* --------------------------------------------
*
* Notes
* o With a parameter ipixout set at 1, 2 or others,
*   this subroutine will generate PPM-P6(binary), PPM-P3(text),
*   or BMP(24bit depth without color table).
*
* o Some parts follow DEC-FORTRAN convention that had been defacto-standard long ago.
*   Some compilers today may not accept if "ipixout" is set other than 2.
*
* o g77 (ver. 3.3.3) works for all three choices.
* o Intel compiler (ver. 9 or later) works for all three choices.
*
* --------------------------------------------
*
       subroutine pixout(rgb,nframe)
       implicit none
* interface arg.
       integer ihpixf, jvpixf
       parameter(ihpixf = 128, jvpixf = 128) ! pixel size, eacg must be multiple of 4, if BMP is chosen as output format.
       character*1 rgb(3,ihpixf,jvpixf)      ! RGB data array
       integer nframe
* local
       character*12 fnameout
       integer i, j, k
       integer itmp, icnt
       character*14 frmtstr
       character*54 headmsw
       character*4  byt4
       character*2  byt2
* choices
       integer ipixout
       parameter(ipixout = 1) ! 1 / 2 / other= PPM6, PPM3, BMP(24bit)

       if (ipixout .EQ. 1) then

* PPM P6

         write(fnameout,'(''smpl'',i3.3,''.ppm'')') nframe ! name of PPM file
         open(unit=2,file=fnameout,status='unknown')
         write(*,*) 'Now writing PPM (P6) file : ', fnameout
* header
         write(2,'(''P6'', 2(1x,i4),'' 255 '',$)')         ! some compiler may not accept this line.
     &     ihpixf, jvpixf
* image data
         itmp = ihpixf * jvpixf * 3
         write(frmtstr,'(''('',i8.8,''A,$)'')') itmp     ! make output "format"
         write(2,fmt=frmtstr)                              ! some compiler may not accept this line.
     &     (((rgb(k,i,j),k=1,3),i=1,ihpixf),j=jvpixf,1,-1) ! here, j (vertical address) runs from top to bottom.
         close(2)

       else if (ipixout .EQ. 2) then

* PPM P3 ! rather "safer" choice for many Fortran compiler(s).

         write(fnameout,'(''smpl'',i3.3,''.ppm'')') nframe ! name of PPM file
         open(unit=2,file=fnameout,status='unknown')
         write(*,*) 'Now writing PPM (P3) file : ', fnameout
* header
         write(2,'(A)') 'P3'
         write(2,'(2(1x,i4),'' 255 '')')  ihpixf, jvpixf
         icnt = 0
* image data
         do j = jvpixf, 1, -1                              ! here, j (vertical address) runs from top to bottom.
         do i = 1, ihpixf, 1
         do k = 1, 3
           itmp = ichar(rgb(k,i,j))
           icnt = icnt + 4
           if (icnt .LT. 60) then
             write(2,fmt='(1x,i3,$)') itmp                 ! "$" is not standard.
           else
             write(2,fmt='(1x,i3)') itmp
             icnt = 0
           endif
         enddo
         enddo
         enddo
         write(2,'(A)') ' '
         close(2)

       else

* BMP (24bit depth)... this part works only when width is multiple of 4.

         itmp = mod(ihpixf, 4)
         if (itmp .NE. 0) then
           write(*,*) 'width must be multiple of 4'
           stop
         endif

         write(fnameout,'(''smpl'',i3.3,''.bmp'')') nframe ! name of BMP file
         open(unit=2,file=fnameout,status='unknown')
         write(*,*) 'Now writing BMP(24bit) file : ', fnameout
* header 1 (file header ; 1--14 byte)
         headmsw( 1: 2) = 'BM'             ! declaring this is BMP file
         itmp = 54 + ihpixf * jvpixf * 3 ! total file size = header + data
         call num2bit4(itmp,byt4)
         headmsw( 3: 6) = byt4(1:4)
         itmp = 0                        ! may be 0
         call num2bit2(itmp,byt2)
         headmsw( 7: 8) = byt2(1:2)
         itmp = 0                        ! may be 0
         call num2bit2(itmp,byt2)
         headmsw( 9:10) = byt2(1:2)
         itmp = 54                       ! must be 54 : total length of header
         call num2bit4(itmp,byt4)
         headmsw(11:14) = byt4(1:4)
* header 2 (bit-map header ; 13--54 byte)
         itmp = 40                       ! must be 40 : length of bit-map header
         call num2bit4(itmp,byt4)
         headmsw(15:18) = byt4(1:4)
         itmp = ihpixf                   ! width
         call num2bit4(itmp,byt4)
         headmsw(19:22) = byt4(1:4)
         itmp = jvpixf                   ! height
         call num2bit4(itmp,byt4)
         headmsw(23:26) = byt4(1:4)
         itmp = 1                        ! must be 1
         call num2bit2(itmp,byt2)
         headmsw(27:28) = byt2(1:2)
         itmp = 24                       ! must be 24 : color depth in bit.
         call num2bit2(itmp,byt2)
         headmsw(29:30) = byt2(1:2)
         itmp = 0                        ! may be 0 : compression method index
         call num2bit4(itmp,byt4)
         headmsw(31:34) = byt4(1:4)
         itmp = 0                        ! may be 0 : file size if compressed
         call num2bit4(itmp,byt4)
         headmsw(35:38) = byt4(1:4)
         itmp = 0                        ! arbit. : pixel per meter, horizontal
         call num2bit4(itmp,byt4)
         headmsw(39:42) = byt4(1:4)
         itmp = 0                        ! arbit. : pixel per meter, vertical
         call num2bit4(itmp,byt4)
         headmsw(43:46) = byt4(1:4)
         itmp = 0                        ! may be 0 here : num. of color used
         call num2bit4(itmp,byt4)
         headmsw(47:50) = byt4(1:4)
         itmp = 0                        ! may be 0 here : num. of important color
         call num2bit4(itmp,byt4)
         headmsw(51:54) = byt4(1:4)

* writing header part
         write(2,'(a54,$)') headmsw(1:54)
* image data
         itmp = ihpixf * jvpixf * 3
         write(frmtstr,'(''('',i8.8,''A,$)'')') itmp
         write(2,fmt=frmtstr)
     &     (((rgb(k,i,j),k=3,1,-1),i=1,ihpixf),j=1,jvpixf) ! writing in BGR order, not RGB.
         close(2)

       endif

       return
       end subroutine pixout

* --------------------------------------
* convert integer values to 4 8-bit characters
* --------------------------------------

       subroutine num2bit4(inum,byt4)
       implicit none
       integer inum
       character*4 byt4
       integer itmp1, itmp2
       itmp1 = inum
       itmp2 = itmp1 / 256**3
       byt4(4:4) = char(itmp2)
       itmp1 =-itmp2 * 256**3 +itmp1
       itmp2 = itmp1 / 256**2
       byt4(3:3) = char(itmp2)
       itmp1 =-itmp2 * 256**2 +itmp1
       itmp2 = itmp1 / 256
       byt4(2:2) = char(itmp2)
       itmp1 =-itmp2 * 256    +itmp1
       byt4(1:1) = char(itmp1)
       return
       end subroutine num2bit4

* --------------------------------------
* convert integer values to 2 8-bit characters
* --------------------------------------

       subroutine num2bit2(inum,byt2)
       implicit none
       integer inum
       character*2 byt2
       integer itmp1, itmp2
       itmp1 = inum
       itmp2 = itmp1 / 256
       byt2(2:2) = char(itmp2)
       itmp1 =-itmp2 * 256 + itmp1
       byt2(1:1) = char(itmp1)
       return
       end subroutine num2bit2


* --------------------------------------------
*   fill rgb data array with something
* --------------------------------------------

       subroutine mkbitmap(rgb,nframe)
       implicit none
       integer nframe
       integer ihpixf, jvpixf
       parameter(ihpixf = 128, jvpixf = 128) ! pixel size
       character*1 rgb(3,ihpixf,jvpixf) !      RGB pixel data array
* local
       real*8  red, gre, blu
       integer ired, igre, iblu
       real*8  ofst
       parameter(ofst = 0.7D+00)
       integer i, j, itmp
       real*8   aa, bb, cc, rr, xx, yy, tt
       integer ichoice
       parameter(ichoice = 1) ! .... choice
       real*8  pi
       parameter(pi = 3.14159265358979D+00)

       if (ichoice .EQ. 0) then
         do 100 j = 1, jvpixf
         do 100 i = 1, ihpixf
           itmp = i*3*nframe + j*2
           itmp = mod(itmp,256)    ! assuming 8-bit color depth, rangeing from 0 to 255
           rgb(1,i,j) = char(itmp) ! red
           itmp = i*1*nframe + j*3
           itmp = mod(itmp,256)
           rgb(2,i,j) = char(itmp) ! green
           itmp = i*5*nframe + j*7
           itmp = mod(itmp,256)
           rgb(3,i,j) = char(itmp) ! blue
 100     continue
       else
         do 101 j = 1, jvpixf
         do 101 i = 1, ihpixf
* red-ball
           tt = dfloat(nframe) / 25.0D+00 !                  time/period
           xx = dfloat(i) / dfloat(ihpixf) - 0.33D+00  !     center x
           yy = dfloat(j) / dfloat(jvpixf) - 0.25D+00  !     center y
           rr = dsqrt(xx**2 + yy**2 + 1.0D-30)
           aa = rr / 0.25D+00 !                              half-width
           bb =(tt - rr) * pi
           cc = dexp(-aa**2) * (dcos(bb))**2
           if (cc .LT. ofst) then
             red = cc / ofst
             gre = 0.0D+00
             blu = 0.0D+00
           else
             red = 1.0D+00
             gre =(cc - ofst) / (1.0D+00 - ofst)
             blu =(cc - ofst) / (1.0D+00 - ofst)
           endif
* green-ball
           tt = dfloat(nframe) / 50.0D+00
           xx = dfloat(i) / dfloat(ihpixf) - 0.40D+00
           yy = dfloat(j) / dfloat(jvpixf) - 0.65D+00
           rr = dsqrt(xx**2 + yy**2 + 1.0D-30)
           aa = rr / 0.40D+00
           bb =(tt - rr) * pi
           cc = dexp(-aa**2) * (dcos(bb))**2
           if (cc .LT. ofst) then ! here and hereafter, additive rgb color is simply added.
             gre = gre + cc / ofst
           else
             red = red +(cc - ofst) / (1.0D+00 - ofst)
             gre = gre + 1.0D+00
             blu = blu +(cc - ofst) / (1.0D+00 - ofst)
           endif
* blue-ball
           tt = dfloat(nframe) / 12.5D+00
           xx = dfloat(i) / dfloat(ihpixf) - 0.75D+00
           yy = dfloat(j) / dfloat(jvpixf) - 0.70D+00
           rr = dsqrt(xx**2 + yy**2 + 1.0D-30)
           aa = rr / 0.30D+00
           bb =(tt - rr) * pi
           cc = dexp(-aa**2) * (dcos(bb))**2
           if (cc .LT. ofst) then
             blu = blu + cc / ofst
           else
             red = red +(cc - ofst) / (1.0D+00 - ofst)
             gre = gre +(cc - ofst) / (1.0D+00 - ofst)
             blu = blu + 1.0D+00
           endif
* yellow-ball
           tt = dfloat(nframe) / 16.66666666666D+00
           xx = dfloat(i) / dfloat(ihpixf) - 0.75D+00
           yy = dfloat(j) / dfloat(jvpixf) - 0.30D+00
           rr = dsqrt(xx**2 + yy**2 + 1.0D-30)
           aa = rr / 0.25D+00
           bb =(tt - rr) * pi
           cc = dexp(-aa**2) * (dcos(bb))**2
           if (cc .LT. ofst) then
             red = red + cc / ofst
             gre = gre + cc / ofst
           else
             red = red + 1.0D+00
             gre = gre + 1.0D+00
             blu = blu +(cc - ofst) / (1.0D+00 - ofst)
           endif

           ired = int(red * 255.0D+00)
           igre = int(gre * 255.0D+00)
           iblu = int(blu * 255.0D+00)
           if (ired .GT. 255) ired = 255
           if (igre .GT. 255) igre = 255
           if (iblu .GT. 255) iblu = 255
           if (ired .LT.   0) ired =   0
           if (igre .LT.   0) igre =   0
           if (iblu .LT.   0) iblu =   0
           rgb(1,i,j) = char(ired)
           rgb(2,i,j) = char(igre)
           rgb(3,i,j) = char(iblu)
 101     continue
       endif
**
* Make a white dot that must appear at a point,
*             1/3 horizontal size (width) from the leftmost
*         and 1/4 vertical (height) from the bottom.
**
*       rgb(1,ihpixf/3,jvpixf/4) = char(255)
*       rgb(2,ihpixf/3,jvpixf/4) = char(255)
*       rgb(3,ihpixf/3,jvpixf/4) = char(255)
**
       return
       end subroutine mkbitmap


* --------------------------------------------
* end of this file, thank you.
* --------------------------------------------
