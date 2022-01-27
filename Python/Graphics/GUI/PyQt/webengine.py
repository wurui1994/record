from PyQt6.QtWebEngineWidgets import QWebEngineView
from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QUrl
import sys

app = QApplication(sys.argv)
view = QWebEngineView()
view.setUrl(QUrl("https://www.baidu.com/"))
view.show()
app.exec()
