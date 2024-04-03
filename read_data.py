import serial
import time
from datetime import datetime

def save_serial_data_to_file(serial_port, filename):
    ser = serial.Serial(serial_port, 9600)  # Adjust baud rate as needed
    while True:
        data = ser.readline().decode('utf-8')  # Read data from serial port
        # print(data)  # Print the data to the console (optional)
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # Get current timestamp
        # print(timestamp)
        formatted_data = f"{timestamp}: {data}"
        print(formatted_data.strip())  # Print the data to the console (optional)
        with open(filename, 'a') as f:
            f.write(formatted_data)
            f.flush()  # Flush buffer to ensure data is written immediately


if __name__ == "__main__":
    # serial_port = input("Enter the serial port (e.g., '/dev/ttyUSB0'): ")
    # filename = input("Enter the filename to save data to: ")
    serial_port = "/dev/tty.usbserial-1420"
    timestamp = datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
    filename = "data_" + str(timestamp) + ".txt"
    save_serial_data_to_file(serial_port, filename)