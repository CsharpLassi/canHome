import flask


from app import flaskApp


@flaskApp.route('/')
@flaskApp.route('/index')
def index():
    return flask.render_template("index.html")
