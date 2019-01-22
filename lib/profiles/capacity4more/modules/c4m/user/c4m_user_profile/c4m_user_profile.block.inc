<?php

/**
 * @file
 * Block definitions for the user profile.
 */

/**
 * Block definition for the top bar (user region).
 *
 * Shows user menu (dropdown).
 *
 * @return array
 *   The block definition.
 */
function _c4m_user_profile_block_user_menu() {
  $block = array();
  $block['subject'] = '';

  if (user_is_anonymous()) {
    return $block;
  }

  // We have a loggedin user.
  global $user;
  $user = user_load($user->uid);

  // User fullname + user picture.
  $full_name_picture = c4m_user_profile_render_user_profile(
    'c4m_user_profile_picture_fullname', $user);

  // User profile menu.
  $menu_list = array(
    'view_profile' => array(
      'title' => t('View Profile'),
      'url' => 'user',
      'options' => array(
        'purl' => array(
          'disabled' => TRUE,
        ),
      ),
    ),
    'edit_profile' => array(
      'title' => t('Edit Profile'),
      'url' => 'user/' . $user->uid . '/edit/',
      'options' => array(
        'purl' => array(
          'disabled' => TRUE,
        ),
      ),
    ),
    'user_content' => array(
      'title' => t('My content'),
      'url' => 'user/' . $user->uid . '/content/',
      'options' => array(
        'purl' => array(
          'disabled' => TRUE,
        ),
      ),
    ),
    'user_logout' => array(
      'title' => t('Log out'),
      'url' => 'user/logout',
      'options' => array(
        'absolute' => TRUE,
        'purl' => array(
          'disabled' => TRUE,
        ),
        'query' => array('destination' => request_path()),
      ),
    ),
  );

  $menu = array(
    '#theme' => 'c4m_user_profile_menu',
    '#menu_items' => $menu_list,
    '#attributes' => array(
      'class' => array('user-profile-menu', 'dropdown-menu'),
    ),
  );
  $menu = render($menu);

  $output = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => $full_name_picture . $menu,
    '#attributes' => array(
      'class' => array('userbar-userprofile', 'dropdown'),
    ),
  );

  $user_groups_top_bar = _c4m_user_profile_my_groups_top_bar();
  $user_projects_top_bar = _c4m_user_profile_my_projects_top_bar();

  $block['content'] = render($output) . $user_projects_top_bar . $user_groups_top_bar;
  return $block;
}

/**
 * Render the top bar menu for "my groups".
 */
function _c4m_user_profile_my_groups_top_bar() {
  global $user;

  module_load_include('inc', 'c4m_features_homepage', 'plugins/content_types/my_groups/my_groups');

  $max_groups_to_display = 3;
  $user_groups = array();

  foreach (c4m_features_homepage_get_user_groups_grouped_by_membership($user) as $group_list) {
    foreach ($group_list as $group) {
      // The max groups to display on the top bar is 3 by definition.
      if (count($user_groups) >= $max_groups_to_display) {
        break;
      }

      $node_view = node_view($group, 'block_list');
      $user_groups[] = render($node_view);
    }

    // The max groups to display on the top bar is 3 by definition.
    if (count($user_groups) >= $max_groups_to_display) {
      $user_groups[] = _c4m_user_profile_render_explore_all_my_groups_link();
      break;
    }
  }

  // The user is not yet a member of any group.
  if (!$user_groups) {
    return '';
  }

  $groups_top_bar = array(
    '#theme' => 'c4m_user_profile_groups_top_bar',
    '#link' => array(
      'url' => 'groups',
      'options' => array(
        'attributes' => array(
          'class' => array('fullname-picture-wrapper', 'dropdown-toggle'),
          'data-toggle' => array('dropdown'),
          'data-disabled' => TRUE,
        ),
        'query' => array(
          'filter' => 'groups',
        ),
        'html' => TRUE,
        'purl' => array(
          'disabled' => TRUE,
        ),
      ),
    ),
  );

  $menu = array(
    '#theme' => 'item_list',
    '#items' => $user_groups,
    '#attributes' => array(
      'class' => array('dropdown-menu', 'user-groups'),
    ),
  );
  $menu = render($menu);

  $output = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => render($groups_top_bar) . $menu,
    '#attributes' => array(
      'class' => array('right-menu-section', 'userbar-userprofile', 'dropdown'),
    ),
  );

  return render($output);
}

