#import libraries
import RPi.GPIO as GPIO
import time
import signal
import sys

#GPIO Basic initialization
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Use a variable for the Pin to use
led = 4
#Initialize the pin
GPIO.setup(led,GPIO.OUT)

val = str(sys.argv[1])
if val=="1":
    print("Turning LED on")
    GPIO.output(led,1)

if val=="0":
    print("Turning LED off")
    GPIO.output(led,0)

