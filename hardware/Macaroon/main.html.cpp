#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <!-- Bootstrap -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css" integrity="sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb" crossorigin="anonymous">
        <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.2/css/foundation.min.css"/>
        
        <!-- jQuery -->
        <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>

        <!-- Bootstrap Tool Kit -->
        <script src="https://rawgit.com/maciej-gurban/responsive-bootstrap-toolkit/master/dist/bootstrap-toolkit.js"></script>

        <!-- noUISlider -->
        <link href="https://cdnjs.cloudflare.com/ajax/libs/noUiSlider/10.0.0/nouislider.min.css" rel="stylesheet"/>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/noUiSlider/10.0.0/nouislider.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/wnumb/1.1.0/wNumb.min.js"></script>

        <!-- Font Awesome Icon -->
        <script src="https://use.fontawesome.com/142debc546.js"></script>

        <!-- Color Picker Tool -->
        <script src="https://cdn.rawgit.com/NC22/HTML5-Color-Picker/8cf7cb27/html5kellycolorpicker.js"></script>
    </head>
    <style>
        .btn-sm {
            padding-bottom: 0;
            padding-top: 0;
        }
        #remove-segment {
            margin: 0;
        }
        #color-picker-row {
            display: flex;
            justify-content: center;
            align-items: center;
        }
        .navbar-item {
            margin: 0;
        }
        .navbar-nav > .active > a {
            background-color: #F66;
        }
        .nav-item > .nav-link {
            padding-left: 20px;
            padding-right: 20px;
        }
        .noUi-tooltip {
            display: none;
        }
        .noUi-active .noUi-tooltip {
            display: block;
        }
        .noUi-connect {
            background: #F66;
        }
        .row > .slider {
            width: 90%;
            padding-bottom: 25px;
        }
        .row > .col-md-6 > .slider {
            width: 100%;
            padding-bottom: 20px;
        }
        .row > .col-md-6 > .btn-group {
            width: 100%;
            padding-top: 25px;
        }
        .row > .col-md-6 > .btn-group > .btn {
            width: 100%;
        }
        .row > .col-md-6 > .btn-group > .dropdown-menu {
            width: 100%;
        }
    </style>
    <body>
        <nav class="navbar navbar-dark bg-danger">
            <a class="navbar-brand text-white">Macaroon</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation" style="margin: 0">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <h4 class="text-white">LED Segments</h4>
                <ul id="LEDsegments" class="navbar-nav">
                    <li class="nav-item active">
                        <a class="nav-link">
                            0 - 9: Static
                            <button id='remove-segment' type="button" class="btn bg-warning btn-sm pull-right">
                                <i class="fa fa-trash"></i>
                            </button>
                        </a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link">
                            0 - 9: Static
                            <button id='remove-segment' type="button" align='center' class="btn bg-warning btn-sm pull-right">
                                <i class="fa fa-trash"></i>
                            </button>
                        </a>
                    </li>
                </ul>
                <button id='add-segment' type="button" class="btn btn-success btn-sm pull-right" onclick="addSegment()">
                    Add Segment
                    <i class="fa fa-plus-square"></i>
                </button>
            </div>
        </nav>
        <div class="container" style="padding: 20px;">
        </div>
        <div class="container">            
            <div class="row justify-content-center">
                <div id="color-picker-row" class="col-md-6">
                    <div id="test-pickers"></div>
                </div>
                <div class="col-md-6">
                    <div class="btn-group">
                        <button id='selector' type="button" class="btn btn-warning btn-lg dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                            Select Mode
                        </button>
                        <div class="dropdown-menu">
                            <a id="0" class="dropdown-item">Static</a>
                            <a id="1" class="dropdown-item">Blink</a>
                            <a id="2" class="dropdown-item">Breath</a>
                            <a id="3" class="dropdown-item">Color Wipe</a>
                            <a id="4" class="dropdown-item">Color Wipe Inverse</a>
                            <a id="5" class="dropdown-item">Color Wipe Reverse</a>
                            <a id="6" class="dropdown-item">Color Wipe Reverse Inverse</a>
                            <a id="7" class="dropdown-item">Color Wipe Random</a>
                            <a id="8" class="dropdown-item">Random Color</a>
                            <a id="9" class="dropdown-item">Single Dynamic</a>
                            <a id="10" class="dropdown-item">Multi Dynamic</a>
                            <a id="11" class="dropdown-item">Rainbow</a>
                            <a id="12" class="dropdown-item">Rainbow Cycle</a>
                            <a id="13" class="dropdown-item">Scan</a>
                            <a id="14" class="dropdown-item">Dual Scan</a>
                            <a id="15" class="dropdown-item">Fade</a>
                            <a id="16" class="dropdown-item">Theater Chase</a>
                            <a id="17" class="dropdown-item">Theater Chase Rainbow</a>
                            <a id="18" class="dropdown-item">Running Lights</a>
                            <a id="19" class="dropdown-item">Twinkle</a>
                            <a id="20" class="dropdown-item">Twinkle Random</a>
                            <a id="21" class="dropdown-item">Twinkle Fade</a>
                            <a id="22" class="dropdown-item">Twinkle Fade Random</a>
                            <a id="23" class="dropdown-item">Sparkle</a>
                            <a id="24" class="dropdown-item">Flash Sparkle</a>
                            <a id="25" class="dropdown-item">Hyper Sparkle</a>
                            <a id="26" class="dropdown-item">Strobe</a>
                            <a id="27" class="dropdown-item">Strobe Rainbow</a>
                            <a id="28" class="dropdown-item">Multi Strobe</a>
                            <a id="29" class="dropdown-item">Blink Rainbow</a>
                            <a id="30" class="dropdown-item">Chase White</a>
                            <a id="31" class="dropdown-item">Chase Color</a>
                            <a id="32" class="dropdown-item">Chase Random</a>
                            <a id="33" class="dropdown-item">Chase Rainbow</a>
                            <a id="34" class="dropdown-item">Chase Flash</a>
                            <a id="35" class="dropdown-item">Chase Flash Random</a>
                            <a id="36" class="dropdown-item">Chase Rainbow White</a>
                            <a id="37" class="dropdown-item">Chase Blackout</a>
                            <a id="38" class="dropdown-item">Chase Blackout Rainbow</a>
                            <a id="39" class="dropdown-item">Color Sweep Random</a>
                            <a id="40" class="dropdown-item">Running Color</a>
                            <a id="41" class="dropdown-item">Running Red Blue</a>
                            <a id="42" class="dropdown-item">Running Random</a>
                            <a id="43" class="dropdown-item">Larson Scanner</a>
                            <a id="44" class="dropdown-item">Comet</a>
                            <a id="45" class="dropdown-item">Fireworks</a>
                            <a id="46" class="dropdown-item">Fireworks Random</a>
                            <a id="47" class="dropdown-item">Merry Christmas</a>
                            <a id="48" class="dropdown-item">Fire Flicker</a>
                            <a id="49" class="dropdown-item">Fire Flicker (soft)</a>
                            <a id="50" class="dropdown-item">Fire Flicker (intense)</a>
                            <a id="51" class="dropdown-item">Circus Combustus</a>
                            <a id="52" class="dropdown-item">Halloween</a>
                            <a id="53" class="dropdown-item">Bicolor Chase</a>
                            <a id="54" class="dropdown-item">Tricolor Chase</a>
                            <a id="55" class="dropdown-item">ICU</a>
                        </div>
                    </div>
                    <div class="slider">
                        <h5> Segment Range: </h5>
                        <div id="slider-range"></div>
                    </div>
                    <div class="slider">
                        <h5> Speed: </h5>
                        <div id="slider-speed"></div>
                    </div>
                    </div>
                </div>
            </div>
            <br>
            <div class="row justify-content-center">
                <div class="slider">
                    <h5> Number of LED: </h5>
                    <div id="slider-LEDcount"></div>
                </div>
                <div class="slider">
                    <h5> Brightness: </h5>
                    <div id="slider-brightness"></div>
                </div>
                <div class="slider">
                    <h5> Sound Trigger Level: </h5>
                    <div id="slider-sound"></div>
                </div>
            </div>
        </div>
        <script src="./js/script.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.3/umd/popper.min.js" integrity="sha384-vFJXuSJphROIrBnz7yo7oB41mKfc8JzQZiCq4NCceLEaO4IHwicKwpJf9c9IpFgh" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/js/bootstrap.min.js" integrity="sha384-alpBpkh1PFOepccYVYDB4do5UnbKysX5WZXm3XxPqe5iKTfUKjNkCk9SaVuEZflJ" crossorigin="anonymous"></script>
    </body>
</html>
)=====";

