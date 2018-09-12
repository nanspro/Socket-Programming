import socket                   
import time

host = "127.0.0.1"
port = 8083

while True:
	filename = raw_input("Enter file you want to download:")
	clock_start = time.clock()
	try:
		s = socket.socket()
	except:
		print("Error creating socket")
	try:             
		s.connect((host, port))
	except:
		print("Connection error")
	try:
		s.send(filename)
	except:
		print("Error sending file")
	try:
		with open(filename, 'wb') as f:
			print 'file opened %s' % filename
			while True:
				print('receiving data...')
				data = s.recv(1024)
				print('data=%s', (data))
				if not data:
					break
				f.write(data)
	except:
		print("error opening file")
	print(filename + " downloaded")
	clock_end = time.clock()
	duration_clock = clock_end - clock_start
	print 'clock:  start = ',clock_start, ' end = ',clock_end
	print 'clock:  duration_clock = ', duration_clock
	s.close()

print('connection closed')
