/**
 * @file
 * Contains a behavior-function to initialize dragndrop_upload_file widget.
 */

(function ($) {
  Drupal.behaviors.dragndropUploadImage = {
    attach: function (context, settings) {
      if (!settings.dragndropUploadImage || navigator.userAgent.match(/MSIE\s(?!10.0)/)) {
        return;
      }

      $.each(settings.dragndropUploadImage, function (i, selector) {
        $(selector, context).once('dnd-upload-image', function () {
          new DnDUploadImage($(this));
        });
      });
    }
  }
})(jQuery);
