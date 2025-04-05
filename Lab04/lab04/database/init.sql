DROP TABLE IF EXISTS tasks;

CREATE TABLE tasks(
    task_id serial primary key,
    created_at timestamp default NOW() NOT NULL,
    description text NOT NULL,
    status text default 'IN_PROGRESS' NOT NULL
);