/**
 * Render the top bar menu for "my projects".
 */
function _c4m_user_profile_my_projects_top_bar() {
  $user_projects = array();

  foreach (c4m_user_og_get_groups(NULL, 'project') as $project) {
    if ($project->c4m_is_template[LANGUAGE_NONE][0]['value'] != '1' && node_access('view', $project)) {
      $node_view = node_view($project, 'block_list');
      $user_projects[] = render($node_view);

      // The max projects to display on the top bar is 3 by definition.
      if (count($user_projects) == 3) {
        $user_projects[] = _c4m_user_profile_render_explore_all_my_projects_link();
        break;
      }
    }
  }

  // The user is not yet a member of any project.
  if (!$user_projects) {
    return '';
  }

  $projects_top_bar = array(
    '#theme' => 'c4m_user_profile_projects_top_bar',
    '#link' => array(
      'url' => 'projects',
      'options' => array(
        'attributes' => array(
          'class' => array('fullname-picture-wrapper', 'dropdown-toggle'),
          'data-toggle' => array('dropdown'),
          'data-disabled' => TRUE,
        ),
        'query' => array(
          'filter' => 'projects',
        ),
        'html' => TRUE,
        'purl' => array(
          'disabled' => TRUE,
        ),
      ),
    ),
  );

  $menu = array(
    '#theme' => 'item_list',
    '#items' => $user_projects,
    '#attributes' => array(
      'class' => array('dropdown-menu', 'user-projects'),
    ),
  );
  $menu = render($menu);

  $output = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#value' => render($projects_top_bar) . $menu,
    '#attributes' => array(
      'class' => array('right-menu-section', 'userbar-userprofile', 'dropdown'),
    ),
  );

  return render($output);
}

/**
 * Render a link to the groups overview page, filtered to the user groups.
 *
 * @return string
 *   A link to the groups page (filtered).
 */
function _c4m_user_profile_render_explore_all_my_groups_link() {
  $text = t('Explore all my groups');
  $text .= '<i class="fa fa-angle-right" aria-hidden="true"></i>';

  $options = array(
    'html' => TRUE,
    'purl' => array(
      'disabled' => TRUE,
    ),
    'query' => array(
      'filter' => 'groups',
    ),
  );

  $link = l($text, '/groups', $options);

  $tag['element'] = array(
    '#tag' => 'div',
    '#value' => $link,
    '#attributes' => array(
      'class' => 'c4m-explore-all-my-groups-link',
    ),
  );

  return theme_html_tag($tag);
}

/**
 * Render a link to the projects overview page, filtered to the user groups.
 *
 * @return string
 *   A link to the projects page (filtered).
 */
function _c4m_user_profile_render_explore_all_my_projects_link() {
  $text = t('Explore all my projects');
  $text .= '<i class="fa fa-angle-right" aria-hidden="true"></i>';

  $options = array(
    'html' => TRUE,
    'purl' => array(
      'disabled' => TRUE,
    ),
    'query' => array(
      'filter' => 'projects',
    ),
  );

  $link = l($text, '/projects', $options);

  $tag['element'] = array(
    '#tag' => 'div',
    '#value' => $link,
    '#attributes' => array(
      'class' => 'c4m-explore-all-my-projects-link',
    ),
  );

  return theme_html_tag($tag);
}

/**
 * Block definition for the top bar (user region).
 *
 * Displays number of messages/notifications/...
 *
 * @return array
 *   The block definition.
 */
function _c4m_user_profile_block_user_notifications() {
  $block = array();
  $block['subject'] = '';

  if (user_is_anonymous()) {
    return NULL;
  }

  // @TODO: submenu, theming function...
  $block['content'] = t('# of messages/notifications/...');

  return $block;
}

/**
 * Block definition for the user_is_invalid_email block.
 *
 * @return array
 *   The block definition.
 */
function _c4m_user_profile_block_user_is_invalid_email() {
  global $user;

  $block = array();
  $block['subject'] = '';

  $block['content'] = t('<div class="well alert"><h3>Your email is no longer valid</h3><p>It seems that the email you used to register on !site !mail is no longer valid.</p><p>Please update your profile accordingly.</p><p>Please !contact_us if you think this is a mistake.</div>', array(
    '!site' => variable_get('site_name'),
    '!mail' => l($user->mail, 'mailto:' . $user->mail, array('absolute' => TRUE)),
    '!contact_us' => l(t('contact us'), 'mailto:capacity4dev@ec.europa.eu', array('absolute' => TRUE)),
  ));

  return $block;
}

