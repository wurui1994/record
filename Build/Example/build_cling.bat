REM vs2017-15.4.2注意事项：

wget https://raw.githubusercontent.com/root-project/cling/master/tools/packaging/cpt.py
python cpt.py --check-requirements 
python cpt.py --create-dev-env Release --with-workdir=./cling-build/

REM 1.去掉cling.vcxproj工程中多余的/Export附加选项。
REM 2.关闭ReportError,否则在刚进入是出现2 2。
REM static void ReportError(DWORD Err, const char* Prefix) {
  REM std::string Message;
  REM GetErrorAsString(Err, Message, Prefix);
  REM //cling::errs() << Message << '\n';
REM }