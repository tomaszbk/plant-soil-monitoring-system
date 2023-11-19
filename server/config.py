import os


config={}

config["PG_HOST"] = 'humidity_sensor-postgres-1'
config["PG_PORT"] = '5432'
config["POSTGRES_DB"] = os.environ.get("POSTGRES_DB")
config["POSTGRES_USER"] = os.environ.get("POSTGRES_USER")
config["POSTGRES_PASSWORD"] = os.environ.get("POSTGRES_PASSWORD")
