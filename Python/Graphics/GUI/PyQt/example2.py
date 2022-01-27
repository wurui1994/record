# An Expression Evaluator in 30 Lines
from __future__ import division

import sys

from PyQt6.QtCore import *
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import (QApplication, QLineEdit, QTextBrowser,
                             QVBoxLayout, QDialog)

class Form(QDialog):
    def __init__(self, parent=None):
        super(Form, self).__init__(parent)
        self.browser = QTextBrowser()
        font = QFont("Consolas", 14, QFont.Weight.DemiBold)
        font.setStyle(QFont.Style.StyleItalic)
        self.browser.setFont(font)
        self.lineedit = QLineEdit('Type an express and press Enter')
        self.lineedit.selectAll()
        layout = QVBoxLayout()
        layout.addWidget(self.browser)
        layout.addWidget(self.lineedit)
        self.setLayout(layout)
        self.lineedit.setFocus()
        # self.connect(self.lineedit,SIGNAL('returnPressed()'),self.updateUi)
        self.lineedit.returnPressed.connect(self.updateUi)
        self.setWindowTitle('Calculate')

    def updateUi(self):
        try:
            text = self.lineedit.text()
            self.browser.append('%s = %s' % (text, eval(text)))
        except:
            self.browser.append('%s is invalid!' % text)

app = QApplication(sys.argv)
app.setFont(QFont("Times New Roman", 14,
            italic=False, weight=QFont.Weight.Bold))
form = Form()
form.show()
app.exec()
