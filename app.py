from flask import Flask, render_template, jsonify, request
import csv
import subprocess
import os

app = Flask(__name__)

process = None

# Load website
@app.route('/')
def home():
    return render_template("index.html")


# START MONITORING
@app.route('/start')
def start():
    global process
    if process is None:
        process = subprocess.Popen(["CNtest.exe"])
    return "Monitoring Started"


# STOP MONITORING
@app.route('/stop')
def stop():
    global process

    if process:
        try:
            os.system(f"taskkill /F /PID {process.pid} /T")
        except Exception as e:
            print(e)

        process = None

    return "Monitoring Stopped"



# GET DATA (WITH FILTERS)
@app.route('/data')
def data():
    protocol = request.args.get('protocol')
    src = request.args.get('src')
    dst = request.args.get('dst')

    results = []

    if not os.path.exists("packets.csv"):
        return jsonify(results)

    with open("packets.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:

            if protocol and row['Protocol'] != protocol:
                continue

            if src and src not in row['SrcIP']:
                continue

            if dst and dst not in row['DstIP']:
                continue

            results.append(row)

    return jsonify(results)


# STATISTICS
@app.route('/stats')
def stats():
    total = tcp = udp = icmp = 0
    size_sum = 0

    if not os.path.exists("packets.csv"):
        return jsonify({})

    with open("packets.csv") as file:
        reader = csv.DictReader(file)
        for row in reader:
            total += 1
            size_sum += int(row['Size'])

            if row['Protocol'] == "TCP": tcp += 1
            if row['Protocol'] == "UDP": udp += 1
            if row['Protocol'] == "ICMP": icmp += 1

    avg = size_sum / total if total else 0

    return jsonify({
        "total": total,
        "tcp": tcp,
        "udp": udp,
        "icmp": icmp,
        "avg": round(avg, 2)
    })
if __name__ == "__main__":
    app.run(debug=True)
