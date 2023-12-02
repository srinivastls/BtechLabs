import socket
import cv2
import pickle
import struct
import tkinter as tk
from PIL import Image, ImageTk
import numpy as np
import threading
import pyshine as ps


IP="172.17.1.243"
PORT=1234
PORT1=1235
PORT2=1236
PORT3=1237
PORT4=1233
SIZE = 4096
FORMAT = "utf-8"
DISCONNECT_MSG = "BYE"


#for video
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((IP,PORT))

#for recv messages
client_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket1.connect((IP,PORT1))



#for recev file
client_socket3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket3.connect((IP,PORT3))

#for recev audio
client_socket4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket4.connect((IP,PORT4))

mode =  'send'
name = 'CLIENT Sending AUDIO'
mode1 =  'get'
name1 = 'CLIENT RECEIVING AUDIO'




# class TwoWindowGUI:
#     def _init_(self, root, frame1, frame2, width, height, channels):
#         self.root = root
#         self.root.title("Two Window GUI")

#         self.width = width
#         self.height = height
#         self.channels = channels

#         # Convert frame data to NumPy arrays
#         self.frame1 = np.frombuffer(frame1, dtype=np.uint8)
#         self.frame2 = np.frombuffer(frame2, dtype=np.uint8)

#         # Reshape arrays to image dimensions
#         self.frame1 = self.frame1.reshape((self.height, self.width, self.channels))
#         self.frame2 = self.frame2.reshape((self.height, self.width, self.channels))

#         # Create labels for displaying images
#         self.label1 = tk.Label(root)
#         self.label1.pack(side="left")

#         self.label2 = tk.Label(root)
#         self.label2.pack(side="right")

#         # Call the update function to start updating images
#         self.update()

#     def update(self):
#         # Convert NumPy arrays to PhotoImage objects
#         img1 = ImageTk.PhotoImage(Image.fromarray(self.frame1))
#         img2 = ImageTk.PhotoImage(Image.fromarray(self.frame2))

#         # Update the labels with the new images
#         self.label1.config(image=img1)
#         self.label1.image = img1

#         self.label2.config(image=img2)
#         self.label2.image = img2

#         # Call the update function after a delay (in milliseconds)
#         self.root.after(10, self.update)



def receive_messages():
    while True:
        try:
            msg = client_socket1.recv(SIZE).decode(FORMAT)
            if msg == DISCONNECT_MSG:
                print("[Server] Disconnected.")
                break
            if (msg == "1" or msg == "2" or msg == "3" or msg == "4" or msg == "5" or msg == "6" or msg == "7" or msg == "8" or msg == "9" or msg == "10" or msg == "11"):
                print(f"[Active number of client] {msg}")
            else:
                print(f"[Client] {msg}")
        except ConnectionAbortedError:
            print("[Server] Connection was aborted by the server.")
            break


def audio_streaming():
    # print("audio")
    data= b""
    payload_size= struct.calcsize("Q")
    audio,context= ps.audioCapture(mode=mode)
    audio1,context1= ps.audioCapture(mode=mode1)
    ps.showPlot(context1,name1)   
    if client_socket4:
        while True:
            
            print("audo insisde")
            frame = audio.get()
            print("audio outside")
            a=pickle.dumps(frame)
            message = struct.pack("Q",len(a))+a
            client_socket4.sendall(message)
            # audio.put(frame)
            try:
                while len(data) < payload_size:
                    packet = client_socket4.recv(4*1024) # 4K
                    if not packet:
                        break
                    data+=packet
                packed_msg_size = data[:payload_size]
                data = data[payload_size:]
                msg_size = struct.unpack("Q",packed_msg_size)[0]
                
                while len(data) < msg_size:
                    data += client_socket4.recv(4*1024)
                frame_data = data[:msg_size]
                data  = data[msg_size:]
            except:
                print("Bye")
            frame = pickle.loads(frame_data)
            audio1.put(frame)
                    

def video_streaming():
   print("hello")
   data = b""
   payload_size = struct.calcsize("Q")
   while True:
        if client_socket:
            cap = cv2.VideoCapture(0)
            while(cap.isOpened()):
                img,frame = cap.read()
                a = pickle.dumps(frame)
                message = struct.pack("Q",len(a))+a
                client_socket.sendall(message)
                cv2.imshow('Video in client',frame)
               
                try:
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
                  
                except:
                    print("bye")
                vid = pickle.loads(frame)
                cv2.imshow('Video in client from server',vid)
                # width=300
                # height=300
                # channels=9
        
                # # Create an instance of the TwoWindowGUI class
                # app = TwoWindowGUI(root, frame, vid, width, height, channels)
                key = cv2.waitKey(1) & 0xFF
                if key ==ord('q'):
                    client_socket.close()
    


def send_file(client, file_path):
    with open(file_path, "rb") as file:
        while True:
            data = file.read(SIZE)
            print(len(data))
            if not data:
                break
            client.send(data)
    client.send(b"")  # Signal the end of the file


def recevive_File():
    
    while True:
        print("Waiting for File ........")
        filename = client_socket3.recv(SIZE).decode(FORMAT)
        if not filename:
            break
        print(filename)
        with open(filename, "wb") as file:
            while True:
                data = client_socket3.recv(SIZE)
                print(len(data))
                if len(data)<4096:
                    file.write(data)
                    break
                file.write(data)
        print("File Received")
  
# Start a new thread for receiving chat messages
chat_thread = threading.Thread(target=receive_messages)
chat_thread.start()

# Start a new thread for video streaming
video_thread = threading.Thread(target=video_streaming)
video_thread.start()

# Start a new thread for receving files
file_recevie_thread = threading.Thread(target=recevive_File)
file_recevie_thread.start()

# Start a new thread for receving audio
audio_thread= threading.Thread(target=audio_streaming)
audio_thread.start()


def to_chat():
    while True:
        msg = input("> ")
        if(msg=="-1"):
            break
        client_socket1.send(msg.encode(FORMAT))

def to_send_file():
    client_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket2.connect((IP,PORT2))
    FILENAME = input("Enter the files name to send with extension (For ex: sample.txt) or for receiving Enter -1: ")
    print(FILENAME)
    client_socket2.send(FILENAME.encode(FORMAT))
    msg = client_socket2.recv(SIZE).decode(FORMAT)
    no = input(msg)
    client_socket2.send(no.encode(FORMAT))
    send_file(client_socket2, FILENAME)
    print("hello")
    client_socket2.close()

while True:
   
    print("1.To Chat\n 2.To Send File")
    option=int(input("Enter here:"))
    if option==1:
        to_chat()
    else:
        to_send_file()