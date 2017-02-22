<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="content-type" content="text/html; charset=UTF-8">
        <title>E-Nable project</title>
        
        <link rel="stylesheet" href="<c:url value="/static/css/foundation.css" />">
        <link rel="stylesheet" href="<c:url value="/static/css/foundation.min.css" />">
    	<link rel="stylesheet" href="<c:url value="/static/css/app.css" />">
   		<script src="<c:url value="/static/js/jquery-3.1.1.min.js" />"></script>
        <script src="<c:url value="/static/js/vendor/foundation.js" />"></script>
        <script src="<c:url value="/static/js/app.js" />"></script>
        <script src="http://code.jquery.com/ui/1.10.1/jquery-ui.js"></script>
    </head>
	<body>
		<script type="text/javascript">
		// -------------- Web service afin de recuperer l'etat des doigts
		var wsUri = "ws://88.170.244.38/getState";
		/*
		function init() {
		}*/
		
		function getEtats() {
		    websocket = new WebSocket(wsUri);
		    
		    websocket.onopen = function(evt)  {
		        //writeToScreen("Connected to Endpoint!");
				console.log("Connected to Endpoint!");
		        doSend("start");
		    };
		    websocket.onmessage = function(evt){
		    	console.log('Message recu');
		        writeToScreen(evt.data);
		    };
		    websocket.onerror = function(evt) {
		        //writeToScreen('ERROR: ' + evt.data);
		        console.log('ERROR: ' + evt.data);
		    };
		    
		}
		
		function doSend(message) {
		    //writeToScreen("Message Sent: " + message);
		    console.log("Message Sent: " + message);
		    websocket.send(message);
		   // websocket.close();
		}
		
		function writeToScreen(message) {
		    var output = document.getElementById("etats");
		    var etats = message.split(" ") ;
		  	output.innerHTML = etats[0]+"/"+etats[1]+"/"+etats[2]+"/"+etats[3];
		  	
		  	var nameImage = "main";
		  	
		  	if(etats[0] === "true"){nameImage = nameImage+"1";}
		  	if(etats[1] === "true"){nameImage = nameImage+"2";}
		  	if(etats[2] === "true"){nameImage = nameImage+"3";}
		  	if(etats[3] === "true"){nameImage = nameImage+"4";}
		  	
		  	console.log(nameImage);

		  	var url = '<c:url value="/static/images/'+nameImage+'.jpg" />';
		  	$("#main").attr("src", url);
		}
		</script>
		
        <h1 style="text-align: center;">E-Nable project - Brahimi Hicham / Bouatmane Anass</h1>
	    <br />
    	<br />
    	<hr />
    	<div id="etats"></div>
		<div style="text-align:center;" ><img id="main" src=<c:url value="/static/images/main.jpg" />></div>
    	<hr />

    	<script>
        function start(){
    		getEtats();
        }
        $(document).ready(start());
        </script>
	</body>
</html>