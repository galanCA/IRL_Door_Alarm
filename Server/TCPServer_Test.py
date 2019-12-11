import socket 
import random
import time
from threading import Thread

'''#
class ClientThread(Thread):
	def __init__(self, ip, port, conn):
		Thread.__init__(self)
		self.ip = ip
		self.port = port
		self.conn = conn
		print ("[+] New server socket thread started for " + ip + ":" + str(port))

	def run(self):
		while True :
			check = self.conn.recv(2028,socket.MSG_PEEK)
			L = len(check)
			if L > 0:
				data = self.conn.recv(2028)
				print ("Server received data: ", data)

			else:
				break
'''


def main():
	# Multithreaded Python server
	TCP_IP = '192.168.50.40'
	TCP_PORT = 3300
	BUFFER_SIZE = 2048

	tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	tcpServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	tcpServer.bind((TCP_IP, TCP_PORT))
	threads = []

	#while True:
	tcpServer.listen(2)
	print("Python Server: Waiting for connection from TCP clients")
	(conn, (ip, port)) = tcpServer.accept()
	print ("Connection created with ",  ip)
	check = conn.recv(2028,socket.MSG_PEEK)
	L = len(check)

	
	if L > 0:
		data = conn.recv(2028)
		print ("Server received data: ", data)
		send_data ='%s'%'On'
		conn.send(send_data.encode())
		time.sleep(20)
		send_data ='%s'%'Off'
		conn.send(send_data.encode())


	tcpServer.close()



		#newthread = ClientThread(ip, port, conn)
		#newthread.start()
		#threads.append(newthread)

	#for t in threads:
	#	t.join()

if __name__ == '__main__':
	main()