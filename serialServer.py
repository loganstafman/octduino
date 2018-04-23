
import serial
import sys
import SendKeys
import threading
import time
from pykeyboard import PyKeyboard

ser = serial.Serial('COM4', 9600)

class keyThread(threading.Thread):
	def run(self):
		keys = ['w','a','s','d']
		while True:
			for k in keys:
				if keyOn[k]:
					SendKeys.SendKeys("{DOWN}")

keyboard = PyKeyboard()
keyOn = {'w': False, 'a': False, 's': False, 'd': False}
#myThread = keyThread(name = "keyThread")
#myThread.start()
while True:
	keyPress = ser.readline().rstrip()
	#SendKeys.SendKeys(keyPress)
	print keyPress
	key = keyPress.split(" ")[0]
	turnOn = keyPress.split(" ")[1] == "on"
	if turnOn:
		#keyOn[key] = True
		keyboard.press_key(key)
	else:
		keyboard.release_key(key)
		#keyOn[key] = False
