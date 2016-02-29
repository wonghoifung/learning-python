from SubscribeReq_pb2 import SubscribeReq
from SubscribeResp_pb2 import SubscribeResp
import socket
import sys
import struct

def main():
	address = ('127.0.0.1', 8080)
	client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	client_socket.connect(address)

	req = SubscribeReq()
	req.subReqID = 123
	req.userName = 'wong'
	req.productName = 'spider'
	req.address = 'zs'
	body = req.SerializeToString()

	client_socket.sendall(struct.pack('>I', len(body)) + body)

	resplen = struct.unpack('>I', client_socket.recv(4))[0]
	respbody = client_socket.recv(resplen)

	resp = SubscribeResp()
	resp.ParseFromString(respbody)

	print 'recv: ' + str(resp.subReqID) + ', ' + str(resp.respCode) + ', ' + resp.desc

if __name__ == "__main__":
	main()
