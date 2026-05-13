const http = require('http');

const prefix = process.env.PREFIX || '/';
const port = 8080;

const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'application/json' });
  res.end(JSON.stringify({ status: 'ok', runtime: 'js' }));
});

server.listen(port, '0.0.0.0', () => {
  console.log(`Listening on port ${port}, prefix: ${prefix}`);
});
