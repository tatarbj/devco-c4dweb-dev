<?php

/**
 * Questa � la parte che gestisce il salvataggio delle posizioni.
 */
function c4d_rcd_ajax_load_positions() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');
  $id_prj       = isset($_POST['id_prj']) ? $_POST['id_prj'] : NULL;
  $area_select  = isset($_POST['area_select']) ? $_POST['area_select'] : NULL;
  $result = SVGeditor::load_positions($id_prj, $area_select);
  return drupal_json_output($result);
}

/**
 * Elenco progetti.
 */
function c4d_rcd_ajax_elenco_progetti() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');

  $results = SVGeditor::elenco_progetti();
  return drupal_json_output($results);
}

/**
 * Questa serve a gestire l'elenco delle priority area.
 */
function c4d_rcd_ajax_elenco_priority_area() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');
  $id_prj = isset($_POST['id_prj']) ? $_POST['id_prj'] : NULL;
  $result = SVGeditor::elenco_priority_area($id_prj);
  return drupal_json_output($result);
}

/**
 * Questa serve a vare l'update dell'elemento.
 */
function c4d_rcd_ajax_update_element(){
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');

  // Get POST values.
  $titolo     = isset($_POST['titolo']) ? $_POST['titolo'] : NULL;
  $colonna    = NULL;
  if (isset($_POST['colonna'])) {
    $colonna = $_POST['colonna'];
  }
  elseif (isset($_POST['colonna_ele'])) {
    $colonna = $_POST['colonna_ele'];
  } 
  $id_ele     = isset($_POST['id_ele']) ? $_POST['id_ele'] : NULL; 
  $descr      = isset($_POST['descr']) ? $_POST['descr'] : NULL; 
  $link_ele   = isset($_POST['link_ele']) ? $_POST['link_ele'] : NULL; 
  $http_type  = isset($_POST['http_type']) ? $_POST['http_type'] : NULL; 
  $vertical   = isset($_POST['vertical']) ? $_POST['vertical'] : NULL;
  $hovering   = isset($_POST['hovering']) ? $_POST['hovering'] : NULL;
  $bg_color   = isset($_POST['bg_col']) ? $_POST['bg_col'] : NULL;
  $ordine     = isset($_POST['ordine']) ? $_POST['ordine'] : NULL;

  SVGeditor::update_element($colonna, $bg_color, $titolo, $descr, $id_ele, $link_ele, $http_type, $vertical, $hovering, $ordine);
}

/**
 *
 */
function c4d_rcd_ajax_update_element2() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');

  $id_record  = isset($_POST['id_record']) ? $_POST['id_record'] : NULL;
  $width      = isset($_POST['width']) ? $_POST['width'] : NULL;
  $height     = isset($_POST['height']) ? $_POST['height'] : NULL;
  $x          = isset($_POST['x']) ? $_POST['x'] : NULL;
  $y          = isset($_POST['y']) ? $_POST['y'] : NULL;

  $result = SVGeditor::update_element2($id_record, $width, $height, $x, $y);
  return drupal_json_output($result);
}

/**
 * Questa � la parte che gestisce.
 */
function c4d_rcd_ajax_save_position() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');

  $tipologia  = isset($_POST['tipologia']) ? $_POST['tipologia'] : NULL;
  $titolo     = isset($_POST['titolo']) ? $_POST['titolo'] : NULL;
  $bg_col     = isset($_POST['bg_col']) ? $_POST['bg_col'] : NULL;
  $bg_color   = isset($_POST['bg_color']) ? $_POST['bg_color'] : NULL;
  $colonna    = isset($_POST['colonna']) ? $_POST['colonna'] : NULL;
  $descr      = isset($_POST['descr']) ? $_POST['descr'] : NULL;
  $id_prj     = isset($_POST['id_prj']) ? $_POST['id_prj'] : NULL;
  $link       = isset($_POST['link_ele']) ? $_POST['link_ele'] : NULL;
  $vertical   = isset($_POST['vertical']) ? $_POST['vertical'] : NULL;
  $hovering   = isset($_POST['hovering']) ? $_POST['hovering'] : NULL;
  $http_type  = isset($_POST['http_type']) ? $_POST['http_type'] : NULL;
  $ordine     = isset($_POST['ordine']) ? $_POST['ordine'] : NULL;

  if (!$bg_color && $bg_col)
    $bg_color = $bg_col;
  // if(!$bg_color && !$bg_col) $bg_color = "#ffcc00" ; 
  $arr = [];
  $arr = SVGeditor::save_position($tipologia, $titolo, $bg_color, $colonna, $descr, $id_prj, $link, $vertical, $hovering, $http_type, $ordine);
  $arr['POST'] = $titolo . ", " . $bg_color . ", " . $colonna . ", " . $descr . ", " . $id_prj . ", " . $link . ", " . $vertical . ", -> " . $hovering;

  return drupal_json_output($arr);
}

/**
 * Questa serve a salvare le posizioni di dutto l'ambaradham.
 */
function c4d_rcd_ajax_save_positions() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');
  $transform    = isset($_POST['transform']) ? $_POST['transform'] : NULL;
  $area_select  = isset($_POST['area_select']) ? $_POST['area_select'] : NULL;
  $id_prj       = isset($_POST['id_prj']) ? $_POST['id_prj'] : NULL;
  $elementi     = isset($_POST['dati_posizione']['elementi']) ? $_POST['dati_posizione']['elementi'] : NULL;
  $link         = isset($_POST['dati_posizione']['link']) ? $_POST['dati_posizione']['link'] : NULL;

  $arr = SVGeditor::save_positions($area_select, $id_prj, $elementi, $link, $transform);
  return drupal_json_output($arr);
}

/**
 * Questa serve a restituire il dettaglio del quadrato.
 */
function c4d_rcd_ajax_dettaglio_elemento() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');
  $id_ele = isset($_POST['id_record']) ? $_POST['id_record'] : NULL;

  $arr = SVGeditor::dettaglio_elemento($id_ele);
  return drupal_json_output($arr);
}

/**
 * Questa dovrebbe servire ad eliminare l'elemento.
 */
function c4d_rcd_ajax_elimina_ele() {
  module_load_include('inc', 'c4d_rcd', 'includes/svg_editor');
  $id_ele = isset($_POST['id_elemento']) ? $_POST['id_elemento'] : NULL;

  $arr = SVGeditor::elimina_ele($id_ele);
  return drupal_json_output($arr);
}

/**
 * Returns a ready-to-use form based on legacy template to be used in the SVG
 * editor.
 *
 * @param string $form_id
 * @return string The HTML output or FALSE if the form doesn't exist.
 */
function c4d_rcd_ajax_get_form($form_id) {
  $forms = [
    'form_inserisci',
    'form_inserisci_float',
    'form_inserisci_vertical',
    'form_inserisci_impact',
    'form_modifica',
    'form_modifica_float',
    'form_modifica_vertical',
    'form_modifica_impact',
  ];
  if (!in_array($form_id, $forms)) {
    return drupal_not_found();
  }

  ob_start();
  require_once drupal_get_path('module', 'c4d_rcd') . '/forms/' . $form_id . '.php';
  return ob_get_clean();
}
