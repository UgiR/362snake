from flask import Flask, render_template, request, abort, jsonify
import datetime as dt
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
    __tablename__ = 'scores'
    id = db.Column(db.Integer, primary_key=True)
    value = db.Column(db.Integer)
    timestamp = db.Column(db.DateTime, default=dt.datetime.utcnow)

    def to_dict(self):
        return {'id': self.id,
                'value': self.value,
                'timestamp': self.timestamp}


@app.route('/')
def index():
    scores_ = Score.query.order_by(Score.value.desc()).all()
    recent = Score.query.order_by(Score.id.desc()).first()
    return render_template('index.html', scores=scores_, recent=recent)


@app.route('/scores', methods=['GET', 'POST'])
def scores():
    if request.method == 'POST':
        if 'value' not in request.args:
            abort(400)
        entry = Score.create(value=request.args.get('value'))
        entry.save()
        return jsonify(entry.to_dict()), 200
    elif request.method == 'GET':
        scores_ = Score.query.order_by(Score.value.amount.desc()).all()
        response = {}
        for score in scores_:
            response[score.id] = score.value
        return response


if __name__ == '__main__':
    app.run()
