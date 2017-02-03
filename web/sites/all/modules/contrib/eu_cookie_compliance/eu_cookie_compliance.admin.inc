<?php
/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Provides form for cookie control popup.
 */
function eu_cookie_compliance_admin_form($form, $form_state) {
  global $language;

  $form = array();

  $form_language = $language;
  $ln = $form_language->language;

  if (isset($form_state['build_info']['args'][0]) && $ln = $form_state['build_info']['args'][0]) {
    $languages = language_list();
    $form_language = (!empty($languages[$ln]) ? $languages[$ln] : $form_language);
  }

  $form['#language'] = $form_language;

  $popup_settings = eu_cookie_compliance_get_settings($ln);

  $default_filter_format = filter_default_format();
  if ($default_filter_format == 'filtered_html') {
    $default_filter_format = 'full_html';
  }

  $form['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  if (module_exists('locale')) {
    $form['eu_cookie_compliance_' . $ln]['#title'] = t('You are editing settings for the %language language.', array('%language' => $form_language->name));
  }

  $form['eu_cookie_compliance_' . $ln]['popup_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable popup'),
    '#default_value' => isset($popup_settings['popup_enabled']) ? $popup_settings['popup_enabled'] : 0,
  );

  $form['popup_message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Popup Message'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['popup_message']['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form['popup_message']['eu_cookie_compliance_' . $ln]['popup_clicking_confirmation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Consent by clicking'),
    '#description' => t('By default by clicking any link on the website the visitor accepts the cookie policy. Uncheck this box if you do not require this functionality. You may want to edit the pop-up message below accordingly.'),
    '#default_value' => isset($popup_settings['popup_clicking_confirmation']) ? $popup_settings['popup_clicking_confirmation'] : 1,
  );

  $form['popup_message']['eu_cookie_compliance_' . $ln]['popup_info'] = array(
    '#type' => 'text_format',
    '#title' => t('Popup message - requests consent'),
    '#default_value' => isset($popup_settings['popup_info']['value']) ? $popup_settings['popup_info']['value'] : '',
    '#required' => TRUE,
    '#format' => isset($popup_settings['popup_info']['format']) ? $popup_settings['popup_info']['format'] : $default_filter_format,
  );

  $form['popup_message']['eu_cookie_compliance_' . $ln]['popup_agree_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Agree button label'),
    '#default_value' => isset($popup_settings['popup_agree_button_message']) ? $popup_settings['popup_agree_button_message'] : t('OK, I agree'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['popup_message']['eu_cookie_compliance_' . $ln]['popup_disagree_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Disagree button label'),
    '#default_value' => isset($popup_settings['popup_disagree_button_message']) ? $popup_settings['popup_disagree_button_message'] : t('No, give me more info'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['thank_you'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Thank You Message'),
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln]['popup_agreed_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable thank you message'),
    '#default_value' => isset($popup_settings['popup_agreed_enabled']) ? $popup_settings['popup_agreed_enabled'] : 1,
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln]['popup_hide_agreed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clicking hides “Thank you” message'),
    '#default_value' => isset($popup_settings['popup_hide_agreed']) ? $popup_settings['popup_hide_agreed'] : 0,
    '#description' => t('Clicking a link hides the thank you message automatically.'),
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln]['popup_agreed'] = array(
    '#type' => 'text_format',
    '#title' => t('Popup message - thank you for giving consent'),
    '#default_value' => isset($popup_settings['popup_agreed']['value']) ? $popup_settings['popup_agreed']['value'] : '',
    '#required' => TRUE,
    '#format' => isset($popup_settings['popup_agreed']['format']) ? $popup_settings['popup_agreed']['format'] : $default_filter_format,
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln]['popup_find_more_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('More info button label'),
    '#default_value' => isset($popup_settings['popup_find_more_button_message']) ? $popup_settings['popup_find_more_button_message'] : t('More info'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['thank_you']['eu_cookie_compliance_' . $ln]['popup_hide_button_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Hide button label'),
    '#default_value' => isset($popup_settings['popup_hide_button_message']) ? $popup_settings['popup_hide_button_message'] : t('Hide'),
    '#size' => 30,
    '#required' => TRUE,
  );

  $form['privacy'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Privacy Policy'),
  );

  $form['privacy']['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form['privacy']['eu_cookie_compliance_' . $ln]['popup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Privacy policy link'),
    '#default_value' => isset($popup_settings['popup_link']) ? $popup_settings['popup_link'] : '',
    '#size' => 60,
    '#maxlength' => 220,
    '#required' => TRUE,
    '#description' => t('Enter link to your privacy policy or other page that will explain cookies to your users. For external links prepend http://'),
  );

  $form['privacy']['eu_cookie_compliance_' . $ln]['popup_link_new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open privacy policy link in a new window'),
    '#default_value' => isset($popup_settings['popup_link_new_window']) ? $popup_settings['popup_link_new_window'] : 1,
  );

  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Appearance'),
  );

  $form['appearance']['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form_color_picker_type = 'textfield';

  if (module_exists('jquery_colorpicker')) {
    $form_color_picker_type = 'jquery_colorpicker';
  }

  $form['appearance']['eu_cookie_compliance_' . $ln]['popup_text_hex'] = array(
    '#type' => $form_color_picker_type,
    '#title' => t('Text Color'),
    '#default_value' => isset($popup_settings['popup_text_hex']) ? check_plain($popup_settings['popup_text_hex']) : 'ffffff',
    '#description' => t('Change the text color of the popup. Provide HEX value without the #'),
    '#element_validate' => array('eu_cookie_compliance_validate_hex'),
  );

  $form['appearance']['eu_cookie_compliance_' . $ln]['popup_bg_hex'] = array(
    '#type' => $form_color_picker_type,
    '#title' => t('Background Color'),
    // Garland colors => 0779BF.
    '#default_value' => isset($popup_settings['popup_bg_hex']) ? check_plain($popup_settings['popup_bg_hex']) : '0779BF',
    '#description' => t('Change the background color of the popup. Provide HEX value without the #'),
    '#element_validate' => array('eu_cookie_compliance_validate_hex'),
  );

  $form['appearance']['eu_cookie_compliance_' . $ln]['popup_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup height in pixels'),
    '#default_value' => isset($popup_settings['popup_height']) ? $popup_settings['popup_height'] : '',
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => FALSE,
    '#description' => t('Enter an integer value for a desired height in pixels or leave empty for automatically adjusted height. Do not set this value if you are using responsive theme.'),

  );

  $form['appearance']['eu_cookie_compliance_' . $ln]['popup_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup width in pixels or a percentage value'),
    '#default_value' => isset($popup_settings['popup_width']) ? $popup_settings['popup_width'] : '100%',
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
    '#description' => t('Set the width of the popup. This can be either an integer value or percentage of the screen width. For example: 200 or 50%'),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Advanced'),
  );

  $form['advanced']['eu_cookie_compliance_' . $ln] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );

  $form['advanced']['eu_cookie_compliance_' . $ln]['popup_position'] = array(
    '#type' => 'checkbox',
    '#title' => t('Place the pop-up at the top of the website'),
    '#default_value' => isset($popup_settings['popup_position']) ? $popup_settings['popup_position'] : 0,
    '#description' => t('By default the pop-up appears at the bottom of the website. Tick this box if you want it to appear at the top'),
  );

  if (module_exists('geoip') || module_exists('smart_ip') || function_exists('geoip_country_code_by_name')) {
    $form['advanced']['eu_cookie_compliance_' . $ln]['eu_only'] = array(
      '#type' => 'checkbox',
      '#title' => t('Only display popup in EU countries (using the <a href="http://drupal.org/project/geoip">geoip</a> module or the <a href="http://drupal.org/project/smart_ip">smart_ip</a> module or the <a href="http://www.php.net/manual/fr/function.geoip-country-code-by-name.php">geoip_country_code_by_name()</a> PHP function)'),
      '#default_value' => isset($popup_settings['eu_only']) ? $popup_settings['eu_only'] : 0,
    );
  }

  $form['advanced']['eu_cookie_compliance_' . $ln]['popup_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup time delay in miliseconds'),
    '#default_value' => isset($popup_settings['popup_delay']) ? $popup_settings['popup_delay'] : 1000,
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  $form['advanced']['eu_cookie_compliance_' . $ln]['popup_scrolling_confirmation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Consent by scrolling'),
    '#default_value' => isset($popup_settings['popup_scrolling_confirmation']) ? $popup_settings['popup_scrolling_confirmation'] : 0,
    '#description' => t("Scrolling makes the visitors to accept the cookie policy. In some contries, like Itay, it is permitted."),
  );

  $form['advanced']['eu_cookie_compliance_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#default_value' => variable_get('eu_cookie_compliance_domain', ''),
    '#description' => t('Sets the domain of the cookie to a specific url. Used when you need consistency across domains. This is language independent.'),
  );

  $form['advanced']['eu_cookie_compliance_cookie_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie lifetime'),
    '#default_value' => variable_get('eu_cookie_compliance_cookie_lifetime', 100),
    '#description' => t("How long does the system remember the user's choice, in days."),
  );

  // Adding option to add/remove popup on specified domains.
  $exclude_domains_option_active = array(
    0 => t('Add'),
    1 => t('Remove'),
  );
  $form['advanced']['eu_cookie_compliance_' . $ln]['domains_option'] = array(
    '#type' => 'radios',
    '#title' => t('Add/Remove popup on specified domains'),
    '#default_value' => isset($popup_settings['domains_option']) ? $popup_settings['domains_option'] : 1,
    '#options' => $exclude_domains_option_active,
    '#description' => t("Specify if you want to add or remove popup on the listed below domains."),
  );
  $form['advanced']['eu_cookie_compliance_' . $ln]['domains_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Domains list'),
    '#default_value' => isset($popup_settings['domains_list']) ? $popup_settings['domains_list'] : '',
    '#description' => t("Specify domains with protocol (e.g. http or https). Enter one domain per line."),
  );

  $form['advanced']['eu_cookie_compliance_' . $ln]['exclude_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude paths'),
    '#default_value' => isset($popup_settings['exclude_paths']) ? $popup_settings['exclude_paths'] : '',
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );

  $form['advanced']['eu_cookie_compliance_' . $ln]['exclude_admin_pages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude admin pages'),
    '#default_value' => isset($popup_settings['exclude_admin_pages']) ? $popup_settings['exclude_admin_pages'] : '',
  );

  return system_settings_form($form);
}

