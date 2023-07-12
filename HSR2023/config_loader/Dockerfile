from archlinux

RUN pacman -Syu --noconfirm
RUN pacman -S gcc git lib32-gcc-libs lib32-glibc make --noconfirm
RUN git clone https://github.com/johnsonjh/ynetd.git /ynetd
RUN cd /ynetd && make

RUN useradd -m ctf

WORKDIR /home/ctf

#RUN cp -R /lib* /home/ctf && \
#    cp -R /usr/lib* /home/ctf

RUN mkdir /home/ctf/dev && \
    mknod /home/ctf/dev/null c 1 3 && \
    mknod /home/ctf/dev/zero c 1 5 && \
    mknod /home/ctf/dev/random c 1 8 && \
    mknod /home/ctf/dev/urandom c 1 9 && \
    chmod 666 /home/ctf/dev/*

RUN mkdir /home/ctf/bin && \
    cp /bin/sh /home/ctf/bin && \
    cp /bin/ls /home/ctf/bin && \
    cp /bin/cat /home/ctf/bin

COPY ./bin/ /home/ctf/
RUN chown -R ctf:ctf /home/ctf && \
    chmod -R 750 /home/ctf && \
    chmod 740 /home/ctf/flag

EXPOSE 1337

USER ctf
CMD ["/ynetd/./ynetd","-p","1337","/home/ctf/chall"]


