from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys
import RPi.GPIO as GPIO
import time

# declare pin number standard
GPIO.setmode(GPIO.BOARD)

#set pin mode
GPIO.setup(7, GPIO.OUT)
GPIO.setup(11, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)

class MyWindow(QMainWindow): #class creating an instance of QMainWindow
    def __init__(self):
        super(MyWindow, self).__init__()
        self.setGeometry(500, 300, 300, 200) #xpos, ypos, width, height
        self.setWindowTitle("LED Switch")
        self.initUI()
        
    def initUI(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("Press a button!")
        self.label.move(100, 150)
        
        self.b1 = QtWidgets.QRadioButton("Red", self)
        #self.b1.setText("Red")
        self.b1.move(100, 50)
        self.b1.clicked.connect(self.clickedRed)
        
        self.b2 = QtWidgets.QRadioButton("Blue", self)
        self.b2.move(100, 75)
        self.b2.clicked.connect(self.clickedBlue)
        
        self.b3 = QtWidgets.QRadioButton("Green", self)
        self.b3.move(100, 100)
        self.b3.clicked.connect(self.clickedGreen)

        
    def clickedRed(self):
        self.label.setText("Red LED On")
        GPIO.output(7, GPIO.HIGH)
        GPIO.output(11, GPIO.LOW)
        GPIO.output(13, GPIO.LOW)
        
    def clickedGreen(self):
        self.label.setText("Green LED On")
        GPIO.output(7, GPIO.LOW)
        GPIO.output(11, GPIO.HIGH)
        GPIO.output(13, GPIO.LOW)
        
    def clickedBlue(self):
        self.label.setText("Blue LED On")
        GPIO.output(7, GPIO.LOW)
        GPIO.output(11, GPIO.LOW)
        GPIO.output(13, GPIO.HIGH)
    
    def closeEvent(self, event):
        GPIO.output(7, GPIO.LOW)
        GPIO.output(11, GPIO.LOW)
        GPIO.output(13, GPIO.LOW)
        

def window():
    app = QApplication(sys.argv) #config setup (os, window specs etc)
    window = MyWindow() #create window instance

    window.show() # initialise window
    sys.exit(app.exec_())
    
window() #launch window