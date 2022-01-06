// const SerialPort = require('serialport')
// const port = new SerialPort('COM5', 
// // function (err) {
// //     if (err) {
// //       return console.log('Error: ', err.message)
// //     } },
//         {
//     baudRate: 9600
    
  
// })

// //main code to read data

// const ReadLine = SerialPort.parsers.Readline;

// const parser = new ReadLine();
// port.pipe(parser);

// let data = [];

// //read data from serial port
// parser.on("data", (line) => {
//     data.push(line)
//     console.log(data)
//     document.getElementById("rona").innerHTML = data;
// } );



// module.exports.data;

//getting serial port list in js


// SerialPort.list().then(function(ports){
//   ports.forEach(function(port){
//     console.log("Port: ", port);
//   })
// });


//socket:


var express = require('express'),
    app = express(),
    server = require('http').Server(app),
    io = require('socket.io')(server),
    port = 8888;

//Server start
server.listen(port, () => console.log('on port' + port))

//user server
app.use(express.static(__dirname + '/public'));


//body parser which is now replaced by express is used to parse body of your choice
app.use(express.urlencoded({extended: false}))//parse simple bodies of url encoded data
app.use(express.json());//this is to extract json data and make it readable

//Insurance to prevent cors error
app.use((req, res, next)=>{
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", 'Origin, X-Requested-With, Content-Type, Accept, Authorization');

    if (req.method === 'OPTIONS'){
        res.header("Access-Control-Allow-Methods", "PUT, POST, PATCH, DELETE, GET");
        return res.status(200).json({});
    }
    next(); 
})


io.on('connection', onConnection);

var connectedSocket = null;
function onConnection(socket){
    connectedSocket = socket;
}




const SerialPort = require('serialport');

let portConn = [];
// SerialPort.list().then(function(ports){
//     ports.forEach(function(port){
//      portConn.push(port)
//     //  console.log(portConn)
//     })
//   });

// console.log(portConn);


const Readline = SerialPort.parsers.Readline; 
const usbport = new SerialPort('COM5');  
const parser = usbport.pipe(new Readline()); 
parser.on('data', function (data) {
   
        
    
    io.emit('serialdata', { data: data});
    console.log(data);

});


