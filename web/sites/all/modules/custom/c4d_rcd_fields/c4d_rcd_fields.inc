<?php

/**
 * Returns an array of property info for
 * c4d_rcd_fields_svg_element_property_info_callback().
 *
 * @see c4d_rcd_fields_svg_element_property_info_callback()
 */
function _c4d_rcd_fields_svg_element_property_info_callback() {
  $result = [];

  $result['vertical'] = [
    'type' => 'integer',
    'label' => t('Vertical'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['tipo'] = [
    'type' => 'integer',
    'label' => t('Tipo'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['colonna'] = [
    'type' => 'integer',
    'label' => t('Colonna'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['vertical'] = [
    'type' => 'text',
    'label' => t('Vertical'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['x'] = [
    'type' => 'text',
    'label' => t('X'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['y'] = [
    'type' => 'text',
    'label' => t('Y'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['width'] = [
    'type' => 'text',
    'label' => t('Width'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['height'] = [
    'type' => 'text',
    'label' => t('Height'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['riga_1'] = [
    'type' => 'text',
    'label' => t('Riga 1'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['riga_2'] = [
    'type' => 'text',
    'label' => t('Riga 2'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['riga_3'] = [
    'type' => 'text',
    'label' => t('Riga 3'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['z_index'] = [
    'type' => 'text',
    'label' => t('Z index'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['contatore_z'] = [
    'type' => 'text',
    'label' => t('Contatore Z'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['titolo'] = [
    'type' => 'text',
    'label' => t('Titolo'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['descr'] = [
    'type' => 'text',
    'label' => t('Description'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['hovering'] = [
    'type' => 'text',
    'label' => t('Hovering'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['http_type'] = [
    'type' => 'text',
    'label' => t('HTTP type'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['color'] = [
    'type' => 'text',
    'label' => t('Color'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  $result['ordine'] = [
    'type' => 'text',
    'label' => t('Ordine'),
    'setter callback' => 'entity_property_verbatim_set',
  ];

  return $result;
}

/**
 * Callback for c4d_rcd_fields_field_widget_form().
 *
 * @see c4d_rcd_fields_field_widget_form()
 */
function _c4d_rcd_fields_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $settings = $instance['widget']['settings'];

  // Define form elements.
  $form_elements = [];

  switch ($instance['widget']['type']) {
    case 'c4d_rcd_svg_element':
      $form_elements['vertical'] = [
        '#type' => 'textfield',
        '#title' => t('vertical'),
        '#default_value' => $items[$delta]['vertical'],
//        '#required' => TRUE,
      ];
      $form_elements['tipo'] = [
        '#type' => 'select',
        '#title' => t('tipo'),
        '#options' => [
          C4D_RCD_FIELDS_TIPO_OUTPUT => t('Output'),
          C4D_RCD_FIELDS_TIPO_OUTCOME => t('Outcome'),
        ],
        '#default_value' => $items[$delta]['tipo'],
//        '#required' => TRUE,
//        '#empty_value' => '-',
//        '#empty_option' => t('Please choose'),
//        '#required' => TRUE,
      ];
      $form_elements['colonna'] = [
        '#type' => 'textfield',
        '#title' => t('colonna'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['colonna'],
      ];
      $form_elements['x'] = [
        '#type' => 'textfield',
        '#title' => t('x'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['x'],
      ];
      $form_elements['y'] = [
        '#type' => 'textfield',
        '#title' => t('y'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['y'],
      ];
      $form_elements['width'] = [
        '#type' => 'textfield',
        '#title' => t('width'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['width'],
      ];
      $form_elements['height'] = [
        '#type' => 'textfield',
        '#title' => t('height'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['height'],
      ];
      $form_elements['riga_1'] = [
        '#type' => 'textfield',
        '#title' => t('riga_1'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['riga_1'],
      ];
      $form_elements['riga_2'] = [
        '#type' => 'textfield',
        '#title' => t('riga_2'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['riga_2'],
      ];
      $form_elements['riga_3'] = [
        '#type' => 'textfield',
        '#title' => t('riga_3'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['riga_3'],
      ];
      $form_elements['z_index'] = [
        '#type' => 'textfield',
        '#title' => t('z_index'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['z_index'],
      ];
      $form_elements['contatore_z'] = [
        '#type' => 'textfield',
        '#title' => t('contatore_z'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['contatore_z'],
      ];
      $form_elements['titolo'] = [
        '#type' => 'textfield',
        '#title' => t('titolo'),
        '#required' => FALSE,
        '#default_value' => $items[$delta]['titolo'],
      ];
      $form_elements['descr'] = [
        '#type' => 'textarea',
        '#title' => t('descr'),
        '#required' => FALSE,
        '#default_value' => $items[$delta]['descr'],
      ];
      $form_elements['hovering'] = [
        '#type' => 'textarea',
        '#title' => t('hovering'),
        '#required' => FALSE,
        '#default_value' => $items[$delta]['hovering'],
      ];
      $form_elements['http_type'] = [
        '#type' => 'value',
        '#value' => 'http://',
      ];
      $form_elements['color'] = [
        '#type' => 'textfield',
        '#title' => t('color'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['color'],
      ];
      $form_elements['ordine'] = [
        '#type' => 'textfield',
        '#title' => t('ordine'),
        '#maxlength' => 50,
        '#required' => FALSE,
        '#default_value' => $items[$delta]['ordine'],
//        '#required' => TRUE,
      ];
      break;
  }

  $element += $form_elements;

  return $element;
}
