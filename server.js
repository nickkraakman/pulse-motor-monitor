const express = require('express');
const bodyParser = require('body-parser');
const sqlite3 = require('sqlite3').verbose(); // Import the sqlite3 module

const app = express();

// Parse incoming JSON data
app.use(bodyParser.json());

// Connect to the database
const db = new sqlite3.Database('./data.db', (err) => {
  if (err) {
    // If there was an error connecting to the database, log it to the console
    console.error(err.message);
  } else {
    // If the database was connected successfully, log a message to the console
    console.log('Connected to the database');
  }
});

// Create the table that will store the data
const sql = `
  CREATE TABLE IF NOT EXISTS data (
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    voltage1 REAL,
    voltage2 REAL,
    rpm REAL,
    switch INTEGER
  )
`;
db.run(sql);

// Handle POST request to save JSON data to the database
app.post('/save-data', (req, res) => {
  const data = req.body;

  // Save the data to the database
  db.run(
    'INSERT INTO data (voltage1, voltage2, rpm, switch) VALUES (?, ?, ?, ?)',
    [data.voltage1, data.voltage2, data.rpm, data.switch],
    (err) => {
      if (err) {
        // If there was an error, send a 500 status code
        res.status(500).send(err);
      } else {
        // If the data was saved successfully, send a 200 status code
        res.sendStatus(200);
      }
    },
  );
});

// Start the server
app.listen(3000, () => {
  console.log('Server listening on port 3000');
});
