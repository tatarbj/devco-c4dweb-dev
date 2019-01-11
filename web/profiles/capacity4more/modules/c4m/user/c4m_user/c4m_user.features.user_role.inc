<?php

/**
 * @file
 * c4m_user.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function c4m_user_user_default_roles() {
  $roles = array();

  // Exported role: SIG administrator.
  $roles['SIG administrator'] = array(
    'name' => 'SIG administrator',
    'weight' => 3,
  );

  return $roles;
}
