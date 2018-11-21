<?php

/**
 * @file
 * This file contains hook implementations named after its calling function.
 * E.g. _MODULE_form_alter() will hold MODULE_form_alter() implementation.
 *
 * The purpose of this structure is to have a more lightweight .module file.
 */

/**
 * Implementation of c4d_rcd_views_pre_render().
 */
function _c4d_rcd_views_pre_render(&$view) {

  // We want to add an 'Add' link to the Indicators view.
  if ($view->name == 'diagram_management' && $view->current_display == 'block_3') {
    // The add link should be displayed if one result or one impact is chosen
    // but not both at the same time.
    $result_chosen = FALSE;
    if ((!empty($view->exposed_input['field_rcd_result_target_id']) && $view->exposed_input['field_rcd_result_target_id'] != 'All')) {
      $result_chosen = TRUE;
      $target_id = $view->exposed_input['field_rcd_result_target_id'];
    }
    $impact_chosen = FALSE;
    if ((!empty($view->exposed_input['field_rcd_result_target_id_1']) && $view->exposed_input['field_rcd_result_target_id_1'] != 'All')) {
      $impact_chosen = TRUE;
      $target_id = $view->exposed_input['field_rcd_result_target_id_1'];
    }

    if ($result_chosen xor $impact_chosen) {
      $diagram_id = $view->args[0];
      $path = '/c4d_rcd/ajax_forms_2/eck__entity__form_add_result_chain_diagram_indicator/0/nojs';
      $query_args = [
        'field_rcd_diagram' => $diagram_id,
        'field_rcd_result' => $target_id,
        'refresh_view' => $view->dom_id,
      ];

      $link = l(t('Add indicator'), $path, ['query' => [$query_args], 'attributes' => ['class' => ['ctools-use-modal']]]);

      // For some reason ctools does not process this link if it wrapped using
      // theme_links(), so we just wrap the link using hard-coded HTML.
      $attachment = '<ul class="action-links"><li>' . $link . '</li></ul>';

      $view->attachment_before = $attachment;
    }
  }

  // Add a query param to pass the views dom id to modal box.
  if ($view->name == 'diagram_management') {
    switch ($view->current_display) {
      case 'block_3':
        // Modify link.
        $view->field['nothing']->options['alter']['path'] .= '?refresh_view=' . $view->dom_id;
        // Delete link.
        $view->field['nothing_1']->options['alter']['path'] .= '?refresh_view=' . $view->dom_id;
        break;
    }
  }
  if ($view->name == 'sectors_management') {
    switch ($view->current_display) {
      case 'block_1':
        // Modify link.
        $view->field['nothing_4']->options['alter']['path'] .= '?refresh_view=' . $view->dom_id;
        // Delete link.
        $view->field['nothing_2']->options['alter']['path'] .= '?refresh_view=' . $view->dom_id;
        break;
    }
  }

  // We want to add a link to the Diagrams view.
  if ($view->name == 'sectors_management' && $view->current_display == 'block_1') {
    // Build the link.
    $path = '/c4d_rcd/ajax_forms_2/eck__entity__form_add_result_chain_diagram_diagram/0/nojs';
    $query_args = ['refresh_view' => $view->dom_id];
    $link = l(t('Add diagram'), $path, ['attributes' => ['class' => ['ctools-use-modal', 'add']], 'query' => $query_args]);

    // For some reason ctools does not process this link if it wrapped using
    // theme_links(), so we just wrap the link using hard-coded HTML.
    $attachment = '<ul class="action-links"><li>' . $link . '</li></ul>';

    $view->attachment_before = $attachment;
  }
}

/**
 * Implements c4d_rcd_form_views_exposed_form_alter().
 */
