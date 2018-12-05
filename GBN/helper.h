//
// Created by arsanuos on 12/2/18.
//

#ifndef TCP_PROTOCOL_HELPER_H
#define TCP_PROTOCOL_HELPER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <string>

#include "../ack_packet.h"
#include "../packet.h"

using namespace std;

packet recv_pkt(int client_fd);

ack_packet recv_ack_pkt(int client_fd);

string get_data(int client_fd, uint16_t size);

uint16_t get_len(int client_fd);

string get_data(int client_fd, uint16_t size);

uint32_t get_seq_num(int client_fd);

bool send_pkt(int fd, packet pkt);

bool send_all(int fd, void *data, uint16_t len);

bool send_ack(int fd, ack_packet pkt);


#endif //TCP_PROTOCOL_HELPER_H