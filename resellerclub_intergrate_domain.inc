<?php

function form_resellerclub_intergrate_domain_availability($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Checks the availability of the specified domain name(s).'),
  );

  $form['domain-name'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain Name'),
    '#required' => TRUE,
  );

  // Adds a simple submit button that refreshes the form and clears its
  // contents. This is the default behavior for forms.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  
  if (isset($form_state['resellerclub_intergrate_result'])) {
    $form['footer_text'] = array(
      '#markup' => '<p>'. $form_state['resellerclub_intergrate_result'] .'</p>',
    );
  }  
  
  return $form;
}


function form_resellerclub_intergrate_domain_availability_submit($form, &$form_state) {
    $pos = strpos($form_state['values']['domain-name'], '.');
    $params = array(
        'domain-name'  => substr($form_state['values']['domain-name'], 0, $pos),
        'tlds'  => substr($form_state['values']['domain-name'], $pos + 1),
    );
    
    $message = resellerclub_intergrate_connect('domain', 'availability', $params);
       
    $form_state['resellerclub_intergrate_result'] = $message;
    $form_state['rebuild'] = TRUE;
}