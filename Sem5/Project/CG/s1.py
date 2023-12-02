import cv2
import socket
import pickle
import struct
import time 

# Create a socket to listen for incoming connections
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("172.17.0.169", 8888))
server_socket.listen(10)

# Accept a connection from a client
client_socket, addr = server_socket.accept()
print("Connection from: " + str(addr))
time.sleep(10)
# Create an OpenCV window to display the received video
cv2.namedWindow("Received Video", cv2.WINDOW_AUTOSIZE)

data = b" "
payload_size = struct.calcsize("Q")

while True:
    while len(data) < payload_size:
        packet = server_socket.recv(4*1024)
        if not packet: break
        data += packet
    packed_msg_size = data[:payload_size]
    data = data[payload_size:]
    msg_size = struct.unpack("Q", packed_msg_size)[0]

    while len(data) < msg_size:
        data += server_socket.recv(4*1024)

    frame_data = data[:msg_size]
    data = data[msg_size]

    # Deserialize the frame and display it
    frame = pickle.loads(frame_data)
    cv2.imshow("Received Video", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cv2.destroyAllWindows()
client_socket.close()
