FROM archlinux:latest

RUN pacman -Fy --noconfirm
RUN pacman -Syu --noconfirm
RUN pacman -S gcc git  make socat --noconfirm

RUN useradd -m ctf

WORKDIR /home/ctf

COPY ./data/ /home/ctf/
RUN chown -R ctf:ctf /home/ctf && \
    chmod -R 500 /home/ctf


EXPOSE 1337

USER ctf
CMD ["socat", "TCP-LISTEN:1337,fork", "EXEC:'/home/ctf/chall'"]
