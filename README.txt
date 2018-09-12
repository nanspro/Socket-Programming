
1.1 A basic server and client using sockets

    - Go to Q1 folder and then go to Server folder : cd Q1/Server
    - compile the server.c : gcc server.c
    - Run the code : ./a.out
    - The server is ready to accept requests from clients at port 8082
    - Open new tab of terminal.
    - Go to Q1 folder and then go to Client folder : cd Q1/Client
    - Compile client.c : gcc client.c
    - Run the code : ./a.out
    - Now the client automatically gets connected to the server at port 8082
    - Now you can request files from server.
    - For testing enter the name of the files which are present in the Data folder which is present in the Server folder.
    - After retrieving the file successfully the client disconnects from server and server gets closed.

1.2 Persistent and Non Persistent connections

    - Go to Q2 folder and then go to Server folder : cd Q2/Server
    - Compile and run the python code (whichever you want to persistent or non-persistent) : python server_persistent.py/server_nonpersistent.py
    - The server is ready to accept requests from clients.
    - Open new terminal and go to Q2 folder and then Client folder : cd Q2/Client
    - Compile and run the client code (corresponding to the server run) : python client_persistent.py/client_nonpersistent.py
    - Now client gets connected to the server.
    - Now you can request multiple files from server.
    - For testing you can enter the filenames of the files which are present in the Data folder which is present in the Server folder. 
    - After retrieving the files we can disconnect the client

** Error handling has been done.
** Port has been kept fixed for both the parts
** Multiple files can be transferred in the second part but in first part single file can be retrieved.
