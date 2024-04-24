import psycopg2
import time

# PostgreSQL connection parameters
conn_params = {
    'dbname': 'temp-hum-db',
    'user': 'usr',
    'password': 'pw',
    'host': 'localhost',
    'port': '5431'
}

demo_device = 'demo_device'

# Connect to PostgreSQL
conn = psycopg2.connect(**conn_params)
cur = conn.cursor()

def initialize_db():
    cur.execute(f"CREATE TABLE IF NOT EXISTS {demo_device} (id SERIAL PRIMARY KEY, time INT,temperature FLOAT, humidity FLOAT)")
    conn.commit()


# Insert temperature data into PostgreSQL
def log_temperature_to_db():
    humidity, temperature = 10, 20
    time_val = time.time()
    if humidity is not None and temperature is not None:
        cur.execute(f"INSERT INTO {demo_device} (time, temperature, humidity) VALUES ({time_val}, {temperature}, {humidity})")
        conn.commit()
    else:
        print("Failed to retrieve data from sensor")

def get_data_from_db():
    cur.execute(f"SELECT * FROM {demo_device}")
    data = cur.fetchall()
    return data

# Call the function to log temperature data periodically
# Implement your own logic for this, e.g., using a scheduler like APScheduler

initialize_db()

log_temperature_to_db()

data = get_data_from_db()

print(data)

# Close the connection
cur.close()
conn.close()
