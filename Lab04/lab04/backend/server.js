const express = require('express')
const bodyParser = require('body-parser')

const app = express();
const port = process.env.port || 3000;

app.use(bodyParser.json())
app.use(
  bodyParser.urlencoded({
    extended: true,
  })
)

const tasksRouter = require("./routes/tasks");

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
})

app.use('/api/tasks', tasksRouter);