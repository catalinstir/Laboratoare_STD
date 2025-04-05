const express = require('express')
const router = express.Router();

const Pool = require('pg').Pool
const pool = new Pool({
    user: process.env.DB_USER,
    host: 'database',
    database: process.env.DB_NAME,
    password: process.env.DB_PASSWORD,
    port: 5432,
  });

router.get('/', (req, res) => {
    pool.query('SELECT * FROM tasks ORDER BY created_at DESC', (error, results) => {
        if (error) {
          throw error;
        }
        res.status(200).json(results.rows);
      })
});

router.post('/', (req, res) => {
    const { description } = req.body

    pool.query('INSERT INTO tasks (description) VALUES ($1)', [description], (error, results) => {
        if (error) {
          throw error;
        }

        res.status(200).send({
          result: "Task successfully added."
        });
    });
});

router.put('/:task_id', (req, res) => {
    const task_id = parseInt(req.params.task_id)

    const { status } = req.body
    pool.query('UPDATE tasks SET status = $1 WHERE task_id = $2', [status, task_id], (error, results) => {
        if (error) {
            throw error
        }

        res.status(200).send(
          {
            result: "Task status was modified."
          });
    })
});

module.exports = router;