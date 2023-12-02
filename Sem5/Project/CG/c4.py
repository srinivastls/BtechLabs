import socket
import cv2
import pickle
import struct

#providing server ip and port
family = socket.AF_INET
protocol = socket.SOCK_STREAM
clien = socket.socket(family, protocol)
clien.connect(("172.17.0.169", 7777))
data = b""
payload_size = struct.calcsize("Q")


# sending our photo in a loop to the server
while True:
    cap = cv2.VideoCapture(0)
    img,fram = cap.read()
    a = pickle.dumps(fram)
    messag = struct.pack("Q",len(a))+a
    clien.sendall(messag)
   
    key = cv2.waitKey(1) & 0xFF
    if key ==ord('q'):
        clien.close()