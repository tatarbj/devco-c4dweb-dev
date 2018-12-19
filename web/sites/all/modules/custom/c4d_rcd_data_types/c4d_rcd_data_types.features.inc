<?php

/**
 * @file
 * c4d_rcd_data_types.features.inc
 */

/**
 * Implements hook_views_api().
 */
function c4d_rcd_data_types_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function c4d_rcd_data_types_eck_bundle_info() {
  $items = array(
    'result_chain_diagram_diagram' => array(
      'machine_name' => 'result_chain_diagram_diagram',
      'entity_type' => 'result_chain_diagram',
      'name' => 'diagram',
      'label' => 'Diagram',
      'config' => array(),
    ),
    'result_chain_diagram_float' => array(
      'machine_name' => 'result_chain_diagram_float',
      'entity_type' => 'result_chain_diagram',
      'name' => 'float',
      'label' => 'Float',
      'config' => array(),
    ),
    'result_chain_diagram_impact' => array(
      'machine_name' => 'result_chain_diagram_impact',
      'entity_type' => 'result_chain_diagram',
      'name' => 'impact',
      'label' => 'Impact',
      'config' => array(),
    ),
    'result_chain_diagram_indicator' => array(
      'machine_name' => 'result_chain_diagram_indicator',
      'entity_type' => 'result_chain_diagram',
      'name' => 'indicator',
      'label' => 'Indicator',
      'config' => array(),
    ),
    'result_chain_diagram_priority_area' => array(
      'machine_name' => 'result_chain_diagram_priority_area',
      'entity_type' => 'result_chain_diagram',
      'name' => 'priority_area',
      'label' => 'Priority Area',
      'config' => array(),
    ),
    'result_chain_diagram_result' => array(
      'machine_name' => 'result_chain_diagram_result',
      'entity_type' => 'result_chain_diagram',
      'name' => 'result',
      'label' => 'Result',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function c4d_rcd_data_types_eck_entity_type_info() {
  $items = array(
    'result_chain_diagram' => array(
      'name' => 'result_chain_diagram',
      'label' => 'Result Chain Diagram',
      'properties' => array(
        'title' => array(
          'label' => 'Title',
          'type' => 'text',
          'behavior' => 'title',
        ),
      ),
    ),
  );
  return $items;
}
