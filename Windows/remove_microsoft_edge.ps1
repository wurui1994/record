# powershell -c start cmd -verb runas
# Install-Package PSSQLite
# Import-Module PSSQLite
# Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "select PackageFullName,IsInbox from Package where PackageFullName like '%Microsoft%' "

# takeown /f C:\ProgramData\Microsoft\Windows\AppRepository /r /d n | out-null
# icacls C:\ProgramData\Microsoft\Windows\AppRepository /grant 'Everyone:(OI)(CI)F' /T /Q

# Change to use PsExec, you can use install-package InvokePsExec to get psexec.exe
# powershell -c "start psexec -a '-i -s powershell' -verb runas"
# or you can use PaExec:
# powershell -c "start paexec -a '-s powershell' -verb runas"
# powershell -c "start -WindowStyle Hidden paexec -a '-i -s powershell' -verb runas"
Invoke-SqliteQuery -Database "C:\ProgramData\Microsoft\Windows\AppRepository\StateRepository-Machine.srd" -Query "update Package set IsInbox=0 where PackageFullName like '%Edge%' "

Get-AppxPackage *edge*|Remove-AppxPackage