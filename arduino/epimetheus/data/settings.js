document.getElementById("delete_data_label").innerHTML=LANG_DELETE_DATA_LABEL;document.getElementById("delete_ok_label").innerHTML=LANG_OK_LABEL;document.getElementById("delete_close").innerHTML=LANG_CANCEL_LABEL;document.getElementById("ip_addr").innerHTML=" - "+location.host;document.getElementById("save_label").innerHTML=LANG_SAVE_LABEL;document.getElementById("download_label").innerHTML=LANG_DOWNLOAD_LABEL;document.getElementById("erase_label").innerHTML=LANG_ERASE_LABEL;document.getElementById("name_label_0").innerHTML=LANG_NAME_LABEL;document.getElementById("password_label_0").innerHTML=LANG_PASSWORD_LABEL;document.getElementById("name_label_1").innerHTML=LANG_NAME_LABEL;document.getElementById("password_label_1").innerHTML=LANG_PASSWORD_LABEL;document.getElementById("validate_label").innerHTML=LANG_VALIDATE_LABEL;var scan_modal=document.getElementById("scan_modal");var scan_btn=document.getElementById("scan_button");var scan_close=document.getElementById("scan_close");var delete_modal=document.getElementById("delete_modal");var delete_btn=document.getElementById("delete_button");var delete_close=document.getElementById("delete_close");var ws=new WebSocket("ws://"+location.host+"/websocket");websocket_status=false;wifi_scan_done=false;name_selected=-1;const save_checkbox=document.getElementById('save_checkbox');ws.onopen=function(event){console.log(LANG_WEBSOCKET_OPEN);websocket_status=true;message={}
message.msg="open_settings";ws.send(JSON.stringify(message));message={}
message.msg="flash";ws.send(JSON.stringify(message));};ws.onmessage=function(event){console.log(event.data);try{data=JSON.parse(event.data);json_parsed=true;}catch(e){json_parsed=false;}
if(json_parsed){if(data.msg=="open_settings"){settings=data;console.log(settings);document.getElementById("name_0").value=settings.wifi1_name;document.getElementById("name_1").value=settings.wifi2_name;}
if(data.msg=="save_settings"){if(data.result){show_ok(LANG_SAVE_OK)}else{show_ok(LANG_SAVE_ERR)}}
if(data.msg=="wifi_scan"){document.getElementById("wifi_scan_table").innerHTML="";data.value.forEach(function(item,index,array){const widget=`<tr class="theme_widget_background margin center"><td onclick="copy_paste(this.innerHTML)">${item}</td></tr>`;document.getElementById("wifi_scan_table").innerHTML+=widget;});wifi_scan_done=true;show_ok(LANG_WIFISCAN_DONE);}
if(data.msg=="delete_file"){if(data.result){show_ok(LANG_DELETED);}else{show_error(LANG_DELETE_ERROR);}}
if(data.msg=="flash"){if(data.value){save_checkbox.checked=true}}}};ws.onerror=function(event){show_error(LANG_WEBSOCKET_ERROR);websocket_status=false;}
ws.onclose=function(event){websocket_status=false;}
function copy_paste(text){console.log(text);document.getElementById("name_"+name_selected).value=text;scan_modal.style.display="none";}
function open_scan(id){scan_modal.style.display="block";if(!wifi_scan_done){websocket_status=true;msg={};msg.msg="wifi_scan";ws.send(JSON.stringify(msg));}
name_selected=id;}
function open_delete(){delete_modal.style.display="block";}
delete_close.onclick=function(){delete_modal.style.display="none";}
scan_close.onclick=function(){name_selected=-1;scan_modal.style.display="none";}
window.onclick=function(event){if(event.target==scan_modal){scan_modal.style.display="none";}}
function delete_data(){if(websocket_status){ws.send("delete_data");delete_modal.style.display="none";}}
function save_settings(){settings={};settings.msg="save_settings";settings.wifi1_name=document.getElementById("name_0").value;settings.wifi2_name=document.getElementById("name_1").value;settings.wifi1_pass=document.getElementById("pass_0").value;settings.wifi2_pass=document.getElementById("pass_1").value;console.log(settings);ws.send(JSON.stringify(settings));}
function show_password(id){var temp=document.getElementById("pass_"+id);if(temp.type==="password"){temp.type="text";}
else{temp.type="password";}}
save_checkbox.addEventListener('change',(event)=>{response={};response.msg="save_flash";if(event.target.checked){response.value=true;show_ok(LANG_SAVE_ON);}else{response.value=false;show_error(LANG_SAVE_OFF);}
ws.send(JSON.stringify(response));})