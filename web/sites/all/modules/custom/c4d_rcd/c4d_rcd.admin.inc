<?php

/**
 * Page callback for the SVG editor.
 *
 * @return string
 *    HTML output.
 */
function c4d_rcd_svg_editor() {
  // Load all needed libraries.
  $libraries = [
    'svgjs',
    'bootstrap-slider',
    'bootstrap',
    'vivus',
  ];
  foreach ($libraries as $name) {
    $library = libraries_load($name);
  }

  // Load all local JS and CSS files. We have them here because some of them
  // were customised in the legacy application, or some we don't know the
  // source.
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/underscore-min.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/pan_zoom_full.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/draggy.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/main.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/bootstrap-dialog.min.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/bootstrap-colorpicker.min.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/bootstrap-colorpicker-plus.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/context.js', ['scope' => 'footer']);
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/gestione_editor.js', ['scope' => 'footer']);

  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-editor.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-dialog.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-colorpicker.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-colorpicker-plus.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/c4d_rcd.css');

  $output = '';
  $output .= _c4d_rdc_svg_editor_controls() . PHP_EOL;
  $output .= theme('svg') . PHP_EOL;
  return $output;
}

/**
 * Returns the form controls for the SVG editor.
 *
 * @return string
 *    HTML output.
 */
function _c4d_rdc_svg_editor_controls() {
  // Sectors & Priority areas select boxes.
  $output = '<div class="input-group" role="group" aria-label="' . t('Sectors and Priority areas') . '">';
    // Sector.
    $select_options = [
      0 => t('Diagrams'),
    ];
    $output .= theme('select', ['element' => ['#options' => $select_options, '#id' => 'prj_id', '#name' => 'prj_id', '#attributes' => ['onchange' => "svg_obj.cambia_prj(this.value);"]]]);
    // Priority areas.
    $select_options = [
      0 => t('Priority Areas'),
    ];
    $output .= theme('select', ['element' => ['#options' => $select_options, '#id' => 'area_select', '#name' => 'area_select', '#attributes' => ['onchange' => "svg_obj.select_area(this.value);"]]]);
  $output .= '</div>';

  // Test link & Resize selected.
  $output .= '<div class="btn-group" role="group">';
    $output .= '<button type="button" class="btn btn-primary" href="javascript:void(0);" onclick="svg_obj.effettua_link();">' . t('Test link') . '</button>';
    $output .= '<button type="button" class="btn btn-primary" href="javascript:void(0);" onclick="svg_obj.resize_selected();">' . t('Resize Selected') . '</button>';
  $output .= '</div>';

  // Align selected.
  $output .= '<div class="btn-group" role="group" aria-label="' . t('Align Selected') . '">';
    // Left Align
    $output .= '<button type="button" class="btn btn-primary" aria-label="' . t('Left Align') . '" title="' . t('Align Selected Left') . '" href="javascript:void(0);" onclick="svg_obj.align_selected(\'left\');">';
      $output .= '<span class="glyphicon glyphicon-object-align-left" aria-hidden="true"></span>';
    $output .= '</button>';
    // Top Align
    $output .= '<button type="button" class="btn btn-primary" aria-label="' . t('Top Align') . '" title="' . t('Align Selected Top') . '" href="javascript:void(0);" onclick="svg_obj.align_selected(\'top\');">';
      $output .= '<span class="glyphicon glyphicon-object-align-top" aria-hidden="true"></span>';
    $output .= '</button>';
  $output .= '</div>';

  // Change width.
  $output .= '<div class="btn-group" role="group" aria-label="' . t('Change width') . '">';
    // Decrease width.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Decrease width') . '" title="' . t('Decrease width') . '" href="javascript:void(0);" onclick="svg_obj.mod_width(-20);">';
      $output .= '<span class="glyphicon glyphicon-minus" aria-hidden="true"></span>';
    $output .= '</button>';
    // Slightly decrease width.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Slightly decrease width') . '" title="' . t('Slightly decrease width') . '" href="javascript:void(0);" onclick="svg_obj.mod_width(-4);">-</button>';
    $output .= '<span class="btn-group-addon" title="' . t('Change width') . '">';
      $output .= '<span class="glyphicon glyphicon-resize-horizontal" aria-hidden="true"></span>';
    $output .= '</span>';
    // Slightly increase width.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Slightly increase width') . '" title="' . t('Slightly increase width') . '" href="javascript:void(0);" onclick="svg_obj.mod_width(4);">+</button>';
    // Increase width.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Increase width') . '" title="' . t('Increase width') . '" href="javascript:void(0);" onclick="svg_obj.mod_width(20);">';
      $output .= '<span class="glyphicon glyphicon-plus" aria-hidden="true"></span>';
    $output .= '</button>';
  $output .= '</div>';

  // Change height.
  $output .= '<div class="btn-group" role="group" aria-label="' . t('Change height') . '">';
    // Decrease height.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Decrease height') . '" title="' . t('Decrease height') . '" href="javascript:void(0);" onclick="svg_obj.mod_height(-20);">';
      $output .= '<span class="glyphicon glyphicon-minus" aria-hidden="true"></span>';
    $output .= '</button>';
    // Slightly decrease height.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Slightly decrease height') . '" title="' . t('Slightly decrease height') . '" href="javascript:void(0);" onclick="svg_obj.mod_height(-4);">-</button>';
    $output .= '<span class="btn-group-addon" title="' . t('Change height') . '">';
      $output .= '<span class="glyphicon glyphicon-resize-vertical" aria-hidden="true"></span>';
    $output .= '</span>';
    // Slightly increase height.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Slightly increase height') . '" title="' . t('Slightly increase height') . '" href="javascript:void(0);" onclick="svg_obj.mod_height(4);">+</button>';
    // Increase height.
    $output .= '<button type="button" class="btn btn-warning" aria-label="' . t('Increase height') . '" title="' . t('Increase height') . '" href="javascript:void(0);" onclick="svg_obj.mod_height(20);">';
      $output .= '<span class="glyphicon glyphicon-plus" aria-hidden="true"></span>';
    $output .= '</button>';
  $output .= '</div>';

  // Zoom information.
  $output .= '<div class="btn-group" role="group" aria-label="' . t('Zoom') . '">';
    $output .= '<span class="btn-group-addon" id="livello_zoom">' . t('Zoom') . ' : ...</span>';
  $output .= '</div>';

  $output = '<div class="btn-toolbar" role="toolbar" aria-label="' . t('Diagram editor toolbar') . '">' . $output . '</div>';

  return $output;
}

