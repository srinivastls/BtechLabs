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
payload_size = struct.calcsize("Q")
#sending photo as a video to the client
clien, addr = serv.accept()
if clien:
    while True:
        cap = cv2.VideoCapture(0)
        img,fram = cap.read()
        a = pickle.dumps(fram)
        messag = struct.pack("Q",len(a))+a
        clien.sendall(messag)
        while len(data) < payload_size:
            packet = clien.recv(4096)
            if not packet: 
                break
            data+=packet
        packed_msg = data[:payload_size]
        data = data[payload_size:]
        msg_size = struct.unpack("Q",packed_msg)[0]
        
        while len(data) < msg_size:
            data += clien.recv(4096)
        frame = data[:msg_size]
        data  = data[msg_size:]
        vid = pickle.loads(frame)
        cv2.imshow("Video from Client",vid)
        key = cv2.waitKey(1) & 0xFF
        if key  == ord('q'):
            break