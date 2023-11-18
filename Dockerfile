FROM python:3.11.6
EXPOSE 8000
WORKDIR /app
COPY requirements.txt .
#when building image
RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt 
COPY server server
#when container is run
CMD ["python", "server/main.py"]