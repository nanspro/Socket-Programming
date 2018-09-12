import socket

host = "127.0.0.1"
port = 8083

try:
    s = socket.socket()
except:
    print("Error creating socket")

try:
    s.bind((host, port))
except:
    print("Binding error")

try:
    s.listen(1)
except:
    print("Listening error")

while True:
    try:
        conn, addr = s.accept()
    except:
        print("error in accepting")
    print 'Got connection from', addr
    
    filename = conn.recv(1024)
    print('Server received', filename)

    try:
        with open("./Data/"+filename,'rb') as f:
            l = f.read(1024)
            while (l):
                conn.send(l)
                print('Sent ',repr(l))
                l = f.read(1024)
    except:
        print("error opening file")

    print('Done sending ' + filename)
    conn.close()
