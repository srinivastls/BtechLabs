import cv2
import socket
import pickle
import struct
import threading

def send_video(client_socket):
    cap = cv2.VideoCapture(0)
    while True:
        ret, frame = cap.read()
        if not ret:
            continue
        try:
            a = pickle.dumps(frame)
            message = struct.pack("Q", len(a)) + a
            client_socket.sendall(message)
        except (socket.error, EOFError) as e:
            print(f"Socket error: {e}")
            break
    client_socket.close()

def receive_video(client_socket, client_name):
    cv2.namedWindow(f"{client_name}'s Video", cv2.WINDOW_NORMAL)
    cv2.resizeWindow(f"{client_name}'s Video", 640, 480)

    while True:
        try:
            data = b""
            payload_size = struct.calcsize("Q")
            while len(data) < payload_size:
                packet = client_socket.recv(4 * 1024)
                if not packet:
                    break
                data += packet
            packed_msg_size = data[:payload_size]
            data = data[payload_size:]
            msg_size = struct.unpack("Q", packed_msg_size)[0]

            while len(data) < msg_size:
                data += client_socket.recv(4 * 1024)
            frame_data = data[:msg_size]
            data = data[msg_size:]
            frame = pickle.loads(frame_data)

            cv2.imshow(f"{client_name}'s Video", frame)
            if cv2.waitKey(1) == 13:
                break
        except Exception as e:
            print(f"Connection to {client_name} closed.")
            break

    cv2.destroyWindow(f"{client_name}'s Video")
    client_socket.close()

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('172.17.2.178', 9999))  # Update with the server's IP and port

name = input("Enter your name: ")
client.send(name.encode())

# Receive client names from the server
client_name = client.recv(1024).decode()
print(f"Connected as {client_name}")

send_thread = threading.Thread(target=send_video, args=(client,))
receive_thread = threading.Thread(target=receive_video, args=(client, client_name))

send_thread.start()
receive_thread.start()
