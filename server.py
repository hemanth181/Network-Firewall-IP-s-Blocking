from flask import Flask, jsonify, render_template
import subprocess
import threading

app = Flask(__name__)

firewall_running = False  # To keep track if the firewall is running

# Function to start the firewall program
def start_firewall():
    global firewall_running
    firewall_running = True
    subprocess.run(["./firewall_program"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Function to stop the firewall program
def stop_firewall():
    global firewall_running
    firewall_running = False
    subprocess.run(["pkill", "-f", "firewall_program"])  # Stop the firewall program

# Route to serve the index.html file
@app.route('/')
def index():
    return render_template('index.html')  # This will serve your index.html from the templates folder

# Route to start the firewall
@app.route('/start-firewall', methods=['GET'])
def start_firewall_route():
    if not firewall_running:
        start_firewall()
        return jsonify({"status": "started"})
    return jsonify({"status": "already running"})

# Route to stop the firewall
@app.route('/stop-firewall', methods=['GET'])
def stop_firewall_route():
    if firewall_running:
        stop_firewall()
        return jsonify({"status": "stopped"})
    return jsonify({"status": "already stopped"})

# Route to get the list of blocked IPs
@app.route('/get-blocked-ips', methods=['GET'])
def get_blocked_ips():
    try:
        with open("blocked_ips.txt", "r") as file:
            blocked_ips = [line.strip() for line in file.readlines()]
        return jsonify({"blocked_ips": blocked_ips})
    except Exception as e:
        return jsonify({"error": str(e)})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
