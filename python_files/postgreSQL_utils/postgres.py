import psycopg2
import time

class DatabaseLogger:
    # A simple class to log data to a PostgreSQL database
    def __init__(self, dbname, user, password, host, port, device_name):
        self.conn_params = {
            'dbname': dbname,
            'user': user,
            'password': password,
            'host': host,
            'port': port
        }
        self.device_name = device_name
        self.conn = None
        self.cur = None

    def connect_to_db(self):
        self.conn = psycopg2.connect(**self.conn_params)
        self.cur = self.conn.cursor()

    def initialize_db(self):
        self.cur.execute(f"CREATE TABLE IF NOT EXISTS {self.device_name} (id SERIAL PRIMARY KEY, time INT,temperature FLOAT, humidity FLOAT)")
        self.conn.commit()

    def log_data_to_db(self, temperature, humidity):
        time_val = int(time.time())
        if humidity is not None and temperature is not None:
            self.cur.execute(f"INSERT INTO {self.device_name} (time, temperature, humidity) VALUES (%s, %s, %s)", (time_val, temperature, humidity))
            self.conn.commit()
        else:
            print("Failed to retrieve data from sensor")

    def close_connection(self):
        if self.cur:
            self.cur.close()
        if self.conn:
            self.conn.close()
