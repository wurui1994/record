# Blank Window
import sys
from PyQt6 import QtWidgets

def main():
    app = QtWidgets.QApplication(sys.argv)
    w = QtWidgets.QWidget()
    w.resize(640, 480)
    w.move(350, 120)
    w.setWindowTitle('Simple')
    w.show()
    return app.exec()

if __name__ == '__main__':
    main()
