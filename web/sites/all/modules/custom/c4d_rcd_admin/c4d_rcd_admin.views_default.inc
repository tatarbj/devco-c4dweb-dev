<?php

/**
 * @file
 * c4d_rcd_admin.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function c4d_rcd_admin_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'diagram_management';
  $view->description = '';
  $view->tag = 'admin';
  $view->base_table = 'eck_result_chain_diagram';
  $view->human_name = 'RCD: Diagram management';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Diagram management';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'title' => 'title',
    'field_rcd_unit' => 'field_rcd_unit',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
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
    'field_rcd_unit' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Your search does not contain any result.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['id'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['field'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Contextual filter: Result Chain Diagram: Id */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

  /* Display: Priority areas */
  $handler = $view->new_display('block', 'Priority areas', 'block');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  /* Field: View results */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'View results';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="#" class="c4d-rcd-jump btn btn-primary btn-sm" data-target-tab="sector-results" data-target-filter="edit-field-rcd-priority-area-target-id" data-target-filter-id="[id]"><span class="glyphicon glyphicon-eye-open" aria-hidden="true"></span> View results</a>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['filters']['type']['value'] = array(
    'priority_area' => 'priority_area',
  );

  /* Display: Impacts */
  $handler = $view->new_display('block', 'Impacts', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Impact id */
  $handler->display->display_options['fields']['id_1']['id'] = 'id_1';
  $handler->display->display_options['fields']['id_1']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id_1']['field'] = 'id';
  $handler->display->display_options['fields']['id_1']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['fields']['id_1']['ui_name'] = 'Impact id';
  $handler->display->display_options['fields']['id_1']['label'] = '';
  $handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id_1']['separator'] = '';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="#" class="c4d-rcd-jump btn btn-primary btn-sm" data-target-tab="sector-indicators" data-target-filter="edit-field-rcd-result-target-id-1" data-target-filter-id="[id_1]"><span class="glyphicon glyphicon-eye-open" aria-hidden="true"></span> Indicators list</a>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['filters']['type']['value'] = array(
    'impact' => 'impact',
  );

  /* Display: Results */
  $handler = $view->new_display('block', 'Results', 'block_2');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['id'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['relationships']['reverse_field_rcd_diagram_result_chain_diagram']['field'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Result Chain Diagram: Type */
  $handler->display->display_options['fields']['field_rcd_type']['id'] = 'field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['table'] = 'field_data_field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['field'] = 'field_rcd_type';
  $handler->display->display_options['fields']['field_rcd_type']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['fields']['field_rcd_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_rcd_type']['alter']['path'] = 'c4d_rcd/ajax_forms_2/c4d_rcd_diagram_result_type_form/[id]/nojs';
  $handler->display->display_options['fields']['field_rcd_type']['alter']['link_class'] = 'ctools-use-modal';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  /* Field: Indicators list */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Indicators list';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="#" class="c4d-rcd-jump btn btn-primary btn-sm" data-target-tab="sector-indicators" data-target-filter="edit-field-rcd-result-target-id" data-target-filter-id="[id]"><span class="glyphicon glyphicon-eye-open" aria-hidden="true"></span> Indicators list</a>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Result Chain Diagram: Type (field_rcd_type) */
  $handler->display->display_options['sorts']['field_rcd_type_value']['id'] = 'field_rcd_type_value';
  $handler->display->display_options['sorts']['field_rcd_type_value']['table'] = 'field_data_field_rcd_type';
  $handler->display->display_options['sorts']['field_rcd_type_value']['field'] = 'field_rcd_type_value';
  $handler->display->display_options['sorts']['field_rcd_type_value']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['sorts']['field_rcd_type_value']['order'] = 'DESC';
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['filters']['type']['value'] = array(
    'result' => 'result',
  );
  /* Filter criterion: Result Chain Diagram: Priority area (field_rcd_priority_area) */
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['id'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['table'] = 'field_data_field_rcd_priority_area';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['field'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['operator_id'] = 'field_rcd_priority_area_target_id_op';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['label'] = 'Priority area';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['operator'] = 'field_rcd_priority_area_target_id_op';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['identifier'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Indicators */
  $handler = $view->new_display('block', 'Indicators', 'block_3');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'title' => 'title',
    'field_rcd_unit' => 'field_rcd_unit',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
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
    'field_rcd_unit' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['id'] = 'field_rcd_result_target_id';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['table'] = 'field_data_field_rcd_result';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['field'] = 'field_rcd_result_target_id';
  $handler->display->display_options['relationships']['field_rcd_result_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_rcd_diagram_target_id']['id'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['relationships']['field_rcd_diagram_target_id']['table'] = 'field_data_field_rcd_diagram';
  $handler->display->display_options['relationships']['field_rcd_diagram_target_id']['field'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['relationships']['field_rcd_diagram_target_id']['relationship'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['relationships']['field_rcd_diagram_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Result Chain Diagram: Unit */
  $handler->display->display_options['fields']['field_rcd_unit']['id'] = 'field_rcd_unit';
  $handler->display->display_options['fields']['field_rcd_unit']['table'] = 'field_data_field_rcd_unit';
  $handler->display->display_options['fields']['field_rcd_unit']['field'] = 'field_rcd_unit';
  /* Field: Modify */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Modify';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="glyphicon glyphicon-pencil" aria-hidden="true"></span> Modify';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '/c4d_rcd/ajax_forms_2/eck__entity__form_edit_result_chain_diagram_indicator/[id]/nojs';
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn btn-primary btn-sm ctools-use-modal c4d-rcd-ajax-reload';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'text-nowrap';
  /* Field: Delete */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Delete';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<span class="glyphicon glyphicon-trash" aria-hidden="true"></span> Delete';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = '/c4d_rcd/ajax_forms_2/eck__entity__delete_form/[id]/nojs';
  $handler->display->display_options['fields']['nothing_1']['alter']['link_class'] = 'btn btn-danger btn-sm ctools-use-modal c4d-rcd-ajax-reload';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Result Chain Diagram: Id */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['relationship'] = 'field_rcd_diagram_target_id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_rcd_diagram_result_chain_diagram';
  $handler->display->display_options['filters']['type']['value'] = array(
    'indicator' => 'indicator',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Result Chain Diagram: Priority area (field_rcd_priority_area) */
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['id'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['table'] = 'field_data_field_rcd_priority_area';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['field'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['relationship'] = 'field_rcd_result_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['operator_id'] = 'field_rcd_priority_area_target_id_op';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['label'] = 'Priority area';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['operator'] = 'field_rcd_priority_area_target_id_op';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['identifier'] = 'field_rcd_priority_area_target_id';
  $handler->display->display_options['filters']['field_rcd_priority_area_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
  );
  /* Filter criterion: Result Chain Diagram: Result (field_rcd_result) */
  $handler->display->display_options['filters']['field_rcd_result_target_id']['id'] = 'field_rcd_result_target_id';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['table'] = 'field_data_field_rcd_result';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['field'] = 'field_rcd_result_target_id';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_rcd_result_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rcd_result_target_id']['expose']['operator_id'] = 'field_rcd_result_target_id_op';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['expose']['label'] = 'Result';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['expose']['operator'] = 'field_rcd_result_target_id_op';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['expose']['identifier'] = 'field_rcd_result_target_id';
  $handler->display->display_options['filters']['field_rcd_result_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Impact */
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['id'] = 'field_rcd_result_target_id_1';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['table'] = 'field_data_field_rcd_result';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['field'] = 'field_rcd_result_target_id';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['ui_name'] = 'Impact';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['group'] = 1;
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['expose']['operator_id'] = 'field_rcd_result_target_id_1_op';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['expose']['label'] = 'Impact';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['expose']['operator'] = 'field_rcd_result_target_id_1_op';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['expose']['identifier'] = 'field_rcd_result_target_id_1';
  $handler->display->display_options['filters']['field_rcd_result_target_id_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
  );
  $export['diagram_management'] = $view;

  $view = new view();
  $view->name = 'sectors_management';
  $view->description = '';
  $view->tag = 'admin';
  $view->base_table = 'eck_result_chain_diagram';
  $view->human_name = 'RCD: Sectors Management';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Diagrams Management';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'title' => 'title',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing',
    'nothing_3' => 'nothing',
    'nothing_5' => 'nothing',
    'nothing_4' => 'nothing',
    'nothing_2' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
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
    'nothing' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_5' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You have no diagram to manage. Click on the "Add" button above to create one.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Field: Result Chain Diagram: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Result Chain Diagram: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Diagram name';
  /* Field: Preview Result Chain */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Preview Result Chain';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="glyphicon glyphicon-pencil" aria-hidden="true"></span> Preview Result Chain';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'c4d_rcd/iframe/[id]';
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn btn-info btn-sm';
  $handler->display->display_options['fields']['nothing']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'text-right';
  $handler->display->display_options['fields']['nothing']['element_label_class'] = 'text-right';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Diagram management */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Diagram management';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<span class="glyphicon glyphicon-cog" aria-hidden="true"></span> Manage results and indicators';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'admin/c4d/sig/diagrams/[id]';
  $handler->display->display_options['fields']['nothing_1']['alter']['link_class'] = 'btn btn-info btn-sm';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Get HTML */
  $handler->display->display_options['fields']['nothing_3']['id'] = 'nothing_3';
  $handler->display->display_options['fields']['nothing_3']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_3']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_3']['ui_name'] = 'Get HTML';
  $handler->display->display_options['fields']['nothing_3']['label'] = '';
  $handler->display->display_options['fields']['nothing_3']['alter']['text'] = '<span class="glyphicon glyphicon-import" aria-hidden="true"></span> Get HTML';
  $handler->display->display_options['fields']['nothing_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_3']['alter']['path'] = 'c4d_rcd/get_iframe_code/[id]/nojs';
  $handler->display->display_options['fields']['nothing_3']['alter']['link_class'] = 'btn btn-info btn-sm ctools-use-modal';
  $handler->display->display_options['fields']['nothing_3']['element_label_colon'] = FALSE;
  /* Field: Export Indicators */
  $handler->display->display_options['fields']['nothing_5']['id'] = 'nothing_5';
  $handler->display->display_options['fields']['nothing_5']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_5']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_5']['ui_name'] = 'Export Indicators';
  $handler->display->display_options['fields']['nothing_5']['label'] = '';
  $handler->display->display_options['fields']['nothing_5']['alter']['text'] = '<span class="glyphicon glyphicon-export" aria-hidden="true"></span> Export Indicators';
  $handler->display->display_options['fields']['nothing_5']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_5']['alter']['path'] = 'results-indicators/export/[id]';
  $handler->display->display_options['fields']['nothing_5']['alter']['link_class'] = 'btn btn-info btn-sm';
  $handler->display->display_options['fields']['nothing_5']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing_5']['element_label_colon'] = FALSE;
  /* Field: Modify */
  $handler->display->display_options['fields']['nothing_4']['id'] = 'nothing_4';
  $handler->display->display_options['fields']['nothing_4']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_4']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_4']['ui_name'] = 'Modify';
  $handler->display->display_options['fields']['nothing_4']['label'] = '';
  $handler->display->display_options['fields']['nothing_4']['alter']['text'] = '<span class="glyphicon glyphicon-pencil" aria-hidden="true"></span> <span class="element-invisible">Modify diagram</span>';
  $handler->display->display_options['fields']['nothing_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_4']['alter']['path'] = '/c4d_rcd/ajax_forms_2/eck__entity__form_edit_result_chain_diagram_diagram/[id]/nojs';
  $handler->display->display_options['fields']['nothing_4']['alter']['alt'] = 'Modify diagram';
  $handler->display->display_options['fields']['nothing_4']['alter']['link_class'] = 'btn btn-primary btn-sm ctools-use-modal';
  $handler->display->display_options['fields']['nothing_4']['element_label_colon'] = FALSE;
  /* Field: Delete */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['ui_name'] = 'Delete';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = '<span class="glyphicon glyphicon-trash" aria-hidden="true"></span> <span class="element-invisible">Delete diagram</span>';
  $handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['alter']['path'] = '/c4d_rcd/ajax_forms_2/eck__entity__delete_form/[id]/nojs';
  $handler->display->display_options['fields']['nothing_2']['alter']['alt'] = 'Delete diagram';
  $handler->display->display_options['fields']['nothing_2']['alter']['link_class'] = 'btn btn-danger btn-sm ctools-use-modal';
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  /* Sort criterion: Result Chain Diagram: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Result Chain Diagram: result_chain_diagram type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_result_chain_diagram';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'diagram' => 'diagram',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['sectors_management'] = $view;

  return $export;
}
