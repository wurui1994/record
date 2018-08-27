#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
Function:
http://www.crifan.com/python_process_excel_chart_graph
 
Author:     Crifan Li
Version:    2012-12-25
Contact:    admin at crifan dot com
"""
 
import os;
from win32com.client import Dispatch;
#from win32com.client import *;
 
def excelChart():
    xl = Dispatch("Excel.Application");
    #xl = win32com.client.Dispatch("Excel.Application")
    print "xl=",xl;
 
    #[1] Fail
    # xlsPath = "chart_demo.xls";
    # wb = xl.Workbooks.open(xlsPath); #pywintypes.com_error
 
    #[2] Fail
    # xlsPath = "D:\tmp\tmp_dev_root\python\excel_chart\chart_demo.xls";
    # absPath = os.path.abspath(xlsPath);
    # print "absPath=",absPath; #absPath= D:\tmp\tmp_dev_root\python\excel_chart\        mp      mp_dev_root\python\excel_chart\chart_demo.xls
    # wb = xl.Workbooks.open(absPath); #pywintypes.com_error
 
    #[3] Fail
    # xlsPath = "D:\tmp\tmp_dev_root\python\excel_chart\chart_demo.xls";
    # normalPath = os.path.normpath(xlsPath);
    # print "normalPath=",normalPath; #normalPath= D:  mp      mp_dev_root\python\excel_chart\chart_demo.xls
    # wb = xl.Workbooks.open(normalPath); #pywintypes.com_error
 
    #[4] Fail
    # rawPath = r"chart_demo.xls";
    # wb = xl.Workbooks.open(rawPath); #pywintypes.com_error
     
    #[5] OK
    xlsPath = "F:\chart_demo.xlsx";
    absPath = os.path.abspath(xlsPath);
    print "absPath=",absPath; #absPath= D:\tmp\tmp_dev_root\python\excel_chart\chart_demo.xls
    wb = xl.Workbooks.open(absPath); #OK
         
    #[6] OK
    # rawPath = r"D:\tmp\tmp_dev_root\python\excel_chart\chart_demo.xls";
    # wb = xl.Workbooks.open(rawPath); # OK
 
 
    xl.Visible = 1;
    ws = wb.Worksheets(1);
    ws.Range('$A1:$D1').Value = ['NAME', 'PLACE', 'RANK', 'PRICE'];
    ws.Range('$A2:$D2').Value = ['Foo', 'Fooland', 1, 100];
    ws.Range('$A3:$D3').Value = ['Bar', 'Barland', 2, 75];
    ws.Range('$A4:$D4').Value = ['Stuff', 'Stuffland', 3, 50];
    wb.Save();
    wb.Charts.Add();
    wc1 = wb.Charts(1);
     
if __name__ == "__main__":
    excelChart();