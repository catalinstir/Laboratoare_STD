# Laboratorul 4 - Docker Compose

## 1. Introducere

Laboratorul se focuseaza pe aplicatiile ce sunt compuse din mai multe elemente (e.g. o pagina compusa dintr-un frontend, un REST API si un database) si usurarea gestionarii si crearii lor cu _Docker Compose_.

### Resurse
Arhiva cu resursele de laborator:
```text
laborator
├── backend/
│   ├── Dockerfile
│   └── ... (Node.js project files)
├── database/
│   ├── Dockerfile
│   └── ... (SQL initialization scripts)
├── frontend/
│   ├── Dockerfile
│   ├── src/
│   └── ... (Angular project files)
└── docker-compose.yml
```
#### docker-compose.yml:
```yaml
services:
  database:
    build: 
      context: ./database
      dockerfile: Dockerfile
    container_name: lab4-db
    volumes:
      - todo-database-volume:/var/lib/postgresql/data
    networks:
      - lab4-std
  backend:
    build: 
      context: ./backend
      dockerfile: Dockerfile
    container_name: lab4-backend
    environment:
      - DB_NAME=laborator
      - DB_USER=student
      - DB_PASSWORD=parolasecreta
    networks:
      - lab4-std
    ports:
      - "3000:3000"
    depends_on:
      - database
  frontend:
    build: 
      context: ./frontend
      dockerfile: Dockerfile
    container_name: lab4-frontend
    networks:
      - lab4-std
    ports:
      - "8080:80"
    depends_on:
      - backend
networks:
  lab4-std:
volumes:
  todo-database-volume:
```
#### docker-compose-dev.yml:
```yaml
services:
  dev-frontend:
    container_name: dev-frontend
    build:
      context: ./frontend
      dockerfile: Dockerfile.development
    volumes:
      - ./frontend/src:/usr/local/app/src
    ports:
      - "4200:4200"
    networks:
      - lab4-std
    depends_on:
      - backend
```
Ne cream o retea virtuala Docker: `docker network create lab4-std`

## 2. Crearea Dockerfiles

### 1. Database

Avem _Dockerfile_-ul pentru db:
```dockerfile
FROM postgres:14

ENV POSTGRES_USER=student
ENV POSTGRES_PASSWORD=parolasecreta
ENV POSTGRES_DB=laborator

COPY *.sql /docker-entrypoint-initdb.d/

EXPOSE 5432
```
Cream imaginea: `docker image build -t laborator/todo-postgres lab04\database`
Si rulam containerul: `docker container run --name database --network lab4-std -d laborator/todo-postgres`

### 2. Backend

Ca si la database, construim imaginea de pe baza _Dockerfile_-ului: `docker image build -t laborator/todo-backend lab04/backend`
Rulam containerul: `docker container run --name backend --network lab4-std -p 3000:3000 -d laborator/todo-backend`

Verificam functionarea serviciului REST API: `curl http://localjost:3000/api/tasks`:
```sh
[]
```
Adaugam un task cu `curl -X POST -d'{"description": "Test"}' -H "Content-Type: application/json" http://localhost:3000/api/tasks`.
Verificand iar task-urile avem:
```sh
[{"task_id":1,"created_at":"2025-04-03T11:21:16.934Z","description":"Test","status":"IN_PROGRESS"}]
```

### 3. Frontend

Pentru frontend vom face un multi-stage build pentru eficienta:
- primul stage foloseste o imagine de `node` pentru a compila fisiere `html` statice ce urmeaza sa fie servite
- al doilea pas foloseste o imagine de `nginx` care va servi fisierele `html` compilate anterior

Observam _Dockerfile_-ul:
```dockerfile
FROM node:18.20-slim AS builder

WORKDIR /usr/local/app

COPY package*.json ./

ENV PATH="/usr/local/app/node_modules/.bin:$PATH"

RUN npm ci

COPY . ./
RUN npm run build --prod


FROM nginx:alpine
COPY --from=builder /usr/local/app/dist/frontend/browser /usr/share/nginx/html
COPY ./nginx.conf /etc/nginx/conf.d/default.conf
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

Construim si imaginea de frontend: `docker image build -t laborator/todo-frontend lab04/frontend`
Si pornim un container cu `docker container run --name todo-frontend --network lab4-std -p 8080:80 -d laborator/todo-frontend`

## 3. Creare fisier Docker Compose

Avand imaginile definite, putem crea fisierul de _docker compose_, avand atrubutele:
- `services`: lista de elemente definite printr-o imagine instantiata, un numar de replici ideintice si alte atribute aditionale:
  - `volumes`
  - `networks`
  - `ports`
  - etc.
- `networks`: lista de retele virtuale folosite in atributul __networks__ din servicii
- `volumes`: lista de volume persistente atribuite serviciilor

Fisierul docker-compose.yml poate fi vazut [mai sus](#docker-compose.yml:).

Comanda pentru a rula infrastructura este: `docker-compose up --build`.

> [!NOTE]
> Se poate adauga flag-ul `--detach` pentru a rula containerele in background

Pentru a opri containerele avem: `docker-compose down`.

## 4. Crearea unui mediu de dezvoltare

Dupa cum am vazut in fisierul prezentat anterior, putem porni intreaga aplicatie printr-o singura comanda.

Pentru a salva moficarile facute asupra interfetei web sau a serverului REST, putem folosi un bind mount, dar pentru frontend de exemplu, avem nevoie de o imagine care sa serveasca direct fisierele sursa.
Astfel, avem fisierul `Dockerfile.development`:
```dockerfile
FROM node:18.20-slim

WORKDIR /usr/local/app

COPY package*.json ./

RUN npm ci

RUN npm install -g @angular/cli@16.2.6

COPY . ./

EXPOSE 4200

CMD ng serve --host 0.0.0.0 --poll 2000 --configuration=hmr --proxy-config ./src/proxy.conf.json
```

Se va crea o imagine din acest fisier si se va porni un container 'montand' _bind mount_-ul si publicand portul corespunzator:
- `docker image build -t laborator/todo-frontend-dev -f Dockerfile.development lab04\frontend`
- `docker container run --name dev-frontend -p 4200:4200 --mount type=bind,src=lab04/frontend/src/,dst=/usr/local/app/src -d laborator/todo-frontend-dev`
, iar pentru integrarea acestui mediu de lucru alaturi de deployment-ul aplicatie, se va crea acest `docker-compose-dev.yml`:
```yaml
services:
  dev-frontend:
    container_name: dev-frontend
    build:
      context: ./frontend
      dockerfile: Dockerfile.development
    volumes:
      - ./frontend/src:/usr/local/app/src
    ports:
      - "4200:4200"
    networks:
      - lab4-std
    depends_on:
      - backend
```

Pentru aplicarea mai multor fisiere de tip compose se foloseste comanda:
- `docker-compose -f docker-compose.yml -f docker-compose-dev.yml up -d --build`

## 5. Extinderea mediului de dezvoltare

Acum vom dezvolta mediul de dezvoltare sa curprinda si partea de backend.

