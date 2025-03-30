FROM php:8.3-apache

RUN docker-php-ext-install mysqli pdo_mysql \
    && rm -rf /var/lib/apt/lists/*

EXPOSE 80

COPY index.php /var/www/html

CMD ["apachectl", "-D", "FOREGROUND"]

