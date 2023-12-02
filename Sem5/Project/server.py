#Importing all the Libraries
import socket, cv2, pickle, struct

#Creating the Socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_name = socket.gethostname()
host_ip = socket.gethostbyname(host_name)
print('HOST IP:', host_ip)
port = 2222
socket_address = (host_ip, port)
print("Socket created successfully !!")

#Binding Socket
server_socket.bind(socket_address)

#Socket Listen
server_socket.listen(5)
print("LISTENING AT:", socket_address)

#Socket Accept
while True:
    client_socket, addr = server_socket.accept()
    print('Got Connection From:', addr)
    if client_socket:
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