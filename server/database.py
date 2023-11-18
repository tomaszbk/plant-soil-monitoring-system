from pymongo import MongoClient
from server.config import config


mongodb_client = MongoClient(config["ATLAS_URI"])
database = mongodb_client[config["DB_NAME"]]