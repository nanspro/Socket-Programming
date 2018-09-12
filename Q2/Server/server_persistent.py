import socket

port = 8090
host = "127.0.0.1"

try:
	s = socket.socket()
except:
	print("Socket creation error")

try:
	s.bind((host, port))
except:
	print("binding error")

try:
	s.listen(5)
except:
	print("listening error")

try:
	conn, addr = s.accept()
except:
	print("error in accepting")

while True:
    filename = conn.recv(1024)

    try:
    	with open("./Data/"+filename,'rb') as f:
        	l = f.read(1024)
        	while (l):
        		conn.send(l)
        		print('Sent ',repr(l))
        		l = f.read(1024)
    except:
    	print("error opening file")

    f.close()
    print('Done sending')

conn.close()





