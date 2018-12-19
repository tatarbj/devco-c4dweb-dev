<?php

/**
 * Callback function to return an Excel export of results & indicators for a
 * given diagram.
 *
 * @param int $diagram_id
 */
function c4d_rcd_export_excel($diagram_id, $stringa_result = FALSE) {
  if (!$library = libraries_load('phpspreadsheet')) {
    return drupal_not_found();
  }
  require_once ($library['library path'] . '/vendor/autoload.php');
  module_load_include('inc', 'c4d_rcd', 'includes/excel.class');

  // Load the diagram object.
  $diagram = _c4d_rcd_load_full_diagram($diagram_id);

  $export = new C4dRcdExcelExportIndicators($diagram);
  $export->export();
  drupal_exit();
}
