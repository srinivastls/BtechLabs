import socket
import cv2
import pickle
import struct
import threading

IP="172.17.0.169"
PORT=1234
PORT1=1235
ADDR = (IP, 1235)
SIZE = 1024
FORMAT = "utf-8"
DISCONNECT_MSG = "BYE"


connected_clients = []

# List to store client connections and addresses
connections = []
addresses = []

# Function to handle individual clients
def handle_client_msg(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    connected = True

    while connected:
        try:
            msg = conn.recv(SIZE).decode(FORMAT)
            if msg == DISCONNECT_MSG:
                print(f"[{addr}] {msg}") 
                print(connections, addresses)
                connections.remove(conn)
                addresses.remove(addr)
                print(connections, addresses)
                connected = False
            else:
                print(f"[{addr}] {type(msg)}")
                if (msg == "1" or msg == "2" or msg == "3" or msg == "4" or msg == "5" or msg == "6" or msg == "7" or msg == "8" or msg == "9" or msg == "10" or msg == "11"):
                    client_number = int(msg) - 1

                if client_number < 0 or client_number >= len(connections):
                    print("Invalid client position.")
                    continue

                target_client = connections[client_number]
                msg = msg

                target_client.send(msg.encode(FORMAT))

        except ConnectionResetError:
            print(f"[{addr}] Client connection forcibly closed.")
            connections.remove(conn)
            addresses.remove(addr)
            break

    conn.close()


def handle_client_video(client_socket):

    print("Accepted connection from:", client_socket.getpeername())
    data = b""
    payload_size = struct.calcsize("Q")
    
    
    #sending photo as a video to the client
    
    if len(connected_clients)>0:
        while True:
            print("hello")
            while len(data) < payload_size:
                packet = client_socket.recv(4096)
                
                if not packet: 
                    break
                data+=packet
            packed_msg = data[:payload_size]
            data = data[payload_size:]
            msg_size = struct.unpack("Q",packed_msg)[0]
            
            while len(data) < msg_size:
                data += client_socket.recv(4096)
            frame = data[:msg_size]
            data  = data[msg_size:]
            vid = pickle.loads(frame)
            if len(connected_clients)>1:
                # print("yoou ")
                try:
                    b = pickle.dumps(vid)
                    message1 = struct.pack("Q",len(b))+b
                    for client in connected_clients:
                        if client!=client_socket:
                            client.sendall(message1)
                except:
                    print("ehllo")
            # cv2.imshow("Video from client_sockett",vid)
            key = cv2.waitKey(1) & 0xFF
            if key  == ord('q'):
                break
    
                    
    # print("Connection closed:", client_socket.getpeername())
    # connected_clients.remove(client_socket)
    # client_socket.close()    


#Socket setup
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((IP,PORT))
server_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket1.bind((IP,PORT1))
server_socket.listen(5)  # Allow up to 5 connections
server_socket1.listen(5)  # Allow up to 5 connections
print("[Starting] server is starting...")
print(f"[Listening] Server is listening on {IP}:{PORT}")
                
                
while True:
    

    #For video
    client_socket, client_address = server_socket.accept()
    connected_clients.append(client_socket)
    client_handler_video = threading.Thread(target=handle_client_video, args=(client_socket,))
    client_handler_video.start()
    
    
    
    #For msg
    conn,addr = server_socket1.accept()
    connections.append(conn)
    addresses.append(addr)
    client_number = len(connections)
    thread_chat = threading.Thread(target=handle_client_msg, args=(conn, addr))
    thread_chat.start()
    
    print(f"[Active connections] {threading.active_count() - 1}")
