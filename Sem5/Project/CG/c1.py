import cv2
import socket
import pickle
import struct

# Create a socket to connect to the server
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("172.17.0.169", 8888))



while True:
    vid = cv2.VideoCapture(0)
    while(vid.isOpened()):
        img, frame = vid.read()
        a = pickle.dumps(frame)
        message = struct.pack("Q",len(a))+a
        client_socket.sendall(message)
        cv2.imshow('TRANSMITTING VIDEO', frame)
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            client_socket.close()


