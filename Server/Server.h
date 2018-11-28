//
// Created by Amr Hendy on 11/28/2018.
//

#ifndef TCP_PROTOCOL_SERVER_H
#define TCP_PROTOCOL_SERVER_H

using namespace std;

#include <string>

class Server {

private:
    int server_port_number;
    int maximum_window_size;
    int random_seed;
    double packet_loss_prob;

public:
    Server(string server_conf_file_dir);
    ~Server();

private:
    void init_server();
    void start_server();
    void handle_client(int client_socket_fd);
    void receive_request_from_client(int client_socket_fd);
    void send_file(int client_socket_fd);
};


#endif //TCP_PROTOCOL_SERVER_H