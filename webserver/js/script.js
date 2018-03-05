// 
var mode = {
    0: {"Name": "Static"},
    1: {"Name": "Blink"},
    2: {"Name": "Breath"},
    3: {"Name": "Color Wipe"},
    4: {"Name": "Color Wipe Inverse"}, 
    5: {"Name": "Color Wipe Reverse"},
    6: {"Name": "Color Wipe Reverse Inverse"},
    7: {"Name": "Color Wipe Random"},
    8: {"Name": "Random Color"},
    9: {"Name": "Single Dynamic"},
    10: {"Name": "Multi Dynamic"},
    11: {"Name": "Rainbow"},
    12: {"Name": "Rainbow Cycle"},
    13: {"Name": "Scan"},
    14: {"Name": "Dual Scan"},
    15: {"Name": "Fade"},
    16: {"Name": "Theater Chase"},
    17: {"Name": "Theater Chase Rainbow"},
    18: {"Name": "Running Lights"},
    19: {"Name": "Twinkle"},
    20: {"Name": "Twinkle Random"},
    21: {"Name": "Twinkle Fade"},
    22: {"Name": "Twinkle Fade Random"},
    23: {"Name": "Sparkle"},
    24: {"Name": "Flash Sparkle"},
    25: {"Name": "Hyper Sparkle"},
    26: {"Name": "Strobe"},
    27: {"Name": "Strobe Rainbow"},
    28: {"Name": "Multi Strobe"},
    29: {"Name": "Blink Rainbow"},
    30: {"Name": "Chase White"},
    31: {"Name": "Chase Color"},
    32: {"Name": "Chase Random"},
    33: {"Name": "Chase Rainbow"},
    34: {"Name": "Chase Flash"},
    35: {"Name": "Chase Flash Random"},
    36: {"Name": "Chase Rainbow White"},
    37: {"Name": "Chase Blackout"},
    38: {"Name": "Chase Blackout Rainbow"},
    39: {"Name": "Color Sweep Random"},
    40: {"Name": "Running Color"},
    41: {"Name": "Running Red Blue"},
    42: {"Name": "Running Random"},
    43: {"Name": "Larson Scanner"},
    44: {"Name": "Comet"},
    45: {"Name": "Fireworks"},
    46: {"Name": "Fireworks Random"},
    47: {"Name": "Merry Christmas"},
    48: {"Name": "Fire Flicker"},
    49: {"Name": "Fire Flicker (soft)"},
    50: {"Name": "Fire Flicker (intense)"},
    51: {"Name": "Circus Combustus"},
    52: {"Name": "Halloween"},
    53: {"Name": "Bicolor Chase"},
    54: {"Name": "Tricolor Chase"},
    55: {"Name": "ICU"}
}

var state = {
    'segments': [
        {
            'segmentStart': 0,
            'segmentEnd': 20,
            'mode': 0,
            'brightness': 122,
            'speed': 122,
            'color': 'FF0000',
        },
    ],
    'countLED': 20,
};

var selectSegment = 0;

// Start Color Picker
var colorPicker = null;
createColorPicker();

// Setup for the Slider 
var sliderLEDCount = document.getElementById('slider-LEDcount');
var sliderRange = document.getElementById('slider-range');
var sliderBrightness = document.getElementById('slider-brightness');
var sliderSpeed = document.getElementById('slider-speed');

noUiSlider.create(sliderLEDCount, {
    start: state['countLED'],
    range: { min: 0, max: 1000 },
    tooltips: [ wNumb({ decimals: 0 }) ],
    connect: [true, false]
});

noUiSlider.create(sliderBrightness, {
    start: state['segments'][selectSegment]['brightness'],
    range: { min: 0, max: 255 },
    tooltips: [ wNumb({ decimals: 0 }) ],
    connect: [true, false]
});

noUiSlider.create(sliderSpeed, {
    start: state['segments'][selectSegment]['speed'],
    range: { min: 0, max: 255 },
    tooltips: [ wNumb({ decimals: 0 }) ],
    connect: [true, false]
});

noUiSlider.create(sliderRange, {
    start: [ 
        state['segments'][selectSegment]['segmentStart'], 
        state['segments'][selectSegment]['segmentEnd'],
    ],
    range: { min: 0, max: state['countLED'] },
    tooltips: [ wNumb({ decimals: 0 }), wNumb({ decimals: 0 }) ],
    connect: true
});

init()

sliderLEDCount.noUiSlider.on('update', function( values, handle ) {
    state['countLED'] = Math.round(values[handle])
});

sliderBrightness.noUiSlider.on('update', function( values, handle ) {
    state['segments'][selectSegment]['brightness'] = Math.round(values[handle]) 
});

sliderSpeed.noUiSlider.on('update', function( values, handle ) {
    state['segments'][selectSegment]['speed'] = Math.round(values[handle]) 
});

sliderRange.noUiSlider.on('update', function( values, handle ) {
    if (handle == 0){
        state['segments'][selectSegment]['segmentStart'] = Math.round(values[handle])
    } else {
        state['segments'][selectSegment]['segmentEnd'] = Math.round(values[handle])
    }
    drawSegment()
});


$(".dropdown-item").click(function(){
    $("#selector").text($(this).text());
    $("#selector").val($(this).text());
    state['segments'][selectSegment]['mode'] = Number($(this).attr('id'))

    drawSegment()
});


