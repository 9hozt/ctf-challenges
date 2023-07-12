FROM php:fpm

RUN apt update && apt upgrade -y
RUN apt install -y zbar-tools
RUN apt install -y qrencode
RUN docker-php-ext-install pdo pdo_mysql
RUN mkdir /history
