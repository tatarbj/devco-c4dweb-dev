<?php

/**
 * Ajax menu callback to get the form.
 */
function c4d_rcd_diagram_get_form($form_id, $item_id, $ajax) {
  $allowed_forms = [
    'eck__entity__form_add_result_chain_diagram_diagram',
    'eck__entity__form_edit_result_chain_diagram_diagram',
    'c4d_rcd_diagram_result_type_form',
    'eck__entity__form_edit_result_chain_diagram_indicator',
    'eck__entity__form_add_result_chain_diagram_indicator',
    'eck__entity__delete_form',
  ];

  // Only allow the wanted forms, we don't manage any other one.
  if (!in_array($form_id, $allowed_forms)) {
    return drupal_not_found();
  }

  if (!$ajax) {
    return drupal_get_form($form_id, $item_id);
  }

  ctools_include('ajax');
  ctools_include('modal');

  // If there is an item_id, we load the item.
  $item = NULL;
  if ($item_id > 0) {
    $items = entity_load(C4D_RCD_ENTITY_TYPE, [$item_id]);
    if (!empty($items)) {
      $item = array_pop($items);
    }
  }

  // Define title and arguments for the forms.
  $args = [];
  switch ($form_id) {

    case 'eck__entity__form_add_result_chain_diagram_diagram':
      $title = t('Add diagram');
      $args[] = entity_create(C4D_RCD_ENTITY_TYPE, ['type' => C4D_RCD_BUNDLE_DIAGRAM]);
      break;

    case 'eck__entity__form_edit_result_chain_diagram_diagram':
      $title = t('Modify diagram %title', ['%title' => $item->title]);
      $args[] = $item;
      break;

    case 'c4d_rcd_diagram_result_type_form':
      $title = t('Change type for %title', ['%title' => $item->title]);
      $args[] = $item;
      break;

    case 'eck__entity__form_edit_result_chain_diagram_indicator':
      $title = t('Modify indicator %title', ['%title' => $item->title]);
      $args[] = $item;
      break;

    case 'eck__entity__form_add_result_chain_diagram_indicator':
      $title = t('Add indicator');
      $args[] = entity_create(C4D_RCD_ENTITY_TYPE, ['type' => C4D_RCD_BUNDLE_INDICATOR]);
      break;

    case 'eck__entity__delete_form':
      $args[] = entity_type_load(C4D_RCD_ENTITY_TYPE);

      switch ($item->type) {
        case C4D_RCD_BUNDLE_INDICATOR:
          $title = t('Delete indicator %title', ['%title' => $item->title]);
          $args[] = bundle_load(C4D_RCD_ENTITY_TYPE, C4D_RCD_BUNDLE_INDICATOR);
          break;

        case C4D_RCD_BUNDLE_DIAGRAM:
          $title = t('Delete diagram %title', ['%title' => $item->title]);
          $args[] = bundle_load(C4D_RCD_ENTITY_TYPE, C4D_RCD_BUNDLE_DIAGRAM);
          break;
      }

      $args[] = $item;
      break;

  }

  // Add the arguments to the form.
  $form_state['build_info']['args'] = $args;
  $form_state['ajax'] = TRUE;
  $form_state['title'] = $title;

  // Use ctools to generate ajax instructions for the browser to create
  // a form in a modal popup.
  $output = ctools_modal_form_wrapper($form_id, $form_state);

  // If the form has been submitted, there may be additional instructions
  // such as dismissing the modal popup.
  if (!empty($form_state['ajax_commands'])) {
    $output = $form_state['ajax_commands'];
  }

  if (!empty($form_state['executed'])) {
    $output[] = ctools_modal_command_dismiss(); // Close modal automatically.
    // Check if we have a view to refresh.
    if (!empty($_GET['refresh_view'])) {
      $output[] = ajax_command_invoke('.view-dom-id-' . $_GET['refresh_view'], 'triggerHandler', ['RefreshView']);
    }
  }

  // Return the ajax instructions to the browser via ajax_render().
  print ajax_render($output);
  drupal_exit();
}

/**
 * Form to set the type of result.
 */
function c4d_rcd_diagram_result_type_form($form, $form_state, $result) {
  $form = [];

  // Store the result for the submit callback.
  $form['result'] = [
    '#type' => 'value',
    '#value' => $result,
  ];

  // Get the type options from the field itself.
  $field = field_info_field('field_rcd_type');
  $allowed_values = list_allowed_values($field);

  // Define form elements.
  $form['type'] = [
    '#title' => t('Type'),
    '#type' => 'radios',
    '#options' => $allowed_values,
    '#default_value' => $result->field_rcd_type[LANGUAGE_NONE][0]['value'],
  ];
  $form['submit'] = [
    '#value' => t('Submit'),
    '#type' => 'submit',
  ];

  return $form;
}

/**
 * Submit handler for c4d_rcd_diagram_result_type_form().
 */
function c4d_rcd_diagram_result_type_form_submit(&$form, &$form_state) {

  // Get the result item.
  $result = $form_state['values']['result'];

  // Check if the type has changed and save it.
  if ($result->field_rcd_type[LANGUAGE_NONE][0]['value'] != $form_state['values']['type']) {
    $result->field_rcd_type[LANGUAGE_NONE][0]['value'] = $form_state['values']['type'];
    field_attach_update(C4D_RCD_ENTITY_TYPE, $result);
  }

  // Tell the browser to close the modal.
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}
