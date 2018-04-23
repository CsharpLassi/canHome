import flask
from flask import Flask

import serial

app = Flask(__name__)


@app.route('/')
@app.route('/index')
def index():
    return flask.render_template("index.html")


@app.route('/on')
def on():
    color = flask.request.args.get("color")

    if color is None:
        return flask.render_template("index.html")

    ser = serial.Serial("/dev/ttyUSB0", 9600)
    ser.write(("on %s;" % color).encode())

    ser.close()

    return flask.render_template("index.html", color=color)


if __name__ == '__main__':
    app.run(host="0.0.0.0")
