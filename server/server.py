#!venv/bin/python3
from app import flaskApp

if __name__ == "__main__":
    flaskApp.run(host="0.0.0.0", port=50010)
