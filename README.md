# Network Firewall with IP Blocking

## Overview

This project implements a **Network Firewall** that captures and analyzes network traffic, detecting and blocking malicious IP addresses. The firewall system is built using **Python**, **C++**, and the **pcap** library. The system uses a Flask-based web interface to start and stop the firewall, making it easy to control the firewall's state. The firewall also logs all blocked IP addresses for auditing purposes.

### Key Features

- **Packet Capturing**: Captures and processes network packets in real-time.
- **IP Blocking**: Blocks IP addresses based on a predefined list of malicious or unauthorized IPs.
- **Logging**: Logs all blocked IP addresses to a text file (`blocked_ips.txt`).
- **Web Interface**: Provides a simple web interface to start and stop the firewall.
  
### Technologies Used

- **Programming Languages**: 
  - **Python**: Flask framework for creating the web interface.
  - **C++**: For building the core firewall program.
- **Libraries & Tools**:
  - **Flask**: Python framework for creating web applications.
  - **pcap**: Library for packet capturing and analyzing network traffic.
  - **netinet**, **arpa**: C++ libraries for handling networking tasks.
- **Web Technologies**:
  - HTML, CSS for the web interface design.

## Installation Guide

Follow these instructions to set up and run the firewall project on your Linux machine.

---

### Prerequisites

Before you start, make sure you have the following tools and libraries installed on your system:

1. **Python 3.6+** for running the Flask web interface and other Python-related tasks.
2. **C++ Compiler** (such as `g++` or `clang`) for compiling the C++ firewall program.
3. **libpcap** library for packet capturing, required by the C++ code.

---

### Step 1: Install Python and Set Up a Virtual Environment

First, install Python 3.6+ if you don't have it already.

#### Install Python 3.6+ and Pip

/***************Create the virtual environment using python3 -m venv: ******************/
	>	python3 -m venv myenv


python3 -m venv myenv

If Python is not installed, use the following commands:

```bash
sudo apt update
sudo apt install python3 python3-pip

# Network Firewall Setup Guide

## Step 1: Set Up a Virtual Environment

It’s recommended to use a Python virtual environment to avoid conflicts with system-wide packages:

1. Create a virtual environment:
   ```bash
  	python3 -m venv myenv
 2. Activate the virtual environment:
 	source myenv/bin/activate 
 	
****	Install the required Python libraries using pip: pip install flask pcapy
****	To compile the C++ program, install a C++ compiler like g++: sudo apt-get install g++
****	The firewall requires the libpcap library for packet capturing. You can install it with the following command: sudo apt-get install libpcap-dev
****	In the project directory, compile the C++ firewall program (firewall_program.cpp) using g++: g++ firewall_program.cpp -o firewall_program
****	Now, start the Flask web server. This will serve the web interface for starting and stopping the firewall : python3 server.py
****	You will see output like this: * Running on http://127.0.0.1:5000 (Press CTRL+C to quit)





###	How to Use the Firewall 
****	To start the firewall and begin blocking predefined IP addresses, navigate to this URL in your browser:
	>>	http://127.0.0.1:5000/start-firewall

****	 To stop the firewall and halt the packet capture, visit the following URL:
	>>	http://127.0.0.1:5000/stop-firewall



