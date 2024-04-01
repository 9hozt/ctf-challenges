FROM archlinux:latest

RUN pacman -Fy --noconfirm
RUN pacman -Syu --noconfirm
RUN pacman -S gcc git  make lib32-glibc --noconfirm 
RUN git clone https://github.com/johnsonjh/ynetd.git /ynetd
RUN cd /ynetd && make

RUN useradd -m ctf

WORKDIR /home/ctf

COPY ./data/ /home/ctf/
RUN chown -R ctf:ctf /home/ctf && \
    chmod -R 500 /home/ctf


EXPOSE 1337

USER ctf
CMD ["/ynetd/./ynetd","-p","1337","/home/ctf/chall"]

