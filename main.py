from MainWindow import *

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = LoginWindow()
    window.setWindowTitle('Sign Up')
    window.setWindowIcon(QtGui.QIcon('assets\\865969.png'))
    window.show()
    sys.exit(app.exec_())