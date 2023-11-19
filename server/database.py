import psycopg2
from server.config import config
from loguru import logger

logger.info("Connecting to PostgreSQL...")
connection = psycopg2.connect(
    host=config["PG_HOST"],
    port=config["PG_PORT"],
    database=config["POSTGRES_DB"],
    user=config["POSTGRES_USER"],
    password=config["POSTGRES_PASSWORD"]
)
cursor = connection.cursor()
logger.info("Connection to PostgreSQL established.")
