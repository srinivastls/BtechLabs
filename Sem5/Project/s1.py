import socket
import cv2
import pickle
import struct
import threading

class VideoConferenceServer:
    def __init__(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind(('localhost', 8000))
        self.server_socket.listen(10)

        self.client_sockets = []
        self.client_threads = []

    def run(self):
        while True:
            client_socket, client_address = self.server_socket.accept()
            self.client_sockets.append(client_socket)

            # Start a new thread to handle the new client connection
            thread = threading.Thread(target=self.handle_client_connection, args=(client_socket,))
            thread.start()
            self.client_threads.append(thread)

    def handle_client_connection(self, client_socket):
        # Receive the video stream from the client
        while True:
            data = client_socket.recv(1024)
            if data:
                # Decode the video frame
                frame = pickle.loads(data)

                # Send the video frame to all other clients
                for client_socket in self.client_sockets:
                    if client_socket != client_socket:
                        client_socket.sendall(frame)

if __name__ == '__main__':
    server = VideoConferenceServer()
    server.run()
