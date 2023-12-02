import socket
import cv2
import pickle
import struct

#providing server ip and port
family = socket.AF_INET
protocol = socket.SOCK_STREAM
clien1 = socket.socket(family, protocol)
clien1.connect(("172.17.0.169", 7777))
data1 = b""
payload_size = struct.calcsize("Q")


# sending our photo in a loop to the server
while True:
    cap = cv2.VideoCapture(0)
    img,fram = cap.read()
    a = pickle.dumps(fram)
    messag = struct.pack("Q",len(a))+a
    clien1.sendall(messag)
    while len(data1) < payload_size:
        packet1 = clien1.recv(4096)
        if not packet1:
            print("not connected") 
            break
        data1+=packet1
    packed_msg1 = data1[:payload_size]
    data1 = data1[payload_size:]
    msg_size = struct.unpack("Q",packed_msg1)[0]
    
    while len(data1) < msg_size:
        data1 += clien1.recv(4096)
    frame = data1[:msg_size]
    data1  = data1[msg_size:]
    vid = pickle.loads(frame)
    cv2.imshow("Video from server to client",vid)
    key = cv2.waitKey(1) & 0xFF
    if key ==ord('q'):
        clien1.close()