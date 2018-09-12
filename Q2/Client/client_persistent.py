import socket                   
import time

host = "127.0.0.1"
port = 8090
try:
    s = socket.socket() 
except:
    print("Error creating socket")            

try:
    s.connect((host, port))
except:
    print("Connection error")                


while True:
    filename = raw_input("Enter file to download:")
    clock_start = time.clock()
    s.send(filename)
    try:
        with open(filename, 'wb') as f:
            print('opening '+filename)
            data = s.recv(1024)
            print(data)
            while data:
                f.write(data)
                if len(data)<1024:
                    print(len(data))
                    break
                data = s.recv(1024)
                print("hi"+data)
    except:
        print("Error opening file")

    print('Successfully get the file')
    clock_end = time.clock()

    duration_clock = clock_end - clock_start
    print 'clock:  start = ',clock_start, ' end = ',clock_end
    print 'clock:  duration_clock = ', duration_clock
    
s.close()
print('connection closed')





