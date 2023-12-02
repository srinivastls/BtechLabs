import socket
import cv2
import pickle
import struct
import threading
from tkinter import *

class VideoConferenceClient:
    def __init__(self):
        self.root = Tk()
        self.root.title("Video Conference Client")

        # Create the video frame
        self.video_frame = Frame(self.root)
        self.video_frame.pack()

        # Create the video canvas
        self.video_canvas = Canvas(self.video_frame, width=640, height=480)
        self.video_canvas.pack()

        # Create the client socket
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect(('localhost', 8000))

        # Start a new thread to receive and display the video stream from the server
        thread = threading.Thread(target=self.receive_and_display_video_stream)
        thread.start()

    def receive_and_display_video_stream(self):
        while True:
            data = self.client_socket.recv(1024)
            if data:
                # Decode the video frame
                frame = pickle.loads(data)

                # Display the video frame
                self.video_canvas.create_image(0, 0, image=frame, anchor=NW)
                self.video_canvas.update()

if __name__ == '__main__':
    client = VideoConferenceClient()
    client.root.mainloop()
