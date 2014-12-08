<?php

function form_resellerclub_intergrate_domain_availability($form, &$form_state) {
  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Checks the availability of the specified domain name(s).'),
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );

  // Adds a simple submit button that refreshes the form and clears its
  // contents. This is the default behavior for forms.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  return $form;
}


function form_resellerclub_intergrate_domain_availability_submit($form, &$form_state) {
	$a = resellerclub_intergrate_build_url('domain', 'availability');
	var_dump($a);die;
  drupal_set_message(t('The form has been submitted. name="@name"',
    array(
      '@name' => $form_state['values']['name'],
    )
  ));
}