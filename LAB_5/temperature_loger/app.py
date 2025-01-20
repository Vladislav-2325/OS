from flask import Flask, request, jsonify, render_template
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///temperatures.db'  # Используем SQLite для простоты
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

# Модель для хранения температуры
class Temperature(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    value = db.Column(db.Float, nullable=False)
    timestamp = db.Column(db.DateTime, default=datetime.utcnow)

# Создание базы данных и таблиц
with app.app_context():
    db.create_all()

@app.route('/')
def welcome():
    return render_template('index.html')

@app.route('/log_temperature', methods=['POST'])
def log_temperature():
    data = request.get_json()
    temperature = data.get('temperature')
    
    if temperature is not None:
        new_temp = Temperature(value=temperature)
        db.session.add(new_temp)
        db.session.commit()
        return jsonify({"message": "Temperature logged"}), 201
    else:
        return jsonify({"error": "Invalid data"}), 400

@app.route('/temperatures', methods=['GET'])
def get_temperatures():
    temps = Temperature.query.all()
    return jsonify([{"id": t.id, "value": t.value, "timestamp": t.timestamp} for t in temps])

@app.route('/statistics', methods=['GET'])
def get_statistics():
    start_date = request.args.get('start')
    end_date = request.args.get('end')

    query = Temperature.query
    if start_date:
        query = query.filter(Temperature.timestamp >= datetime.fromisoformat(start_date))
    if end_date:
        query = query.filter(Temperature.timestamp <= datetime.fromisoformat(end_date))

    stats = query.all()
    return jsonify([{"id": t.id, "value": t.value, "timestamp": t.timestamp} for t in stats])

if __name__ == '__main__':
    app.run(debug=True)
