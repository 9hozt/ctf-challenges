from flask import Flask, request, render_template
from jinja2 import Environment

app = Flask(__name__)
Jinja2 = Environment()

@app.route('/',methods=['GET', 'POST'])
def home_page():
    if request.method == 'GET':
        output = "Bienvenue sur le Chat not GPT, quel est votre question ?"
        is_value = False
        return  render_template('home.html', output=output,is_value=is_value)
    else:
        ua = request.headers.get('User-Agent')
        if "tplmap" in ua:
            return render_template('500.html')
        name = request.values.get('name', None)
        output = Jinja2.from_string('Je suis désolé, mais en tant que modèle de langage, la seule réponse que je peux apporter à la question: ' + name + ' est : 42!').render()
        is_value = True
        return render_template('home.html', output=output,is_value=is_value)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
