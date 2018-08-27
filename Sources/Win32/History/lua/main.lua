local testlib = package.loadlib("opendll.dll","luaopen_MyLuaDLL");   --获取DLL中抛出函数地址
print (testlib) 
if(testlib)then
    testlib();  --调用DLL中抛出函数
else
    -- Error
end
 
MyLuaDLL.HelloWorld();
 
a,b=MyLuaDLL.average(23,33,3344);
print("average:",a,"sum:",b);