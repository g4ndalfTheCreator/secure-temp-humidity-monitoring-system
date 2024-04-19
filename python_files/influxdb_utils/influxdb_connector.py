import influxdb_client, os, time
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

token = os.environ.get("INFLUXDB_TOKEN")
token = "vSo3ZMVzJoFnAlsyLGH5Pf9dYHNZjUZ9vETMYXG3BtppVWWnU4PHAO6XNMs5KIdNAhQze1AvTFsVbXvroQ-L-Q=="
org = "org"
url = "http://localhost:8086"

client = influxdb_client.InfluxDBClient(url=url, token=token, org=org)

bucket="temp"

write_api = client.write_api(write_options=SYNCHRONOUS)
   
for value in range(5):
  point = (
    Point("measurement1")
    .tag("tagname1", "tagvalue1")
    .field("field1", value)
  )
  write_api.write(bucket=bucket, org="org", record=point)
  time.sleep(1) # separate points by 1 second

  query_api = client.query_api()

query = """from(bucket: "temp")
 |> range(start: -10m)
 |> filter(fn: (r) => r._measurement == "measurement1")"""
tables = query_api.query(query, org="org")

for table in tables:
  for record in table.records:
    print(record)

# query_api = client.query_api()

query_api = client.query_api()

query = """from(bucket: "temp")
  |> range(start: -10m)
  |> filter(fn: (r) => r._measurement == "measurement1")
  |> mean()"""
tables = query_api.query(query, org="org")

for table in tables:
    for record in table.records:
        print(record)