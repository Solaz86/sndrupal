<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_degrees_form($form, &$form_state) {
  $form['name'] = array(
  '#type' => 'textfield',
  '#title' => t('Create degrees'),
  );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'accept'
  );

  $form['confirmation_modal'] = modal_confirm_delete($form_state);

  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => array('Degrees'),
    '#options' => get_degrees_table(),
    '#empty' => t('No campground to claim'),
    '#attributes' => array(
      'class' => array('table')
    )
  );

  $form['delete_selected'] = array(
    '#type' => 'submit',
    '#value' => t('Delete selected'),
    '#name' => 'show_confirm_delete',
    '#ajax' => array(
      'callback' => 'delete_callback'
    )
  );
  return $form;
}


/**
 * Implements hook_validate().
 */
function sicnotas_management_degrees_form_validate($form, &$form_state) {
  $filter = array_filter($form_state['values']['table']);
  $degree = $form_state['values']['name'];
  if ($form_state['triggering_element']['#name'] == 'accept') {
    if (empty($degree)) {
      form_set_error('name', t('This field is required'));
    }
  }
  if ($form_state['triggering_element']['#name'] == 'confirm_delete'){
    $query = db_select('sicnotas_management_courses', 'smc')
                ->fields('smc', array('degree_id'))
                ->condition('degree_id', $filter)
                ->countQuery()
                ->execute()->fetchField();
    if ($query) {
      form_set_error('name', t('Dont´t delete this degree, it is using it in Couse registration form'));
    }
  }
}

/**
 * Implements hook_form_submit().
 */
function sicnotas_management_degrees_form_submit($form, &$form_state) {
  $table_name = str_replace('_form', '', $form_state['values']['form_id']);
  $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
  $form_state['storage']['delete'] = FALSE;
  $filter = array_filter($form_state['values']['table']);
  switch ($form_state['triggering_element']['#name']) {
    case 'accept':
      $degree_name = $form_state['values']['name'];
      $record = array(
        'name' => $degree_name,
      );
      db_insert($table_name)
          ->fields($record)
          ->execute();
      drupal_set_message(t("The $subject_message $degree_name is successfully created"));
      break;

    case 'show_confirm_delete':
      if (!empty($filter)) {
        return  $form_state['storage']['delete'] = TRUE;
      }
      break;
    case 'confirm_delete':
      $subject_message = ucfirst($subject_message);
      if (!empty($filter)) {
        db_delete($table_name)
          ->condition('id', $filter, 'IN')
          ->execute();
        return drupal_set_message(t("$subject_message successfully deleted"));
      }
      break;
  }
}

function delete_callback($form, &$form_state){
  if (!empty($form_state['storage']['delete'])) {
    $commands = array();
    $commands[] = ajax_command_invoke('#myModal', 'modal', array('show'));
    return array(
      '#type' => 'ajax',
      '#commands' => $commands
    );
  }
}