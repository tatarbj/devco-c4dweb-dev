<?php

/**
 * @file
 * C4M Admin Groups views functionality.
 */

/**
 * Implements hook_views_data().
 */
function c4m_admin_groups_views_data() {
  $data['node']['group_admin'] = array(
    'title' => t('Group admin'),
    'help' => t('The admin of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_admin',
      'group' => 'Content',
    ),
  );

  $data['node']['group_purl'] = array(
    'title' => t('PURL path'),
    'help' => t('The purl path of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_purl',
      'group' => 'Content',
    ),
  );

  $data['node']['group_approve'] = array(
    'title' => t('Group approve link'),
    'help' => t('Approval link for a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_approve_link',
      'group' => 'Content',
    ),
  );

  $data['node']['group_domains'] = array(
    'title' => t('Group domains'),
    'help' => t('Domains of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_domains',
      'group' => 'Content',
    ),
  );

  $data['node']['group_metrics'] = array(
    'title' => t('Group metrics'),
    'help' => t('Metrics about a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_metrics',
      'group' => 'Content',
    ),
  );

  $data['node']['group_moderators'] = array(
    'title' => t('Group moderators'),
    'help' => t('The moderators of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_moderators',
      'group' => 'Content',
    ),
  );

  $data['node']['group_organisations'] = array(
    'title' => t('Group organisations'),
    'help' => t('Organisations of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_organisations',
      'group' => 'Content',
    ),
  );

  $data['node']['group_reject'] = array(
    'title' => t('Group reject link'),
    'help' => t('Reject link for a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_reject_link',
      'group' => 'Content',
    ),
  );

  $data['node']['group_visibility'] = array(
    'title' => t('Group visibility'),
    'help' => t('Visibility information of a group.'),
    'field' => array(
      'handler' => 'c4m_admin_groups_views_handler_field_group_visibility',
      'group' => 'Content',
    ),
  );

  return $data;
}
