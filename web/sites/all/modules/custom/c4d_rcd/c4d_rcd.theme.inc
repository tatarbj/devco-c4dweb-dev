<?php

/**
 * Implements template_process_svg().
 */
function c4d_rcd_preprocess_svg(&$variables) {

}

/**
 * Implements template_process_svg_iframe_content().
 */
function c4d_rcd_preprocess_svg_iframe_content(&$variables) {
  $diagram = $variables['diagram'];
  $variables['id'] = $diagram->id;
}
