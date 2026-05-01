# Project Title: Network Traffic Monitoring System

# Overview: 
        This project is a web-based network traffic monitoring system that simulates packet capturing, stores the data in a CSV file, and displays real-time network activity through an interactive dashboard.

It integrates:

A C++ packet generator (simulating network traffic)
A Flask backend (API + data processing)
A frontend dashboard (HTML, CSS, JavaScript)

The system allows users to start/stop monitoring, filter traffic, and view statistics in real time.

# Scope:
        Simulated packet generation
        CSV-based packet storage
        Real-time data fetching (auto-refresh every 2 seconds)
        Protocol-based filtering (TCP, UDP, ICMP)
        IP-based filtering (Source & Destination)
        Traffic statistics calculation

# Dataset Description:
        Dataset is generated using a C++ program that writes packets to csv file.

# Attributes (Columns):

    Column Name	-> Description
    Timestamp -> Packet generation time
    SrcIP -> Source IP address
    DstIP -> Destination IP address
    Protocol -> TCP / UDP / ICMP
    Size -> Packet size (bytes)
    SrcPort -> Source port number
    DstPort -> Destination port 

# Tech Stack: 
    Backend
    Python (Flask) – Web server & API handling
    REST APIs:
    /start -> Start monitoring
    /stop -> Stop monitoring
    /data -> Fetch filtered packets
    /stats -> Get statistics
     Packet Generator
    C++
    Generates CSV dataset using random values
    Compiled as:
    CNtest.exe
    Frontend
    HTML – Structure
    CSS – Styling
    JavaScript – Dynamic update
 
 # Author:

    Abdullah Imran
    BS Computer Science – Semester 4
    Course: Computer Networks
    Spring 2026
