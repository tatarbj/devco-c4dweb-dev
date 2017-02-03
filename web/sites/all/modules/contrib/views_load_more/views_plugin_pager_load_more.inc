<?php

/**
 * @file
 *
 * The plugin to handle Load More pager.
 *
 * @ingroup views_pager_plugins
 */

class views_plugin_pager_load_more extends views_plugin_pager_full {

  /**
   * Summary title overwrite.
   */
  function summary_title() {
    if (!empty($this->options['offset'])) {
      return format_plural($this->options['items_per_page'], 'Load more pager, @count item, skip @skip', 'Load more pager, @count items, skip @skip', array('@count' => $this->options['items_per_page'], '@skip' => $this->options['offset']));
    }
    return format_plural($this->options['items_per_page'], 'Load more pager, @count item', 'Load more pager, @count items', array('@count' => $this->options['items_per_page']));
  }

  /**
   * Options definition overwrite.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['waypoint'] = array(
      'contains' => array(
        'infinite' => array('default' => FALSE),
      ),
    );
    $options['more_button_text'] = array(
      'default' => t('Load more'),
      'translatable' => TRUE,
    );
    $options['more_button_empty_text'] = array(
      'default' => '',
      'translatable' => TRUE,
    );
    $options['items_on_first_page'] = array(
      'default' => '',
      'translateable' => FALSE,
    );
    $options['advance'] = array(
      'contains' => array(
        // @todo change name to content_selector
        'content_class' => array('default' => ''),
        'pager_selector' => array('default' => ''),
      ),
    );
    $options['effects'] = array(
      'contains' => array(
        'type' => array('default' => 'none'),
        'speed' => array('default' => ''),
      ),
    );
    return $options;
  }

  /**
   * Options form overwrite.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Keep items per page as the first form element on the page followed by
    // the option to change the 'load more' button text
    $form['items_per_page']['#weight'] = -2;

    // Option for users to specify the text used on the 'load more' button.
    $form['more_button_text'] = array(
      '#type' => 'textfield',
      '#title' => t('More link text'),
      '#description' => t('The text that will be displayed on the link that is used to load more elements. For example "Show me more"'),
      '#default_value' => $this->options['more_button_text'] ? $this->options['more_button_text'] : t('Load more'),
      '#weight' => -1,
    );
    // Option for users to specify the text used on the 'load more' button when no mor result is found.
    $form['more_button_empty_text'] = array(
      '#type' => 'textfield',
      '#title' => t('More link text when empty'),
      '#description' => t('The text that will replace the link that is used to load more elements when there is no more element to load. For example "No more results"'),
      '#default_value' => $this->options['more_button_empty_text'] ? $this->options['more_button_empty_text'] : '',
      '#weight' => -1,
    );

    $form['items_on_first_page'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of items on the first page'),
      '#weight' => 0,
      '#default_value' => $this->options['items_on_first_page'] ? $this->options['items_on_first_page'] : '',
    );

    if (module_exists('waypoints')) {
      $form['waypoint'] = array(
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#tree' => TRUE,
        '#title' =>  t('Waypoint Support'),
        '#input' => TRUE,
        '#description' => t('Waypoints is a small jQuery plugin that makes it easy to execute a function whenever you scroll to an element.'),
      );
      $form['waypoint']['infinite'] = array(
        '#type' => 'checkbox',
        '#title' => t('Infinite scrolling'),
        '#description' => t('Load more content when the user reaches the bottom of the page.'),
        '#default_value' => $this->options['waypoint']['infinite'],
      );
    }

    // Advanced options, override default selectors.
    $form['advance'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
      '#title' =>  t('Advanced Options'),
      '#input' => TRUE,
      '#description' => t('Configure advanced options.'),
    );
    // Option to specify the content_class, which is the wrapping div for views
    // rows.  This allows the JS to both find new rows on next pages and know
    // where to put them in the page.
    // @todo change name to content_selector
    $form['advance']['content_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Content selection selector'),
      '#description' => t('jQuery selector for the rows wrapper, relative to the view container.  Use when overriding the views markup.  Note that Views Load More requires a wrapping element for the rows.  Unless specified, Views Load More will use <strong><code>&gt; .view-content</code></strong>.'),
      '#default_value' => $this->options['advance']['content_class'],
    );
    // Option to specify the pager_selector, which is the pager relative to the
    // view container.
    $form['advance']['pager_selector'] = array(
      '#type' => 'textfield',
      '#title' => t('Pager selector'),
      '#description' => t('jQuery selector for the pager, relative to the view container.  Use when overriding the pager markup so that Views Load More knows where to find and how to replace the pager.  Unless specified, Views Load More will use <strong><code>.pager-load-more</code></strong>.'),
      '#default_value' => $this->options['advance']['pager_selector'],
    );
    // Affect the way that Views Load More adds new rows
    $form['effects'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
      '#title' =>  t('JQuery Effects'),
      '#input' => TRUE,
    );
    $form['effects']['type'] = array(
      '#type' => 'select',
      '#options' => array(
        'none' => t('None'),
        'fade' => t('Fade'),
      ),
      '#default_vaue' => 'none',
      '#title' => t('Effect Type'),
      '#default_value' => $this->options['effects']['type'],
    );
    $form['effects']['speed'] = array(
      '#type' => 'select',
      '#options' => array(
        'slow' => t('Slow'),
        'fast' => t('Fast'),
      ),
      '#states' => array(
        'visible' => array(
          '#edit-pager-options-effects-type' => array('value' => t('fade')),
        ),
      ),
      '#title' => t('Effect Speed'),
      '#default_value' => $this->options['effects']['speed'],
    );
  }

  /**
   * render overwrite.
   */
  function render($input) {
    if (module_exists('waypoints') && $this->options['waypoint']['infinite'] == 1) {
      $viewsLoadMore = array();
      $waypoint_opts = array(
        'offset' => '100%',
      );
      drupal_alter('views_load_more_waypoint_opts', $waypoint_opts, $this->view);
      $viewsLoadMore[$this->view->name . '-' . $this->view->current_display] = array(
        'view_name' => $this->view->name,
        'view_display_id' => $this->view->current_display,
        'waypoints' => 'infinite',
        'opts' => $waypoint_opts,
      );
      drupal_add_library('waypoints', 'waypoints');
      drupal_add_js(array('viewsLoadMore' => $viewsLoadMore), 'setting');
    }

    $pager_theme = views_theme_functions('views_load_more_pager', $this->view, $this->display);

    $vars = array(
      'parameters' => $input,
      'element' => $this->options['id'],
      'more_button_text' => $this->options['more_button_text'],
      'more_button_empty_text' => $this->options['more_button_empty_text'],
    );

    return theme($pager_theme, $vars);
  }

