var http = require('http');

var handleRequest = function(request, response) {
  console.log('Received request for URL: ' + request.url);
  response.writeHead(200);

  // V2
  var date = new Date();

  // V1
  // response.end('Hello World! - ' );

  // V2
  response.end('Hello World! - ' + date.toISOString() );
};

var www = http.createServer(handleRequest);
www.listen(8080);
