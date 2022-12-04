
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

using boost::asio::ip::tcp;

const int max_length = 1024;

enum class RobotCommand : char { INIT = 'I', START = 'S', STOP = 'X' };

std::unordered_map<std::string, RobotCommand> ROBOT_CMD_MAP{
        {"INIT", RobotCommand::INIT},
        {"START", RobotCommand::START},
        {"STOP", RobotCommand::STOP}};

void session(tcp::socket sock) {
    try {
        for (;;) {
            char data[max_length];

            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
            if (length) {
                std::string data_str(data, length);
                std::cout << data_str << "\n";
                if (ROBOT_CMD_MAP.find(data_str) != ROBOT_CMD_MAP.end()) {
                    RobotCommand new_command = ROBOT_CMD_MAP.at(data_str);
                    switch (new_command) {
                    case RobotCommand::INIT: {
                        std::cout << "INIT command \n";
                        break;
                    }
                    case RobotCommand::START: {
                        std::cout << "START command \n";
                        break;
                    }
                    case RobotCommand::STOP: {
                        std::cout << "STOP command \n";
                        break;
                    }
                    default: {
                        break;
                    }
                    }
                } else {
                    std::cout << "Invalid command! \n";
                }
            }

            boost::asio::write(sock, boost::asio::buffer(data, length));
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_context &io_context, unsigned short port) {
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    for (;;) {
        std::thread(session, a.accept()).detach();
    }
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        server(io_context, std::atoi(argv[1]));
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}