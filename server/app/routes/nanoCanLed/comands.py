import flask

from app import flaskApp
from app.routes.nanoCanLed import ledController


@flaskApp.route('/led/on')
def on():
    color = flask.request.args.get("color")

    if color is None:
        return flask.redirect("/")

    ledController.print(("on %s;" % color))

    return flask.redirect("/")
