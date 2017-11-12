/**
 *
 * HTML5 Color Picker
 *
 * Licensed under the MIT license.
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * Copyright 2012, Script Tutorials
 * http://www.script-tutorials.com/
 */

// create canvas and context objects

var canvas = document.getElementById('picker');
var context = canvas.getContext('2d');
var imageObj = new Image();

imageObj.onload = function() {
    context.drawImage(imageObj, 0, 0, imageObj.width, imageObj.height);
};
imageObj.crossOrigin = 'anonymous';
imageObj.src = 'https://i.imgur.com/8xVt7AE.png';

$('#picker').mousemove(function(e) { // mouse move handler

    // get coordinates of current position
    var canvasOffset = $(canvas).offset();
    var canvasX = Math.floor(e.pageX - canvasOffset.left);
    var canvasY = Math.floor(e.pageY - canvasOffset.top);

    // get current pixel
    var imageData = context.getImageData(canvasX, canvasY, 1, 1);
    $("span").text(canvasX + ", " + canvasY);
    var pixel = imageData.data;

    // update preview color
    var pixelColor = "rgb("+pixel[0]+", "+pixel[1]+", "+pixel[2]+")";
    $('.preview').css('backgroundColor', pixelColor);

    // update controls
    $('#rVal').val(pixel[0]);
    $('#gVal').val(pixel[1]);
    $('#bVal').val(pixel[2]);
    $('#rgbVal').val(pixel[0]+','+pixel[1]+','+pixel[2]);

    var dColor = pixel[2] + 256 * pixel[1] + 65536 * pixel[0];
    $('#hexVal').val('#' + ('0000' + dColor.toString(16)).substr(-6));
});