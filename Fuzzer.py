# Fuzzer Author: Juan Sacco <jsacco@exploitpack.com>
# Date and time: 31 October 2017
# Description: This a yet simple fuzzer that makes use of SCAPY to create random stuff and
# send/receive fuzz packets over TCP.

from scapy.all import *
import binascii
import socket

def fuzz_replier(target,port):
    try:
        # Open socket
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Set reuse ON
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # Bind port
        s.bind((target, port))
        s.listen(1)
        conn, addr = s.accept()
        print("[" + time.strftime('%a %H:%M:%S') + "]" + " - " + "Connected to: "), addr
        print("[" + time.strftime('%a %H:%M:%S') + "]" + " - " + "Waiting for a connection.. ")
        # Loop to send crafted packages
        while 1:
            data = conn.recv(4096)
            if not data: break
            print("[" + time.strftime('%a %H:%M:%S') + "]" + " - " + "Received: ") + data
            packet = IP(dst=target) / TCP(dport=port) / fuzz(Raw())
            # payload
            if payload != "EMPTY":
                packet = payload*multiplier
                s.send(packet)
            else:
                s.send(bytes(packet))
            # Log the packet  in hexa and timestamp
            fileLog = target + ".log"
            logPacket = open(fileLog, "aw+")
            logPacket.write("["+time.strftime('%a %H:%M:%S')+"]"+ " - Packet sent: " + binascii.hexlify(bytes(packet))+"\n")
            logPacket.close()

            # Write bytecodes to socket
            print("["+time.strftime('%a %H:%M:%S')+"]"+" - "+"Packet sent: ")
            conn.send(bytes(packet))
            print(bytes(packet))
        conn.close()
        s.close()
        fuzz_replier(target,port)
    except socket.error as error:
        print error
        print "Sorry something went wrong!"

def fuzz_connect(target,port):
    try:
        while 1:
            # Open socket
            s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
            # Set reuse ON
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            # Bind port
            s.connect((target, port))
            s.settimeout(0)
            print("[" + time.strftime('%a %H:%M:%S') + "]" + " - " + "Connected to:"), target, port
            print("[" + time.strftime('%a %H:%M:%S') + "]" + " - " + "Establishing connection.. ")
            packet = IP(dst=target) / TCP(dport=port) / fuzz(Raw())
            # payload
            if payload != "EMPTY":
                packet = payload*multiplier
                s.send(packet)
            else:
                s.send(bytes(packet))
            # Log the packet in hexa and timestamp
            fileLog = target + ".log"
            logPacket = open(fileLog, "a+")
            logPacket.write("["+time.strftime('%a %H:%M:%S')+"]"+ " - Packet sent: " + binascii.hexlify(bytes(packet))+"\n")
            logPacket.close()
            print("Packet: "+binascii.hexlify(bytes(packet))+"\n")
            # Write bytecodes to socket
            print("["+time.strftime('%a %H:%M:%S')+"]"+" - "+"Packet sent: ")
            s.send(bytes(packet))
            # Packet sent:
            print(bytes(packet))
            try:
                data = s.recv(4096)
                s.settimeout(5.0)
                print("Last packet: "+binascii.hexlify(bytes(packet))+"\n")
                print("[" + time.strftime('%a %H:%M:%S') + "]" + " - "+ "Data received: '{msg}'".format(msg=data))
            except socket.error, e:
                err = e.args[0]
                if err == errno.EAGAIN or err == errno.EWOULDBLOCK:
                    print 'Sorry, No data available'
                    continue
        s.close()
    except socket.error as error:
        print error
        print "Sorry, something went wrong!"



def howtouse():
    print "Usage: Fuzzer.py [OPTION] Hostname Port Payload"
    print "[*] Mandatory arguments:"
    print "[-] Specify a hostname and a target"
    print "[-] Choose server or client depends on your application"

    print "[*] Optional arguments:"
    print "[-] Use a custom payload if you want to append something!"
    print ""
    print "[*] Version 1.1? Oooops haha. Not really."
    print "[*] Snap! Something went wrong.."
    print "[*] How to use: \"python FuzzerTCP.py server/client ipaddress port\""
    sys.exit(-1)

if __name__ == "__main__":
    try:
        # Set target
        type = sys.argv[1]
        target = sys.argv[2]
        port = int(sys.argv[3])
        
	if len(sys.argv) > 4:
	    payload = sys.argv[4]
	else:
	    payload = 'EMPTY'
	    
        if len(sys.argv) > 5:
	    multiplier = int(sys.argv[5])
	else:
	    payload = 'EMPTY'

        print "[*] Fuzzer + Scapy by Juan Sacco "
        print "[*] Exploit Pack <jsacco@exploitpack.com> "
        if type == "client":
            fuzz_connect(target, port)
        fuzz_replier(target, port)
    except IndexError:
        howtouse()
