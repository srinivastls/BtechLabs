import cv2
import socket
import pickle
import struct

# Create a socket to connect to the server
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("172.17.0.169", 8888))

# Create a VideoCapture object to capture video from the system camera
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    # Serialize the frame using pickle and send it to the server
    data = pickle.dumps(frame)
    client_socket.sendall(struct.pack("<L", len(data)) + data)

# Release resources
cap.release()
client_socket.close()
