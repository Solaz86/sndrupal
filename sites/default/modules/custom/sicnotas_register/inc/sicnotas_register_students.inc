<?php

/**
 * Implements hook_form().
 */
function sicnotas_register_students_form($form, &$form_state) {

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
  );

  $form['lastname'] = array(
    '#type' => 'textfield',
    '#title' => t('Lastname'),
  );

  $form['document'] = array(
    '#type' => 'select',
    '#title' => t('Document type'),
    '#options' => array('ti' => 'T.I.', 'cc' => 'CC')
  );

  $form['identification'] = array(
    '#type' => 'textfield',
    '#title' => t('Identification number'),
  );

  $form['student_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Student Email'),
  );

  $form['attendant_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Attendant name'),
  );

  $form['attendant_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Attendant phone number'),
  );

  $form['attendant_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Identification number'),
  );
  
  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
  );

  // $or = db_or();
  // $or->condition('name', 'teacher');
  // $or->condition('name', 'School administrator');

  // $roles = db_select('role', 'r')
  //           ->fields('r', array('rid', 'name')) 
  //           ->condition($or)
  //           ->execute()->fetchAllKeyed();

  // $form['rol'] = array(
  //   '#type' => 'radios',
  //   '#title' => t('User type'),
  //   '#options' => $roles,
  //   '#default_value' => 5
  // );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' =>t('Accept'),
    '#name' => 'accept'
  );


  return $form;
}