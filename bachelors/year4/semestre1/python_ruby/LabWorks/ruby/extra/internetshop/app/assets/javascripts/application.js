// This is a manifest file that'll be compiled into application.js, which will include all the files
// listed below.
//
// Any JavaScript/Coffee file within this directory, lib/assets/javascripts, vendor/assets/javascripts,
// or any plugin's vendor/assets/javascripts directory can be referenced here using a relative path.
//
// It's not advisable to add code directly here, but if you do, it'll appear at the bottom of the
// compiled file.
//
// Read Sprockets README (https://github.com/rails/sprockets#sprockets-directives) for details
// about supported directives.
//
//= require jquery
//= require jquery_ujs

//= require turbolinks
//= require moment
//= require bootstrap-sprockets
//= require bootstrap-datetimepicker
//= require_tree .

$('.datetimepicker').datetimepicker();

function readImage(input, img_id) {
    if (input.files && input.files[0]) {
        var reader = new FileReader();

        reader.onload = function (e) {
            document.getElementById(img_id).setAttribute('src', e.target.result)
        };

        reader.readAsDataURL(input.files[0]);
    }
}

function avatar_error(obj) {
    obj.onerror = null
    obj.src = '/default_avatar.jpg';
}
