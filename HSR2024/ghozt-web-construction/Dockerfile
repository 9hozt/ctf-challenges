FROM python:3.10-rc-alpine

RUN pip install flask

RUN adduser -D ctf

COPY app.py /home/ctf/app/app.py
COPY templates/ /home/ctf/app/templates/
COPY ./flag.txt /home/ctf/flag.txt
RUN chmod 644 /home/ctf/flag.txt
EXPOSE 5000
USER ctf
WORKDIR /home/ctf/app
CMD python -u app.py
