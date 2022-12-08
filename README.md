To install and run the Express.js server with SQLite, you will need to have Node.js and npm (the Node.js package manager) installed on your system. Here are the general steps that you can follow:

1. Create a new directory for your project, and navigate to it in a terminal.
2. Run `npm init` to initialize a new npm project in the directory. This will create a `package.json` file that lists the dependencies for the project.
3. Install the required dependencies by running `npm install --save express body-parser sqlite3`. This will install the `Express.js`, `body-parser`, and `sqlite3` modules and add them to the dependencies section of the package.json file.
4. Create a file called `server.js` in the project directory and paste the code that I provided earlier into it. This will be the entry point for the server.
5. Run the server by executing `node server.js` in the terminal. This will start the server and listen for incoming requests on port 3000.

If you want to access the server from a web browser, you can use a tool like ngrok to create a public URL that you can use to access the server from the internet. You can learn more about ngrok at https://ngrok.com/.