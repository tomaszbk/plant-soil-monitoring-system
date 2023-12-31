from pymongo import MongoClient
from server.config import config
from loguru import logger


logger.info("Connecting to MongoDB...")
mongodb_client = MongoClient(config["ATLAS_URI"])
database = mongodb_client[config["DB_NAME"]]
logger.info("Connection to MongoDB established.")