function init() {

    colorPicker.setColorByHex('#' + state['segments'][selectSegment]['color']);

    sliderLEDCount.noUiSlider.updateOptions({
        start: state['countLED'],
    });

    sliderBrightness.noUiSlider.updateOptions({
        start: state['segments'][selectSegment]['brightness'],
    });

    sliderSpeed.noUiSlider.updateOptions({
        start: state['segments'][selectSegment]['speed'],
    });

    sliderRange.noUiSlider.updateOptions({
        start: [ 
            state['segments'][selectSegment]['segmentStart'], 
            state['segments'][selectSegment]['segmentEnd'],
        ],
        range: { min: 0, max: state['countLED'] },
    });

    $("#selector").text(mode[state['segments'][selectSegment]['mode']]['Name']);
    $("#selector").val(mode[state['segments'][selectSegment]['mode']]['Name']);

}


// Viewport that changes the size of the color picker
(function($, document, window, viewport){

    viewport.use('Foundation');
    if (colorPicker !== null) {
        function checksize() {
            if( viewport.is('small') ) {
                colorPicker.resize(300);
            } else if ( viewport.is('medium') ) {
                colorPicker.resize(400);
            } else if( viewport.is('>=large') ) {
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

// Color Picker Setup
function createColorPicker() {
    // generate random size parametrs
    if (document.getElementById('test-pickers') !== null){
        var rand = function(min, max) { return Math.floor(Math.random() * (max - min + 1)) + min; };
        var place = document.createElement('DIV');
        document.getElementById('test-pickers').appendChild(place);
        var r = rand(0, 255), g = rand(0, 255), b = rand(0, 255), a = 0.9;

        var color = '#' + state['segments'][selectSegment]['color']
        var method = 'triangle';
        colorPicker = new KellyColorPicker({
            place : place,
            size : 400,
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
            state['segments'][selectSegment]['color'] = this.componentToHex(rgba.r) + componentToHex(rgba.g) + componentToHex(rgba.b)
            // if (sendData === false){
            //     $.ajax({
            //         type: 'GET',
            //         url: 'set',
            //         data: {
            //             c: this.componentToHex(rgba.r) + componentToHex(rgba.g) + componentToHex(rgba.b)
            //         }
            //     });
            //     sendData = true;
            // }
        }

        colorPicker.addUserEvent("change", onchange);
    }
};

function getEventTarget(e) {
    e = e || window.event;
    return e.target || e.srcElement; 
}


var ul = document.getElementById('LEDsegments');
ul.onclick = function(event) {
    var target = getEventTarget(event);
    var index = Number(target.id)
    if (target.className.indexOf('nav-link') !== -1) {
        // Making Active Selection
        selectSegment = index
        init()
        drawSegment()
    } else {
        // Remove Segment
        if (state['segments'].length > 1){
            if (index == 0) {
                state['segments'][index + 1]['segmentStart'] = 0
            } else if (index == state['segments'].length - 1) {
                state['segments'][index - 1]['segmentEnd'] = state['segments'][index]['segmentEnd']
            } else {
                state['segments'][index + 1]['segmentStart'] = state['segments'][index]['segmentStart']
                if (state['segments'][index]['segmentStart'] != state['segments'][index]['segmentEnd']) {
                    state['segments'][index - 1]['segmentEnd'] = state['segments'][index]['segmentStart'] - 1
                }        
            }
            state['segments'].splice(index, 1);
            drawSegment()
        }
    }
};

drawSegment();

function drawSegment() {
    function _createSegment(string, index) {
        var ul = document.getElementById("LEDsegments");
        var li = document.createElement("li");
        var a = document.createElement("a");
        var button = document.createElement("button")
        var i = document.createElement("i")

        i.setAttribute("class", "fa fa-trash")
        i.setAttribute("id", index)
        button.setAttribute("class", "btn bg-warning btn-sm pull-right")
        button.setAttribute("id", index)
        button.setAttribute("type", "button")
        button.appendChild(i)

        a.setAttribute("class", "nav-link")
        a.setAttribute("id", index)
        a.appendChild(document.createTextNode(string))
        a.appendChild(button)

        var liClass = "nav-item"
        if (index == selectSegment) {
            liClass += " active"
        }

        li.setAttribute("class", liClass)
        li.appendChild(a);
        ul.appendChild(li);
    }

    $('#LEDsegments').empty();

    state['segments'].forEach(function(segment, index){
        var name = mode[segment['mode']]['Name'] + ': ' + segment['segmentStart'] + '-' + segment['segmentEnd']
        _createSegment(name, index)
    })
}

function addSegment() {
    var lastSegment = state['countLED']

    for (var i = state['segments'].length - 1; i >= 0; i--){
        var start = state['segments'][i]['segmentStart']
        var end = state['segments'][i]['segmentEnd']

        if (end === 0) break;
        if (end == lastSegment) {
            lastSegment--
            state['segments'][i]['segmentEnd'] = lastSegment
            if (start === end) {
                state['segments'][i]['segmentStart'] = lastSegment
            } else {
                break
            }
        } 
    }

    state['segments'].push({
            'segmentStart': state['countLED'],
            'segmentEnd': state['countLED'],
            'mode': 0,
            'brightness': 122,
            'speed': 122,
            'color': 'FF0000'
    })

    drawSegment()
}