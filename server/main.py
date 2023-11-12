from fastapi import FastAPI, Request
from contextlib import asynccontextmanager
from datetime import datetime
from pymongo import MongoClient
from server.config import config


@asynccontextmanager
async def lifespan(app: FastAPI):
    app.mongodb_client = MongoClient(config["ATLAS_URI"])
    app.database = app.mongodb_client[config["DB_NAME"]]
    print("Connected to the MongoDB database!")
    yield
    app.mongodb_client.close()


app = FastAPI(lifespan=lifespan)
    

@app.post("/humidity")
async def root(humidity: float, request: Request):
    now = datetime.now()
    request.app.database.humiditydb.insert_one({'date': now, 'humidity': humidity})
    return {'date': now, 'humidity': humidity}
