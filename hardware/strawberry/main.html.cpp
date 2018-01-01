#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css" integrity="sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb" crossorigin="anonymous">
        <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/foundation/5.5.2/css/foundation.min.css"/>
        <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.0.0/css/bootstrap-slider.min.css"></script>
        <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
        <script src="https://rawgit.com/maciej-gurban/responsive-bootstrap-toolkit/master/dist/bootstrap-toolkit.js"></script>
    </head>
    <body>
        <nav class="navbar navbar-dark bg-primary">
            <a class="navbar-brand" href="./">Strawberry</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav">
                    <li class="nav-item active">
                        <a class="nav-link" href="./">Home <span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="./settings">Settings</a>
                    </li>
                </ul>
            </div>
        </nav>
        <div class="container" style="padding: 20px;">
            <div class="row ">
                <div class="btn-group">
                    <button type="button" class="btn btn-secondary btn-lg dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        Select Mode
                    </button>
                    <div class="dropdown-menu dropdown-menu-right">
                    </div>
                </div>
            </div>
        </div>
        <div class="container">
            <div class="row justify-content-center">
                <div class="col-centered">
                    <div id="test-pickers"></div>
                </div>
            </div>
            <div class="row justify-content-center" style="padding-top: 20px;">
                <div class="col-md-4">
                    <input type="text" class="form-control" id="hexVal" disabled/>
                </div>
            </div>
            <div class="row justify-content-center" style="padding-top: 10px;">
                <span>Brightness: <span id="brightness-value">255</span></span>
            </div>
            <div class="row justify-content-center">
                <input id="brightness-slider" type="text" data-slider-min="1" data-slider-max="255" data-slider-step="1" data-slider-value="255"/>
            </div>
            <div class="row justify-content-center" style="padding-top: 10px;">
                <span>Speed: <span id="speed-value">200</span></span>
            </div>
            <div class="row justify-content-center">
                <input id="speed-slider" type="text" data-slider-min="1" data-slider-max="200" data-slider-step="1" data-slider-value="200"/>
            </div>
        </div>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-slider/10.0.0/bootstrap-slider.min.js"></script>
        <script src="https://cdn.rawgit.com/NC22/HTML5-Color-Picker/8cf7cb27/html5kellycolorpicker.js"></script>
        <script src="./js/script.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.3/umd/popper.min.js" integrity="sha384-vFJXuSJphROIrBnz7yo7oB41mKfc8JzQZiCq4NCceLEaO4IHwicKwpJf9c9IpFgh" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/js/bootstrap.min.js" integrity="sha384-alpBpkh1PFOepccYVYDB4do5UnbKysX5WZXm3XxPqe5iKTfUKjNkCk9SaVuEZflJ" crossorigin="anonymous"></script>
    </body>
</html>
)=====";