/**
 * Validates form for cookie control popup.
 */
function eu_cookie_compliance_admin_form_validate($form, &$form_state) {
  $form_language = $form['#language'];

  $ln = $form_language->language;
  if (!preg_match('/^[1-9][0-9]{0,4}$/', $form_state['values']['eu_cookie_compliance_' . $ln]['popup_height']) && !empty($form_state['values']['eu_cookie_compliance_' . $ln]['popup_height'])) {
    form_set_error('eu_cookie_compliance_' . $ln . '][popup_height', t('Height must be an integer value .'));
  }
  if ((!preg_match('/^[1-9][0-9]{0,4}$/', $form_state['values']['eu_cookie_compliance_' . $ln]['popup_delay'])) && ($form_state['values']['eu_cookie_compliance_' . $ln]['popup_delay'] != "0")) {
    form_set_error('eu_cookie_compliance_' . $ln . '][popup_delay', t('Delay must be an integer value.'));
  }
  if (!preg_match('/^[1-9][0-9]{0,4}\%?$/', $form_state['values']['eu_cookie_compliance_' . $ln]['popup_width'])) {
    form_set_error('eu_cookie_compliance_' . $ln . '][popup_width', t('Width must be an integer or a percentage value.'));
  }
  $popup_link = $form_state['values']['eu_cookie_compliance_' . $ln]['popup_link'];
  // If the link contains a fragment then check if it validates then rewrite
  // link with full url.
  if ((strpos($popup_link, '#') !== FALSE) && (strpos($popup_link, 'http') === FALSE)) {
    $fragment = explode('#', $popup_link);
    $popup_link = url($fragment[0], array('fragment' => $fragment[1], 'absolute' => TRUE));
    form_set_error('eu_cookie_compliance_' . $ln . '][popup_link', t('Looks like your privacy policy link contains fragment #, you should make this an absolute url eg @link', array('@link' => $popup_link)));
  }

  cache_clear_all('eu_cookie_compliance_client_settings:' . $ln, 'cache', TRUE);
}

/**
 * Validate field for a HEX value if a value is set.
 */
function eu_cookie_compliance_validate_hex($element, &$form_state) {
  if (!empty($element['#value']) && !preg_match('/^[0-9a-fA-F]{3,6}$/', $element['#value'])) {
    form_error($element, t('%name must be a HEX value (without leading #) or empty.', array('%name' => $element['#title'])));
  }
}
