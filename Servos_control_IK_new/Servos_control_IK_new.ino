#include <WiFi.h>
#include <DNSServer.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


const char* ssid = "TEST-123";
const char* password = "12345678";
int connections = 0;

WiFiServer server(80);

String header;

String moveString = String(6);
String valueStringq1 = String(5);
String valueStringq2 = String(5);
String valueStringq3 = String(5);

int pos1 = 0;
int pos2 = 0;


int pwe1control = 1520;
int pwe2control = 1520;
int pwe3control = 1520;

void dg_in_pwe3(int deg){
float mid = 1520;
int pwe3 = mid + deg * 10.3529412;
//servo3.writeMicroseconds(pwe3)
if (pwe3control > pwe3){
	while (pwe3control > pwe3){
		servo3.writeMicroseconds(pwe3control);
		pwe3control = pwe3control - 5 ;
		delay(50);
	}
	pwe3control = pwe3;
	servo3.writeMicroseconds(pwe3control);
	
}
else {
	while (pwe3control < pwe3){
		servo3.writeMicroseconds(pwe3control);
		pwe3control = pwe3control + 5 ;
		delay(50);
	}
	pwe3control = pwe3;
	servo3.writeMicroseconds(pwe3control);
}
}
void dg_in_pwe2(int deg){
float mid = 1520;
int pwe2 = mid - deg * 10.3529412;
//servo2.writeMicroseconds(pwe2)
if (pwe2control > pwe2){
	while (pwe2control > pwe2){
		servo2.writeMicroseconds(pwe2control);
		pwe2control = pwe2control - 5 ;
		delay(50);
	}
	pwe2control = pwe2;
	servo2.writeMicroseconds(pwe2control);
	
}
else {
	while (pwe2control < pwe2){
		servo2.writeMicroseconds(pwe2control);
		pwe2control = pwe2control + 5 ;
		delay(50);
	}
	pwe2control = pwe2;
	servo2.writeMicroseconds(pwe2control);
}
}
void dg_in_pwe1(int deg){
  //Serial.println(deg);
float mid = 1520;
int pwe1 = mid + deg * 10.3529412;
  //Serial.println(pwe1);

//servo1.writeMicroseconds(pwe1)
if (pwe1control > pwe1){
	while (pwe1control > pwe1){
		servo1.writeMicroseconds(pwe1control);
    Serial.println(pwe1control);
		pwe1control = pwe1control - 5 ;
		delay(50);
	}
	pwe1control = pwe1;
	servo1.writeMicroseconds(pwe1control);
	
}
else {
	while (pwe1control < pwe1){
		servo1.writeMicroseconds(pwe1control);
		Serial.println(pwe1control);
		pwe1control = pwe1control + 5 ;
		delay(50);
	}
	pwe1control = pwe1;
	servo1.writeMicroseconds(pwe1control);
}

}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  connections += 1;
  showConnectionsCount();
}

void showConnectionsCount() {
  char data[32];
  sprintf(data, "Connections: %d", connections);
  Serial.println(data);
}