  /**
   * Modify the query for paging.
   */
  public function query() {
    parent::query();
    if (!$this->different_item_count_on_first_page()) {
      return;
    }

    $items_per_page = intval($this->options['items_per_page']);
    $items_on_first_page = intval($this->options['items_on_first_page']);
    $current_page = $this->get_current_page();
    if ($current_page === 0) {
      $this->view->query->set_limit($items_on_first_page);
    }
    elseif ($current_page > 0) {
      $offset = $items_on_first_page + (($current_page - 1) * $items_per_page);
      $this->view->query->set_offset($offset);
    }
  }

  /**
   * Checks item count is different on first page.
   */
  public function different_item_count_on_first_page() {
    $items_per_page = intval($this->get_items_per_page());
    $items_on_first_page = intval($this->options['items_on_first_page']);
    return (
      !$this->items_per_page_exposed()
      && $items_per_page > 0
      && $items_on_first_page > 0
      && $items_on_first_page != $items_per_page
    );
  }

  /**
   * Get number of total pages.
   */
  function get_pager_total() {
    if (!$this->different_item_count_on_first_page()) {
      return parent::get_pager_total();
    }

    // Total items is calculated with the offset setting.
    $total = $this->get_total_items();
    $items_per_page = intval($this->get_items_per_page());
    $total -= $items_on_first_page = intval($this->options['items_on_first_page']);
    return 1 + ceil($total / $items_per_page);
  }
}
