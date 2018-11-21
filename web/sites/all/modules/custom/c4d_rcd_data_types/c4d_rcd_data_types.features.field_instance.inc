<?php

/**
 * @file
 * c4d_rcd_data_types.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function c4d_rcd_data_types_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'result_chain_diagram-diagram-field_rcd_matrix'.
  $field_instances['result_chain_diagram-diagram-field_rcd_matrix'] = array(
    'bundle' => 'diagram',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_matrix',
    'label' => 'Matrix',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-float-field_rcd_diagram'.
  $field_instances['result_chain_diagram-float-field_rcd_diagram'] = array(
    'bundle' => 'float',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_diagram',
    'label' => 'Diagram',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-float-field_rcd_svg_element'.
  $field_instances['result_chain_diagram-float-field_rcd_svg_element'] = array(
    'bundle' => 'float',
    'default_value' => array(
      0 => array(
        'vertical' => '',
        'tipo' => 1,
        'colonna' => '',
        'x' => '',
        'y' => '',
        'width' => '',
        'height' => '',
        'riga_1' => '',
        'riga_2' => '',
        'riga_3' => '',
        'z_index' => '',
        'contatore_z' => '',
        'titolo' => '',
        'descr' => '',
        'hovering' => '',
        'http_type' => 'http://',
        'color' => '',
        'ordine' => '',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'c4d_rcd_fields',
        'settings' => array(),
        'type' => 'c4d_rcd_svg_element_formatter_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_svg_element',
    'label' => 'SVG Element',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'c4d_rcd_fields',
      'settings' => array(),
      'type' => 'c4d_rcd_svg_element',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-impact-field_rcd_diagram'.
  $field_instances['result_chain_diagram-impact-field_rcd_diagram'] = array(
    'bundle' => 'impact',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_diagram',
    'label' => 'Diagram',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-impact-field_rcd_svg_element'.
  $field_instances['result_chain_diagram-impact-field_rcd_svg_element'] = array(
    'bundle' => 'impact',
    'default_value' => array(
      0 => array(
        'vertical' => '',
        'tipo' => 1,
        'colonna' => '',
        'x' => '',
        'y' => '',
        'width' => '',
        'height' => '',
        'riga_1' => '',
        'riga_2' => '',
        'riga_3' => '',
        'z_index' => '',
        'contatore_z' => '',
        'titolo' => '',
        'descr' => '',
        'hovering' => '',
        'http_type' => 'http://',
        'color' => '',
        'ordine' => '',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'c4d_rcd_fields',
        'settings' => array(),
        'type' => 'c4d_rcd_svg_element_formatter_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_svg_element',
    'label' => 'SVG Element',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'c4d_rcd_fields',
      'settings' => array(),
      'type' => 'c4d_rcd_svg_element',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-indicator-field_rcd_additional_information'.
  $field_instances['result_chain_diagram-indicator-field_rcd_additional_information'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_additional_information',
    'label' => 'Additional information',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-indicator-field_rcd_data_source'.
  $field_instances['result_chain_diagram-indicator-field_rcd_data_source'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_data_source',
    'label' => 'Data source',
    'required' => 0,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-indicator-field_rcd_diagram'.
  $field_instances['result_chain_diagram-indicator-field_rcd_diagram'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_diagram',
    'label' => 'Diagram',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'disable',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'providers' => array(
            'og_context' => FALSE,
            'url' => 1,
          ),
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-indicator-field_rcd_result'.
  $field_instances['result_chain_diagram-indicator-field_rcd_result'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_result',
    'label' => 'Result',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'disable',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'providers' => array(
            'og_context' => FALSE,
            'url' => 1,
          ),
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-indicator-field_rcd_type_of_data_source'.
  $field_instances['result_chain_diagram-indicator-field_rcd_type_of_data_source'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_type_of_data_source',
    'label' => 'Type of data source',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-indicator-field_rcd_unit'.
  $field_instances['result_chain_diagram-indicator-field_rcd_unit'] = array(
    'bundle' => 'indicator',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_unit',
    'label' => 'Unit',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-priority_area-field_rcd_diagram'.
  $field_instances['result_chain_diagram-priority_area-field_rcd_diagram'] = array(
    'bundle' => 'priority_area',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_diagram',
    'label' => 'Diagram',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-priority_area-field_rcd_svg_element'.
  $field_instances['result_chain_diagram-priority_area-field_rcd_svg_element'] = array(
    'bundle' => 'priority_area',
    'default_value' => array(
      0 => array(
        'value' => array(
          'colonna' => '',
          'contatore_z' => '',
          'height' => '',
          'http_type' => 'http://',
          'riga_1' => '',
          'riga_2' => '',
          'riga_3' => '',
          'tipo' => 1,
          'vertical' => 0,
          'width' => '',
          'x' => '',
          'y' => '',
          'z_index' => '',
        ),
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'c4d_rcd_fields',
        'settings' => array(),
        'type' => 'c4d_rcd_svg_element_formatter_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_svg_element',
    'label' => 'SVG Element',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'c4d_rcd_fields',
      'settings' => array(),
      'type' => 'c4d_rcd_svg_element',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-result-field_rcd_diagram'.
  $field_instances['result_chain_diagram-result-field_rcd_diagram'] = array(
    'bundle' => 'result',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_diagram',
    'label' => 'Diagram',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-result-field_rcd_priority_area'.
  $field_instances['result_chain_diagram-result-field_rcd_priority_area'] = array(
    'bundle' => 'result',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_priority_area',
    'label' => 'Priority area',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'result_chain_diagram-result-field_rcd_svg_element'.
  $field_instances['result_chain_diagram-result-field_rcd_svg_element'] = array(
    'bundle' => 'result',
    'default_value' => array(
      0 => array(
        'value' => array(
          'colonna' => '',
          'contatore_z' => '',
          'height' => '',
          'http_type' => 'http://',
          'riga_1' => '',
          'riga_2' => '',
          'riga_3' => '',
          'tipo' => 1,
          'vertical' => 0,
          'width' => '',
          'x' => '',
          'y' => '',
          'z_index' => '',
        ),
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'c4d_rcd_fields',
        'settings' => array(),
        'type' => 'c4d_rcd_svg_element_formatter_default',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_svg_element',
    'label' => 'SVG Element',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'c4d_rcd_fields',
      'settings' => array(),
      'type' => 'c4d_rcd_svg_element',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'result_chain_diagram-result-field_rcd_type'.
  $field_instances['result_chain_diagram-result-field_rcd_type'] = array(
    'bundle' => 'result',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'result_chain_diagram',
    'field_name' => 'field_rcd_type',
    'label' => 'Type',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'content_taxonomy_opt_groups' => FALSE,
      ),
      'type' => 'options_select',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional information');
  t('Data source');
  t('Diagram');
  t('Matrix');
  t('Priority area');
  t('Result');
  t('SVG Element');
  t('Type');
  t('Type of data source');
  t('Unit');

  return $field_instances;
}
