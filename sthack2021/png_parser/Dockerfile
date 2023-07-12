FROM php:7.4.24-apache

# RUN pecl install xdebug && docker-php-ext-enable xdebug
RUN docker-php-ext-install exif


COPY ./config/php.ini /usr/local/etc/php/php.ini

RUN chown root:www-data /var/www/html && \
    chmod 750 /var/www/html

RUN mkdir -p /var/www/dev/uploads && \
    mkdir -p /var/www/dev/logs && \
    chown root:www-data /var/www/dev/uploads && \
    chown root:www-data /var/www/dev/logs && \
    chmod 770 /var/www/dev/uploads && \
    chmod 770 /var/www/dev/logs

COPY ./src /var/www/html
RUN mv /var/www/html/flag.txt /

COPY ./dev /var/www/dev

COPY ./config/000-default.conf /etc/apache2/sites-available

COPY ./png_analyzer /var/www/dev/png_analyzer

RUN chown www-data:www-data /var/www/dev/png_analyzer

RUN chmod +x /var/www/dev/png_analyzer

RUN a2ensite 000-default

WORKDIR /var/www/html

CMD ["apache2-foreground"]
