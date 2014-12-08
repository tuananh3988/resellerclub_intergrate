<?php

function form_resellerclub_intergrate_config($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Reseller Club settings'),
  );

  $form['resellerclub_id'] = array(
    '#type' => 'textfield',
    '#title' => t('App id'),
	'#default_value' => variable_get('resellerclub_id', ''),
	'#required' => TRUE,
  );

  $form['resellerclub_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Api key'),
	'#default_value' => variable_get('resellerclub_key', ''),
	'#required' => TRUE,
  );
  
  $form['resellerclub_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server'),
	'#default_value' => variable_get('resellerclub_server', 'https://test.httpapi.com'),
	'#required' => TRUE,
  );
  
  return system_settings_form($form);
}

function resellerclub_intergrate_connect($type, $key, $params) {
	
	
}

function resellerclub_intergrate_build_url($type, $key, $params = array()) {
	global $endpoints;
	$url = variable_get('resellerclub_server') . $endpoints[$type][$key] . '?auth-userid=' . variable_get('resellerclub_id') .
		'&api-key=' . variable_get('resellerclub_id');
	
	return $url;
}
