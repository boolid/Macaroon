#include <pgmspace.h>
char main_js[] PROGMEM = R"=====(
var colorPicker = null;
var sendData = false;
setInterval(sendDataCheck, 200);

function sendDataCheck() {
    if (sendData === true) {
        sendData = false;
    }
}

$(window).on('load', function() {
    if ($(".dropdown-menu").length > 0) {
        $.ajax({
            type: 'GET',
            url: 'modes',
            success: function(response) {
                $(".dropdown-menu").append( response );
                $(".dropdown-item").click(function(){
                    $(".btn:first-child").text($(this).text());
                    $(".btn:first-child").val($(this).text());
                    $.ajax({
                        type: 'GET',
                        url: 'set',
                        data: {
                            m: this.value
                        }
                    });
                });
            }
        });
    }
    $.ajax({
        type: 'GET',
        url: 'setup',
        success: function(response) {
            if($("#brightness-value").length > 0) {
                $("#brightness-value").text(response['brightness'])
                var brightness = new Slider('#brightness-slider');
                brightness.setValue(response['brightness'])
            }
            if($("#speed-value").length > 0) {
                $("#speed-value").text(response['speed'])
                var speed = new Slider('#speed-slider');
                speed.setValue(response['speed'])
            }
            if($("#led-count").length > 0) {
                $("#led-count").val(response['ledlength'])
            }
        }
    });

});

$("#brightness-slider").on("change", function(slideEvt) {
    if (sendData === false){
        $.ajax({
            type: 'GET',
            url: 'set',
            data: {
                b: slideEvt.value.newValue
            }
        });
        sendData = true;
    }
    $("#brightness-value").text(slideEvt.value.newValue);
});

$("#speed-slider").on("change", function(slideEvt) {
    if (sendData === false){
        $.ajax({
            type: 'GET',
            url: 'set',
            data: {
                s: slideEvt.value.newValue
            }
        });
        sendData = true;
    }
    $("#speed-value").text(slideEvt.value.newValue);
});


createColorPicker();

$("#led-button").on("click", function(){
    if (sendData === false){
        $.ajax({
            type: 'GET',
            url: 'set',
            data: {
                l: $("#led-count").val()
            }
        });
        sendData = true;
    }
});

(function($, document, window, viewport){

    viewport.use('Foundation');
    if (colorPicker !== null) {
        function checksize() {
            if( viewport.is('small') ) {
                colorPicker.resize(300);
            }

            if( viewport.is('medium') ) {
                colorPicker.resize(400);
            }

            if( viewport.is('>=large') ) {
                colorPicker.resize(500);
            }
        }

        checksize();

        // Executes once whole document has been loaded
        $(document).ready(function() {
            checksize();
        });

        $(window).resize(
            viewport.changed(function(){
                checksize();
            })
        );
    }

})(jQuery, document, window, ResponsiveBootstrapToolkit);

function componentToHex(c) {
    var hex = c.toString(16);
    return hex.length === 1 ? "0" + hex : hex;
};

function createColorPicker() {
    // generate random size parametrs
    if (document.getElementById('test-pickers') !== null){
        var rand = function(min, max) { return Math.floor(Math.random() * (max - min + 1)) + min; };
        var place = document.createElement('DIV');
        document.getElementById('test-pickers').appendChild(place);
        var r = rand(0, 255), g = rand(0, 255), b = rand(0, 255), a = 0.9;
        var color = 'rgba(' + r + ',' + g +',' + b +','+ a +')';
        var method = 'triangle';
        colorPicker = new KellyColorPicker({
            place : place,
            size : 300,
            input : 'hexVal',
            method : 'triangle',
            color : color,
        });
        // set size options to ColorPicker
        colorPicker.getWheel().width += 40;

        // update to applay size options
        colorPicker.updateView(true);

        var onchange = function(self) {
            var rgba = colorPicker.getCurColorRgba();
            if (sendData === false){
                $.ajax({
                    type: 'GET',
                    url: 'set',
                    data: {
                        c: this.componentToHex(rgba.r) + componentToHex(rgba.g) + componentToHex(rgba.b)
                    }
                });
                sendData = true;
            }
        }

        colorPicker.addUserEvent("change", onchange);
    }
};

String.prototype.format = function() {
  a = this;
  for (k in arguments) {
    a = a.replace("{" + k + "}", arguments[k])
  }
  return a
}
)=====";

