<?php
/**
 * @file
 * moodle_sso.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function moodle_sso_user_default_roles() {
  $roles = array();

  // Exported role: service-authentication.
  $roles['service-authentication'] = array(
    'name' => 'service-authentication',
    'weight' => 3,
  );

  return $roles;
}
