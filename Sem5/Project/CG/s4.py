import socket
import cv2
import pickle
import struct

# Socket Create
family = socket.AF_INET
protocol = socket.SOCK_STREAM
serv = socket.socket(family, protocol)

# binding ip address with the port
serv.bind(('172.17.0.169', 7777))
serv.listen(5)
data = b""
data1= b""
payload_size = struct.calcsize("Q")
#sending photo as a video to the client

clien, addr = serv.accept()
clien1, addr1 = serv.accept()
while True:
    while len(data) < payload_size:
        packet = clien1.recv(4096)
        packet1 = clien.recv(4096)
        if not packet or not packet1: 
            break
        else:
            print("connected1")
            data+=packet
            data1+=packet1
        
    packed_msg = data[:payload_size]
    data = data[payload_size:]
    packed_msg1 = data1[:payload_size]
    data1 = data1[payload_size:]
    clien.sendall(packed_msg)
    clien1.sendall(packed_msg1)
    
    msg_size = struct.unpack("Q",packed_msg1)[0]
    
    while len(data1) < msg_size:
        data1 += clien1.recv(4096)
    frame = data1[:msg_size]
    data1  = data1[msg_size:]
    vid = pickle.loads(frame)
    cv2.imshow("Video from server to client",vid)
    
    key = cv2.waitKey(1) & 0xFF
    if key  == ord('q'):
        break