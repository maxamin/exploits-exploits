import socket
import sys
import time

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('IP_ADDRESS', PORT)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)
id = 0

while 1:
    time.sleep(1)
    id += 1
    print("%d " % id)
    message = "testing message" + str(id)
    sock.sendall(message)
    if id > 10:
        break