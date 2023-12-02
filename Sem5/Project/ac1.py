import socket
import cv2
import pickle
import struct
import tkinter as tk
from PIL import Image, ImageTk
import numpy as np
import threading


IP="172.17.0.169"
PORT=1234
PORT1=1235
SIZE = 1024
FORMAT = "utf-8"
DISCONNECT_MSG = "BYE"
data = b""
payload_size = struct.calcsize("Q")


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((IP,PORT))

client_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket1.connect((IP,PORT1))



# class TwoWindowGUI:
#     def __init__(self, root, frame1, frame2, width, height, channels):
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


def video_streaming():
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
                        packet = client_socket.recv(54096)
                            
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
                vid = pickle.loads(frame,encoding="bytes")
                cv2.imshow('Video in client from server',vid)
                # width=300
                # height=300
                # channels=9
        
                # # Create an instance of the TwoWindowGUI class
                # app = TwoWindowGUI(root, frame, vid, width, height, channels)
                key = cv2.waitKey(1) & 0xFF
                if key ==ord('q'):
                    client_socket.close()
    

def chat_input():
     while True:
        msg = input("> ")
        client_socket1.send(msg.encode(FORMAT))

# Start a new thread for receiving chat messages
#chat_thread = threading.Thread(target=receive_messages)
#chat_thread.start()
#chat_thread_input=threading.Thread(target=chat_input)
#chat_thread_input.start()

# Start a new thread for video streaming
video_thread = threading.Thread(target=video_streaming)
video_thread.start()



  

# while True:
#         # print("hello")
        
#         if client_socket:
#             cap = cv2.VideoCapture(0)
#             while(cap.isOpened()):
#                 img,frame = cap.read()
#                 a = pickle.dumps(frame)
#                 message = struct.pack("Q",len(a))+a
#                 client_socket.sendall(message)
#                 cv2.imshow('Video in client',frame)
                
#                 try:
#                     while len(data) < payload_size:
#                         packet = client_socket.recv(4096)
                            
#                         if not packet: 
#                             break
#                         data+=packet
                    
#                     packed_msg = data[:payload_size]
#                     data = data[payload_size:]
#                     msg_size = struct.unpack("Q",packed_msg)[0]
                        
#                     while len(data) < msg_size:
#                         data += client_socket.recv(4096)
#                     frame = data[:msg_size]
#                     data  = data[msg_size:]
#                 except:
#                     print("bye")
#                 vid = pickle.loads(frame)
#                 cv2.imshow('Video in client from server',vid)
#                 # width=300
#                 # height=300
#                 # channels=9
        
#                 # # Create an instance of the TwoWindowGUI class
#                 # app = TwoWindowGUI(root, frame, vid, width, height, channels)
#                 key = cv2.waitKey(1) & 0xFF
#                 if key ==ord('q'):
#                     client_socket.close()
      
