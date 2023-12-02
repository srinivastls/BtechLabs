import socket
import cv2
import pickle
import struct
import uuid
import tkinter as tk
from PIL import Image, ImageTk
import numpy as np
import threading
import pyshine as ps
import re
import time
import pygame

pygame.init()
# Create the screen
tempr = 1

if tempr == 1:
    x = 0.8
    y = 0.8
    counter = 10
    timeinterval = 0.05
    screen = pygame.display.set_mode((900*x, 620*y))

    player1set = ''
    Name = ''
    Email = 0

    def ui():
        
       

        fonts3 = pygame.font.SysFont('Georgia', int(40*x), bold=True)
        message = fonts3.render("Enter the Name: ", True, 'white')
        message1 = fonts3.render("Enter the college EmailId: ", True, 'white')
        start = fonts3.render('Join', True, 'white')

        # Button positions
        button_positions = {
            "Start": (450*x, 500*y),
        }

        def gradientRects(screen, left_colour, right_colour, target_rect):
            gradient_surface = pygame.Surface(
                (target_rect.width, target_rect.height))
            left_color_stop = left_colour
            right_color_stop = right_colour
            for x in range(target_rect.width):
                factor = x / (target_rect.width - 1)
                r = int(left_color_stop[0] + factor *
                        (right_color_stop[0] - left_color_stop[0]))
                g = int(left_color_stop[1] + factor *
                        (right_color_stop[1] - left_color_stop[1]))
                b = int(left_color_stop[2] + factor *
                        (right_color_stop[2] - left_color_stop[2]))
                pygame.draw.line(gradient_surface, (r, g, b),
                                 (x, 0), (x, target_rect.height))
            screen.blit(gradient_surface, target_rect)

        target_rects = pygame.Rect(0, 0, 900*x, 620*y)
        Start_button = pygame.Rect(390*x, 430*y, 125*x, 60*y)
        id = pygame.font.SysFont('Georgia', int(40*x), bold=True)
        emails = pygame.font.SysFont('Georgia', int(40*x), bold=True)

        # Load background image
        global Name
        global Email
        global tempr
        ids = ''
        email = ''
        id_input_active = True
        running = True

        while running:
            gradientRects(screen, (150, 100, 40), (0, 100, 200), target_rects)
            screen.blit(message, (200, 150))
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.KEYDOWN:
                    if id_input_active:
                        if event.key == pygame.K_RETURN:  # User pressed Enter to switch to entering email
                            id_input_active = False
                        else:
                            ids += event.unicode
                    else:  # Entering email
                        if event.key == pygame.K_RETURN:  # User pressed Enter to start
                            if "@iiitdm.ac.in" in email.lower():
                                Name = ids
                                running = False
                        else:
                            email += event.unicode

                if event.type == pygame.MOUSEBUTTONUP:
                    if Start_button.collidepoint(event.pos):
                        if email and "@iiitdm.ac.in" in email.lower():
                            Email = email
                            Name = ids
                            running = False

            show_id = id.render(ids, True, (0, 0, 0))
            screen.blit(show_id, (270, 200))

            if id_input_active:
                if ids != '':
                    screen.blit(message1, (150, 250))
            else:  # Entering email
                screen.blit(message1, (150, 250))
                email_paid = emails.render(email, True, (0, 0, 0))
                screen.blit(email_paid, (220, 300))
                if email and "@iiitdm.ac.in" in email:
                    tempr = 0
                    pygame.draw.rect(screen, (200, 200, 100),
                                     Start_button, border_radius=3)
                    screen.blit(start, (320, 350))
                else:
                    tempr = 1

            pygame.display.update()

    ui()
    pygame.display.quit()

