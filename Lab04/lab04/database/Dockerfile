FROM postgres:14


ENV POSTGRES_USER=student
ENV POSTGRES_PASSWORD=parolasecreta
ENV POSTGRES_DB=laborator

COPY *.sql /docker-entrypoint-initdb.d/

EXPOSE 5432
