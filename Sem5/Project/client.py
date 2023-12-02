#Import the Libraries

import socket, cv2, pickle, struct

 #socket create
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#In the host_ip put the IP address you just got as output after running the Server.py code.
host_name = socket.gethostname()
host_ip = socket.gethostbyname(host_name)
port = 2222     
client_socket.connect((host_ip,port))
data = b""
payload_size = struct.calcsize("Q")
while True:
    while len(data) < payload_size:
        packet = client_socket.recv(4*1024) 
        if not packet: break
        data+=packet
    packed_msg_size = data[:payload_size]
    data = data[payload_size:]
    msg_size = struct.unpack("Q", packed_msg_size)[0]    
    
    while len(data) < msg_size:
        data += client_socket.recv(4*1024)
    frame_data = data[:msg_size]
    data = data[msg_size:]
    frame = pickle.loads(frame_data)
    cv2.imshow("Recived", frame)
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):     #using the letter q to quit 
        break
client_socket.close()