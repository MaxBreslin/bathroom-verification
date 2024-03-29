# Mostly generated by ChatGPT

#imports HTTPServer (basic server hosting class) and
#BaseHTTPRequestHandler (provides basic methods for requests like
#GET and POST)
from http.server import HTTPServer, BaseHTTPRequestHandler
#imports parsing methods for urls and querys
from urllib.parse import urlparse, parse_qs

#creates new class inheriting from parent class 'BaseHTTPRequestHandler'
class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    #overrides the method 'do_POST' defined in 'BaseHTTPRequestHandler'
    def do_POST(self):
        #gets integer number of bytes to read from the header of the
        #request handler?
        content_length = int(self.headers['Content-Length'])
        #reads the file for content_length bytes in context of utf-8
        body = self.rfile.read(content_length).decode('utf-8')
        #parses body using urllib.parse, params now contains the
        #id, timestamp, and bathroom-id
        params = parse_qs(body)
        
        #
        self.send_response(200)
        #for this instance of the class, the send_header method of
        #'BaseHTTPRequestHandler' will send along with the body a header
        #that states the content-type is plain text of encoding utf-8
        self.send_header('Content-type', 'text/plain; charset=utf-8')
        #indicates the end of the headers and the start of the body of
        #the response
        self.end_headers()
        
        #defines response with all the same values as 'params' but formats
        #it to look better for the write file
        response = f"student-id: {params['student-id']}\ntimestamp: {params['timestamp']}\nbathroom-id: {params['bathroom-id']}\n"
        #prints response to the terminal for testing purposes
        print(response)
        #opens 'bathroom-data.txt' and writes all the formatted data from 
        #the response variable into it
        with open('bathroom-data.txt', 'a') as f:
            f.write(response)

#defines the 'run' function with attributes 'server_class' which defaults
#to HTTPServer, 'handler_class' which defaults to
#SimpleHTTPRequestHandler, and 'port' which defaults to 8000
def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    #defines server_address as a local variable with port 8000
    #what does teh empty string do?
    server_address = ('', port)
    #defines httpd as a local variable equal to an HTTPServer instance
    #'server_class' with the 'server_address' and an instance of
    #SimpleHTTPRequestHandler 'handler_class'
    httpd = server_class(server_address, handler_class)
    #prints message to the terminal for testing purposes
    print('Starting server...')
    #boots the http server by calling the serve_forever method of httpd,
    #which will indefinitely listen for events until manually stopped
    httpd.serve_forever()

#checks if simple-server.py is being run as the main script, and calls
#the run function
if __name__ == '__main__':
    run()