function _c4d_rcd_form_views_exposed_form_alter(&$form, &$form_state) {

  if ($form_state['view']->name == 'diagram_management') {

    switch ($form_state['view']->current_display) {

      case 'block_2':
      case 'block_3':
        $diagram_id = $form_state['view']->args[0];

        // We are using the "Render Views filters as select list" field option
        // for field_rcd_priority_area. However this option renders all results
        // for that field regardless of the current viewed item.
        // So we filter out the select options here.
        if (isset($form['field_rcd_priority_area_target_id'])) {          

          // Load priority areas for this diagram.
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
            ->entityCondition('bundle', C4D_RCD_BUNDLE_PRIORITY_AREA)
            ->fieldCondition('field_rcd_diagram', 'target_id', $diagram_id)
            ->fieldOrderBy('field_rcd_svg_element', 'contatore_z');
          $query_result = $query->execute();

          if (isset($query_result[C4D_RCD_ENTITY_TYPE])) {
            // We need to keep the 'All' option if it exists.
            if (isset($form['field_rcd_priority_area_target_id']['#options']['All'])) {
              $query_result[C4D_RCD_ENTITY_TYPE]['All'] = $form['field_rcd_priority_area_target_id']['#options']['All'];
            }

            // Filter out options.
            $form['field_rcd_priority_area_target_id']['#options'] = array_intersect_key($form['field_rcd_priority_area_target_id']['#options'], $query_result[C4D_RCD_ENTITY_TYPE]);
          }
        }

        // We are using the "Render Views filters as select list" field option
        // for field_rcd_result. However this option renders all results for
        // that field regardless of the current viewed item.
        // So we filter out the select options here.
        if (isset($form['field_rcd_result_target_id'])) {

          // Load results for this diagram.
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
            ->entityCondition('bundle', C4D_RCD_BUNDLE_RESULT)
            ->fieldCondition('field_rcd_diagram', 'target_id', $diagram_id)
            ->fieldOrderBy('field_rcd_svg_element', 'contatore_z');
          if (isset($form_state['view']->exposed_input['field_rcd_priority_area_target_id'])
              && is_numeric($form_state['view']->exposed_input['field_rcd_priority_area_target_id'])) {
            $query->fieldCondition('field_rcd_priority_area', 'target_id', $form_state['view']->exposed_input['field_rcd_priority_area_target_id']);
          }
          $query_result = $query->execute();

          if (isset($query_result[C4D_RCD_ENTITY_TYPE])) {
            // We need to keep the 'All' option if it exists.
            $all = NULL;
            if (isset($form['field_rcd_result_target_id']['#options']['All'])) {
              $all = $form['field_rcd_result_target_id']['#options']['All'];
            }

            // Filter out options.
            $form['field_rcd_result_target_id']['#options'] = array_intersect_key($form['field_rcd_result_target_id']['#options']['Result'], $query_result[C4D_RCD_ENTITY_TYPE]);

            if (!empty($all)) {
              $form['field_rcd_result_target_id']['#options'] = ['All' => $all] + $form['field_rcd_result_target_id']['#options'];
            }
          }
        }

        // We are using the "Render Views filters as select list" field option
        // for field_rcd_result. However this option renders all results for
        // that field regardless of the current viewed item.
        // So we filter out the select options here.
        if (isset($form['field_rcd_result_target_id_1'])) {

          // Load impacts for this diagram.
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
            ->entityCondition('bundle', C4D_RCD_BUNDLE_IMPACT)
            ->fieldCondition('field_rcd_diagram', 'target_id', $diagram_id)
            ->fieldOrderBy('field_rcd_svg_element', 'contatore_z');
          $query_result = $query->execute();

          if (isset($query_result[C4D_RCD_ENTITY_TYPE])) {
            // We need to keep the 'All' option if it exists.
            $all = NULL;
            if (isset($form['field_rcd_result_target_id_1']['#options']['All'])) {
              $all = $form['field_rcd_result_target_id_1']['#options']['All'];
            }

            // Filter out options.
            $form['field_rcd_result_target_id_1']['#options'] = array_intersect_key($form['field_rcd_result_target_id_1']['#options']['Impact'], $query_result[C4D_RCD_ENTITY_TYPE]);

            if (!empty($all)) {
              $form['field_rcd_result_target_id_1']['#options'] = ['All' => $all] + $form['field_rcd_result_target_id_1']['#options'];
            }
          }
        }
        break;

    }

    // Fix an issue with reset button in exposed filters and AJAXified view.
    // @see https://www.drupal.org/project/views/issues/720054
    // Solution based on https://julian.pustkuchen.com/node/659

    // Get the submission button ID and add an onclick event to submit the form.
    $submit_btn_id = $form['submit']['#id'];
    $form['reset']['#attributes'] = [
      'onclick' => "javascript:jQuery(this.form).clearForm();jQuery(this.form).find('#$submit_btn_id').trigger('click');return false;",
    ];
  }
}
