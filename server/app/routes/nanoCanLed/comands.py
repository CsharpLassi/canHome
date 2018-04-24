import flask

from app import flaskApp
from app.routes.nanoCanLed import ledController


@flaskApp.route('/led/on')
def ledOn():
    color = flask.request.args.get("color")

    if color:
        ledController.print(("set %s;" % color))

    ledController.print("on;")

    return flask.redirect("/")


@flaskApp.route('/led/startBar')
def led_start_ar():
    color = flask.request.args.get("color")

    if color:
        ledController.print(("set %s;" % color))

    ledController.print("startBar;")

    return flask.redirect("/")


@flaskApp.route('/led/set')
def ledSet():
    color = flask.request.args.get("color")

    if color:
        ledController.print(("setBackgroundColor %s;" % color))

    return flask.redirect("/")


@flaskApp.route('/led/off')
def ledOff():
    ledController.print("off;")

    return flask.redirect("/")
