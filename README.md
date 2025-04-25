In this project, a basic mutual chatting program is developed with socket programming in C.

There are 2 ends which are server and client.
In the **server**, 
- Firstly, a **socket is created** for server end with these properties: IPV4 addressing and TCP.
- Secondly, **bind** operation is generated: The socket is binded with a specified port number and an IP address.
- Thirdly, **listen** operation is generated: The socket can listen the connection request thanks to this operation. Here, how many clients can be listened are specified.
- Fourdly, **accept** operation is generated: The server accepts the connection requests of the clients. 
  

In the **client**,
- Firstly, a socket is created for server end with these properties: IPV4 addressing and TCP.
- Secondly, **connect** operation is generated: It send a connect request to the server. After the acception of the server for this connection request, the communication of the server and the client will be started.
  
After these, they can be communicated with **send** and **recv** methods.
The connection can be finished with using **close** for these sockets.  
