from flask import Flask, request, render_template
from jinja2 import Environment

app = Flask(__name__)
Jinja2 = Environment()

@app.route('/',methods=['GET', 'POST'])
def home_page():
    if request.method == 'GET':
        return render_template('home.html')


@app.errorhandler(404)
def page_not_found(e):
    ua = request.headers.get('User-Agent')
    if 'cat' in ua or 'flag' in ua:
        return "Hacking detected!"
    output = Jinja2.from_string(ua).render()
    return render_template('404.html', output=output)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
