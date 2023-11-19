CREATE SCHEMA sensor;
CREATE TABLE sensor.humidity (
    id SERIAL PRIMARY KEY,
    value REAL NOT NULL,
    timestamp TIMESTAMP NOT NULL
);