<?php
/**
 * Implements hook_form().
 */
function sicnotas_register_staff_form($form, &$form_state) {

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
    '#options' => array('cc' => 'CC', 'ce' => 'CE')
  );

  $form['identification'] = array(
    '#type' => 'textfield',
    '#title' => t('Identification number'),
  );

  $form['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
  );

  $form['phone_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone number'),
  );

  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
  );

  $or = db_or();
  $or->condition('name', 'teacher');
  $or->condition('name', 'School administrator');

  $roles = db_select('role', 'r')
            ->fields('r', array('rid', 'name')) 
            ->condition($or)
            ->execute()->fetchAllKeyed();

  $form['rol'] = array(
    '#type' => 'radios',
    '#title' => t('User type'),
    '#options' => $roles,
    '#default_value' => 5
  );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' =>t('Accept'),
    '#name' => 'accept'
  );

  return $form;
}

/**
 * Implements hook_validate().
 */
function sicnotas_register_staff_form_validate($form, &$form_state) {
  $id_number = $form_state['values']['identification'];
  $query = db_select('users', 'u');
  $query->join('field_data_field_numero_de_identificacion', 'fdni', 'fdni.entity_id = u.uid');
  $id_exist = $query
              ->fields('u', array('uid'))
              ->fields('fdni', array('field_numero_de_identificacion_value', 'entity_id'))
              ->condition('fdni.field_numero_de_identificacion_value', $id_number)
              ->execute()->fetchAll();
  if (!empty($id_exist)) {
    form_set_error('identification', t('this Identification number already exist'));
  }
  if (empty($form_state['values']['name'])) {
    form_set_error('name', t('Field Name required'));
  }
  if (empty($form_state['values']['lastname'])) {
    form_set_error('lastname', t('Field Lastname required'));
  }
  if (empty($id_number)) {
    form_set_error('identification', t('Field Idetificacion required'));
  }
  if (empty($form_state['values']['address'])) {
    form_set_error('address', t('Field Address required'));
  }
  if (!is_numeric($form_state['values']['phone_number'])) {
    form_set_error('phone_number', t('This field must be numeric'));
  }
  if (!valid_email_address($form_state['values']['mail'])) {
    form_set_error('mail', t('Invalid email'));
  }
}


/**
 * Implementation of hook_bean_form_submit().
 */
function sicnotas_register_staff_form_submit($form, $form_state) {
  $account = new stdClass();
  $account->is_new = TRUE;
// defino el registro unico name concatenando con el numero de id
  $name_id = $form_state['values']['name'] . $form_state['values']['identification'];
  $new_user = array(
      'name' => $name_id,
      'mail' => $form_state['values']['mail'],
      'init' => $form_state['values']['mail'],
      'pass' => $form_state['values']['identification'],
      'status' => 1,
      'access' => REQUEST_TIME,
    );
  user_save($account, $new_user);
  // Asignacion del rol y campos custom
  $user = user_load($account->uid);
  $user->field_nombre[LANGUAGE_NONE][0]['value'] = $form_state['values']['name'];
  $user->field_apellido[LANGUAGE_NONE][0]['value'] = $form_state['values']['lastname'];
  $user->field_direccion[LANGUAGE_NONE][0]['value'] = $form_state['values']['address'];
  $user->field_telefono[LANGUAGE_NONE][0]['value'] = $form_state['values']['phone_number'];
  $user->field_tipo_de_documento[LANGUAGE_NONE][0]['value'] = $form_state['values']['document'];
  $user->field_numero_de_identificacion[LANGUAGE_NONE][0]['value'] = $form_state['values']['identification'];
  user_multiple_role_edit(array($user->uid), 'add_role', $form_state['values']['rol']);
  user_save($user);
}

