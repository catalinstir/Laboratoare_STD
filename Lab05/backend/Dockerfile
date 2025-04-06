FROM node:alpine

WORKDIR /app

COPY package*.json .

RUN npm install

RUN chown -R node:node /app

COPY . .

EXPOSE 8080

CMD [ "node", "index.js" ]
