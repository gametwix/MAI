# Communicating message servers

Distributed system for asynchronous request processing. Provides interaction between control and computing nodes, the network structure is a tree. If some of the nodes are unavailable, the parent nodes remain operational.

## Formulation of the problem

Implement a distributed system for asynchronous request processing. In this distributed system, there should be 2 types of nodes: "control" and "computing". It is necessary to combine these nodes in accordance with the topology that is defined by the option. Communication between nodes must be done using message queuing technology. Also in this system, it is necessary to provide for checking the availability of nodes in accordance with the option. When killing (kill -9) any computing node, the system should try to maintain its performance as much as possible, namely, all child nodes of the killed node may become inaccessible, but the parent nodes must remain operational.
The control node is responsible for entering commands from the user and sending those commands to the compute nodes. The topology is a general tree, the check is the availability of a ping id, the computational program is a search for a substock in a string.

## General information about the program

The program is written in C language on a Unix-like operating system based on Linux kernels. The program uses the ZeroMQ message queue.

The program supports the following commands:

* **create [id] [parent]** - create a node with id [id] whose parent is the node with id[parent].
* **remove [id]** - removes the node with the given id.
* **exec [id] [string] [pattern]** - runs on the node [id] search for the substring [pattern] in [string].
* **ping [id]** – checking the availability of host [id].

Exit from the program occurs at the end of input, that is, by pressing CTRL + D.

## Program example

### Create a network

```
./client
create 2 -1
Ok: 2770
create 3 2
Ok: 2773
create 4 3
Ok: 2776
create 5 3
Ok: 2779
```

![](/2_course/OS/LB6_8/images/ZMQ_1.jpg)

### Checking servers availability and calling calculations

```
ping 5
Ok: 1
ping 4
Ok: 1
exec 3
abracadabra
abra
Ok:3:0;7
```

### Remove the server with id 5 and check its availability

```
remove 5
Ok
ping 5
Error: Not found
```

![](/2_course/OS/LB6_8/images/ZMQ_2.jpg)

### Remove the server with id 3 and its children and check their availability

```
remove 3
Ok
ping 3
Error: Not found
remove 4
Error: Not found
```

![](/2_course/OS/LB6_8/images/ZMQ_3.jpg)