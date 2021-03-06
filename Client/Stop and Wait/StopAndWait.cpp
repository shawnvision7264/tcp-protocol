//
// Created by Amr Hendy on 12/7/2018.
//

#include "StopAndWait.h"

//fileWriter must be intialized in consturctor or remove it from header.
StopAndWait::StopAndWait(int socket_fd, string file_name): fileReader(), fileWriter(file_name){
    StopAndWait::socket_fd = socket_fd;
    StopAndWait::file_path = file_name;
}


// called by the server
void StopAndWait::sendFile(double loss_prob, int seed_number){
    fileReader = FileReader(file_path);
    get_loss_packets(loss_prob, seed_number);
    int total_packets = fileReader.get_total_packet_number();
    for(int packet_index = 0; packet_index < total_packets; packet_index++){
        sendPacket(packet_index);
    }
}

void StopAndWait::sendPacket(int packet_index) {
    int status;
    if(loss_packets_indices.count(packet_index)){
        status = recevAck();
        loss_packets_indices.erase(packet_index);
    }
    else{
        Packet packet = fileReader.get_chunk_data(packet_index);
        Sender sender;
        sender.send_packet(packet, socket_fd);
        status = recevAck();
    }
    if(status == 0){
        // resend the packet
        sendPacket(packet_index);
    }
    return;
}

int StopAndWait::recevAck() {
    struct sockaddr_in socket_address;
    int status;
    Receiver::receive_ack_packet(StopAndWait::socket_fd, socket_address, status, STOP_AND_WAIT_TIMEOUT);
    return status;
}


// called by the client
void StopAndWait::recevFile(int total_packets, struct sockaddr_in socket_address){
    fileWriter = FileWriter(file_path);
    for(int packet_index = 0; packet_index < total_packets; packet_index++){
        Packet packet = receivePacket(packet_index, socket_address);
        fileWriter.write_chunk_data(packet.seqno, string(packet.data, packet.len));
    }
}

Packet StopAndWait::receivePacket(int packet_index, struct sockaddr_in socket_address){
    Packet packet = Receiver::receive_packet(socket_fd, socket_address);
    while(1) {
        if (PacketHandler::compare_packet_checksum(packet) && packet.seqno == packet_index) {
            // true check sum send the ack
            sendAck(packet_index);
            return packet;
        }
    }
}

void StopAndWait::sendAck(int packet_index){
    Ack_Packet ack_packet = PacketHandler::create_ack_packet(packet_index, sizeof(packet_index));
    Sender sender;
    sender.send_ack(ack_packet, socket_fd);
}


void StopAndWait::get_loss_packets(double loss_prob, int seed_number){
    srand(seed_number);
    int total_packets = fileReader.get_total_packet_number();
    int total_loss_packets = ceil(loss_prob * total_packets);
    set<int> loss_packets_indices;
    for(int i = 0; i < total_loss_packets; i++){
        int index = rand() % total_packets;
        if(loss_packets_indices.count(index) == 0){
            loss_packets_indices.insert(index);
        }
        else{
            // as that index is already exist
            i--;
        }
    }
    StopAndWait::loss_packets_indices = loss_packets_indices;
}
