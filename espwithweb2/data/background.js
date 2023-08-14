function randomizeCircles() {
  var numCircles = 25;

  // Create circles dynamically
  for (var i = 0; i < numCircles; i++) {
    var circle = document.createElement("div");
    circle.className = "circlebg";
    setRandomProperties(circle);
    document.getElementById("background").appendChild(circle);
  }
}
  function randomizeCircles1() {
  var numCircles = 25;

  // Create circles dynamically
  for (var i = 0; i < numCircles; i++) {
    var circle = document.createElement("div");
    circle.className = "circlebg1";
    setRandomProperties(circle);
    document.getElementById("background").appendChild(circle);
  }
}

function setRandomProperties(circle) {
  // Generate random values for top, left, width, and background-color
  var topValue = Math.floor(Math.random() * document.body.offsetHeight) + "px";
  var leftValue = Math.floor(Math.random() * document.body.offsetWidth) + "px";
  
  var widthValue = Math.floor(Math.random() * 150) + 10 + "px";
  var colorValue = getRandomColor();

  // Apply random values to the circle element
  circle.style.top = topValue;
  circle.style.left = leftValue;
  circle.style.width = widthValue;
  circle.style.height = widthValue;
  circle.style.backgroundColor = colorValue;
}

function getRandomColor() {
  var pageName = window.location.pathname.split("/").pop();
  if (pageName === "Temperature.html") {
    var shadesOfRed = ["#FF0000", "#FF3333", "#FF6666", "#FF9999", "#FFCCCC"];
    var randomIndex = Math.floor(Math.random() * shadesOfRed.length);
    return shadesOfRed[randomIndex];
  } else if (pageName === "Humidity.html") {
    var shadesOfBlue = ["#0000FF", "#0055FF", "#0099FF", "#00CCFF", "#00FFFF"];
    var randomIndex = Math.floor(Math.random() * shadesOfBlue.length);
    return shadesOfBlue[randomIndex];
  }else if (pageName === "CO.html") {
    var shadesOfGreen = ["#00FF00", "#33FF33", "#66FF66", "#99FF99", "#CCFFCC"];
    var randomIndex = Math.floor(Math.random() * shadesOfGreen.length);
    return shadesOfGreen[randomIndex];
  } else if (pageName === "PM25.html") {
    var shadesOfYellow = ["#FFFF00", "#FFFF33", "#FFFF66", "#FFFF99", "#FFFFCC"];
    var randomIndex = Math.floor(Math.random() * shadesOfYellow.length);
    return shadesOfYellow[randomIndex];
  }else {
    var shadesOfRed = ["#FF0000", "#FF3333", "#FF6666", "#FF9999", "#FFCCCC"];
    var randomIndex = Math.floor(Math.random() * shadesOfRed.length);
    return shadesOfRed[randomIndex];
  }
}


// Call the function to generate random circles
randomizeCircles();
randomizeCircles1();