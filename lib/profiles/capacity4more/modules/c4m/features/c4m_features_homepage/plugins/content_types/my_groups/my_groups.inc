<?php

/**
 * @file
 * My groups panels block.
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('My groups'),
  'description' => t("Renders authenticated user's groups."),
  'category' => t('C4M'),
  'hook theme' => 'c4m_features_homepage_my_groups_content_type_theme',
);

/**
 * Render callback.
 */
function c4m_features_homepage_my_groups_content_type_render($subtype, $conf, $args, $context) {
  global $user;
  $groups = c4m_features_homepage_get_user_groups_grouped_by_membership($user, TRUE);

  $block = new stdClass();
  $block->module = 'c4m_features_homepage';
  $block->title = '';
  $block->content = '';
  if (empty($groups)) {
    return $block;
  }

  $rendered_groups = '';
  $count = 0;
  $max_groups_to_display = 5;
  $total_groups = 0;

  // Render node views for each group.
  foreach ($groups as $type => $group_list) {
    $total_groups += count($group_list);

    if ($count >= $max_groups_to_display) {
      continue;
    }

    $title = c4m_features_homepage_get_group_type_title($type);
    $rendered_groups .= '<h4>' . $title . '</h4>';

    foreach ($group_list as $group) {
      if ($count >= $max_groups_to_display) {
        continue;
      }

      $node_view = node_view($group, 'block_list');
      $rendered_groups .= drupal_render($node_view);

      $count++;
    }
  }

  // When total groups are greater than the max groups to display then we
  // should display the "show more" button.
  $display_see_more = $total_groups > $max_groups_to_display;

  $link_options = array(
    'query' => array(
      'filter' => 'groups',
    )
  );
  $variables = array(
    'groups' => $rendered_groups,
    'link' => url('groups', $link_options),
    'display_see_more' => $display_see_more,
  );
  $output = '';
  if ($rendered_groups) {
    $output .= theme('c4m_features_homepage_my_groups', $variables);
    $renderable_array = c4m_features_homepage_node_creation_button_cta('group');
    $output .= render($renderable_array);
  }

  $block->content = $output;
  return $block;
}

/**
 * Returns the title for the type of membership of a group.
 *
 * @param string $type
 *   The group membership type.
 *
 * @return string
 *   The translated title for the membership type.
 */
function c4m_features_homepage_get_group_type_title($type) {
  $titles = array(
    'owner' => t('Owner of the following Group(s)'),
    'administrator' => t('Administrator of the following Group(s)'),
    'member' => t("Member of the following Group(s)"),
    'pending' => t('Membership requested in the following Group(s)'),
  );

  return $titles[$type];
}

/**
 * Returns the list of groups of an user.
 *
 * @param object $account
 *   User object. Defaults global user if NULL.
 * @param bool $allow_pending
 *   Optional include requested groups (pending status).
 *
 * @returns mixed|null
 *   List of groups or NULL if the user has no groups.
 */
function c4m_features_homepage_get_user_groups($account = NULL, $allow_pending = FALSE) {
  $groups = c4m_user_og_get_groups($account, 'group', NODE_PUBLISHED, TRUE, $allow_pending);

  // Removes groups where the logged in user has no access.
  $groups = array_filter($groups, 'c4m_features_homepage_node_access_view_filter');

  usort($groups, '_c4m_og_sort_by_status');

  return $groups;
}

/**
 * Callback for array_filter that checks if the user has access to the node.
 *
 * @param object $node
 *   Node object.
 *
 * @returns boolean
 *   Indicates if the user has access or not.
 */
function c4m_features_homepage_node_access_view_filter($node) {
  return node_access('view', $node);
}

/**
 * Returns the list of groups of an user, grouped by the membership type.
 *
 * @param object $account
 *   User object. Defaults global user if NULL.
 * @param bool $allow_pending
 *   Optional include requested groups (pending status).
 *
 * @returns mixed|null
 *   List of groups or NULL if the user has no groups.
 */
function c4m_features_homepage_get_user_groups_grouped_by_membership($account = NULL, $allow_pending = FALSE) {
  $groups = c4m_features_homepage_get_user_groups($account, $allow_pending);

  $grouped_groups = array(
    'owner' => array(),
    'administrator' => array(),
    'member' => array(),
  );
  foreach ($groups as $group) {
    $membership = c4m_user_og_get_role_in_group($account, $group);
    $grouped_groups[$membership][$group->nid] = $group;
  }

  // Remove empty list of groups so the block is not rendered if there are no
  // groups.
  foreach ($grouped_groups as $type => $groups) {
    if (empty($groups)) {
      unset($grouped_groups[$type]);
    }
  }

  return $grouped_groups;
}

/**
 * Edit form.
 */
function c4m_features_homepage_my_groups_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function c4m_features_homepage_my_groups_content_type_theme(&$theme, $plugin) {
  $theme['c4m_features_homepage_my_groups'] = array(
    'variables' => array(
      'groups' => NULL,
      'link' => NULL,
      'display_see_more' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'my-groups',
  );
}