/**
 * Page callback for the diagrams management (indicators).
 *
 * @return string
 *    HTML output.
 */
function c4d_rcd_diagram_management($diagram) {
  // Load the modal library and add the modal javascript.
  ctools_include('modal');
  ctools_modal_add_js();

  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-sectors.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/c4d_rcd.css');

  // Add size settings for the modals.
  drupal_add_js([
      'CToolsModal' => [
        'modalSize' => [
          'type' => 'scale',
          'width' => '.8',
          'height' => '.6',
        ], 
      ],
    ], 'setting');

  drupal_add_library('system', 'ui.tabs');
  drupal_add_js(drupal_get_path('module', 'c4d_rcd') . '/js/diagram-management.js');
  $output = '';
  $tabs = [
    'priority-areas' => [
      'label' => t('Priority areas'),
      'content' => views_embed_view('diagram_management', 'block', $diagram->id),
    ],
    'impact' => [
      'label' => t('Impact'),
      'content' => views_embed_view('diagram_management', 'block_1', $diagram->id),
    ],
    'results' => [
      'label' => t('Results'),
      'content' => views_embed_view('diagram_management', 'block_2', $diagram->id),
    ],
    'indicators' => [
      'label' => t('Indicators'),
      'content' => views_embed_view('diagram_management', 'block_3', $diagram->id),
    ],
  ];

  $output .= '<div id="sector-management-tabs">';
  $output .= '<ul>';
  foreach ($tabs as $key => $item) {
    $output .= '<li><a href="#sector-' . $key . '">' . $item['label'] . '</a></li>';
  }
  $output .= '</ul>';
  foreach ($tabs as $key => $item) {
    $output .= '<div id="sector-' . $key . '">' . $item['content'] . '</div>';
  }
  $output .= '</div>';

  return $output;
}

/**
 * Page callback for the diagrams list.
 *
 * @return string
 *    HTML output.
 */
function c4d_rcd_diagram_list() {
  // Load the modal library and add the modal javascript.
  ctools_include('modal');
  ctools_modal_add_js();

  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/bootstrap-sectors.min.css');
  drupal_add_css(drupal_get_path('module', 'c4d_rcd') . '/css/c4d_rcd.css');

  // Add size settings for the modals.
  drupal_add_js([
      'CToolsModal' => [
        'modalSize' => [
          'type' => 'scale',
          'width' => '.8',
          'height' => '.6',
        ], 
      ],
    ], 'setting');

  return views_embed_view('sectors_management', 'block_1');
}
