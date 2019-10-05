make:
	rpcgen -C whiteboard.x
	gcc server.c whiteboard_svc.c whiteboard_xdr.c -o server
	gcc client.c whiteboard_clnt.c whiteboard_xdr.c -o client
	gcc wbadmin.c whiteboard_clnt.c whiteboard_xdr.c -o wbadmin

