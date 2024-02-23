import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtCore import QTimer
from Gui import Ui_MainWindow
import serial

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        # Open the serial port
        self.serialInst = serial.Serial("COM4", 9600)

        # Create a QTimer to read serial periodically
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.read_serial)
        self.timer.start(100)  # Adjust the interval (milliseconds) as needed

    def read_serial(self):
        if self.serialInst.in_waiting:
            # Read a line from the serial port
            packet = self.serialInst.readline()
            # Treat the line as the value itself
            value = packet.decode('utf-8').strip()
            # Convert the value to an integer
            try:
                value_int = int(value)
                # Update your widget with the received value
                self.progressBar.setValue(value_int)
            except ValueError:
                print("Invalid value received from Arduino:", value)

    def closeEvent(self, event):
        # Close the serial port when the window is closed
        self.serialInst.close()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
