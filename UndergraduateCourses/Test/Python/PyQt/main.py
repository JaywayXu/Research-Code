import sys
from PyQt5.QtWidgets import QApplication, QWidget

if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = QWidget()
    widget.resize(400, 400)
    widget.setWindowTitle('Hello World')
    widget.show()
    sys.exit(app.exec_())
