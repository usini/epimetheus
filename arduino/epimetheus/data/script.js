var ws=new WebSocket("ws://"+location.host+"/websocket");websocket_status=false;var chart_0_ctx=document.getElementById("chart_0").getContext('2d');chart_0=new Chart(chart_0_ctx,{type:'line',data:{datasets:[]},options:{}});time="";function currentTime(){var t=setTimeout(currentTime,1000);var date=new Date();var hour=updateTime(date.getHours());var min=updateTime(date.getMinutes());var sec=updateTime(date.getSeconds());time=hour+":"+min+":"+sec;document.getElementById("clock").innerHTML=time;}
function updateData(){var t=setTimeout(updateData,1000);if(websocket_status){msg={};msg.msg="update";ws.send(JSON.stringify(msg));}}
function updateTime(k){if(k<10){return"0"+k;}
else{return k;}}
function update_clock(){var date=new Date();message={};message.msg="set_clock";message.year=date.getFullYear();message.month=date.getMonth()+1;message.day=date.getDay();message.hour=date.getHours();message.minute=date.getMinutes();message.second=date.getSeconds();ws.send(JSON.stringify(message));}
currentTime();updateData();nb_sensors=0;ws.onopen=function(event){console.log(LANG_WEBSOCKET_OPEN);websocket_status=true;msg={};msg.msg="list";ws.send(JSON.stringify(msg));msg={};msg.msg="flash";ws.send(JSON.stringify(msg));msg={};msg.msg="name";ws.send(JSON.stringify(msg));msg.msg="get_clock"
ws.send(JSON.stringify(msg));};ws.onmessage=function(event){if(!isNaN(event.data)){json_parsed=false;}else{try{data=JSON.parse(event.data);json_parsed=true;}catch(e){json_parsed=false;}}
if(json_parsed){if(data.msg=="list"){generate_sensors(JSON.parse(event.data));}
if(data.msg=="name"){document.getElementById("esp_name").value=data.value;}
if(data.msg=="flash"){if(!data.value){document.getElementById("save_flash_icon").style.display="none";}}
if(data.msg=="change_name"){if(data.result){show_ok(LANG_NAME_SAVED_OK);}else{show_error(LANG_NAME_SAVED_ERROR);}}
if(data.msg=="get_clock"){var date_local=new Date();var date_remote=data["value"];var diff=Math.abs(Date.parse(date_local)-Date.parse(data["value"]))
if(diff>=5){update_clock();}}}else{chart_0.data.labels.push(time)
data=event.data.split(';');data.forEach(function(item,index,array){document.getElementById("sensor_value_"+index).innerHTML=item;chart_0.data.datasets[index].data.push(item);});chart_0.update();}}
ws.onclose=function(event){console.log(LANG_WEBSOCKET_CLOSED);}
ws.onerror=function(event){console.log(LANG_WEBSOCKET_ERROR);show_error(LANG_WEBSOCKET_ERROR);websocket_status=false;};function generate_sensors(data){if(data.result){data.value="...";const widget=`<tr class="theme_widget_background margin center"><td>${data.text}</td><td id="sensor_${data.id}"style="color:${data.color};"><span id="sensor_value_${data.id}">${data.value}</span>${data.unit}</td><td class="right">${data.sensor}</td></tr>`;widgets_code=document.getElementById("widgets").innerHTML
document.getElementById("widgets").innerHTML+=widget;nb_sensors++;chart_0.data.datasets.push({label:data.text,borderColor:data.color,borderWidth:1,data:[]})
chart_0.update();}}
const name_input=document.getElementById("esp_name");name_input.addEventListener("keydown",function(event){if(event.key==="Enter"){event.preventDefault();response={};response.msg="change_name";response.value=name_input.value;ws.send(JSON.stringify(response));}});