import win32com.client
from win32com.gen_py import msxl
g = globals()
for c in dir(msxl.constants) : g[c] = getattr(msxl.constants, c)

xlApp = win32com.client.Dispatch('Excel.Application')
xlBook=xlApp.Workbooks.Add()
xlSheet=xlBook.Worksheets(1)
xlSheet.Range('$A1:$D1').Value = ['NAME', 'PLACE', 'RANK', 'PRICE'];
xlSheet.Range('$A2:$D2').Value = ['Foo', 'Fooland', 1, 100];
xlSheet.Range('$A3:$D3').Value = ['Bar', 'Barland', 2, 75];
xlSheet.Range('$A4:$D4').Value = ['Stuff', 'Stuffland', 3, 50];
xlBook.Save();
xlChart=xlBook.Charts.Add();
xlChart.ChartType=xlLineMarkers