import socket
import cv2
import pickle
import struct
import threading
import pyshine as ps
IP="192.168.189.49"

PORT=1234# for video
PORT1=1235#for chat
PORT2=1236#for sending file transfer
PORT3=1237#for receving file
PORT4=1233#for audio
ADDR = (IP, 1235)
SIZE = 4096
FORMAT = "utf-8"
DISCONNECT_MSG = "BYE"


connected_clients = []

# List to store client connections and addresses
connections = []
addresses = []
clients_sen = []
clients_recv = []
clients_audio=[]

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
                for client in connections:
                    if client!=conn:
                        client.send(msg.encode(FORMAT))

        except ConnectionResetError:
            print(f"[{addr}] Client connection forcibly closed.")
            connections.remove(conn)
            addresses.remove(addr)
            break

    conn.close()



#Funciton to send audio
def handle_client_audio(client_socket):
    data = b""
    payload_size = struct.calcsize("Q")
   
    # ps.showPlot(context,name)
    if len(clients_audio)>0:
        while True:
            # print("hi")
            while len(data) < payload_size:
                packet = client_socket.recv(8192)
                if not packet:
                    break
                data+=packet
            packed_msg_size = data[:payload_size]
            data = data[payload_size:]
            msg_size = struct.unpack("Q",packed_msg_size)[0]
        
            while len(data) < msg_size:
                data += client_socket.recv(8192)
            frame_data = data[:msg_size]
            data  = data[msg_size:]
            frame = pickle.loads(frame_data)
            # audio.put(frame)
            if len(clients_audio)>1:
                # print("yoou ")
                try:
                    c = pickle.dumps(frame)
                    message1 = struct.pack("Q",len(c))+c
                    for client in clients_audio:
                        if client!=client_socket:
                            client.sendall(message1)
                except:
                    print("ehllo")
            
#Function to handle indivail files
def handle_client_video(client_socket):

    print("Accepted connection from:", client_socket.getpeername())
    data = b""
    payload_size = struct.calcsize("Q")
    #sending photo as a video to the client
    if len(connected_clients)>0:
        while True:
            # print("hello")
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


def send_chunk(cli, chunk):
    target_client = clients_recv[cli - 1]
    print(len(chunk))
    target_client.send(chunk)

def receive_and_send_chunks(sender_conn, receiver_conn,filename):
    target=clients_recv[receiver_conn-1]
    target.send(filename.encode(FORMAT))
    while True:
        chunk = sender_conn.recv(SIZE)
        if not chunk:
            break
        send_chunk(receiver_conn, chunk)
    
    print("ENd")
    
 
#Function to handle for file
def handle_client_file(conn,addr):
    connected = True
    
    while connected:
        try:
            filename = conn.recv(SIZE).decode(FORMAT)
            if not filename:
                break
            print(filename)
            msg = "Send the receive client no:"
            conn.send(msg.encode(FORMAT))
            rec_input=conn.recv(SIZE).decode(FORMAT)
            rec_input=int(rec_input)
            receive_and_send_chunks(conn, rec_input,filename)  # Modify to specify the receiver client here
            print("123")
        except Exception as e:
            print(f"Error handling client {addr}: {e}")
            break

    print(f"{addr} DISCONNECTED")
   
    conn.close()

#Socket setup
#server for video
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((IP,PORT))
# server for chat
server_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket1.bind((IP,PORT1))

#sending server for filetranfer
server_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket2.bind((IP,PORT2))

#receving server for filetranfer
server_socket3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket3.bind((IP,PORT3))

#receving server for audio transfer
server_socket4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket4.bind((IP,PORT4))



server_socket.listen(5)  # Allow up to 5 connections
server_socket1.listen(5)  # Allow up to 5 connections
server_socket2.listen(5)  # Allow up to 5 connections
server_socket3.listen(5)  # Allow up to 5 connections
server_socket4.listen(5)  # Allow up to 5 connections
print("[Starting] server is starting...")
print(f"[Listening] Server is listening on {IP}:{PORT}")
     
#for all other message video and receving thread           
def all_Connect():
        while True:
            #threding for video
            client_socket, client_address = server_socket.accept()
            connected_clients.append(client_socket)
            client_handler_video = threading.Thread(target=handle_client_video, args=(client_socket,))
            client_handler_video.start()
                
        
            #thread for msg
            conn,addr = server_socket1.accept()
            connections.append(conn)
            addresses.append(addr)
            thread_chat = threading.Thread(target=handle_client_msg, args=(conn, addr))
            thread_chat.start()    
            
            
            #thread for audio
            conn,addr = server_socket4.accept()
            clients_audio.append(conn)
           
            thread_audio = threading.Thread(target=handle_client_audio, args=(conn,))
            thread_audio.start()    
            
            
            #for reecvin for file
            conn,addr=server_socket3.accept()
            clients_recv.append(conn)
            
            print(f"[Active connections] {threading.active_count() - 1}")
    
#for connecting senders clients            
def Send_thread():  
    while True:      
        #thread for sending transfer
        conn, addr = server_socket2.accept()
        clients_sen.append(conn)
        thread_file = threading.Thread(target=handle_client_file, args=(conn, addr))          #calling the handle clinet funciton
        thread_file.start()
        
                
send_thread=threading.Thread(target=all_Connect)
se_thread=threading.Thread(target=Send_thread)
send_thread.start()
se_thread.start()

       
        


   
    
    
