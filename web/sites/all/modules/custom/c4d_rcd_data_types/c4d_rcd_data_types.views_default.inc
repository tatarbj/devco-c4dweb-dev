<?php

/**
 * @file
 * c4d_rcd_data_types.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function c4d_rcd_data_types_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'results_indicators';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_result_chain_diagram';
  $view->human_name = 'RCD: Results & Indicators';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Results & Indicators';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_rcd_unit' => 'field_rcd_unit',
    'field_rcd_data_source' => 'field_rcd_data_source',
    'field_rcd_additional_information' => 'field_rcd_data_source',
    'field_rcd_type' => 'field_rcd_type',
    'title_1' => 'field_rcd_type',
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_rcd_unit' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rcd_data_source' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br>',
      'empty_column' => 0,
    ),
    'field_rcd_additional_information' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_rcd_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br>',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['id'] = 'field_rcd_result_target_id';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['table'] = 'field_data_field_rcd_result';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['field'] = 'field_rcd_result_target_id';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['required'] = TRUE;
  /* Field: Result Chain Diagram: Unit */
  $handler->display->display_options['fields']['field_rcd_unit']['id'] = 'field_rcd_unit';
  $handler->display->display_options['fields']['field_rcd_unit']['table'] = 'field_data_field_rcd_unit';
  $handler->display->display_options['fields']['field_rcd_unit']['field'] = 'field_rcd_unit';
  $handler->display->display_options['fields']['field_rcd_unit']['exclude'] = TRUE;
  /* Field: Result Chain Diagram: Data source */
  $handler->display->display_options['fields']['field_rcd_data_source']['id'] = 'field_rcd_data_source';
  $handler->display->display_options['fields']['field_rcd_data_source']['table'] = 'field_data_field_rcd_data_source';
  $handler->display->display_options['fields']['field_rcd_data_source']['field'] = 'field_rcd_data_source';
  $handler->display->display_options['fields']['field_rcd_data_source']['exclude'] = TRUE;
  /* Field: Result Chain Diagram: Additional information */
  $handler->display->display_options['fields']['field_rcd_additional_information']['id'] = 'field_rcd_additional_information';
  $handler->display->display_options['fields']['field_rcd_additional_information']['table'] = 'field_data_field_rcd_additional_information';
  $handler->display->display_options['fields']['field_rcd_additional_information']['field'] = 'field_rcd_additional_information';
  $handler->display->display_options['fields']['field_rcd_additional_information']['exclude'] = TRUE;
  /* Field: Result Chain Diagram: Type */
  $handler->display->display_options['fields']['field_rcd_type']['id'] = 'field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['table'] = 'field_data_field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['field'] = 'field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['relationship'] = 'field_rcd_result_target_id';
  $handler->display->display_options['fields']['field_rcd_type']['label'] = 'Result';
  $handler->display->display_options['fields']['field_rcd_type']['empty'] = 'Impact';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_rcd_result_target_id';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Indicators';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] ([field_rcd_unit])
<br>
Data source: [field_rcd_data_source]
<br>
[field_rcd_additional_information]';
  /* Sort criterion: Result Chain Diagram: Type (field_rcd_type) */
  $handler->display->display_options['sorts']['field_rcd_type_value']['id'] = 'field_rcd_type_value';
  $handler->display->display_options['sorts']['field_rcd_type_value']['table'] = 'field_data_field_rcd_type';
  $handler->display->display_options['sorts']['field_rcd_type_value']['field'] = 'field_rcd_type_value';
  $handler->display->display_options['sorts']['field_rcd_type_value']['relationship'] = 'field_rcd_result_target_id';
  /* Contextual filter: Result Chain Diagram: Diagram (field_rcd_diagram) */
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['id'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['table'] = 'field_data_field_rcd_diagram';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['field'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_argument_options']['index'] = '0';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Result Chain Diagram: Id */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['relationship'] = 'field_rcd_result_target_id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['id']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['id']['not'] = TRUE;
  /* Contextual filter: Result Chain Diagram: Id */
  $handler->display->display_options['arguments']['id_1']['id'] = 'id_1';
  $handler->display->display_options['arguments']['id_1']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['arguments']['id_1']['field'] = 'id';
  $handler->display->display_options['arguments']['id_1']['relationship'] = 'field_rcd_result_target_id';
  $handler->display->display_options['arguments']['id_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['id_1']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['id_1']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['id_1']['break_phrase'] = TRUE;
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'indicator' => 'indicator',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'results-indicators/%/%';

  /* Display: Attachment - Highlighted result */
  $handler = $view->new_display('attachment', 'Attachment - Highlighted result', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Result Chain Diagram: Diagram (field_rcd_diagram) */
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['id'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['table'] = 'field_data_field_rcd_diagram';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['field'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['default_argument_options']['index'] = '0';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_rcd_diagram_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Result Chain Diagram: Id */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['relationship'] = 'field_rcd_result_target_id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['id']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $export['results_indicators'] = $view;

  return $export;
}
