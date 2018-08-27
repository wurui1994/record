@echo off
REM makerootfs unsquashrootfs rootfs.sfs
if "%1" == "unsquashrootfs" goto :unsquashrootfs

set wrfs=%~1
set wrfs=%wrfs:~3%
set wrfs=%wrfs:\=/%
set mountpoint=/mnt/%cd:~0,1%/
set "_UCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ"
set "_LCASE=abcdefghijklmnopqrstuvwxyz"
for /l %%a in (0,1,25) do (
	call set "_FROM=%%_UCASE:~%%a,1%%
	call set "_TO=%%_LCASE:~%%a,1%%
	call set "mountpoint=%%mountpoint:!_FROM!=!_TO!%%
)

:makerootfs
bash -c "mksquashfs / rootfs.sfs -b 1048576 -comp xz -Xdict-size 100%% -all-root -e /mnt 2>/dev/null"
goto :eof

REM permissions
REM put rootfs.sfs in rootfs/root dir
:unsquashrootfs
REM set mountpoint=%mountpoint%%wrfs%
echo "Unsquashing rootfs."
bash -c "unsquashfs -f -x -d ~/rootfs-temp %~n2.sfs 2>/dev/null"
timeout /t 5
REM Maybe fail. Please move rootfs-temp to rootfs after check
move rootfs/root/rootfs-temp rootfs-temp
echo "Finish Unsquashing rootfs."
goto :eof