void setup() {
  Serial.begin(115200);    
  
  servo4.attach(32);
  servo3.attach(33);
  servo2.attach(25);
  servo1.attach(26);
  
  Serial.println();
  Serial.println("Configuring access point...");

  // Start access point 
  WiFi.mode(WIFI_AP);                   
  WiFi.softAP(ssid, password);
  WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);

  IPAddress ip_address = WiFi.softAPIP();     //IP Address of our accesspoint

  // Start web server
  server.begin();
  
  Serial.print("AP IP address: ");
  Serial.println(ip_address);



  // Total number of connections
  showConnectionsCount();
  
  servo1.writeMicroseconds(pwe1control);
  servo2.writeMicroseconds(pwe2control);
  servo3.writeMicroseconds(pwe3control);
  servo4.write(20);

}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
     Serial.println("Client connected");
    
    String currentLine = "";   // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client's connected
      if (client.available()) {        // if there's bytes to read from the client,
        char c = client.read();      // read a byte, then
        Serial.write(c);                // print it out the serial monitor
        if (c == '\n') {                 // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // Send header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
// показываем веб-страницу:
			String responseHTML = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='icon' href='data:;base64,='>"
  "<title>ServoGUI</title><style>"
  "body{font-size: 32px; }"
  "  input{font-size : 24px;}"
  "input[type="text"]{width: 50px;}"
  ".Inf{font-size: 24px; } "

  
        ".block1 {"
			
			"width: 100vw;"
			"height: 100vw;"
        "} "
		

        "/* для декстопов */"
        "@media (min-width:481px) {"
            ".block1 {"
				"margin: 0 auto;"

				"width: 480px;"
				"height: 480px;"
            "}"
			".slider {"
			"width: 300px;}"
			"}"
    ".block_info {"
		"margin: 0 auto;"

		"width: 240px;"
		"height: 240px;}	"		
  ".infoblock{"
  "border-radius: 50%;"
  " background: #ccc"
 " }"
  "  .slider {"
   "   width: 40%;}"
  ".inputwindow{"
	  
  "  width: 30px;} "
	".control_b {"
	"	width:100%;"
	"	height:100%;} "
  ".ee_control_b { "
   " width:50px;"
   " height: 25px;}   "
  "i {border: solid black;"
 " border-width: 0 4.5px 4.5px 0;"
 " display: inline-block;"
  "padding: 15px;}"
  ".right {transform: rotate(-45deg);"
 "   -webkit-transform: rotate(-45deg);}"
 " .left {transform: rotate(135deg);"
 "  -webkit-transform:  (135deg);}"
 " .up{transform: rotate(-135deg);"
  "  -webkit-transform: rotate(-135deg);}"
  ".down{transform: rotate(45deg);"
 "   -webkit-transform: rotate(45deg);}  "
 " .le{transform: rotate(-90deg);"
  "  -webkit-transform: rotate(-90deg);}  "
 " .ri{transform: rotate(180deg);"
  "  -webkit-transform: rotate(180deg);}"
  ".tap{transform: rotate(-135deg);"
  "   width: 5px; "
  "   height: 5px;"
  "   background: #000000;"
"	border-radius: 50%;}"

"	table{ height: 100%;}"

  "    #main {display: none;"
	"    position: absolute;"
  "      top: 200px;"
  "      left: 0;"
  "      width: 100%;"
  "      height: 100%;}"
	"  #main:target {display: block;}"
  "    #okno {"
     "   width: 300px;"
		"height: 500px;"
	"	background: #cccccc;	"	
     "   padding: 15px;"
		"text-align: justify;"
      "  position: absolute;"
      "  top: 0;"
      "  right: 0;"
      "  bottom: 0;"
      "  left: 0;"
     "  margin: auto;"
     " }"

"</style> "
 " <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script></head>"
"<body><h1>ServoGUI with ESP32</h1>  "
"   <a href='#' id='main'>"
 "     <div id='okno'>"
  "      <div class='block_info'><table width='100%' heigh='100%'>"
	"  <tr>"
  "    <td><button class='control_b'><i class='ri'></i>1</button></td> "
   "   <td><button class='control_b'><i class='up'></i>2</button></td>  "
   "   <td><button class='control_b'><i class='le'></i>1 </button></td>"
	"  </tr>"
	"  <tr>"
	"  <td><button class='control_b'><i class='left'></i>3</button></td> "
   "   <td><button class='control_b'><i class='tap'></i>4</button></td>"
	"  <td><button  class='control_b'><i class='right'></i>3</button></td>"
	"  </tr><tr><td></td>"
    "  <td><button  class='control_b'><i class='down'></i>2</button></td>"
    "  <td></td></tr></table></div>"
	"  <div class='Inf'>1 - Вращение рабочего органа вокруг оси Y<br>"
"2 - Перемещение рабочего органа вдоль оси Z<br>"
"3 - Перемещение рабочего органа вдоль оси X<br>"
"4 - Сжатие/Разжатие захвата</div>"
   "   </div>"
   " </a>"
     

 
	"<div><h2>Set joint position</h2>"
  "<p>q1:<input type='range' min='-85' max='85' id='rq1' onchange='set_iq1()' class='slider'/>"
  "<input type='text' id='iq1' class='inputwindow' value='0' onchange='set_rq1()'>, deg.</p>"
 " <p>q2:<input type='range' min='-85' max='85' id='rq2' onchange='set_iq2()' class='slider'/>"
  "<input type='text' id='iq2' class='inputwindow' value='0' onchange='set_rq2()'>, deg.</p>"
  
  "  <p>q3:<input type='range' min='-85' max='85' id='rq3' onchange='set_iq3()' class='slider'/>"
  "<input type='text' id='iq3' class='inputwindow' value='0' onchange='set_rq3()'>, deg.</p>"
 " <p><input type='button' value='Set joint' onclick='set_joint()'/></p></div>      "
 " <div> <h2>Inverse kinematics solution</h2>"
 " <p>x:<input type='range' min='-454' max='454' id='rx' onchange='set_ix()' class='slider'/>"
 " <input type='text' id='ix'  class='inputwindow' value='0' onchange='set_rx()'>, mm</p>"
  "<p>z:<input type='range' min='0' max='497' id='rz' value='497' onchange='set_iz()' class='slider'/>"
 " <input type='text' id='iz'  class='inputwindow' value='497' onchange='set_rz()'>, mm</p>"
 "   <p>a:<input type='range' min='-180' max='180' id='ralf' onchange='set_ialf()' class='slider'/>"
 " <input type='text' id='ialf' class='inputwindow' value='0' onchange='set_ralf()'>, deg.</p>"
 " <p><input type='button' value='IK solution' onclick='ik_solution()'/></p></div>"
"  <div><p><input type='button' value='Up' onclick='get_up()'/></p>"
 " <p><input type='button' value='Down' onclick='get_down()'/></p></div>"
 " <div><h2 align='center' >Control board<a href='#main'><sup>info</sup></a></h2></div>"

     
   
 " <div class='block1'><table width='100%' heigh='100%'>"
"	  <tr>"
  "    <td><button class='control_b' onclick='le_cb()'><i class='ri'></i></button></td> "
  "    <td><button class='control_b' onclick='up_cb()'><i class='up'></i></button></td>  "
  "    <td><button class='control_b' onclick='ri_cb()'><i class='le'></i></button></td>"
	"  </tr>"
	"  <tr>"
	"  <td><button class='control_b' onclick='left_cb()'><i class='left'></i></button></td> "
   "   <td><button class='control_b' onclick='get_change()'><i class='tap'></i></button></td>"
	"  <td><button  class='control_b' onclick='right_cb()'><i class='right'></i></button></td>"
	"  </tr><tr><td></td>"
   "   <td><button  class='control_b' onclick='down_cb()'><i class='down'></i></button></td>"
    "  <td></td></tr></table></div>  "	    
 " <script>"
	"var grip_open = true;"
   " const L0 = 43.36;"
    "const L1 = 191.96;"
    "const L2 = 117.63;"
   " const L3 = 144.16;"
   " var q1 = 0;"
   " var q2 = 0;"
  "  var q3 = 0;"
  "  var x = 0;"
   " var z = 497;"
   " var alf = 0;  "
 " var rq1el = document.getElementById('rq1');"
 " var rq2el = document.getElementById('rq2');"
 " var rq3el = document.getElementById('rq3');"
 " var rxel = document.getElementById('rx');"
 " var rzel = document.getElementById('rz');"
 " var ralfel = document.getElementById('ralf');"
 " var iq1el = document.getElementById('iq1');"
 " var iq2el = document.getElementById('iq2');"
 " var iq3el = document.getElementById('iq3');"
  "var ixel = document.getElementById('ix');"
 " var izel = document.getElementById('iz');"
 " var ialfel = document.getElementById('ialf'); "
 " $.ajaxSetup({timeout:1000});  "
 " function radians(grad){"
     " return (grad * Math.PI) / 180;}   "
 " function get_up(){"
  "  $.get('/?move=' + 'up' + '&');"
  "  {Connection: close};} "
  "function get_down(){"
  "  $.get('/?move=down&');"
  "  {Connection: close};}"
  "function get_change(){"
  "  if (grip_open){"
"	get_up();"
"	grip_open = false;"
	"}"
	"else{"
	"get_down();"
	"grip_open = true;}"
	"console.log(grip_open);"
   " };	"
   " function get_q(q1, q2, q3){"
    "  var q1str = String(Math.round(q1/0.017453292))"
   " var q2str = String(Math.round(q2/0.017453292))"
   " var q3str = String(Math.round(q3/0.017453292))"
    "$.get('/?q1=' + q1str + '&q2=' + q2str + '&&q3=' + q3str + '&&&');"
  "  {Connection: close};}"
 " function set_iq1(){     "
"    q1 = parseFloat(radians(rq1el.value));"
 "   iq1el.value=rq1el.value;} "
 " function set_iq2(){"
   " q2 = parseFloat(radians(rq2el.value));"
  "  iq2el.value=rq2el.value;} "
  "function set_iq3(){"
 "   q3 = parseFloat(radians(rq3el.value));"
  "  iq3el.value=rq3el.value;} "
  "function set_ix(){"
 "   x=parseFloat(rxel.value);"
 "   ixel.value=x;}  "
 " function set_iz(){"
 "   z=parseFloat(rzel.value);"
 "   izel.value=z;}  "
 " function set_ialf(){"
  "  alf=parseFloat(radians(ralfel.value));"
  "  ialfel.value=ralfel.value;}"
  "  function set_rq1(){     "
  "  q1 = parseFloat(radians(iq1el.value));"
 "   rq1el.value=iq1el.value;} "
"  function set_rq2(){"
  "  q2 = parseFloat(radians(iq2el.value));"
   " rq2el.value=iq2el.value;} "
  "function set_rq3(){"
  "  q3 = parseFloat(radians(iq3el.value));"
  "  rq3el.value=iq3el.value;} "
  "function set_rx(){"
  "  x=parseFloat(ixel.value);"
  "  rxel.value=x;}"
  "function set_rz(){"
  "  z=parseFloat(izel.value);"
  "  rzel.value=z;}"
  "function set_ralf(){"
  "  alf=parseFloat(radians(ialfel.value));"
  "  ralfel.value=ialfel.value;}"
  
 " function set_joint(){"
  "  var c1 = Math.cos(q1);"
  "    var c12 = Math.cos(q1 + q2);"
   "   var c123 = Math.cos(q1 + q2 + q3);"
   "   var s1 = Math.sin(q1);"
   "   var s12 = Math.sin(q1 + q2);"
   "   var s123 = Math.sin(q1 + q2 + q3);"
   " z = Math.round(L0 + L1 * c1 + L2 * c12 + L3 * c123);"
   "   x = Math.round(L1 * s1 + L2 * s12 + L3 * s123);"
   " if (((L1 * c1) < 0) || ((L1 * c1 + L2 * c12) < 0) || ((L1 * c1 + L2 * c12 + L3 * c123) < 0)){"
   "   alert('Error! Joint s positions are incorrect. Please, repeat input again.');}"
   " else{"
   "   alf = q1 + q2 + q3"
   "   ixel.value=Math.round(x);"
    "  izel.value=Math.round(z);"
   "   ialfel.value= parseInt(rq1el.value) + parseInt(rq2el.value) + parseInt(rq3el.value);"
   "   rxel.value=Math.round(x);"
   "   rzel.value=Math.round(z);"
   "   ralfel.value= parseInt(rq1el.value) + parseInt(rq2el.value) + parseInt(rq3el.value);"
    "  get_q(q1, q2, q3);}}"
 " function ik_solution(){"
 "   if(Math.sqrt(x*x+z*z) < 37){"
  "    alert('Error End-effectors position are incorrect. Please, repeat input again.')}"
   " else{"
   "   var calf = Math.cos(alf);"
  "      var salf = Math.sin(alf);"
   "   var x1 = z - L3 * calf - L0;"
   "   var y1 = x - L3 * salf;"
  "    var cq2 = (x1 * x1 + y1 * y1 - L1 * L1 - L2 * L2) / (2 * L1 * L2);"
   "   var q02 = Math.acos(cq2);}"
  "  if (!q02){alert('Error! End-effectors position are incorrect. Please, repeat input again.');}"
  "  else{"
  "    if (x < 0){var q002 = -Math.abs(q02);}"
  "    else{"
  "    var q002 = Math.abs(q02);}"
  "    var c2 = Math.cos(q002);"
   "     var s2 = Math.sin(q002);"
   "   var K = L1 + L2 * c2;"
   "   var D = (y1 * L2 * s2) * (y1 * L2 * s2) - (L2 * L2 * s2 * s2 + K * K) * (y1 * y1 - K * K);"
    "  var cq1_1 = ((y1 * L2 * s2) + Math.sqrt(D)) / (L2 * L2 * s2 * s2 + K * K);"
    "  var cq1_2 = ((y1 * L2 * s2) - Math.sqrt(D)) / (L2 * L2 * s2 * s2 + K * K);"
    "  var q1_11 = Math.acos(cq1_1);"
    "    var q1_12 = -q1_11;"
   "   var q001 = q1_11;"
   "   var q003 = alf - q001 - q002;"
   "   var yn = L1 * Math.sin(q001) + L2 * Math.sin(q001 + q002) + L3 * Math.sin(q001 + q002 + q003);"
  "      var xn = L0 + L1 * Math.cos(q001) + L2 * Math.cos(q001 + q002) + L3 * Math.cos(q001 + q002 + q003);"
   "   if (z==Math.round(xn) && x==Math.round(yn)){"
   "     q1 = q001;"
 "       q2 = q002;"
 "     q3 = q003;}"
 "     else{"
   "     q001 = q1_12;"
  "      q003 = alf - q001 - q002;"
  "      yn = L1 * Math.sin(q001) + L2 * Math.sin(q001 + q002) + L3 * Math.sin(q001 + q002 + q003);"
 "         xn = L0 + L1 * Math.cos(q001) + L2 * Math.cos(q001 + q002) + L3 * Math.cos(q001 + q002 + q003);"
 "     q1 = q001;"
 "     q2 = q002;"
 "     q3 = q003;}"
 "     console.log(q1, q2, q3);"
 "     rq1.value=Math.round(q1 / 0.017453292);"
  "    rq2.value=Math.round(q2 / 0.017453292);"
 "     rq3.value=Math.round(q3 / 0.017453292);"
    "  iq1.value=Math.round(q1 / 0.017453292);"
   "   iq2.value=Math.round(q2 / 0.017453292);"
   "   iq3.value=Math.round(q3 / 0.017453292);"
 "  if ((q1 > 1.48)||(q2 > 1.48)||(q3 > 1.48)||(q1 < -1.48)||(q2 < -1.48)||(q3 < -1.48)){alert('Error! End-effectors position are incorrect. Please, repit input again.');}else{get_q(q1, q2, q3);}}}"
 " function up_cb(){"
 "   z = z+1;"
"   izel.value=z;"
 "   rzel.value=z;"
 "   ik_solution();}"
"  function down_cb(){"
 "   z = z-1;"
 "   izel.value=z;"
  "  rzel.value=z;"
 "   ik_solution();}"
 " function right_cb(){"
 "   x = x+1;"
 "   ixel.value=x;"
  "  rxel.value=x;"
  "  ik_solution();}"
 " function left_cb(){"
 "   x = x-1;"
 "   ixel.value=x;"
 "   rxel.value=x;"
 "   ik_solution();}"
 " function ri_cb(){"
  "  alf = alf+0.017;"
 "   ialfel.value=Math.round(alf/0.017);"
 "   ralfel.value=Math.round(alf/0.017);"
  "  ik_solution();}"
  "  function le_cb(){"
 "   alf = alf-0.017;"
  "  ialfel.value=Math.round(alf/0.017);"
  "  ralfel.value=Math.round(alf/0.017);"
  "  ik_solution();}"
 " </script></body></html>";

            client.println(responseHTML);            
            // The HTTP response ends with another blank line
            if(header.indexOf("GET /?move=")>=0) {
              Serial.println(header);              
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              moveString = header.substring(pos1+1, pos2);
              Serial.println(moveString);
              
			  if(moveString=="up"){
			    servo4.writeMicroseconds(3000);
          
     			  
			  }
			  else{
			    servo4.writeMicroseconds(1727);
			    
			  }              
            }
            else if (header.indexOf("GET /?q1=")>=0){
              Serial.println(header); 
              				
			  pos1 = header.indexOf("q1=");
              pos2 = header.indexOf("&");
              valueStringq1 = header.substring(pos1+3, pos2);
              Serial.println(valueStringq1);
			  pos1 = header.indexOf("q2=");
              pos2 = header.indexOf("&&");
              valueStringq2 = header.substring(pos1+3, pos2);
              Serial.println(valueStringq2);
			  pos1 = header.indexOf("q3=");
              pos2 = header.indexOf("&&&");
              valueStringq3 = header.substring(pos1+3, pos2);
              Serial.println(valueStringq3);
              // вращаем ось сервомотора:			  
			  dg_in_pwe3(valueStringq3.toInt());
			  dg_in_pwe2(valueStringq2.toInt());
			  dg_in_pwe1(valueStringq1.toInt());
			  //servo1.writeMicroseconds(valueStringq1.toInt());
			  //servo2.writeMicroseconds(valueStringq2.toInt());
			  //servo3.writeMicroseconds(valueStringq3.toInt());
			  
       //Serial.println(valueStringq1);
       //Serial.println(valueStringq2);
       //Serial.println(valueStringq3);
       
       
			}			
            // конец HTTP-ответа задается 
            // с помощью дополнительной пустой строки:
            client.println();
            break;
          } else { // if we got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if we got anything else but a CR character,
          currentLine += c;   // add it to the end of the currentLine
        }
      }
    }
    // очищаем переменную «header»:
    header = "";
    // отключаем соединение:
    client.stop();
    Serial.println("Client disconnected.");
               //  "Клиент отключился."
    Serial.println("");

  }
}
