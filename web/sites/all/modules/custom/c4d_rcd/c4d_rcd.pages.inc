<?php

/**
 * Returns the SVG viewer to include in an iframe.
 *
 * @param int $diagram_id
 *    Diagram ID.
 *
 * @return string
 *    HTML output.
 */
function c4d_rcd_get_iframe_content($diagram_id) {
  $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$diagram_id]);
  if (!$entity = array_pop($entities)) {
    return drupal_not_found();
  }

  $output = '';
  $output .= theme('svg_iframe_content', ['diagram' => $entity]) . PHP_EOL;
  return $output;
}

/**
 * Returns the iframe code for a diagram.
 *
 * @param int $diagram_id
 *    Diagram ID.
 *
 * @return string
 *    HTML output.
 */
function c4d_rcd_get_iframe_code($diagram_id, $ajax) {
  $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$diagram_id]);
  if (!$entity = array_pop($entities)) {
    return drupal_not_found();
  }

  ctools_include('ajax');
  ctools_include('modal');

  $output = '';
  $url = url('/c4d_rcd/iframe/' . $diagram_id, ['absolute' => TRUE]);
  $iframe = '<iframe src="' . $url . '" name="visualizzatore_svg" scrolling="no" style="border: 1px solid #333; width: 100% ; height: 500px; overflow:hidden"></iframe>';
  $output .= '<pre>' . htmlentities($iframe) . '</pre>';

  if (!$ajax) {
    return $output;
  }

  ctools_modal_render('Copy and paste', $output);
  drupal_exit();
}
