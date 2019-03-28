import time
import RPi.GPIO as GPIO

SER = 11  # Pin for serial
RCLK = 12  # Pin for register clock
SRCLK = 13  # Pin for serial clock

# Initialize pins to output
GPIO.setmode(GPIO.BOARD)
GPIO.setup(SER, GPIO.OUT)
GPIO.setup(RCLK, GPIO.OUT)
GPIO.setup(SRCLK, GPIO.OUT)
GPIO.output(SER, GPIO.LOW)
GPIO.output(RCLK, GPIO.LOW)
GPIO.output(SRCLK, GPIO.LOW)

# 32-Bit pattern used for registers
# First 16 bits (bits 0 - 15) for the 16 rows (positive)
# Second 16 bits (bits 16 - 31) for 16 columns (negative)
#
# In this case, the first 16 bits are all HIGH, so all rows
# will receive positive voltage
# The other bits are LOW, so all columns will be GROUND
# This pattern will light up all LEDs
pat = 0b11111111111111110000000000000000


# Load bit pattern to registers
def load(pat):
    for i in range(32):
        state = (pat >> i) & 0b1  # Isolate the last bit
        GPIO.output(SER, int(state))  # Set serial pin to hold this value
        GPIO.output(SRCLK, GPIO.HIGH)  # Set clock to high to load value
        GPIO.output(SRCLK, GPIO.LOW)  # Reset clock to LOW

	# Once loop is complete, set the register clock to HIGH
	# to load register values 
    GPIO.output(RCLK, GPIO.HIGH)
    GPIO.output(RCLK, GPIO.LOW)

try:
	# Load pattern infinitely (loop not necessary, but useful for testing)
    while (1):
        load(pat)
except KeyboardInterrupt:
	# When existing with ctrl-C, we make sure to do 'cleanup' on pins
    GPIO.cleanup()
