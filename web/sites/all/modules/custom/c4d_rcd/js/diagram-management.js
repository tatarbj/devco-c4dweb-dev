(function($, Drupal, window, document, undefined) {

  // Apply tabs behavior to sector-management-tabs.
  Drupal.behaviors.sector_management_tabs = {
    attach : function(context, settings) {
      $("#sector-management-tabs").tabs();
    }
  };

  // Apply the jump behavior to our custom links.
  Drupal.behaviors.sector_management_jump = {
    attach : function(context, settings) {
      $('.c4d-rcd-jump', context).click(function () {
        // Activate the target tab.
        var tab_id = $(this).attr('data-target-tab');
        var index = $('#sector-management-tabs a[href="#' + tab_id + '"]').parent().index();
        $('#sector-management-tabs').tabs('option', 'active', index);

        // Filter out items list by clicking the targeted filter.
        var filter_id = $(this).attr('data-target-filter');
        var item_id = $(this).attr('data-target-filter-id');
        $('#' + filter_id).val(item_id).trigger('change');
      });
    }
  };

  /**
   * Refreshes the given view thorugh AJAX, while keeping potential exposed
   * filters.
   *
   * @param string dom_id
   * @returns void
   */
  function c4d_rcd_refresh_view(dom_id) {
    // Find out if we have an exposed filter.
    if ($('.view-dom-id-' + dom_id + ' > .views-exposed-form').length) {
      // Submit the exposed form.
      if ($('.view-dom-id-' + dom_id + ' > form').length) {
        $('.view-dom-id-' + dom_id + ' > form').submit();
      }
    }
    else {
      // Refresh the view with built-in function.
      $('.view-dom-id-' + dom_id).trigger('RefreshView');
    }
  }

})(jQuery, Drupal, this, this.document);
