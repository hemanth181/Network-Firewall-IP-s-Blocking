#include <iostream>
#include <pcap.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <vector>
#include <fstream>

using namespace std;

// Your local IP address (localhost)
string myLocalIP = "127.0.0.1";

// A list of blocked IPs
vector<string> blockedIPs = {"192.168.1.100", "10.0.0.5", myLocalIP};  // Includes your localhost IP

// Function to check if the IP is blocked
bool isBlocked(string ip) {
    for (string blocked : blockedIPs) {
        if (ip == blocked) {
            return true;
        }
    }
    return false;
}

// Function to write the blocked IPs to a file
void writeBlockedIPsToFile() {
    ofstream outFile("blocked_ips.txt");  // Open a file to store blocked IPs
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    for (const string& ip : blockedIPs) {
        outFile << ip << endl;  // Write each blocked IP to the file
    }
    outFile.close();
}

// Function to process each packet
void handlePacket(unsigned char *userData, const struct pcap_pkthdr *packetHeader, const unsigned char *packetData) {
    struct ip *ipHeader = (struct ip*)(packetData + 14);  // Get IP header from packet
    char srcIP[INET_ADDRSTRLEN];  // Buffer to hold the source IP address
    inet_ntop(AF_INET, &(ipHeader->ip_src), srcIP, INET_ADDRSTRLEN);  // Convert source IP to string
    string sourceIP = srcIP;  // Convert to string for easy comparison

    // Check if the source IP is blocked
    if (isBlocked(sourceIP)) {
        cout << "Blocked: " << sourceIP << endl;
    } else {
        cout << "Allowed: " << sourceIP << endl;
    }
}

// Main function to capture packets
int main() {
    // Write the blocked IPs to the file before starting packet capture
    writeBlockedIPsToFile();

    char errorBuffer[PCAP_ERRBUF_SIZE];
    // Open the network interface for packet capture (e.g., "eth0" or "wlan0")
    pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errorBuffer);  // Replace "eth0" with your interface
    if (handle == nullptr) {
        cout << "Error: " << errorBuffer << endl;
        return -1;
    }

    struct bpf_program fp;
    const char *filterExpression = "ip";  // Filter to capture only IP packets
    if (pcap_compile(handle, &fp, filterExpression, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        cout << "Error compiling filter: " << pcap_geterr(handle) << endl;
        return -1;
    }
    
    if (pcap_setfilter(handle, &fp) == -1) {
        cout << "Error setting filter: " << pcap_geterr(handle) << endl;
        return -1;
    }

    // Capture packets continuously
    pcap_loop(handle, 0, handlePacket, nullptr);

    pcap_close(handle);  // Close the capture handle
    return 0;
}