if tempr == 0:
    # IP = socket.gethostbyname(socket.gethostname())
    IP = "192.168.82.6"
    PORT = 1234
    PORT1 = 1235
    PORT2 = 1236
    PORT3 = 1237
    PORT4 = 1233
    SIZE = 4096
    FORMAT = "utf-8"
    DISCONNECT_MSG = "BYE"

    root = tk.Tk()
    root.title(f"Welcome to video call {Name}")

    # Create Canvas widgets for displaying video streams
    canvas1 = tk.Canvas(root, width=450, height=400)
    canvas1.grid(row=0, column=0, padx=5, pady=5)  # Top-left

    canvas2 = tk.Canvas(root, width=450, height=400)
    canvas2.grid(row=0, column=1, padx=5, pady=5)  # Top-right

    canvas3 = tk.Canvas(root, width=900, height=200, bg='lightblue')
    canvas3.grid(row=1, column=0, columnspan=2, padx=5, pady=5)

    message = ''

    filename = ""
    client_no = ""

    def display_message():
        val = ["1", "2", "3", "4", "5"]
        message = input_entry.get()
        if message == "-1":
            print(message)
            input_entry.delete(0, tk.END)
            message_text.config(state=tk.NORMAL)
            message_text.insert(tk.END, f"Enter FileName:\n")
            message_text.config(state=tk.DISABLED)
        elif "." in message:
            message_text.config(state=tk.NORMAL)
            message_text.insert(tk.END, f"{message}\n")
            message_text.config(state=tk.DISABLED)
            global filename
            filename = message
            print(filename)
            message_text.config(state=tk.NORMAL)
            message_text.insert(tk.END, f"Enter ClientNumber(eg:1, 2):\n")
            message_text.config(state=tk.DISABLED)
            input_entry.delete(0, tk.END)
        elif message in val:
            message_text.config(state=tk.NORMAL)
            message_text.insert(tk.END, f"ClientNo:{message}\n")
            global client_no
            client_no = message
            input_entry.delete(0, tk.END)
            to_send_file(filename, client_no)

        elif message:
            msg = message
            client_socket1.send(msg.encode(FORMAT))
            message_text.config(state=tk.NORMAL)
            message_text.insert(tk.END, f"{message}\n")
            message_text.config(state=tk.DISABLED)
            input_entry.delete(0, tk.END)

    frame = tk.Frame(canvas3, bg='black', width=850,
                     height=150)

    message_text = tk.Text(frame, width=70, height=6)
    message_text.config(state=tk.DISABLED)
    message_text.pack(padx=20, pady=8)

    input_entry = tk.Entry(frame, width=70)
    input_entry.pack(pady=5)

    send_button = tk.Button(
        frame, text="Send", command=display_message, width=10)
    send_button.pack(padx=2, pady=5)

    # Embed the frame in canvas3 at the bottom
    canvas3.create_window(450, 100, window=frame, anchor=tk.CENTER)

    # for video
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((IP, PORT))

    # for recv messages
    client_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket1.connect((IP, PORT1))

    # for recev file
    client_socket3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket3.connect((IP, PORT3))

    # for recev audio
    client_socket4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket4.connect((IP, PORT4))

    mode = 'send'
    name = 'CLIENT Sending AUDIO'
    mode1 = 'get'
    name1 = 'CLIENT RECEIVING AUDIO'

    def receive_messages():
        while True:
            try:
                msg = client_socket1.recv(SIZE).decode(FORMAT)
                if msg == DISCONNECT_MSG:
                    print("[Server] Disconnected.")
                    break
                message_text.config(state=tk.NORMAL)
                message_text.insert(tk.END, f"Client:{msg}\n")
                message_text.config(state=tk.DISABLED)
                input_entry.delete(0, tk.END)
            except ConnectionAbortedError:
                print("[Server] Connection was aborted by the server.")
                break

    def audio_streaming():
        # print("audio")
        data = b""
        payload_size = struct.calcsize("Q")
        audio, context = ps.audioCapture(mode=mode)
        # ps.showPlot(context1,name1)
        if client_socket4:
            while True:
                try:
                    frame = audio.get()
                    a = pickle.dumps(frame)
                    message = struct.pack("Q", len(a))+a
                    client_socket4.sendall(message)
                except:
                    continue

    def receive_audio():
        data = b""
        payload_size = struct.calcsize("Q")
        audio1, context1 = ps.audioCapture(mode=mode1)
        while True:
            try:
                while len(data) < payload_size:
                    packet = client_socket4.recv(2048)  # 4K
                    if not packet:
                        break
                    data += packet
                packed_msg_size = data[:payload_size]
                data = data[payload_size:]
                msg_size = struct.unpack("Q", packed_msg_size)[0]

                while len(data) < msg_size:
                    data += client_socket4.recv(2048)
                frame_data = data[:msg_size]
                data = data[msg_size:]
                audio1.put(frame)
                frame = pickle.loads(frame_data)
            except:
                print("Bye")
            
            

    def video_streaming():
        data = b""
        payload_size = struct.calcsize("Q")

        while True:
            if client_socket:
                cap = cv2.VideoCapture(0)
                while (cap.isOpened()):
                    img, frame = cap.read()
                    a = pickle.dumps(frame)
                    message = struct.pack("Q", len(a)) + a
                    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                    client_socket.sendall(message)
                    photo = ImageTk.PhotoImage(image=Image.fromarray(frame))
                    canvas1.create_image(0, 0, anchor=tk.NW, image=photo)
                    canvas1.update()

    def receive_frames():
        data = b""
        payload_size = struct.calcsize("Q")
        frame_data = None
        while True:
            try:
                while len(data) < payload_size:
                    packet = client_socket.recv(512)  # Increase buffer size
                    if not packet:
                        break
                    data += packet

                packed_msg = data[:payload_size]
                data = data[payload_size:]
                msg_size = struct.unpack("Q", packed_msg)[0]

                while len(data) < msg_size:
                    data += client_socket.recv(512)  # Increase buffer size
                frame_data = data[:msg_size]
                data = data[msg_size:]

            except Exception as e:
                print("Error:", e)
                break

            vid = pickle.loads(frame_data)

            # Update the canvas with the received frame
            vid = cv2.cvtColor(vid, cv2.COLOR_BGR2RGB)
            photo = ImageTk.PhotoImage(image=Image.fromarray(vid))
            canvas2.create_image(0, 0, anchor=tk.NW, image=photo)
            canvas2.update()

    def send_file(client, file_path):
        final_len = 0
        with open(file_path, "rb") as file:
            while True:
                data = file.read(SIZE)
                final_len += len(data)
                if not data:
                    break
        final_len = str(final_len)
        client.send(final_len.encode(FORMAT))
        time.sleep(2)
        print(final_len)

        with open(file_path, "rb") as file:
            while True:
                data = file.read(SIZE)
                # print(len(data))
                if not data:
                    break
                client.send(data)
        client.send(b"")  # Signal the end of the file

    def recevive_File():
        while True:
            print("Waiting for File ........")
            filename = client_socket3.recv(SIZE).decode(FORMAT)
            final_len = client_socket3.recv(SIZE).decode(FORMAT)
            print(final_len)
            final_len = int(final_len)
            if not filename:
                break
            print(filename)
            with open(filename, "wb") as file:
                while True:
                    data = client_socket3.recv(SIZE)
                    length = len(data)

                    final_len -= length
                    file.write(data)
                    if final_len <= 0:
                        break
            print("File Received")

    def to_send_file(filename, no):
        client_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket2.connect((IP, PORT2))
        FILENAME = filename
        print(FILENAME)
        client_socket2.send(FILENAME.encode(FORMAT))
        time.sleep(2)
        # msg = client_socket2.recv(SIZE).decode(FORMAT)
        print(no, filename)
        no = str(no)
        client_socket2.send(no.encode(FORMAT))
        time.sleep(2)
        send_file(client_socket2, FILENAME)
        client_socket2.close()

    def main1():
        mac = ':'.join(re.findall('..', '%012x' % uuid.getnode()))
        client_socket1.send(mac.encode(FORMAT))

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
    audio_thread = threading.Thread(target=audio_streaming)
    audio_thread.start()

    # start main thread
    main_thread = threading.Thread(target=main1)
    main_thread.start()

    # Create a separate thread for receiving frames
    receive_thread = threading.Thread(target=receive_frames)
    receive_thread.start()

    # receving audio of client
    receive_audio = threading.Thread(target=receive_audio)
    receive_audio.start()

    root.mainloop()