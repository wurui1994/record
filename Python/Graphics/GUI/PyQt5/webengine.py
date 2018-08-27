from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QUrl
import sys

app = QApplication(sys.argv)
view=QWebEngineView()
view.setUrl(QUrl("https://www.baidu.com/"))
view.show()
app.exec_()