#add somewhere in imports
from flask_cors import CORS
#add after app declaration to make sure frontend can call
CORS(app)
#add method somewhere to make total sum available
@app.route("/distance", methods=["GET"])
def get():
    sum = 0.0
    for i, v in devices.items():
        sum += v['total_received_km']
    return jsonify({
        "sum": sum
    }), 200

    
