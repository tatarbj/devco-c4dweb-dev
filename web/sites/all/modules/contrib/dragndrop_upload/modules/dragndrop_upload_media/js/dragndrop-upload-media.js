/**
 * @file
 * Contains a behavior-function to integrate DnD widgets with Media browser.
 *
 * Settings are provided via Drupal.settings.dragndropUploadMedia variable.
 */

(function ($) {
  Drupal.behaviors.dragndropUploadMedia = {
    attach: function (context, settings) {
      if (!settings.dragndropUploadMedia || navigator.userAgent.match(/MSIE\s(?!10.0)/)) {
        return;
      }

      $.each(settings.dragndropUploadMedia, function (selector, eachSettings) {
        $(selector, context).once('dnd-upload-media', function () {
          new DnDUploadMedia($(this), eachSettings);
        });
      });
    }
  };
})(jQuery);
