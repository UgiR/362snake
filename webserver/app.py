from flask import Flask, render_template, request, abort
from flask_sqlalchemy import SQLAlchemy
from config import Config

app = Flask(__name__)
app.config.from_object(Config)
db = SQLAlchemy(app)


class CRUD:

    @classmethod
    def create(cls, **kwargs):
        instance = cls(**kwargs)
        return instance.save()

    def update(self, commit=True, **kwargs):
        for attr, val in kwargs.items():
            setattr(self, attr, val)
        if commit:
            self.save()
        return self

    def save(self, commit=True):
        db.session.add(self)
        if commit:
            db.session.commit()
        return self

    def delete(self, commit=True):
        db.session.delete(self)
        if commit:
            db.session.commit()


class Score(db.Model, CRUD):
    id = db.Column(db.Integer, primary_key=True)
    score = db.Column(db.Integer)


@app.route('/')
def index():
    return 'index.html'


@app.route('/scores', methods=['GET', 'POST'])
def scores():
    if request.method == 'POST':
        if not request.json or not 'score' in request.json:
            abort(400)
        entry = Score.create(score=request.json['score'])
        entry.save()
    elif request.method == 'GET':
        # retrieve scores
        pass



if __name__ == '__main__':
    app.run()
    db.create_all()
