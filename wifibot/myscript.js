
var heartBeatTime = 50;

$.ajaxSetup({timeout:heartBeatTime-10});

var KEYS = [
  87,  //w,
  65,  //a,
  83,  //s,
  68,  //d,
  37,  //left,
  39,  //right,
  38,  //up,
  40,  //down,
  32   //space,
];

var pressedKeys = [];

for (var i = 0; i < KEYS.length; ++i) {
  pressedKeys.push(0);
}

var latch = false;

function readUrlAV (form) {
    TextVar = form.inputbox.value;
	VideoVar = "http://"+TextVar+":8080/video";
	AudioVar = "http://"+TextVar+":8080/audio.opus";
	document.getElementById("video").setAttribute('data', VideoVar);
	document.getElementById("audio").setAttribute('data', AudioVar);
}

var interval;

function testarArduino (form) {
  if (!interval) {
    interval = setInterval(function(){
      TextVar = myform2.inputbox.value;
      ArduinoVar = "http://" + TextVar + ":80";
      $.get( ArduinoVar, { "k": pressedKeys.join('') })	;
      {Connection: close};
    }, heartBeatTime);
  }
}

document.onkeydown = checkKeyDown;
document.onkeyup = checkKeyUp;

function checkKeyDown(e) {
  e = e || window.event;

  for (var i = 0; i < KEYS.length; ++i) {
    if (e.keyCode == KEYS[i]) {
      pressedKeys[i] = 1;
    }
  }
}

function checkKeyUp(e) {
  e = e || window.event;
  for (var i = 0; i < KEYS.length; ++i) {
    if (e.keyCode == KEYS[i]) {
      pressedKeys[i] = 0;
    }
  }
}



/*
function checkKeyDown(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
        // up arrow
		if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm1": 1000 })	;
			{Connection: close};
			latch = true;
		}
    }
    else if (e.keyCode == '40') {
        // down arrow
		if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm2": 1000 })	;
			{Connection: close};
			latch = true;
		}
    }
    else if (e.keyCode == '37') {
       // left arrow
	   if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm3": 1000 })	;
			{Connection: close};
			latch = true;
		}

	}
    else if (e.keyCode == '39') {
       // right arrow
	   if (latch == false) {
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm4": 1000 })	;
			{Connection: close};
			latch = true;
		}
	}
}
*/
/*
function checkKeyUp(e) {
    e = e || window.event;

    if ((e.keyCode == '38')||(e.keyCode == '40')||(e.keyCode == '37')||(e.keyCode == '39')) {
        // up arrow
		setTimeout(doNothing, 50);
    }
}

function doNothing(){
	TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "cm5": 1000 })	;
		{Connection: close};
		latch = false;
}
*/