/**
 * Helper function to render user profile.
 *
 * @param string $theme_function
 *    Name of the theme function to be used.
 * @param object $user
 *    User object.
 *
 * @return string
 *    The rendered output.
 */
function c4m_user_profile_render_user_profile($theme_function, $user) {
  switch ($theme_function) {
    case 'c4m_user_profile_picture_fullname':
      $user_profile = array(
        '#theme' => 'c4m_user_profile_picture_fullname',
        '#user' => $user,
        '#link' => array(
          'url' => 'user/' . $user->uid,
          'options' => array(
            'attributes' => array(
              'class' => array('fullname-picture-wrapper', 'dropdown-toggle'),
              'data-toggle' => array('dropdown'),
              'data-disabled' => TRUE,
            ),
            'html' => TRUE,
            'purl' => array(
              'disabled' => TRUE,
            ),
          ),
        ),
      );
      break;
  }

  return render($user_profile);
}

/**
 * Block definition for the user_confirm_email block.
 *
 * @return array
 *   The block definition.
 */
function _c4m_user_profile_block_user_confirm_email() {
  $block = array();
  $block['subject'] = '';

  $block['content'] = t('<div class="well bg-warning"><h3>Your email needs to be confirmed</h3><p>Please check your inbox to confirm your new email address.</p></div>');

  return $block;
}

/**
 * Block definition for the user_my_profile_groups block.
 *
 * @return array
 *   The rendered "my groups" block.
 */
function _c4m_user_profile_block_user_my_profile_groups() {
  module_load_include('inc', 'c4m_features_homepage', 'plugins/content_types/my_groups/my_groups');

  $block = array();
  $block['subject'] = '';
  $block['content'] = '';

  // Gets the user of the profile being viewed.
  $account = menu_get_object('user');

  // Prevent the block to be rendered if the block is added by mistake in a non
  // user profile page.
  if (is_null($account)) {
    return $block;
  }

  $groups = c4m_features_homepage_get_user_groups_grouped_by_membership($account);

  // Prevent the block to be rendered if the user has no groups.
  if (empty($groups)) {
    return $block;
  }

  $rendered_groups = '';
  // Render node views for each group.
  foreach ($groups as $type => $group_list) {
    $title = c4m_features_homepage_get_group_type_title($type);
    $rendered_groups .= '<h4>' . $title . '</h4>';

    foreach ($group_list as $group) {
      $node_view = node_view($group, 'block_list');
      $rendered_groups .= drupal_render($node_view);
    }
  }

  $variables = array(
    'groups' => $rendered_groups,
  );

  $block['content'] = !empty($rendered_groups) ? theme('c4m_user_profile_my_profile_groups', $variables) : FALSE;

  return $block;
}

/**
 * Block definition for the user_my_profile_projects block.
 *
 * @return array
 *   The rendered "my projects" block.
 */
function _c4m_user_profile_block_user_my_profile_projects() {
  module_load_include('inc', 'c4m_features_homepage', 'plugins/content_types/my_projects/my_projects');

  $block = array();
  $block['subject'] = '';
  $block['content'] = '';

  // Gets the user of the profile being viewed.
  $account = menu_get_object('user');

  // Prevent the block to be rendered if the block is added by mistake in a non
  // user profile page.
  if (is_null($account)) {
    return $block;
  }

  $projects = c4m_features_homepage_get_user_projects_grouped_by_membership($account);

  // Prevent the block to be rendered if the user has no projects.
  if (empty($projects)) {
    return $block;
  }

  $rendered_projects = '';
  // Render node views for each project.
  foreach ($projects as $type => $project_list) {
    $title = c4m_features_homepage_get_project_type_title($type);
    $rendered_projects .= '<h4>' . $title . '</h4>';

    foreach ($project_list as $project) {
      $node_view = node_view($project, 'block_list');
      $rendered_projects .= drupal_render($node_view);
    }
  }

  $variables = array(
    'projects' => $rendered_projects,
  );

  $block['content'] = !empty($rendered_projects) ? theme('c4m_user_profile_my_profile_projects', $variables) : FALSE;

  return $block;
}