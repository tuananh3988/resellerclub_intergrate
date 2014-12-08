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
	$build = resellerclub_intergrate_build_url($type, $key, $params);
        $result = curl_get_contents($build['url'], $build['params']);

        if(isset($result['status']) && $result['status'] == 'ERROR') {
                $message = $result['message'];
        }
        else {
            foreach ($result['data'] as $k => $v) {
                $message = $k . ' ' . $v['status'];
            }
        }
        
        return $message;
}

function resellerclub_intergrate_build_url($type, $key, $params = array()) {
	global $endpoints;
	$url = variable_get('resellerclub_server') . $endpoints[$type][$key]['url'];
	
        $paramStr = 'auth-userid=' . variable_get('resellerclub_id') . '&api-key=' . variable_get('resellerclub_key');;
        foreach($endpoints[$type][$key]['params'] as $param) {
            if(!empty($params[$param])) {
                $paramStr .= '&' . $param . '=' . $params[$param];
            }
        }
        
	return array('url' => $url, 'params' => $paramStr);
}

function curl_get_contents($url, $params) {
    $ch = curl_init();
   
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $params);

    
    if(curl_errno($ch) > 0) {
        $result = array(
            'status' => 'ERROR',
            'message' => curl_error($ch),
        );
    }
    else {
        $data = json_decode(curl_exec($ch), TRUE);
        if(isset($data['status']) && $data['status'] == 'ERROR') {
            $result = $data;
        }
        else {
            $result = array(
                'status' => 'SUCCESS',
                'data' => $data,
            );
        }
        
    }
    
    curl_close($ch);
    
    return $result;
}