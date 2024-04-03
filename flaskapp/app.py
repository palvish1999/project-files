from flask import Flask, request 
import json

app = Flask(__name__)

# Endpoint to receive data from ESP8266
@app.route('/receive_data', methods=['GET'])
def receive_data():
    content_type = request.headers.get('Content-Type')
    
    # Check if the Content-Type is JSON or if it's not set
    if content_type == 'application/json' or not content_type:
        data = request.get_json()
        print("Received JSON data from ESP8266:", data)
        # Process the received JSON data here as needed
        return "JSON data received successfully"
    else:
        return "Unsupported Content-Type. Only 'application/json' is accepted.", 415  # 415: Unsupported Media Type

if __name__ == '__main__':
    app.run(debug=True)  # Run the app in debug mode
