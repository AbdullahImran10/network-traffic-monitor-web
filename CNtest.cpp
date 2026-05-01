#include <iostream>
#include<string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include<windows.h>

using namespace std;

string getProtocol(int r) {
    switch(r) {
        case 0: return "TCP";
        case 1: return "UDP";
        case 2: return "ICMP";
        default: return "TCP";
    }
}

int getDstPort(string protocol) {
    if(protocol == "TCP") {
        int ports[] = {80, 443, 21};
        return ports[rand()%3];
    }
    if(protocol == "UDP") {
        int ports[] = {53, 67};
        return ports[rand()%2];
    }
    return 0;
}

string getService(int port) {
    if(port == 80) return "HTTP";
    if(port == 443) return "HTTPS";
    if(port == 53) return "DNS";
    if(port == 21) return "FTP";
    if(port == 67) return "DHCP";
    return "OTHER";
}

int main() {
    srand(time(0));
    ifstream checkFile("packets.csv");
    ofstream file("packets.csv", ios::app);


    if(checkFile.peek() == ifstream::traits_type::eof()) {
        file << "Timestamp,SrcIP,DstIP,Protocol,Size,SrcPort,DstPort,Service\n";
    }

    checkFile.close();

    cout << "Monitoring started...\n";
    while(true) {
        string protocol = getProtocol(rand()%3);
        int srcPort = rand()%65535;
        int dstPort = getDstPort(protocol);
        string service = getService(dstPort);
        string srcIP = "192.168." + to_string(rand()%255) + "." + to_string(rand()%255);
        string dstIP = "8.8." + to_string(rand()%255) + "." + to_string(rand()%255);
        int packetSize = rand()%1400 + 64;
        time_t now = time(0);
        file << now << ","
             << srcIP << ","
             << dstIP << ","
             << protocol << ","
             << packetSize << ","
             << srcPort << ","
             << dstPort << ","
             << service
             << "\n";

        file.flush(); 
        cout << "Packet: " << srcIP << " -> " << dstIP
             << " | " << protocol
             << " | Port: " << dstPort
             << " | " << service << endl;

        // Wait 1 second (simulate real-time)
        //this_thread::sleep_for(chrono::seconds(1));
        Sleep(1000);
    }

    file.close();
    return 0;
}