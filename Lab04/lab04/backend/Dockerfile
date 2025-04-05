FROM node:18.19.1

WORKDIR /usr/src/app
COPY package*.json ./

RUN npm ci

ENV DB_NAME=laborator
ENV DB_USER=student
ENV DB_PASSWORD=parolasecreta

COPY . .

EXPOSE 3000
CMD [ "node", "server.js" ]