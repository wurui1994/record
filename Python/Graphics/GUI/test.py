# -*- coding: utf-8 -*-

import sys
from PyQt6.QtCore import pyqtSlot
from PyQt6.QtWidgets import QDialog, QApplication, QFileDialog

class Hash(QDialog):
    def __init__(self, parent=None):
        super(Hash, self).__init__(parent)
        # self.setupUi(self)

    @pyqtSlot()
    def on_open_btn_clicked(self):
        """
        Slot documentation goes here.
        """
        file = QFileDialog.getOpenFileName(self, "open file", '/')
        self.fileAddr_txt.setText(file)
        # TODO: not implemented yet
        #raise NotImplementedError

if __name__ == '__main__':
    app = QApplication(sys.argv)
    dlg = Hash()
    dlg.show()
    sys.exit(app.exec())
