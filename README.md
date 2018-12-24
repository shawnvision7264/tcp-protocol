# TCP Reliable Data Transport Protocol
Here's our own implementation for Reliable Transport Protocol which used in transport layers.

*Reliable transport protocol runs on top of an unreliable delivery mechanism.*

## RDT methods
### Stop and Wait
Simply, the server sends only one packet until it receives the successful acknowledgement from the client.

### Selective Repeat
Implementation for one of the most common pipelining methods, where the server sends up to N packets with associated timers for each individual packet.<br/>
This method is practical as it doesn't work by `cumulative acknowledgements` like **GBN**, mentioned later. Otherwise, it only sends unacknowledged packets.

### Go-Back-In (GBN)
It works like the previous method, except that the whole window has only one timer because it works by `cumulative acknowledgements`, so in case of packet loss, it retransmits the whole window again.

## Congestion Control
**TCP** is well-known for it's congestion control process as shown in the state diagram shown below.

<p align="center">
  <img width="650" height="500" src="img/img.png">
</p>

The state diagram shows how the server window size is dynamically changed based on the congestion of the network by using `Additive increase Multiplicative decrease`.

## Packet Loss Simulation
The system is given a packet loss propability in the configuration file. This *PLP* ranges from $0$ to $1$, where PLP% of the packets are considered lost. In addition, a seed value for the random generator is also given to select the indices of lost packets.

## Prerequisite installed
- C++11 or higher compiler.

## Authors
* **Amr Hendy** [AmrHendy](https://github.com/AmrHendy)
* **Arsanous Essa** [Arsanous](https://github.com/Arsanuos)
* **Mohammed Deifallah** [Mohammed-Deifallah](https://github.com/Mohammed-Deifallah)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
