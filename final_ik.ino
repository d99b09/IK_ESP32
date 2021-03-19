#include <WiFi.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const char* ssid     = "a407";//"iGarage";"a202";
const char* password = "Xqwert1!";//"igarage18";"gamma113";

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
void dg_in_pwe(int deg1, int deg2, int deg3){
	int mid = 1520;
 Serial.println(deg1);
 Serial.println(deg2);
 Serial.println(deg3);
	int pwe1 = mid + deg1 * 10.3529412;
	int pwe2 = mid - deg2 * 10.3529412;
	int pwe3 = mid + deg3 * 10.3529412;
 
	for (int i = 0; i < 200; i++){
		servo1.writeMicroseconds(pwe1control);
		servo2.writeMicroseconds(pwe2control);
		servo3.writeMicroseconds(pwe3control);
	if (pwe1control > pwe1){
		pwe1control = pwe1control - 5;
		}
	if (pwe1control < pwe1){
		pwe1control = pwe1control + 5;
		}
	if (pwe2control > pwe2){
		pwe2control = pwe2control - 5;
		}
	if (pwe2control < pwe2){
		pwe2control = pwe2control + 5;
		}
	if (pwe3control > pwe3){
		pwe3control = pwe3control - 5;
		}
	if (pwe3control < pwe3){
		pwe3control = pwe3control + 5;
		}
  delay(50);
	}
  //pwe1control = pwe1;
  //servo1.writeMicroseconds(pwe1control);
  //pwe2control = pwe2;
  //servo2.writeMicroseconds(pwe2control);
  //pwe3control = pwe3;
  //servo3.writeMicroseconds(pwe3control);
}
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
    //Serial.println(pwe1control);
		pwe1control = pwe1control - 5 ;
		delay(50);
	}
	pwe1control = pwe1;
	servo1.writeMicroseconds(pwe1control);
	
}
else {
	while (pwe1control < pwe1){
		servo1.writeMicroseconds(pwe1control);
		//Serial.println(pwe1control);
		pwe1control = pwe1control + 5 ;
		delay(50);
	}
	pwe1control = pwe1;
	servo1.writeMicroseconds(pwe1control);
}

}

void setup() {
  Serial.begin(115200);
  
 
  servo4.attach(32);
  servo3.attach(33);
  servo2.attach(25);
  servo1.attach(26);
  

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");  
  Serial.println("IP address: ");    
  Serial.println(WiFi.localIP());
  server.begin();
  
  servo1.writeMicroseconds(pwe1control);
  servo2.writeMicroseconds(pwe2control);
  servo3.writeMicroseconds(pwe3control);
  servo4.write(20);

}

