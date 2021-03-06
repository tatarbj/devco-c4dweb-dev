<?php

/**
 * @file
 * Views plugins.
 */

/**
 * Implements hook_views_plugins().
 *
 * Returns the topics (interests) of the current user.
 */
function c4m_message_views_plugins() {
  $plugins = array(
    'module' => 'c4m_message',
    'argument default' => array(
      'c4m_message_user_interests' => array(
        'title' => t('C4M message user interests'),
        'handler' => 'c4m_message_user_interests',
        'path' => drupal_get_path('module', 'c4m_message') . '/includes',
        'theme path' => drupal_get_path('module', 'views') . '/theme',
        'theme file' => 'theme.inc',
        // So that the parent class is included.
        'parent' => 'fixed',
      ),
    ),
  );

  return $plugins;
}
