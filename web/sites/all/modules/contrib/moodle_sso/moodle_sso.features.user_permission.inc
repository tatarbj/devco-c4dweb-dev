<?php
/**
 * @file
 * moodle_sso.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function moodle_sso_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'service-authentication' => 'service-authentication',
    ),
    'module' => 'user',
  );

  return $permissions;
}
