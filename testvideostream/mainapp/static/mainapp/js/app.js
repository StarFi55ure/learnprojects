

var video_w = 640;
var video_h = 480;

var small = false;
$('.shrink').on('click', function () {
    if (!small) {
        $('#videoobject').css('position', 'fixed');

        $('#videoobject').animate({
            width: 160,
            height: 120,
            left: 40,
            bottom: 20
        }, 600);

        small = true;
    } else {

        var offset = $('#streamcontainer').offset();

        $('#videoobject').animate({
            width: video_w,
            height: video_h,
            left: offset.left,
            top: offset.top
        }, {
            duration: 600,
            complete: function () {
                $('#videoobject').css({
                    position: '',
                    top: '',
                    left: '',
                    bottom: ''
                });
            }
        });

        small = false;
    }
});

$(document).ready(function () {
    $('#videoobject').attr('src', 'http://localhost:5000/stream');
    $('video.sidebar').attr('src', 'http://localhost:5000/stream');
});