void loop() {
  WiFiClient client = server.available();
  if (client) {                          
    Serial.println("New Client."); 
      
    String currentLine = "";
	while (client.connected()) {
    
		if (client.available()) {     // если у клиента есть данные,
                                    // которые можно прочесть, 
        char c = client.read();     // считываем байт, а затем    
             // печатаем его в мониторе порта
        header += c;

        
        
        if (c == '\n') {            // если этим байтом является
                                    // символ новой строки
          // если получили два символа новой строки подряд,
          // то это значит, что текущая строчка пуста;
          // это конец HTTP-запроса клиента,
          // а значит – пора отправлять ответ:
          if (currentLine.length() == 0) {

            

            
            // HTTP-заголовки всегда начинаются
            // с кода ответа (например, «HTTP/1.1 200 OK»)
            // и информации о типе контента
            // (чтобы клиент понимал, что получает);
            // в конце пишем пустую строчку:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
                       //  "Соединение: отключено"
            client.println();

            // показываем веб-страницу:
            client.println("<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='icon' href='data:;base64,='>");
            client.println("  <title>ServoGUI</title><style>");
            client.println("    .slider {");
            client.println("      width: 300px;}");
            client.println("  .inputwindow{");
            client.println("    width: 30px;} ");
            client.println("  .control_b { ");
            client.println("    width:50px;");
            client.println("    height: 50px;} ");
            client.println("  .ee_control_b { ");
            client.println("    width:50px;");
            client.println("    height: 25px;}   ");
            client.println("  i {border: solid black;");
            client.println("  border-width: 0 3px 3px 0;");
            client.println("  display: inline-block;");
            client.println("  padding: 10px;}");
            client.println("  .right {transform: rotate(-45deg);");
            client.println("    -webkit-transform: rotate(-45deg);}");
            client.println("  .left {transform: rotate(135deg);");
            client.println("    -webkit-transform: rotate(135deg);}");
            client.println("  .up{transform: rotate(-135deg);");
            client.println("    -webkit-transform: rotate(-135deg);}");
            client.println("  .down{transform: rotate(45deg);");
            client.println("    -webkit-transform: rotate(45deg);}  ");
            client.println("  .le{transform: rotate(-90deg);");
            client.println("    -webkit-transform: rotate(-90deg);}  ");
            client.println("  .ri{transform: rotate(180deg);");
            client.println("    -webkit-transform: rotate(180deg);}</style> ");
            client.println("  <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script></head>");
            client.println("<body><h1>ServoGUI with ESP32</h1>  ");
            client.println("  <div><h2>Set joint position</h2>");
            client.println("  <p>q1:<input type='range' min='-85' max='85' id='rq1' onchange='set_iq1()' class='slider'/>");
            client.println("  <input type='text' id='iq1' class='inputwindow' value='0' onchange='set_rq1()'>, deg.</p>");
            client.println("  <p>q2:<input type='range' min='-85' max='85' id='rq2' onchange='set_iq2()' class='slider'/>");
            client.println("  <input type='text' id='iq2' class='inputwindow' value='0' onchange='set_rq2()'>, deg.</p>");
            client.println("    <p>q3:<input type='range' min='-85' max='85' id='rq3' onchange='set_iq3()' class='slider'/>");
            client.println("  <input type='text' id='iq3' class='inputwindow' value='0' onchange='set_rq3()'>, deg.</p>");
            client.println("  <p><input type='button' value='Set joint' onclick='set_joint()'/></p></div>      ");
            client.println("  <div> <h2>Inverse kinematics solution</h2>");
            client.println("  <p>x:<input type='range' min='-454' max='454' id='rx' onchange='set_ix()' class='slider'/>");
            client.println("  <input type='text' id='ix'  class='inputwindow' value='0' onchange='set_rx()'>, mm</p>");
            client.println("  <p>z:<input type='range' min='0' max='497' id='rz' value='497' onchange='set_iz()' class='slider'/>");
            client.println("  <input type='text' id='iz'  class='inputwindow' value='497' onchange='set_rz()'>, mm</p>");
            client.println("    <p>a:<input type='range' min='-180' max='180' id='ralf' onchange='set_ialf()' class='slider'/>");
            client.println("  <input type='text' id='ialf' class='inputwindow' value='0' onchange='set_ralf()'>, deg.</p>");
            client.println("  <p><input type='button' value='IK solution' onclick='ik_solution()'/></p></div>");
            client.println("  <div><p><input type='button' value='Up' onclick='get_up()'/></p>");
            client.println("  <p><input type='button' value='Down' onclick='get_down()'/></p></div>  ");
            client.println("  <div><h2>Control board</h2><table><tr>");
            client.println("            <td><button class='control_b' onclick='le_cb()'><i class='ri'></i></button></td> ");
            client.println("      <td><button class='control_b' onclick='up_cb()'><i class='up'></i></button></td>  ");
            client.println("      <td><button class='control_b' onclick='ri_cb()'><i class='le'></i></button></td></tr><tr>");
            client.println("            <td><button class='control_b' onclick='left_cb()'><i class='left'></i></button></td> ");
            client.println("      <td><table><tr><td><button class='ee_control_b' onclick='get_up()'><i class='up'></i></button></td></tr>");
            client.println("      <tr><td><button class='ee_control_b' onclick='get_down()'><i class='down'></i></button>");
            client.println("      </td></tr></table></td> ");
            client.println("      <td><button  class='control_b' onclick='right_cb()'><i class='right'></i></button></td>");
            client.println("        </tr><tr><td></td>");
            client.println("      <td><button  class='control_b' onclick='down_cb()'><i class='down'></i></button></td>");
            client.println("      <td></td></tr></table><div>  ");
            client.println("  <script>");
            client.println("    const L0 = 43.36;");
            client.println("  const L1 = 191.96;");
            client.println("    const L2 = 117.63;");
            client.println("    const L3 = 144.16;");
            client.println("    var q1 = 0;");
            client.println("    var q2 = 0;");
            client.println("    var q3 = 0;");
            client.println("    var x = 0;");
            client.println("    var z = 497;");
            client.println("    var alf = 0;  ");
            client.println("  var rq1el = document.getElementById('rq1');");
            client.println("  var rq2el = document.getElementById('rq2');");
            client.println("  var rq3el = document.getElementById('rq3');");
            client.println("  var rxel = document.getElementById('rx');");
            client.println("  var rzel = document.getElementById('rz');");
            client.println("  var ralfel = document.getElementById('ralf');");
            client.println("  var iq1el = document.getElementById('iq1');");
            client.println("  var iq2el = document.getElementById('iq2');");
            client.println("  var iq3el = document.getElementById('iq3');");
            client.println("  var ixel = document.getElementById('ix');");
            client.println("  var izel = document.getElementById('iz');");
            client.println("  var ialfel = document.getElementById('ialf'); ");
            client.println("  $.ajaxSetup({timeout:1000});  ");
            client.println("  function radians(grad){");
            client.println("      return (grad * Math.PI) / 180;}   ");
            client.println("    function get_up(){");
            client.println("    $.get('/?move=' + 'up' + '&');");
            client.println("    {Connection: close};} ");
            client.println("  function get_down(){");
            client.println("    $.get('/?move=down&');");
            client.println("    {Connection: close};}   ");
            client.println("    function get_q(q1, q2, q3){");
            client.println("      var q1str = String(Math.round(q1/0.017453292))");
            client.println("    var q2str = String(Math.round(q2/0.017453292))");
            client.println("    var q3str = String(Math.round(q3/0.017453292))");
            client.println("    $.get('/?q1=' + q1str + '&q2=' + q2str + '&&q3=' + q3str + '&&&');");
            client.println("    {Connection: close};}");
            client.println("  function set_iq1(){     ");
            client.println("    q1 = parseFloat(radians(rq1el.value));");
            client.println("    iq1el.value=rq1el.value;} ");
            client.println("  function set_iq2(){");
            client.println("    q2 = parseFloat(radians(rq2el.value));");
            client.println("    iq2el.value=rq2el.value;} ");
            client.println("  function set_iq3(){");
            client.println("    q3 = parseFloat(radians(rq3el.value));");
            client.println("    iq3el.value=rq3el.value;} ");
            client.println("  function set_ix(){");
            client.println("    x=parseFloat(rxel.value);");
            client.println("    ixel.value=x;}  ");
            client.println("  function set_iz(){");
            client.println("    z=parseFloat(rzel.value);");
            client.println("    izel.value=z;}  ");
            client.println("  function set_ialf(){");
            client.println("    alf=parseFloat(radians(ralfel.value));");
            client.println("    ialfel.value=ralfel.value;}");
            client.println("    function set_rq1(){     ");
            client.println("    q1 = parseFloat(radians(iq1el.value));");
            client.println("    rq1el.value=iq1el.value;} ");
            client.println("  function set_rq2(){");
            client.println("    q2 = parseFloat(radians(iq2el.value));");
            client.println("    rq2el.value=iq2el.value;} ");
            client.println("  function set_rq3(){");
            client.println("    q3 = parseFloat(radians(iq3el.value));");
            client.println("    rq3el.value=iq3el.value;} ");
            client.println("  function set_rx(){");
            client.println("    x=parseFloat(ixel.value);");
            client.println("    rxel.value=x;}  ");
            client.println("  function set_rz(){");
            client.println("    z=parseFloat(izel.value);");
            client.println("    rzel.value=z;}  ");
            client.println("  function set_ralf(){");
            client.println("    alf=parseFloat(radians(ialfel.value));");
            client.println("    ralfel.value=ialfel.value;}");
            client.println("  ");
            client.println("  function set_joint(){");
            client.println("    var c1 = Math.cos(q1);");
            client.println("      var c12 = Math.cos(q1 + q2);");
            client.println("      var c123 = Math.cos(q1 + q2 + q3);");
            client.println("      var s1 = Math.sin(q1);");
            client.println("      var s12 = Math.sin(q1 + q2);");
            client.println("      var s123 = Math.sin(q1 + q2 + q3);   ");
            client.println("    z = Math.round(L0 + L1 * c1 + L2 * c12 + L3 * c123);");
            client.println("      x = Math.round(L1 * s1 + L2 * s12 + L3 * s123);");
            client.println("    if (((L1 * c1) < 0) || ((L1 * c1 + L2 * c12) < 0) || ((L1 * c1 + L2 * c12 + L3 * c123) < 0)){");
            client.println("      alert('Error! Joint s positions are incorrect. Please, repit input again.');}");
            client.println("    else{");
            client.println("      alf = q1 + q2 + q3");
            client.println("      ixel.value=Math.round(x);");
            client.println("      izel.value=Math.round(z);");
            client.println("      ialfel.value= parseInt(rq1el.value) + parseInt(rq2el.value) + parseInt(rq3el.value);");
            client.println("      rxel.value=Math.round(x);");
            client.println("      rzel.value=Math.round(z);");
            client.println("      ralfel.value= parseInt(rq1el.value) + parseInt(rq2el.value) + parseInt(rq3el.value);");
            client.println("      get_q(q1, q2, q3);}}");
            client.println("  ");
            client.println("  function ik_solution(){");
            client.println("    if(Math.sqrt(x*x+z*z) < 37){");
            client.println("      alert('Error End-effectors position are incorrect. Please, repit input again.')}");
            client.println("    else{");
            client.println("      var calf = Math.cos(alf);");
            client.println("        var salf = Math.sin(alf);");
            client.println("      var x1 = z - L3 * calf - L0;");
            client.println("      var y1 = x - L3 * salf;");
            client.println("      var cq2 = (x1 * x1 + y1 * y1 - L1 * L1 - L2 * L2) / (2 * L1 * L2);");
            client.println("      var q02 = Math.acos(cq2);}");
            client.println("    if (!q02){alert('Error! End-effectors position are incorrect. Please, repit input again.');}");
            client.println("    else{   ");
            client.println("      if (x < 0){var q002 = -Math.abs(q02);}");
            client.println("      else{");
            client.println("      var q002 = Math.abs(q02);}    ");
            client.println("      var c2 = Math.cos(q002);");
            client.println("        var s2 = Math.sin(q002);    ");
            client.println("      var K = L1 + L2 * c2;");
            client.println("      var D = (y1 * L2 * s2) * (y1 * L2 * s2) - (L2 * L2 * s2 * s2 + K * K) * (y1 * y1 - K * K);");
            client.println("      var cq1_1 = ((y1 * L2 * s2) + Math.sqrt(D)) / (L2 * L2 * s2 * s2 + K * K);");
            client.println("      var cq1_2 = ((y1 * L2 * s2) - Math.sqrt(D)) / (L2 * L2 * s2 * s2 + K * K);    ");
            client.println("      var q1_11 = Math.acos(cq1_1);");
            client.println("        var q1_12 = -q1_11;");
            client.println("      var q001 = q1_11;");
            client.println("      var q003 = alf - q001 - q002;   ");
            client.println("      var yn = L1 * Math.sin(q001) + L2 * Math.sin(q001 + q002) + L3 * Math.sin(q001 + q002 + q003);");
            client.println("        var xn = L0 + L1 * Math.cos(q001) + L2 * Math.cos(q001 + q002) + L3 * Math.cos(q001 + q002 + q003);   ");
            client.println("      if (z==Math.round(xn) && x==Math.round(yn)){");
            client.println("        q1 = q001;");
            client.println("        q2 = q002;");
            client.println("      q3 = q003;}");
            client.println("      else{");
            client.println("        q001 = q1_12;");
            client.println("        q003 = alf - q001 - q002;");
            client.println("        yn = L1 * Math.sin(q001) + L2 * Math.sin(q001 + q002) + L3 * Math.sin(q001 + q002 + q003);");
            client.println("          xn = L0 + L1 * Math.cos(q001) + L2 * Math.cos(q001 + q002) + L3 * Math.cos(q001 + q002 + q003);");
            client.println("      q1 = q001;");
            client.println("      q2 = q002;");
            client.println("      q3 = q003;}");
            client.println("      console.log(q1, q2, q3);");
            client.println("      rq1.value=Math.round(q1 / 0.017453292);");
            client.println("      rq2.value=Math.round(q2 / 0.017453292);");
            client.println("      rq3.value=Math.round(q3 / 0.017453292);");
            client.println("      iq1.value=Math.round(q1 / 0.017453292);");
            client.println("      iq2.value=Math.round(q2 / 0.017453292);");
            client.println("      iq3.value=Math.round(q3 / 0.017453292);");
            client.println("    if ((q1 > 1.48)||(q2 > 1.48)||(q3 > 1.48)||(q1 < -1.48)||(q2 < -1.48)||(q3 < -1.48)){alert('Error! End-effectors position are incorrect. Please, repit input again.');}else{get_q(q1, q2, q3);}}}");
            client.println("  function up_cb(){");
            client.println("    z = z+1;");
            client.println("    izel.value=z;");
            client.println("    rzel.value=z;");
            client.println("    ik_solution();}  ");
            client.println("  function down_cb(){");
            client.println("    z = z-1;");
            client.println("    izel.value=z;");
            client.println("    rzel.value=z;");
            client.println("    ik_solution();}  ");
            client.println("  function right_cb(){");
            client.println("    x = x+1;");
            client.println("    ixel.value=x;");
            client.println("    rxel.value=x;");
            client.println("    ik_solution();}  ");
            client.println("  function left_cb(){");
            client.println("    x = x-1;");
            client.println("    ixel.value=x;");
            client.println("    rxel.value=x;");
            client.println("    ik_solution();}   ");
            client.println("  function ri_cb(){");
            client.println("    alf = alf+0.017;");
            client.println("    ialfel.value=Math.round(alf/0.017);");
            client.println("    ralfel.value=Math.round(alf/0.017);");
            client.println("    ik_solution();}  ");
            client.println("    function le_cb(){");
            client.println("    alf = alf-0.017;");
            client.println("    ialfel.value=Math.round(alf/0.017);");
            client.println("    ralfel.value=Math.round(alf/0.017);");
            client.println("    ik_solution();}  ");
            client.println("  </script></body></html>");

            

            

            

            
            
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
			  int deg3 = valueStringq3.toInt();
			  int deg2 = valueStringq2.toInt();
			  int deg1 = valueStringq1.toInt();
			  dg_in_pwe(deg1, deg2, deg3);
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
            // выходим из цикла while(): 
            break;
          } else { // если получили символ новой строки,
                   // очищаем текущую строку «currentLine»:
            currentLine = "";
          }
        } else if (c != '\r') {  // если получили любые данные,
                                 // кроме символа возврата каретки,
          currentLine += c;      // добавляем эти данные 
                                 // в конец строки «currentLine»
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
  
