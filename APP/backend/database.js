import client from 'pg';

const database = new client.Pool({
    user: "postgres",
    host: "localhost",
    database: "postgres",
    password: "Gerfederer44",
});

export default database;