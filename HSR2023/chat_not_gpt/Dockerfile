FROM python:3.10-rc-alpine

RUN pip install flask

RUN adduser -D ctf

COPY app.py ./
COPY templates/home.html ./templates/home.html
COPY ./flag.txt /home/ctf/flag.txt
RUN chmod 644 /home/ctf/flag.txt
EXPOSE 5000
USER ctf
CMD python -u app.py
